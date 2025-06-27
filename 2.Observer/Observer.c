#include <stdio.h>
#include <stdbool.h>

// 定义最大观察者数量
#define MAX_OBSERVERS 3

// 前向声明
typedef struct Observer Observer;
typedef struct WeatherData WeatherData;

// 观察者接口函数指针类型
typedef void (*UpdateFunc)(Observer*, float temperature, float humidity, float pressure);

// 观察者结构体
struct Observer {
    UpdateFunc update;  // 回调函数
};

// 主题接口
typedef struct {
    void (*registerObserver)(void*, Observer*);
    void (*removeObserver)(void*, Observer*);
    void (*notifyObservers)(void*);
} SubjectInterface;

// 天气数据结构体
struct WeatherData {
    SubjectInterface* vtable;
    float temperature;
    float humidity;
    float pressure;
    Observer* observers[MAX_OBSERVERS];
    int observerCount;
};

// 布告板结构体
typedef struct {
    Observer base;  // 继承Observer
    char* name;     // 布告板名称
} DisplayElement;

// 函数声明
void weatherData_registerObserver(void* subject, Observer* observer);
void weatherData_removeObserver(void* subject, Observer* observer);
void weatherData_notifyObservers(void* subject);
void currentConditionsDisplay_update(Observer* observer, float temperature, float humidity, float pressure);
void statisticsDisplay_update(Observer* observer, float temperature, float humidity, float pressure);
void forecastDisplay_update(Observer* observer, float temperature, float humidity, float pressure);
void weatherData_setMeasurements(WeatherData* weatherData, float temperature, float humidity, float pressure);

// WeatherData虚函数表
static SubjectInterface weatherDataVtable = {
    .registerObserver = weatherData_registerObserver,
    .removeObserver = weatherData_removeObserver,
    .notifyObservers = weatherData_notifyObservers
};

// 注册观察者
void weatherData_registerObserver(void* subject, Observer* observer) {
    WeatherData* weatherData = (WeatherData*)subject;
    if (weatherData->observerCount < MAX_OBSERVERS) {
        weatherData->observers[weatherData->observerCount++] = observer;
        printf("注册观察者: %p\n", observer);
    } else {
        printf("错误: 观察者数量已达到最大值\n");
    }
}

// 移除观察者
void weatherData_removeObserver(void* subject, Observer* observer) {
    WeatherData* weatherData = (WeatherData*)subject;
    int i,j;
    for (i = 0; i < weatherData->observerCount; i++) {
        if (weatherData->observers[i] == observer) {
            // 将后面的观察者前移
            for (j = i; j < weatherData->observerCount - 1; j++) {
                weatherData->observers[j] = weatherData->observers[j + 1];
            }
            weatherData->observerCount--;
            printf("移除观察者: %p\n", observer);
            return;
        }
    }
    printf("错误: 未找到观察者 %p\n", observer);
}

// 通知所有观察者
void weatherData_notifyObservers(void* subject) {
    WeatherData* weatherData = (WeatherData*)subject;
    int i;
    for (i = 0; i < weatherData->observerCount; i++) {
        Observer* observer = weatherData->observers[i];
        observer->update(observer, weatherData->temperature, 
                         weatherData->humidity, weatherData->pressure);
    }
}

// 更新当前状况布告板
void currentConditionsDisplay_update(Observer* observer, float temperature, float humidity, float pressure) {
    DisplayElement* display = (DisplayElement*)observer;
    printf("[%s] 当前状况: 温度 %.1f°C, 湿度 %.1f%%\n", 
           display->name, temperature, humidity);
}

// 更新统计信息布告板
void statisticsDisplay_update(Observer* observer, float temperature, float humidity, float pressure) {
    static float maxTemp = -273.15f;
    static float minTemp = 1000.0f;
    static float tempSum = 0.0f;
    static int count = 0;
    
    DisplayElement* display = (DisplayElement*)observer;
    
    if (temperature > maxTemp) maxTemp = temperature;
    if (temperature < minTemp) minTemp = temperature;
    
    tempSum += temperature;
    count++;
    
    printf("[%s] 温度统计: 最高 %.1f°C, 最低 %.1f°C, 平均 %.1f°C\n", 
           display->name, maxTemp, minTemp, tempSum / count);
}

// 更新天气预报布告板
void forecastDisplay_update(Observer* observer, float temperature, float humidity, float pressure) {
    DisplayElement* display = (DisplayElement*)observer;
    printf("[%s] 天气预报: ", display->name);
    
    if (pressure > 1013.25f) {
        printf("天气晴朗\n");
    } else if (pressure < 1013.25f) {
        printf("可能有暴风雨\n");
    } else {
        printf("天气保持不变\n");
    }
}

// 设置气象测量值并通知观察者
void weatherData_setMeasurements(WeatherData* weatherData, float temperature, float humidity, float pressure) {
    weatherData->temperature = temperature;
    weatherData->humidity = humidity;
    weatherData->pressure = pressure;
    weatherData->vtable->notifyObservers(weatherData);
}

int main() {
    // 静态分配WeatherData
    WeatherData weatherData = {
        .vtable = &weatherDataVtable,
        .temperature = 0.0f,
        .humidity = 0.0f,
        .pressure = 1013.25f,
        .observerCount = 0
    };
    
    // 静态分配布告板
    DisplayElement currentDisplay = {
        .base = { .update = currentConditionsDisplay_update },
        .name = "当前状况"
    };
    
    DisplayElement statsDisplay = {
        .base = { .update = statisticsDisplay_update },
        .name = "统计信息"
    };
    
    DisplayElement forecastDisplay = {
        .base = { .update = forecastDisplay_update },
        .name = "天气预报"
    };
    
    printf("=== 气象站观察者模式示例 ===\n");
    
    // 注册观察者
    weatherData.vtable->registerObserver(&weatherData, &currentDisplay.base);
    weatherData.vtable->registerObserver(&weatherData, &statsDisplay.base);
    weatherData.vtable->registerObserver(&weatherData, &forecastDisplay.base);
    
    // 模拟天气变化
    printf("\n-- 第一次更新 --\n");
    weatherData_setMeasurements(&weatherData, 25.0f, 65.0f, 1015.0f);
    
    printf("\n-- 第二次更新 --\n");
    weatherData_setMeasurements(&weatherData, 28.0f, 70.0f, 1009.0f);
    
    // 移除一个观察者
    weatherData.vtable->removeObserver(&weatherData, &statsDisplay.base);
    
    printf("\n-- 第三次更新 (移除统计布告板后) --\n");
    weatherData_setMeasurements(&weatherData, 26.5f, 68.0f, 1011.0f);
    
    return 0;
}
