#include <stdio.h>

// 模型(Model)：负责数据和业务逻辑
typedef struct {
    int count;               // 数据
    void (*onChange)();      // 数据变化时的回调函数
} CounterModel;

// 视图(View)：负责数据展示，依赖模型
typedef struct {
    CounterModel* model;     // 关联的模型
    void (*render)();        // 渲染视图的函数
} CounterView;

// 控制器(Controller)：负责处理用户输入，协调模型和视图
typedef struct {
    CounterModel* model;     // 关联的模型
    CounterView* view;       // 关联的视图
    void (*increment)();     // 处理递增的函数
    void (*decrement)();     // 处理递减的函数
    void (*reset)();         // 处理重置的函数
} CounterController;

// 模型方法：初始化
void initModel(CounterModel* model) {
    model->count = 0;
    model->onChange = NULL;
}

// 视图方法：初始化
void initView(CounterView* view, CounterModel* model) {
    view->model = model;
}

// 视图方法：渲染（显示数据）
void renderView(CounterView* view) {
    printf("\n当前计数: %d\n", view->model->count);
    printf("操作: (+)递增  (-)递减  (r)重置  (q)退出\n");
    printf("请输入操作: ");
}

// 控制器方法：初始化
void initController(CounterController* controller, CounterModel* model, CounterView* view) {
    controller->model = model;
    controller->view = view;
}

// 控制器方法：处理递增
void incrementCounter(CounterController* controller) {
    controller->model->count++;
    if (controller->model->onChange) {
        controller->model->onChange();
    }
}

// 控制器方法：处理递减
void decrementCounter(CounterController* controller) {
    controller->model->count--;
    if (controller->model->onChange) {
        controller->model->onChange();
    }
}

// 控制器方法：处理重置
void resetCounter(CounterController* controller) {
    controller->model->count = 0;
    if (controller->model->onChange) {
        controller->model->onChange();
    }
}

// 全局变量 - 用于回调函数中访问视图
CounterView* globalView;

// 模型数据变化时的回调函数
void onModelChange() {
    renderView(globalView);
}

int main() {
    // 在栈上创建MVC组件（不使用动态内存分配）
    CounterModel model;
    CounterView view;
    CounterController controller;
    
    // 初始化组件
    initModel(&model);
    initView(&view, &model);
    initController(&controller, &model, &view);
    
    // 设置函数指针
    view.render = renderView;
    controller.increment = incrementCounter;
    controller.decrement = decrementCounter;
    controller.reset = resetCounter;
    
    // 设置模型变化回调
    globalView = &view;
    model.onChange = onModelChange;
    
    // 应用程序主循环
    char input;
    renderView(&view);
    while (1) {
        input = getchar();
        // 处理输入缓冲区
        if (input != '\n') {
            switch (input) {
                case '+':
                    controller.increment(&controller);
                    break;
                case '-':
                    controller.decrement(&controller);
                    break;
                case 'r':
                case 'R':
                    controller.reset(&controller);
                    break;
                case 'q':
                case 'Q':
                    printf("\n程序退出\n");
                    return 0;
                default:
                    printf("无效操作，请重新输入: ");
                    break;
            }
        }
    }
    
    return 0;
}
