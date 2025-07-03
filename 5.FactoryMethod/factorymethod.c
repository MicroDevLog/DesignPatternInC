#include <stdio.h>
#include <string.h>

// 披萨类型枚举
typedef enum {
    CHEESE,
    PEPPERONI,
    VEGGIE,
    UNKNOWN
} PizzaType;

// 披萨结构体
typedef struct {
    char name[30];
    char dough[20];
    char sauce[20];
    char toppings[5][20];
    int toppingCount;
} Pizza;

// 全局披萨实例数组，不同类型的披萨店使用不同的实例
Pizza g_pizzas[3]; // 0: 纽约店, 1: 芝加哥店, 2: 加州店
int g_currentStore; // 当前使用的披萨店索引

// 重置披萨
void resetPizza(Pizza* pizza) {
    strcpy(pizza->name, "");
    strcpy(pizza->dough, "");
    strcpy(pizza->sauce, "");
    pizza->toppingCount = 0;
}

// 添加配料
void addTopping(Pizza* pizza, const char* topping) {
    if (pizza->toppingCount < 5) {
        strcpy(pizza->toppings[pizza->toppingCount++], topping);
    }
}

// 披萨店结构体（相当于抽象基类）
typedef struct PizzaStore {
    Pizza* (*createPizza)(struct PizzaStore* store, PizzaType type);
    Pizza* (*orderPizza)(struct PizzaStore* store, PizzaType type);
    char name[20]; // 店铺名称
} PizzaStore;

// 订购披萨的通用流程
Pizza* orderPizza(PizzaStore* store, PizzaType type) {
    int i;
    Pizza* pizza = store->createPizza(store, type);
    
    printf("\n--- %s 正在制作 %s ---\n", store->name, pizza->name);
    printf("准备 %s\n", pizza->dough);
    printf("添加 %s\n", pizza->sauce);
    for (i = 0; i < pizza->toppingCount; i++) {
        printf("添加 %s\n", pizza->toppings[i]);
    }
    printf("烘烤披萨\n");
    printf("切片\n");
    printf("装盒\n");
    printf("--- %s 制作完成 ---\n", pizza->name);
    
    return pizza;
}

// 纽约披萨店
typedef struct {
    PizzaStore base;
} NYPizzaStore;

// 纽约店创建披萨（工厂方法）
Pizza* nyCreatePizza(NYPizzaStore* store, PizzaType type) {
    g_currentStore = 0;
    Pizza* pizza = &g_pizzas[g_currentStore];
    resetPizza(pizza);
    
    switch (type) {
        case CHEESE:
            strcpy(pizza->name, "纽约风格芝士披萨");
            strcpy(pizza->dough, "薄脆面团");
            strcpy(pizza->sauce, "番茄酱");
            addTopping(pizza, " mozzarella");
            addTopping(pizza, " 罗勒");
            break;
        case PEPPERONI:
            strcpy(pizza->name, "纽约风格意大利辣香肠披萨");
            strcpy(pizza->dough, "超薄脆面团");
            strcpy(pizza->sauce, "意式番茄酱");
            addTopping(pizza, " mozzarella");
            addTopping(pizza, " 意大利辣香肠");
            break;
        case VEGGIE:
            strcpy(pizza->name, "纽约风格蔬菜披萨");
            strcpy(pizza->dough, "全麦面团");
            strcpy(pizza->sauce, "特制酱料");
            addTopping(pizza, " 蘑菇");
            addTopping(pizza, " 洋葱");
            addTopping(pizza, " 青椒");
            break;
        default:
            strcpy(pizza->name, "未知披萨");
            break;
    }
    
    return pizza;
}

// 初始化纽约披萨店
void initNYPizzaStore(NYPizzaStore* store) {
    strcpy(store->base.name, "纽约披萨店");
    store->base.createPizza = (Pizza* (*)(PizzaStore*, PizzaType))nyCreatePizza;
    store->base.orderPizza = orderPizza;
}

// 芝加哥披萨店
typedef struct {
    PizzaStore base;
} ChicagoPizzaStore;

// 芝加哥店创建披萨（工厂方法）
Pizza* chicagoCreatePizza(ChicagoPizzaStore* store, PizzaType type) {
    g_currentStore = 1;
    Pizza* pizza = &g_pizzas[g_currentStore];
    resetPizza(pizza);
    
    switch (type) {
        case CHEESE:
            strcpy(pizza->name, "芝加哥风格芝士披萨");
            strcpy(pizza->dough, "厚面团");
            strcpy(pizza->sauce, "浓番茄酱");
            addTopping(pizza, " 马苏里拉奶酪");
            addTopping(pizza, "  Parmesan");
            break;
        case PEPPERONI:
            strcpy(pizza->name, "芝加哥风格意大利辣香肠披萨");
            strcpy(pizza->dough, "超厚面团");
            strcpy(pizza->sauce, "番茄大蒜酱");
            addTopping(pizza, " 马苏里拉奶酪");
            addTopping(pizza, " 意大利辣香肠片");
            break;
        case VEGGIE:
            strcpy(pizza->name, "芝加哥风格蔬菜披萨");
            strcpy(pizza->dough, "深盘面团");
            strcpy(pizza->sauce, "意式红酱");
            addTopping(pizza, " 蘑菇");
            addTopping(pizza, " 橄榄");
            addTopping(pizza, " 菠菜");
            break;
        default:
            strcpy(pizza->name, "未知披萨");
            break;
    }
    
    return pizza;
}

// 初始化芝加哥披萨店
void initChicagoPizzaStore(ChicagoPizzaStore* store) {
    strcpy(store->base.name, "芝加哥披萨店");
    store->base.createPizza = (Pizza* (*)(PizzaStore*, PizzaType))chicagoCreatePizza;
    store->base.orderPizza = orderPizza;
}

// 加州披萨店
typedef struct {
    PizzaStore base;
} CaliforniaPizzaStore;

// 加州店创建披萨（工厂方法）
Pizza* californiaCreatePizza(CaliforniaPizzaStore* store, PizzaType type) {
    g_currentStore = 2;
    Pizza* pizza = &g_pizzas[g_currentStore];
    resetPizza(pizza);
    
    switch (type) {
        case CHEESE:
            strcpy(pizza->name, "加州风格芝士披萨");
            strcpy(pizza->dough, "全麦薄面团");
            strcpy(pizza->sauce, "轻番茄酱");
            addTopping(pizza, " 山羊奶酪");
            addTopping(pizza, "  香草");
            break;
        case PEPPERONI:
            strcpy(pizza->name, "加州风格意大利辣香肠披萨");
            strcpy(pizza->dough, "全麦面团");
            strcpy(pizza->sauce, "蒜香番茄酱");
            addTopping(pizza, " 马苏里拉奶酪");
            addTopping(pizza, "  有机意大利辣香肠");
            break;
        case VEGGIE:
            strcpy(pizza->name, "加州风格蔬菜披萨");
            strcpy(pizza->dough, "藜麦面团");
            strcpy(pizza->sauce, "鳄梨酱");
            addTopping(pizza, " 烤蔬菜");
            addTopping(pizza, "  豆芽");
            addTopping(pizza, "  芝麻菜");
            break;
        default:
            strcpy(pizza->name, "未知披萨");
            break;
    }
    
    return pizza;
}

// 初始化加州披萨店
void initCaliforniaPizzaStore(CaliforniaPizzaStore* store) {
    strcpy(store->base.name, "加州披萨店");
    store->base.createPizza = (Pizza* (*)(PizzaStore*, PizzaType))californiaCreatePizza;
    store->base.orderPizza = orderPizza;
}

int main() {
    // 初始化三家不同的披萨店
    NYPizzaStore nyStore;
    initNYPizzaStore(&nyStore);
    
    ChicagoPizzaStore chicagoStore;
    initChicagoPizzaStore(&chicagoStore);
    
    CaliforniaPizzaStore californiaStore;
    initCaliforniaPizzaStore(&californiaStore);
    
    // 从不同的店订购披萨
    PizzaStore* store = (PizzaStore*)&nyStore;
    store->orderPizza(store, CHEESE);
    
    store = (PizzaStore*)&chicagoStore;
    store->orderPizza(store, PEPPERONI);
    
    store = (PizzaStore*)&californiaStore;
    store->orderPizza(store, VEGGIE);
    
    return 0;
}
