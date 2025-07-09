#include <stdio.h>
#include <stdbool.h>

// 定义电器设备
typedef struct {
    const char* name;
    void (*on)(void*);
    void (*off)(void*);
} Device;

// 电灯设备
typedef struct {
    Device base;
    bool isOn;
} Light;

void lightOn(void* light) {
    Light* l = (Light*)light;
    l->isOn = true;
    printf("%s 已打开\n", l->base.name);
}

void lightOff(void* light) {
    Light* l = (Light*)light;
    l->isOn = false;
    printf("%s 已关闭\n", l->base.name);
}

// 音响设备
typedef struct {
    Device base;
    bool isOn;
    int volume;
} Stereo;

void stereoOn(void* stereo) {
    Stereo* s = (Stereo*)stereo;
    s->isOn = true;
    printf("%s 已打开\n", s->base.name);
}

void stereoOff(void* stereo) {
    Stereo* s = (Stereo*)stereo;
    s->isOn = false;
    printf("%s 已关闭\n", s->base.name);
}

// 命令接口
typedef struct {
    void (*execute)(void*);
    void (*undo)(void*);
} Command;

// 电灯开命令
typedef struct {
    Command base;
    Light* light;
    bool lastState;
} LightOnCommand;

void lightOnExecute(void* cmd) {
    LightOnCommand* loc = (LightOnCommand*)cmd;
    loc->lastState = loc->light->isOn;
    lightOn(loc->light);
}

void lightOnUndo(void* cmd) {
    LightOnCommand* loc = (LightOnCommand*)cmd;
    if (loc->lastState) {
        lightOn(loc->light);
    } else {
        lightOff(loc->light);
    }
}

// 电灯关命令
typedef struct {
    Command base;
    Light* light;
    bool lastState;
} LightOffCommand;

void lightOffExecute(void* cmd) {
    LightOffCommand* loc = (LightOffCommand*)cmd;
    loc->lastState = loc->light->isOn;
    lightOff(loc->light);
}

void lightOffUndo(void* cmd) {
    LightOffCommand* loc = (LightOffCommand*)cmd;
    if (loc->lastState) {
        lightOn(loc->light);
    } else {
        lightOff(loc->light);
    }
}

// 音响开命令
typedef struct {
    Command base;
    Stereo* stereo;
    bool lastState;
    int lastVolume;
} StereoOnCommand;

void stereoOnExecute(void* cmd) {
    StereoOnCommand* soc = (StereoOnCommand*)cmd;
    soc->lastState = soc->stereo->isOn;
    soc->lastVolume = soc->stereo->volume;
    stereoOn(soc->stereo);
    soc->stereo->volume = 11; // 设置默认音量
    printf("%s 音量设置为 %d\n", soc->stereo->base.name, soc->stereo->volume);
}

void stereoOnUndo(void* cmd) {
    StereoOnCommand* soc = (StereoOnCommand*)cmd;
    if (soc->lastState) {
        stereoOn(soc->stereo);
        soc->stereo->volume = soc->lastVolume;
        printf("%s 音量恢复为 %d\n", soc->stereo->base.name, soc->stereo->volume);
    } else {
        stereoOff(soc->stereo);
    }
}

// 音响关命令
typedef struct {
    Command base;
    Stereo* stereo;
    bool lastState;
    int lastVolume;
} StereoOffCommand;

void stereoOffExecute(void* cmd) {
    StereoOffCommand* soc = (StereoOffCommand*)cmd;
    soc->lastState = soc->stereo->isOn;
    soc->lastVolume = soc->stereo->volume;
    stereoOff(soc->stereo);
}

void stereoOffUndo(void* cmd) {
    StereoOffCommand* soc = (StereoOffCommand*)cmd;
    if (soc->lastState) {
        stereoOn(soc->stereo);
        soc->stereo->volume = soc->lastVolume;
        printf("%s 音量恢复为 %d\n", soc->stereo->base.name, soc->stereo->volume);
    } else {
        stereoOff(soc->stereo);
    }
}

// 空命令（用于初始化遥控器插槽）
typedef struct {
    Command base;
} NoCommand;

void noExecute(void* cmd) {
    printf("无命令执行\n");
}

void noUndo(void* cmd) {
    printf("无命令可撤销\n");
}

// 遥控器
#define MAX_COMMANDS 7

typedef struct {
    Command* onCommands[MAX_COMMANDS];
    Command* offCommands[MAX_COMMANDS];
    Command* lastCommand;
} RemoteControl;

void initRemoteControl(RemoteControl* remote) {
    NoCommand noCmd;
    int i;
    noCmd.base.execute = noExecute;
    noCmd.base.undo = noUndo;
    
    for (i = 0; i < MAX_COMMANDS; i++) {
        remote->onCommands[i] = (Command*)&noCmd;
        remote->offCommands[i] = (Command*)&noCmd;
    }
    remote->lastCommand = (Command*)&noCmd;
}

void setCommand(RemoteControl* remote, int slot, Command* onCmd, Command* offCmd) {
    if (slot >= 0 && slot < MAX_COMMANDS) {
        remote->onCommands[slot] = onCmd;
        remote->offCommands[slot] = offCmd;
    }
}

void pressOnButton(RemoteControl* remote, int slot) {
    if (slot >= 0 && slot < MAX_COMMANDS) {
        remote->onCommands[slot]->execute(remote->onCommands[slot]);
        remote->lastCommand = remote->onCommands[slot];
    }
}

void pressOffButton(RemoteControl* remote, int slot) {
    if (slot >= 0 && slot < MAX_COMMANDS) {
        remote->offCommands[slot]->execute(remote->offCommands[slot]);
        remote->lastCommand = remote->offCommands[slot];
    }
}

void pressUndoButton(RemoteControl* remote) {
    remote->lastCommand->undo(remote->lastCommand);
}

// 测试主函数
int main() {
    // 静态分配设备和命令对象
    Light livingRoomLight = {
        .base = {
            .name = "客厅电灯",
            .on = lightOn,
            .off = lightOff
        },
        .isOn = false
    };
    
    Light kitchenLight = {
        .base = {
            .name = "厨房电灯",
            .on = lightOn,
            .off = lightOff
        },
        .isOn = false
    };
    
    Stereo livingRoomStereo = {
        .base = {
            .name = "客厅音响",
            .on = stereoOn,
            .off = stereoOff
        },
        .isOn = false,
        .volume = 0
    };
    
    LightOnCommand livingRoomLightOn = {
        .base = {
            .execute = lightOnExecute,
            .undo = lightOnUndo
        },
        .light = &livingRoomLight
    };
    
    LightOffCommand livingRoomLightOff = {
        .base = {
            .execute = lightOffExecute,
            .undo = lightOffUndo
        },
        .light = &livingRoomLight
    };
    
    LightOnCommand kitchenLightOn = {
        .base = {
            .execute = lightOnExecute,
            .undo = lightOnUndo
        },
        .light = &kitchenLight
    };
    
    LightOffCommand kitchenLightOff = {
        .base = {
            .execute = lightOffExecute,
            .undo = lightOffUndo
        },
        .light = &kitchenLight
    };
    
    StereoOnCommand stereoOn = {
        .base = {
            .execute = stereoOnExecute,
            .undo = stereoOnUndo
        },
        .stereo = &livingRoomStereo
    };
    
    StereoOffCommand stereoOff = {
        .base = {
            .execute = stereoOffExecute,
            .undo = stereoOffUndo
        },
        .stereo = &livingRoomStereo
    };
    
    // 初始化遥控器
    RemoteControl remote;
    initRemoteControl(&remote);
    
    // 设置命令
    setCommand(&remote, 0, (Command*)&livingRoomLightOn, (Command*)&livingRoomLightOff);
    setCommand(&remote, 1, (Command*)&kitchenLightOn, (Command*)&kitchenLightOff);
    setCommand(&remote, 2, (Command*)&stereoOn, (Command*)&stereoOff);
    
    // 测试遥控器
    printf("=== 测试遥控器 ===\n");
    
    printf("\n按下客厅电灯开启按钮:\n");
    pressOnButton(&remote, 0);
    
    printf("\n按下客厅电灯关闭按钮:\n");
    pressOffButton(&remote, 0);
    
    printf("\n按下撤销按钮:\n");
    pressUndoButton(&remote);
    
    printf("\n按下厨房电灯开启按钮:\n");
    pressOnButton(&remote, 1);
    
    printf("\n按下音响开启按钮:\n");
    pressOnButton(&remote, 2);
    
    printf("\n按下撤销按钮:\n");
    pressUndoButton(&remote);
    
    printf("\n按下音响关闭按钮:\n");
    pressOffButton(&remote, 2);
    
    printf("\n按下撤销按钮:\n");
    pressUndoButton(&remote);
    
    return 0;
}    