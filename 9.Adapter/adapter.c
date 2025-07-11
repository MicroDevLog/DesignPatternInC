#include <stdio.h>

// 定义鸭子接口
typedef struct {
    void (*quack)(void);
    void (*fly)(void);
} Duck;

// 定义火鸡接口
typedef struct {
    void (*gobble)(void);
    void (*fly)(void);
} Turkey;

// 具体鸭子实现
void mallard_quack(void) {
    printf("Quack\n");
}

void mallard_fly(void) {
    printf("I'm flying\n");
}

// 具体火鸡实现
void wild_turkey_gobble(void) {
    printf("Gobble gobble\n");
}

void wild_turkey_fly(void) {
    printf("I'm flying a short distance\n");
}

// 火鸡适配器 - 实现鸭子接口
void turkey_adapter_quack(void);
void turkey_adapter_fly(void);

static Turkey* turkey;  // 适配器内部持有的火鸡对象

Duck create_turkey_adapter(Turkey* t) {
    turkey = t;
    Duck adapter = {
        .quack = turkey_adapter_quack,
        .fly = turkey_adapter_fly
    };
    return adapter;
}

void turkey_adapter_quack(void) {
    turkey->gobble();
}

void turkey_adapter_fly(void) {
    int i;
    // 火鸡飞行距离短，需要多次飞行来模拟鸭子
    for (i = 0; i < 5; i++) {
        turkey->fly();
    }
}

int main(void) {
    // 创建具体火鸡
    Turkey wild_turkey = {
        .gobble = wild_turkey_gobble,
        .fly = wild_turkey_fly
    };
    
    // 创建火鸡适配器(伪装成鸭子)
    Duck turkey_duck = create_turkey_adapter(&wild_turkey);
    
    // 测试适配器
    printf("The TurkeyAdapter says...\n");
    turkey_duck.quack();
    turkey_duck.fly();
    
    return 0;
}
