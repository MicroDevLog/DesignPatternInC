#include <stdio.h>
#include <string.h>

// 定义比萨类型枚举
typedef enum {
    CHEESE_PIZZA,  /*奶酪披萨*/
    VEGGIE_PIZZA,  /*素食披萨*/
    CLAM_PIZZA,    /*蛤蜊披萨*/
    UNKNOWN_PIZZA  /*未知比萨类型*/
} PizzaType;

// 定义比萨结构体
typedef struct {
    PizzaType type;
    char name[20];     /*比萨名称*/
    char dough[20];    /*面团类型*/
    char sauce[20];    /*酱料类型*/
    char toppings[50]; /*配料*/
} Pizza;

// 初始化比萨结构体
void init_pizza(Pizza *pizza, PizzaType type, const char *name, 
                const char *dough, const char *sauce, const char *toppings) {
    pizza->type = type;
    strncpy(pizza->name, name, sizeof(pizza->name) - 1);
    strncpy(pizza->dough, dough, sizeof(pizza->dough) - 1);
    strncpy(pizza->sauce, sauce, sizeof(pizza->sauce) - 1);
    strncpy(pizza->toppings, toppings, sizeof(pizza->toppings) - 1);
}

// 简单比萨工厂函数
int create_pizza(PizzaType type, Pizza *pizza) {
    switch (type) {
        case CHEESE_PIZZA:
            init_pizza(pizza, CHEESE_PIZZA, "芝士比萨", "薄饼", "番茄酱", "马苏里拉芝士");
            return 1;
        case VEGGIE_PIZZA:
            init_pizza(pizza, VEGGIE_PIZZA, "素食比萨", "全麦饼", "橄榄油", "蘑菇、青椒、洋葱");
            return 1;
        case CLAM_PIZZA:
            init_pizza(pizza, CLAM_PIZZA, "蛤蜊比萨", "厚饼", "白酱", "蛤蜊、芝士");
            return 1;
        default:
            return 0; // 创建失败
    }
}

// 比萨操作函数
void prepare_pizza(const Pizza *pizza) {
    printf("准备 %s\n", pizza->name);
    printf("面团: %s\n", pizza->dough);
    printf("酱料: %s\n", pizza->sauce);
    printf("配料: %s\n", pizza->toppings);
}

void bake_pizza(const Pizza *pizza) {
    printf("烘烤 %s: 25分钟，温度350°F\n", pizza->name);
}

void cut_pizza(const Pizza *pizza) {
    printf("切割 %s: 切成对角片\n", pizza->name);
}

void box_pizza(const Pizza *pizza) {
    printf("包装 %s: 放入官方比萨盒\n", pizza->name);
}

// 比萨店订单处理函数
void order_pizza(PizzaType type) {
    Pizza pizza;
    
    if (!create_pizza(type, &pizza)) {
        printf("错误: 不支持的比萨类型\n");
        return;
    }
    
    prepare_pizza(&pizza);
    bake_pizza(&pizza);
    cut_pizza(&pizza);
    box_pizza(&pizza);
    
    printf("比萨准备好了！\n");
}

int main() {
    printf("--- 订单 1: 芝士比萨 ---\n");
    order_pizza(CHEESE_PIZZA);
    
    printf("\n--- 订单 2: 蛤蜊比萨 ---\n");
    order_pizza(CLAM_PIZZA);
    
    printf("\n--- 订单 3: 未知类型 ---\n");
    order_pizza(UNKNOWN_PIZZA);
    
    return 0;
}
