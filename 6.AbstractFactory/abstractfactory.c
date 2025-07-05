#include <stdio.h>
#include <string.h>

// 前向声明
typedef struct Dough Dough;
typedef struct Sauce Sauce;
typedef struct Cheese Cheese;
typedef struct PizzaIngredientFactory PizzaIngredientFactory;

// 原料结构体定义
struct Dough {
    char name[50];
};

struct Sauce {
    char name[50];
};

struct Cheese {
    char name[50];
};

// 抽象工厂接口 - 定义创建原料的方法
struct PizzaIngredientFactory {
    void (*createDough)(PizzaIngredientFactory*, Dough*);
    void (*createSauce)(PizzaIngredientFactory*, Sauce*);
    void (*createCheese)(PizzaIngredientFactory*, Cheese*);
};

// 纽约原料工厂
typedef struct {
    PizzaIngredientFactory factory; // 继承抽象工厂
} NYPizzaIngredientFactory;

// 芝加哥原料工厂
typedef struct {
    PizzaIngredientFactory factory; // 继承抽象工厂
} ChicagoPizzaIngredientFactory;

// 纽约原料工厂方法实现
void nyCreateDough(PizzaIngredientFactory* factory, Dough* dough) {
    strcpy(dough->name, "纽约薄面团");
}

void nyCreateSauce(PizzaIngredientFactory* factory, Sauce* sauce) {
    strcpy(sauce->name, "纽约番茄酱");
}

void nyCreateCheese(PizzaIngredientFactory* factory, Cheese* cheese) {
    strcpy(cheese->name, "纽约马苏里拉奶酪");
}

// 芝加哥原料工厂方法实现
void chicagoCreateDough(PizzaIngredientFactory* factory, Dough* dough) {
    strcpy(dough->name, "芝加哥厚面团");
}

void chicagoCreateSauce(PizzaIngredientFactory* factory, Sauce* sauce) {
    strcpy(sauce->name, "芝加哥番茄酱");
}

void chicagoCreateCheese(PizzaIngredientFactory* factory, Cheese* cheese) {
    strcpy(cheese->name, "芝加哥帕尔马干酪");
}

// 初始化工厂
void initNYPizzaIngredientFactory(NYPizzaIngredientFactory* factory) {
    factory->factory.createDough = nyCreateDough;
    factory->factory.createSauce = nyCreateSauce;
    factory->factory.createCheese = nyCreateCheese;
}

void initChicagoPizzaIngredientFactory(ChicagoPizzaIngredientFactory* factory) {
    factory->factory.createDough = chicagoCreateDough;
    factory->factory.createSauce = chicagoCreateSauce;
    factory->factory.createCheese = chicagoCreateCheese;
}

// 披萨制作函数 - 使用抽象工厂
void makePizza(PizzaIngredientFactory* factory, const char* name) {
    Dough dough;
    Sauce sauce;
    Cheese cheese;
    
    printf("制作%s:\n", name);
    factory->createDough(factory, &dough);
    factory->createSauce(factory, &sauce);
    factory->createCheese(factory, &cheese);
    
    printf("使用了: %s, %s, %s\n", dough.name, sauce.name, cheese.name);
}

int main() {
    // 静态创建工厂实例
    NYPizzaIngredientFactory nyFactory;
    ChicagoPizzaIngredientFactory chicagoFactory;
    
    // 初始化工厂
    initNYPizzaIngredientFactory(&nyFactory);
    initChicagoPizzaIngredientFactory(&chicagoFactory);
    
    // 制作纽约风味披萨
    makePizza((PizzaIngredientFactory*)&nyFactory, "纽约风味芝士披萨");
    
    // 制作芝加哥风味披萨
    makePizza((PizzaIngredientFactory*)&chicagoFactory, "芝加哥风味芝士披萨");
    
    return 0;
}
