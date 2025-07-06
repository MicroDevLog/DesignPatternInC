#ifndef CHOCOLATE_BOILER_H
#define CHOCOLATE_BOILER_H

// 巧克力锅炉状态枚举
typedef enum {
    EMPTY,       // 空的
    FILLING,    // 填充中
    BOILING,    // 煮沸中
    READY       // 准备好（已煮沸）
} BoilerState;

// 巧克力锅炉结构体（不对外暴露具体实现）
typedef struct ChocolateBoiler ChocolateBoiler;

// 获取单例实例
ChocolateBoiler* chocolateBoiler_getInstance(void);

// 填充原料
void chocolateBoiler_fill(ChocolateBoiler* boiler);

// 煮沸
void chocolateBoiler_boil(ChocolateBoiler* boiler);

// 排出巧克力
void chocolateBoiler_drain(ChocolateBoiler* boiler);

// 获取当前状态
BoilerState chocolateBoiler_getState(ChocolateBoiler* boiler);

#endif // CHOCOLATE_BOILER_H
