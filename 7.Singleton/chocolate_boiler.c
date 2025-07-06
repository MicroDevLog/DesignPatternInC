#include "chocolate_boiler.h"
#include <stdbool.h>

// 巧克力锅炉结构体具体实现
struct ChocolateBoiler {
    bool hasMilk;       // 是否有牛奶
    bool hasChocolate;  // 是否有巧克力
    bool isBoiled;      // 是否已煮沸
    BoilerState state;  // 当前状态
};

// 静态全局变量 - 确保只有一个实例
static ChocolateBoiler instance = {false, false, false, EMPTY};

// 获取单例实例
ChocolateBoiler* chocolateBoiler_getInstance(void) {
    // 返回静态实例的地址，确保全局唯一
    return &instance;
}

// 填充原料（只有空的时候才能填充）
void chocolateBoiler_fill(ChocolateBoiler* boiler) {
    if (boiler->state == EMPTY) {
        boiler->hasMilk = true;
        boiler->hasChocolate = true;
        boiler->isBoiled = false;
        boiler->state = FILLING;
        // 模拟填充过程
        boiler->state = BOILING;
    }
}

// 煮沸（只有填充了且未煮沸才能煮沸）
void chocolateBoiler_boil(ChocolateBoiler* boiler) {
    if (boiler->hasMilk && boiler->hasChocolate && !boiler->isBoiled && 
        boiler->state == BOILING) {
        // 模拟煮沸过程
        boiler->isBoiled = true;
        boiler->state = READY;
    }
}

// 排出巧克力（只有煮沸了才能排出）
void chocolateBoiler_drain(ChocolateBoiler* boiler) {
    if (boiler->isBoiled && boiler->state == READY) {
        boiler->hasMilk = false;
        boiler->hasChocolate = false;
        boiler->isBoiled = false;
        boiler->state = EMPTY;
    }
}

// 获取当前状态
BoilerState chocolateBoiler_getState(ChocolateBoiler* boiler) {
    return boiler->state;
}
