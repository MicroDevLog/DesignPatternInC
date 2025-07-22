#include <stdio.h>
#include <string.h>

/* 定义菜单项结构 */
typedef struct {
    char name[50];
    char description[100];
    int vegetarian;
    double price;
} MenuItem;

/* 迭代器接口 */
typedef struct {
    int (*hasNext)(void*);
    MenuItem* (*next)(void*);
} Iterator;

/* 前置声明 PancakeHouseMenu */
typedef struct PancakeHouseMenu PancakeHouseMenu;

/* 煎饼屋菜单迭代器状态 */
typedef struct {
    PancakeHouseMenu* menu;
    int position;
} PancakeIteratorState;

/* 煎饼屋菜单 - 使用数组实现 */
#define MAX_PANCAKE_ITEMS 10
struct PancakeHouseMenu {
    MenuItem items[MAX_PANCAKE_ITEMS];
    int count;
    Iterator iterator;
    PancakeIteratorState iteratorState; // 存储迭代器状态
};

/* 餐厅菜单 - 使用数组实现 */
#define MAX_DINER_ITEMS 5
typedef struct {
    MenuItem items[MAX_DINER_ITEMS];
    int position;
    Iterator iterator;
} DinerMenu;

int pancakeIteratorHasNext(void* state) {
    PancakeIteratorState* iteratorState = (PancakeIteratorState*)state;
    return iteratorState->position < iteratorState->menu->count;
}

MenuItem* pancakeIteratorNext(void* state) {
    PancakeIteratorState* iteratorState = (PancakeIteratorState*)state;
    if (pancakeIteratorHasNext(state)) {
        MenuItem* item = &iteratorState->menu->items[iteratorState->position];
        iteratorState->position++;
        return item;
    }
    return NULL;
}

void initPancakeHouseMenu(PancakeHouseMenu* menu) {
    menu->count = 0;
    menu->iterator.hasNext = pancakeIteratorHasNext;
    menu->iterator.next = pancakeIteratorNext;
    
    // 初始化迭代器状态
    menu->iteratorState.menu = menu;
    menu->iteratorState.position = 0;
}

void addPancakeItem(PancakeHouseMenu* menu, const char* name, 
                    const char* description, int vegetarian, double price) {
    if (menu->count < MAX_PANCAKE_ITEMS) {
        MenuItem item;
        strcpy(item.name, name);
        strcpy(item.description, description);
        item.vegetarian = vegetarian;
        item.price = price;
        menu->items[menu->count++] = item;
    }
}

int dinerIteratorHasNext(void* menu) {
    DinerMenu* dinerMenu = (DinerMenu*)menu;
    return dinerMenu->position < MAX_DINER_ITEMS && 
           dinerMenu->items[dinerMenu->position].price != 0.0;
}

MenuItem* dinerIteratorNext(void* menu) {
    DinerMenu* dinerMenu = (DinerMenu*)menu;
    if (dinerIteratorHasNext(menu)) {
        return &dinerMenu->items[dinerMenu->position++];
    }
    return NULL;
}

void initDinerMenu(DinerMenu* menu) {
    menu->position = 0;
    int i;
    for (i = 0; i < MAX_DINER_ITEMS; i++) {
        menu->items[i].price = 0.0; /* 用价格为0表示空项 */
    }
    menu->iterator.hasNext = dinerIteratorHasNext;
    menu->iterator.next = dinerIteratorNext;
}

void addDinerItem(DinerMenu* menu, const char* name, 
                  const char* description, int vegetarian, double price) {
    int i;
    for (i = 0; i < MAX_DINER_ITEMS; i++) {
        if (menu->items[i].price == 0.0) {
            MenuItem item;
            strcpy(item.name, name);
            strcpy(item.description, description);
            item.vegetarian = vegetarian;
            item.price = price;
            menu->items[i] = item;
            break;
        }
    }
}

/* 女招待类 */
typedef struct {
    PancakeHouseMenu* pancakeMenu;
    DinerMenu* dinerMenu;
} Waitress;

void initWaitress(Waitress* waitress, PancakeHouseMenu* pancakeMenu, DinerMenu* dinerMenu) {
    waitress->pancakeMenu = pancakeMenu;
    waitress->dinerMenu = dinerMenu;
}

void printMenu(Waitress* waitress) {
    printf("MENU\n----\nBREAKFAST\n");
    // 重置煎饼屋菜单迭代器状态
    waitress->pancakeMenu->iteratorState.position = 0;
    Iterator* pancakeIterator = &waitress->pancakeMenu->iterator;
    void* pancakeState = &waitress->pancakeMenu->iteratorState;
    while (pancakeIterator->hasNext(pancakeState)) {
        MenuItem* item = pancakeIterator->next(pancakeState);
        printf("%s, $%.2f\n", item->name, item->price);
        printf("  -- %s\n", item->description);
        if (item->vegetarian) {
            printf("  (V)\n");
        }
    }

    printf("\nLUNCH\n");
    // 重置餐厅菜单迭代器位置
    waitress->dinerMenu->position = 0;
    Iterator* dinerIterator = &waitress->dinerMenu->iterator;
    void* dinerMenu = waitress->dinerMenu;
    while (dinerIterator->hasNext(dinerMenu)) {
        MenuItem* item = dinerIterator->next(dinerMenu);
        printf("%s, $%.2f\n", item->name, item->price);
        printf("  -- %s\n", item->description);
        if (item->vegetarian) {
            printf("  (V)\n");
        }
    }
}

int main() {
    /* 创建菜单 */
    PancakeHouseMenu pancakeMenu;
    initPancakeHouseMenu(&pancakeMenu);
    addPancakeItem(&pancakeMenu, "K&B's Pancake Breakfast", 
                  "Pancakes with scrambled eggs, and toast", 1, 2.99);
    addPancakeItem(&pancakeMenu, "Regular Pancake Breakfast", 
                  "Pancakes with fried eggs, sausage", 0, 2.99);

    DinerMenu dinerMenu;
    initDinerMenu(&dinerMenu);
    addDinerItem(&dinerMenu, "Vegetarian BLT", 
                "(Fakin') Bacon with lettuce & tomato on whole wheat", 1, 2.99);
    addDinerItem(&dinerMenu, "BLT", 
                "Bacon with lettuce & tomato on whole wheat", 0, 2.99);

    /* 创建女招待 */
    Waitress waitress;
    initWaitress(&waitress, &pancakeMenu, &dinerMenu);

    /* 打印菜单 */
    printMenu(&waitress);
    
    // 可以再次打印菜单，验证非破坏性遍历
    printf("\n\nREPRINTING MENU:\n");
    printMenu(&waitress);

    return 0;
}
