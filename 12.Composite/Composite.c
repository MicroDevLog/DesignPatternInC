#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_ITEMS 10
#define MAX_MENUS 5

// 菜单项结构体
typedef struct MenuItem {
    char name[MAX_NAME_LENGTH];
    char description[MAX_NAME_LENGTH];
    double price;
    int vegetarian;
} MenuItem;

// 菜单结构体 - 显式命名为struct Menu
typedef struct Menu {
    char name[MAX_NAME_LENGTH];
    char description[MAX_NAME_LENGTH];
    union {
        MenuItem items[MAX_ITEMS];
        struct Menu* submenus[MAX_MENUS];  // 使用命名的struct Menu*
    } content;
    int itemCount;
    int isSubmenu;  // 0表示菜单项，1表示子菜单
} Menu;

// 初始化菜单项
void initMenuItem(MenuItem* item, const char* name, const char* desc, double price, int veg) {
    strncpy(item->name, name, MAX_NAME_LENGTH - 1);
    strncpy(item->description, desc, MAX_NAME_LENGTH - 1);
    item->price = price;
    item->vegetarian = veg;
}

// 初始化菜单
void initMenu(Menu* menu, const char* name, const char* desc, int isSubmenu) {
    strncpy(menu->name, name, MAX_NAME_LENGTH - 1);
    strncpy(menu->description, desc, MAX_NAME_LENGTH - 1);
    menu->itemCount = 0;
    menu->isSubmenu = isSubmenu;
}

// 添加菜单项到菜单
void addMenuItem(Menu* menu, const MenuItem* item) {
    if (menu->itemCount < MAX_ITEMS && !menu->isSubmenu) {
        menu->content.items[menu->itemCount++] = *item;
    }
}

// 添加子菜单到菜单
void addSubmenu(Menu* menu, Menu* submenu) {
    if (menu->itemCount < MAX_MENUS && menu->isSubmenu) {
        menu->content.submenus[menu->itemCount++] = submenu;
    }
}

// 打印菜单项
void printMenuItem(const MenuItem* item) {
    printf("  %-20s $%.2f\n", item->name, item->price);
    printf("    -- %s\n", item->description);
    if (item->vegetarian) {
        printf("    (V)\n");
    }
}

// 递归打印菜单
void printMenu(const Menu* menu, int depth) {
    int i,j;
    for (i = 0; i < depth; i++) printf("  ");
    printf("%s\n", menu->name);
    for (i = 0; i < depth; i++) printf("  ");
    printf("-------------------\n");
    
    if (menu->isSubmenu) {
        for (i = 0; i < menu->itemCount; i++) {
            printMenu(menu->content.submenus[i], depth + 1);
        }
    } else {
        for (i = 0; i < menu->itemCount; i++) {
            for (j = 0; j < depth; j++) printf("  ");
            printMenuItem(&menu->content.items[i]);
        }
    }
}

int main() {
    // 静态定义所有菜单和菜单项
    Menu allMenus, pancakeHouseMenu, dinerMenu, cafeMenu, dessertMenu;
    MenuItem item1, item2, item3, item4;
    
    // 初始化菜单
    initMenu(&allMenus, "所有菜单", "全部组合菜单", 1);
    initMenu(&pancakeHouseMenu, "煎饼屋菜单", "早餐", 0);
    initMenu(&dinerMenu, "餐厅菜单", "午餐", 1);
    initMenu(&cafeMenu, "咖啡厅菜单", "晚餐", 1);
    initMenu(&dessertMenu, "甜点菜单", "甜点", 0);
    
    // 初始化菜单项
    initMenuItem(&item1, "素食BLT", "煎豆腐配生菜和番茄全麦面包", 2.99, 1);
    initMenuItem(&item2, "BLT", "培根配生菜和番茄全麦面包", 2.99, 0);
    initMenuItem(&item3, "蔬菜汉堡和薯条", "素食汉堡配新鲜薯条", 3.99, 1);
    initMenuItem(&item4, "苹果派", "苹果派配香草冰淇淋", 1.59, 1);
    
    // 构建菜单结构
    addMenuItem(&pancakeHouseMenu, &item1);
    addMenuItem(&dinerMenu, &item2);
    addMenuItem(&cafeMenu, &item3);
    addMenuItem(&dessertMenu, &item4);
    
    addSubmenu(&dinerMenu, &dessertMenu);
    addSubmenu(&allMenus, &pancakeHouseMenu);
    addSubmenu(&allMenus, &dinerMenu);
    addSubmenu(&allMenus, &cafeMenu);
    
    // 打印菜单
    printMenu(&allMenus, 0);
    
    return 0;
}
