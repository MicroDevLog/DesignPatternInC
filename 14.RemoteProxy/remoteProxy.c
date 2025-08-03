#include <stdio.h>
#include <string.h>
#include <stdlib.h> // 新增：包含atoi函数所需的头文件
#include <unistd.h> // 用于模拟网络延迟的sleep函数

// 糖果机状态枚举
typedef enum {
    SOLD_OUT,
    NO_QUARTER,
    HAS_QUARTER,
    SOLD
} State;

// 前向声明
typedef struct CandyMachine CandyMachine;
typedef struct CandyMachineProxy CandyMachineProxy;

// 糖果机接口定义（函数指针）
typedef struct {
    State (*getState)(void* machine);
    int (*getCount)(void* machine);
    const char* (*getLocation)(void* machine);
} CandyMachineInterface;

// 真实的糖果机（远程对象）
struct CandyMachine {
    CandyMachineInterface* vtable;
    int count;
    State state;
    char location[20];
};

// 代理对象（本地代理）
struct CandyMachineProxy {
    CandyMachineInterface* vtable;
    char location[20];
    // 代理需要知道远程对象的位置信息
};

// 全局变量 - 模拟不使用动态内存分配
CandyMachine realMachine;
CandyMachineProxy proxy;
char networkBuffer[100]; // 模拟网络缓冲区

// 真实糖果机方法实现
State realGetState(void* machine) {
    CandyMachine* cm = (CandyMachine*)machine;
    return cm->state;
}

int realGetCount(void* machine) {
    CandyMachine* cm = (CandyMachine*)machine;
    return cm->count;
}

const char* realGetLocation(void* machine) {
    CandyMachine* cm = (CandyMachine*)machine;
    return cm->location;
}

// 真实糖果机的接口表
CandyMachineInterface realMachineVtable = {
    realGetState,
    realGetCount,
    realGetLocation
};

// 模拟网络发送函数
void sendOverNetwork(const char* data) {
    printf("[网络] 发送: %s\n", data);
    strcpy(networkBuffer, data);
    sleep(1); // 模拟网络延迟
}

// 模拟网络接收函数
void receiveFromNetwork(char* buffer, int size) {
    strncpy(buffer, networkBuffer, size);
    printf("[网络] 接收: %s\n", buffer);
    sleep(1); // 模拟网络延迟
}

// 代理方法实现 - 这些方法会通过网络与远程对象通信
State proxyGetState(void* machine) {
    CandyMachineProxy* proxy = (CandyMachineProxy*)machine;
    
    // 发送请求到远程
    sendOverNetwork("REQUEST_STATE");
    
    // 接收响应
    char response[20];
    receiveFromNetwork(response, sizeof(response));
    
    // 转换响应为状态
    if (strcmp(response, "SOLD_OUT") == 0) return SOLD_OUT;
    if (strcmp(response, "NO_QUARTER") == 0) return NO_QUARTER;
    if (strcmp(response, "HAS_QUARTER") == 0) return HAS_QUARTER;
    if (strcmp(response, "SOLD") == 0) return SOLD;
    
    return SOLD_OUT;
}

int proxyGetCount(void* machine) {
    CandyMachineProxy* proxy = (CandyMachineProxy*)machine;
    
    // 发送请求到远程
    sendOverNetwork("REQUEST_COUNT");
    
    // 接收响应
    char response[20];
    receiveFromNetwork(response, sizeof(response));
    
    // 转换响应为数量
    return atoi(response);
}

const char* proxyGetLocation(void* machine) {
    CandyMachineProxy* proxy = (CandyMachineProxy*)machine;
    return proxy->location; // 位置信息本地存储，不需要网络请求
}

// 代理的接口表
CandyMachineInterface proxyVtable = {
    proxyGetState,
    proxyGetCount,
    proxyGetLocation
};

// 模拟远程对象处理网络请求
void handleRemoteRequest() {
    char request[20];
    strcpy(request, networkBuffer);
    
    if (strcmp(request, "REQUEST_STATE") == 0) {
        const char* stateStr;
        switch (realMachine.state) {
            case SOLD_OUT: stateStr = "SOLD_OUT"; break;
            case NO_QUARTER: stateStr = "NO_QUARTER"; break;
            case HAS_QUARTER: stateStr = "HAS_QUARTER"; break;
            case SOLD: stateStr = "SOLD"; break;
        }
        strcpy(networkBuffer, stateStr);
    }
    else if (strcmp(request, "REQUEST_COUNT") == 0) {
        sprintf(networkBuffer, "%d", realMachine.count);
    }
}

// 初始化函数
void initMachines(const char* location, int initialCount) {
    // 初始化真实糖果机
    realMachine.vtable = &realMachineVtable;
    realMachine.count = initialCount;
    realMachine.state = initialCount > 0 ? NO_QUARTER : SOLD_OUT;
    strncpy(realMachine.location, location, sizeof(realMachine.location)-1);
    
    // 初始化代理
    proxy.vtable = &proxyVtable;
    strncpy(proxy.location, location, sizeof(proxy.location)-1);
}

// 客户端代码 - 监视器
void monitorMachine(CandyMachineInterface* machine, void* instance) {
    printf("\n监控糖果机: %s\n", machine->getLocation(instance));
    printf("当前库存: %d\n", machine->getCount(instance));
    
    State state = machine->getState(instance);
    printf("当前状态: ");
    switch (state) {
        case SOLD_OUT: printf("已售罄\n"); break;
        case NO_QUARTER: printf("无硬币\n"); break;
        case HAS_QUARTER: printf("有硬币\n"); break;
        case SOLD: printf("售出中\n"); break;
    }
}

// 模拟远程糖果机操作
void simulateRemoteOperation() {
    // 模拟远程糖果机售出一颗糖果
    if (realMachine.count > 0) {
        realMachine.count--;
        realMachine.state = SOLD;
        printf("\n[远程糖果机] 售出一颗糖果\n");
        
        // 模拟状态转换
        sleep(1);
        realMachine.state = realMachine.count > 0 ? NO_QUARTER : SOLD_OUT;
    }
}

int main() {
    // 初始化糖果机和代理
    initMachines("中央车站", 10);
    
    // 客户端通过代理监控远程糖果机
    printf("=== 第一次监控 ===\n");
    monitorMachine(proxy.vtable, &proxy);
    handleRemoteRequest(); // 处理代理发出的请求
    
    // 模拟远程操作
    simulateRemoteOperation();
    
    // 再次监控
    printf("\n=== 第二次监控 ===\n");
    monitorMachine(proxy.vtable, &proxy);
    handleRemoteRequest(); // 处理代理发出的请求
    
    return 0;
}
