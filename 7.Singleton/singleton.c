#include "chocolate_boiler.h"
#include <stdio.h>

// 状态描述字符串
const char* getStateString(BoilerState state) {
    switch(state) {
        case EMPTY: return "空的";
        case FILLING: return "填充中";
        case BOILING: return "煮沸中";
        case READY: return "准备好（已煮沸）";
        default: return "未知状态";
    }
}

int main() {
    // 获取巧克力锅炉实例
    ChocolateBoiler* boiler1 = chocolateBoiler_getInstance();
    ChocolateBoiler* boiler2 = chocolateBoiler_getInstance();
    
    // 验证是否为同一个实例
    if (boiler1 == boiler2) {
        printf("两个实例是相同的，单例模式生效\n");
    } else {
        printf("错误：创建了多个实例\n");
    }
    
    // 测试锅炉操作
    printf("初始状态: %s\n", getStateString(chocolateBoiler_getState(boiler1)));
    
    chocolateBoiler_fill(boiler1);
    printf("填充后状态: %s\n", getStateString(chocolateBoiler_getState(boiler1)));
    
    chocolateBoiler_boil(boiler1);
    printf("煮沸后状态: %s\n", getStateString(chocolateBoiler_getState(boiler1)));
    
    chocolateBoiler_drain(boiler1);
    printf("排出后状态: %s\n", getStateString(chocolateBoiler_getState(boiler1)));
    
    return 0;
}
