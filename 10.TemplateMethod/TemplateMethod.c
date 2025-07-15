#include <stdio.h>

// 定义咖啡因饮料抽象基类
typedef struct CaffeineBeverage {
    void (*prepareRecipe)(struct CaffeineBeverage*);
    void (*boilWater)(struct CaffeineBeverage*);
    void (*brew)(struct CaffeineBeverage*);
    void (*pourInCup)(struct CaffeineBeverage*);
    void (*addCondiments)(struct CaffeineBeverage*);
    int (*customerWantsCondiments)(struct CaffeineBeverage*);
} CaffeineBeverage;

// 模板方法
void prepareRecipe(CaffeineBeverage* beverage) {
    beverage->boilWater(beverage);
    beverage->brew(beverage);
    beverage->pourInCup(beverage);
    if (beverage->customerWantsCondiments(beverage)) {
        beverage->addCondiments(beverage);
    }
}

// 默认实现
void boilWater(CaffeineBeverage* beverage) {
    printf("Boiling water\n");
}

void pourInCup(CaffeineBeverage* beverage) {
    printf("Pouring into cup\n");
}

int customerWantsCondiments(CaffeineBeverage* beverage) {
    return 1; // 默认需要调料
}

// 咖啡具体实现
typedef struct Coffee {
    CaffeineBeverage base;
} Coffee;

void coffeeBrew(CaffeineBeverage* beverage) {
    printf("Dripping Coffee through filter\n");
}

void coffeeAddCondiments(CaffeineBeverage* beverage) {
    printf("Adding Sugar and Milk\n");
}

int coffeeCustomerWantsCondiments(CaffeineBeverage* beverage) {
    // 简单实现，实际应用中可以根据用户输入决定
    return 1;
}

void initCoffee(Coffee* coffee) {
    coffee->base.prepareRecipe = prepareRecipe;
    coffee->base.boilWater = boilWater;
    coffee->base.brew = coffeeBrew;
    coffee->base.pourInCup = pourInCup;
    coffee->base.addCondiments = coffeeAddCondiments;
    coffee->base.customerWantsCondiments = coffeeCustomerWantsCondiments;
}

// 茶具体实现
typedef struct Tea {
    CaffeineBeverage base;
} Tea;

void teaBrew(CaffeineBeverage* beverage) {
    printf("Steeping the tea\n");
}

void teaAddCondiments(CaffeineBeverage* beverage) {
    printf("Adding Lemon\n");
}

int teaCustomerWantsCondiments(CaffeineBeverage* beverage) {
    // 简单实现，实际应用中可以根据用户输入决定
    return 1;
}

void initTea(Tea* tea) {
    tea->base.prepareRecipe = prepareRecipe;
    tea->base.boilWater = boilWater;
    tea->base.brew = teaBrew;
    tea->base.pourInCup = pourInCup;
    tea->base.addCondiments = teaAddCondiments;
    tea->base.customerWantsCondiments = teaCustomerWantsCondiments;
}

int main() {
    Coffee coffee;
    Tea tea;

    initCoffee(&coffee);
    initTea(&tea);

    printf("Making coffee...\n");
    coffee.base.prepareRecipe((CaffeineBeverage*)&coffee);

    printf("\nMaking tea...\n");
    tea.base.prepareRecipe((CaffeineBeverage*)&tea);

    return 0;
}
