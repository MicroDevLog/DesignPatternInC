#include <stdio.h>
#include <string.h>

/* 定义最大字符串长度和装饰器链的最大深度 */
#define MAX_DESC_LENGTH 100
#define MAX_DECORATORS 5

/* 饮料基类接口 */
typedef struct Beverage {
    char description[MAX_DESC_LENGTH];
    float (*cost)(struct Beverage*);
    void (*getDescription)(struct Beverage*, char*);
    int decorator_count;
    struct Beverage* decorators[MAX_DECORATORS];
} Beverage;

/* 具体饮料实现 */
typedef struct {
    Beverage base;
} Espresso;

typedef struct {
    Beverage base;
} HouseBlend;

/* 调料装饰器基类 */
typedef struct CondimentDecorator {
    Beverage base;
    Beverage* beverage;  /* 被装饰的饮料 */
} CondimentDecorator;

/* 具体调料装饰器 */
typedef struct {
    CondimentDecorator base;
} Mocha;

typedef struct {
    CondimentDecorator base;
} Whip;

/* 饮料实现函数 */
float Espresso_cost(Beverage* self) {
    return 1.99f;
}

void Espresso_getDescription(Beverage* self, char* desc) {
    strcpy(desc, "Espresso");
}

void Espresso_init(Espresso* this) {
    Beverage* base = &this->base;
    base->cost = Espresso_cost;
    base->getDescription = Espresso_getDescription;
    base->decorator_count = 0;
}

float HouseBlend_cost(Beverage* self) {
    return 0.89f;
}

void HouseBlend_getDescription(Beverage* self, char* desc) {
    strcpy(desc, "House Blend Coffee");
}

void HouseBlend_init(HouseBlend* this) {
    Beverage* base = &this->base;
    base->cost = HouseBlend_cost;
    base->getDescription = HouseBlend_getDescription;
    base->decorator_count = 0;
}

/* 调料装饰器实现函数 */
float Mocha_cost(Beverage* self) {
    CondimentDecorator* decorator = (CondimentDecorator*)self;
    return 0.20f + decorator->beverage->cost(decorator->beverage);
}

void Mocha_getDescription(Beverage* self, char* desc) {
    CondimentDecorator* decorator = (CondimentDecorator*)self;
    char temp_desc[MAX_DESC_LENGTH];
    decorator->beverage->getDescription(decorator->beverage, temp_desc);
    sprintf(desc, "%s, Mocha", temp_desc);
}

void Mocha_init(Mocha* this, Beverage* beverage) {
    CondimentDecorator* base = &this->base;
    base->base.cost = Mocha_cost;
    base->base.getDescription = Mocha_getDescription;
    base->beverage = beverage;
    
    /* 将装饰器添加到被装饰对象的装饰器链中 */
    if (beverage->decorator_count < MAX_DECORATORS) {
        beverage->decorators[beverage->decorator_count++] = &base->base;
    }
}

float Whip_cost(Beverage* self) {
    CondimentDecorator* decorator = (CondimentDecorator*)self;
    return 0.10f + decorator->beverage->cost(decorator->beverage);
}

void Whip_getDescription(Beverage* self, char* desc) {
    CondimentDecorator* decorator = (CondimentDecorator*)self;
    char temp_desc[MAX_DESC_LENGTH];
    decorator->beverage->getDescription(decorator->beverage, temp_desc);
    sprintf(desc, "%s, Whip", temp_desc);
}

void Whip_init(Whip* this, Beverage* beverage) {
    CondimentDecorator* base = &this->base;
    base->base.cost = Whip_cost;
    base->base.getDescription = Whip_getDescription;
    base->beverage = beverage;
    
    /* 将装饰器添加到被装饰对象的装饰器链中 */
    if (beverage->decorator_count < MAX_DECORATORS) {
        beverage->decorators[beverage->decorator_count++] = &base->base;
    }
}

int main() {
    /* 创建饮料和调料实例（静态分配） */
    Espresso espresso;
    Mocha mocha1;
    Mocha mocha2;
    Whip whip;
    
    /* 初始化组件 */
    Espresso_init(&espresso);
    Mocha_init(&mocha1, &espresso.base);
    Mocha_init(&mocha2, &mocha1.base.base);
    Whip_init(&whip, &mocha2.base.base);
    
    /* 使用最外层装饰器 */
    Beverage* myBeverage = &whip.base.base;
    
    /* 输出结果 */
    char desc[MAX_DESC_LENGTH];
    myBeverage->getDescription(myBeverage, desc);
    printf("Description: %s\n", desc);
    printf("Cost: $%.2f\n", myBeverage->cost(myBeverage));
    
    return 0;
}
