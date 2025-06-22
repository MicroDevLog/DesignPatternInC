#include <stdio.h>
#include <string.h>

// 行为接口定义
typedef struct FlyBehavior FlyBehavior;
typedef struct QuackBehavior QuackBehavior;

// 飞行行为函数指针类型
typedef void (*FlyFunction)(const FlyBehavior*);
// 呱呱叫行为函数指针类型
typedef void (*QuackFunction)(const QuackBehavior*);

// 飞行行为结构体
struct FlyBehavior {
    FlyFunction fly;
};

// 呱呱叫行为结构体
struct QuackBehavior {
    QuackFunction quack;
};

// 鸭子基类
typedef struct Duck {
    const char* name;
    const FlyBehavior* flyBehavior;
    const QuackBehavior* quackBehavior;
    void (*display)(const struct Duck*);
    void (*performFly)(const struct Duck*);
    void (*performQuack)(const struct Duck*);
    void (*setFlyBehavior)(struct Duck*, const FlyBehavior*);
    void (*setQuackBehavior)(struct Duck*, const QuackBehavior*);
} Duck;

// 飞行行为实现
void flyWithWings(const FlyBehavior* self) {
    printf("I'm flying!!\n");
}

void flyNoWay(const FlyBehavior* self) {
    printf("I can't fly\n");
}

void flyRocketPowered(const FlyBehavior* self) {
    printf("I'm flying with a rocket!\n");
}

// 呱呱叫行为实现
void quack(const QuackBehavior* self) {
    printf("Quack\n");
}

void muteQuack(const QuackBehavior* self) {
    printf("<< Silence >>\n");
}

void squeak(const QuackBehavior* self) {
    printf("Squeak\n");
}

// 鸭子基类方法实现
void duckPerformFly(const Duck* self) {
    self->flyBehavior->fly(self->flyBehavior);
}

void duckPerformQuack(const Duck* self) {
    self->quackBehavior->quack(self->quackBehavior);
}

void duckSetFlyBehavior(Duck* self, const FlyBehavior* fb) {
    self->flyBehavior = fb;
}

void duckSetQuackBehavior(Duck* self, const QuackBehavior* qb) {
    self->quackBehavior = qb;
}

// 具体鸭子类实现
void mallardDisplay(const Duck* self) {
    printf("I'm a real Mallard duck. My name is %s\n", self->name);
}

void redheadDisplay(const Duck* self) {
    printf("I'm a Redhead duck. My name is %s\n", self->name);
}

void rubberDisplay(const Duck* self) {
    printf("I'm a rubber duckie. My name is %s\n", self->name);
}

void decoyDisplay(const Duck* self) {
    printf("I'm a duck decoy. My name is %s\n", self->name);
}

// 静态行为实例
static const FlyBehavior flyWithWingsBehavior = { flyWithWings };
static const FlyBehavior flyNoWayBehavior = { flyNoWay };
static const FlyBehavior flyRocketPoweredBehavior = { flyRocketPowered };

static const QuackBehavior quackBehavior = { quack };
static const QuackBehavior muteQuackBehavior = { muteQuack };
static const QuackBehavior squeakBehavior = { squeak };

// 初始化鸭子对象（不使用动态内存分配）
void initDuck(Duck* duck, const char* name, const FlyBehavior* fb, 
              const QuackBehavior* qb, void (*display)(const Duck*)) {
    duck->name = name;
    duck->flyBehavior = fb;
    duck->quackBehavior = qb;
    duck->display = display;
    duck->performFly = duckPerformFly;
    duck->performQuack = duckPerformQuack;
    duck->setFlyBehavior = duckSetFlyBehavior;
    duck->setQuackBehavior = duckSetQuackBehavior;
}

// 主函数演示
int main() {
    // 静态分配鸭子对象
    Duck mallard, redhead, rubber, decoy;
    
    // 初始化各种鸭子
    initDuck(&mallard, "绿头鸭", &flyWithWingsBehavior, &quackBehavior, mallardDisplay);
    initDuck(&redhead, "红头鸭", &flyWithWingsBehavior, &quackBehavior, redheadDisplay);
    initDuck(&rubber, "橡皮鸭", &flyNoWayBehavior, &squeakBehavior, rubberDisplay);
    initDuck(&decoy, "诱饵鸭", &flyNoWayBehavior, &muteQuackBehavior, decoyDisplay);
    
    printf("==== 初始鸭子行为 ====\n");
    // 测试绿头鸭
    mallard.display(&mallard);
    mallard.performFly(&mallard);
    mallard.performQuack(&mallard);
    printf("\n");
    
    // 测试红头鸭
    redhead.display(&redhead);
    redhead.performFly(&redhead);
    redhead.performQuack(&redhead);
    printf("\n");
    
    // 测试橡皮鸭
    rubber.display(&rubber);
    rubber.performFly(&rubber);
    rubber.performQuack(&rubber);
    printf("\n");
    
    // 测试诱饵鸭
    decoy.display(&decoy);
    decoy.performFly(&decoy);
    decoy.performQuack(&decoy);
    printf("\n");
    
    // 动态改变鸭子行为
    printf("==== 改变鸭子行为 ====\n");
    printf("给橡皮鸭装上火箭推进器...\n");
    rubber.setFlyBehavior(&rubber, &flyRocketPoweredBehavior);
    rubber.performFly(&rubber);
    
    printf("给诱饵鸭装上会叫的装置...\n");
    decoy.setQuackBehavior(&decoy, &quackBehavior);
    decoy.performQuack(&decoy);
    
    return 0;
}