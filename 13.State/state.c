#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  // 新增头文件包含

// 前置声明状态结构体
typedef struct State State;

// 糖果机结构体
typedef struct {
    int count;           // 糖果数量
    bool hasQuarter;     // 是否有25分钱
    bool isWinner;       // 是否是赢家
    const State* state;  // 当前状态
} GumballMachine;

// 状态接口：定义所有可能的操作
struct State {
    void (*insertQuarter)(GumballMachine* machine);
    void (*ejectQuarter)(GumballMachine* machine);
    void (*turnCrank)(GumballMachine* machine);
    void (*dispense)(GumballMachine* machine);
};

// 状态实现：没有25分钱状态
void noQuarterInsertQuarter(GumballMachine* machine);
void noQuarterEjectQuarter(GumballMachine* machine);
void noQuarterTurnCrank(GumballMachine* machine);
void noQuarterDispense(GumballMachine* machine);

static const State NO_QUARTER_STATE = {
    .insertQuarter = noQuarterInsertQuarter,
    .ejectQuarter = noQuarterEjectQuarter,
    .turnCrank = noQuarterTurnCrank,
    .dispense = noQuarterDispense
};

// 状态实现：有25分钱状态
void hasQuarterInsertQuarter(GumballMachine* machine);
void hasQuarterEjectQuarter(GumballMachine* machine);
void hasQuarterTurnCrank(GumballMachine* machine);
void hasQuarterDispense(GumballMachine* machine);

static const State HAS_QUARTER_STATE = {
    .insertQuarter = hasQuarterInsertQuarter,
    .ejectQuarter = hasQuarterEjectQuarter,
    .turnCrank = hasQuarterTurnCrank,
    .dispense = hasQuarterDispense
};

// 状态实现：售出糖果状态
void soldStateInsertQuarter(GumballMachine* machine);
void soldStateEjectQuarter(GumballMachine* machine);
void soldStateTurnCrank(GumballMachine* machine);
void soldStateDispense(GumballMachine* machine);

static const State SOLD_STATE = {
    .insertQuarter = soldStateInsertQuarter,
    .ejectQuarter = soldStateEjectQuarter,
    .turnCrank = soldStateTurnCrank,
    .dispense = soldStateDispense
};

// 状态实现：糖果售罄状态
void soldOutStateInsertQuarter(GumballMachine* machine);
void soldOutStateEjectQuarter(GumballMachine* machine);
void soldOutStateTurnCrank(GumballMachine* machine);
void soldOutStateDispense(GumballMachine* machine);

static const State SOLD_OUT_STATE = {
    .insertQuarter = soldOutStateInsertQuarter,
    .ejectQuarter = soldOutStateEjectQuarter,
    .turnCrank = soldOutStateTurnCrank,
    .dispense = soldOutStateDispense
};

// 状态实现：赢家状态
void winnerStateInsertQuarter(GumballMachine* machine);
void winnerStateEjectQuarter(GumballMachine* machine);
void winnerStateTurnCrank(GumballMachine* machine);
void winnerStateDispense(GumballMachine* machine);

static const State WINNER_STATE = {
    .insertQuarter = winnerStateInsertQuarter,
    .ejectQuarter = winnerStateEjectQuarter,
    .turnCrank = winnerStateTurnCrank,
    .dispense = winnerStateDispense
};

// 初始化糖果机
void initGumballMachine(GumballMachine* machine, int count) {
    machine->count = count;
    machine->hasQuarter = false;
    machine->isWinner = false;
    if (count > 0) {
        machine->state = &NO_QUARTER_STATE;
    } else {
        machine->state = &SOLD_OUT_STATE;
    }
}

// 状态操作实现：没有25分钱状态
void noQuarterInsertQuarter(GumballMachine* machine) {
    printf("你投入了25分钱\n");
    machine->hasQuarter = true;
    machine->state = &HAS_QUARTER_STATE;
}

void noQuarterEjectQuarter(GumballMachine* machine) {
    printf("你还没有投入25分钱\n");
}

void noQuarterTurnCrank(GumballMachine* machine) {
    printf("你转动了曲柄，但是没有投入25分钱\n");
}

void noQuarterDispense(GumballMachine* machine) {
    printf("你需要先付款\n");
}

// 状态操作实现：有25分钱状态
void hasQuarterInsertQuarter(GumballMachine* machine) {
    printf("你不能再投入另一个25分钱\n");
}

void hasQuarterEjectQuarter(GumballMachine* machine) {
    printf("25分钱已退回\n");
    machine->hasQuarter = false;
    machine->state = &NO_QUARTER_STATE;
}

void hasQuarterTurnCrank(GumballMachine* machine) {
    printf("你转动了曲柄...\n");
    // 10%概率成为赢家
    machine->isWinner = (rand() % 10 == 0);
    machine->state = &SOLD_STATE;
}

void hasQuarterDispense(GumballMachine* machine) {
    printf("没有糖果发放\n");
}

// 状态操作实现：售出糖果状态
void soldStateInsertQuarter(GumballMachine* machine) {
    printf("请稍等，我们正在发放糖果\n");
}

void soldStateEjectQuarter(GumballMachine* machine) {
    printf("对不起，你已经转动了曲柄\n");
}

void soldStateTurnCrank(GumballMachine* machine) {
    printf("转动两次曲柄不会得到另一颗糖果！\n");
}

void soldStateDispense(GumballMachine* machine) {
    if (machine->count > 0) {
        machine->count--;
        printf("糖果滚出来了\n");
        
        if (machine->isWinner && machine->count > 0) {
            machine->count--;
            printf("恭喜你，你是赢家！额外获得一颗糖果！\n");
            machine->isWinner = false;
            
            if (machine->count > 0) {
                machine->hasQuarter = false;
                machine->state = &NO_QUARTER_STATE;
            } else {
                printf("Oops，糖果售罄了！\n");
                machine->state = &SOLD_OUT_STATE;
            }
        } else {
            if (machine->count > 0) {
                machine->hasQuarter = false;
                machine->state = &NO_QUARTER_STATE;
            } else {
                printf("Oops，糖果售罄了！\n");
                machine->state = &SOLD_OUT_STATE;
            }
        }
    } else {
        printf("Oops，糖果售罄了！\n");
        machine->state = &SOLD_OUT_STATE;
    }
}

// 状态操作实现：糖果售罄状态
void soldOutStateInsertQuarter(GumballMachine* machine) {
    printf("对不起，糖果已售罄\n");
}

void soldOutStateEjectQuarter(GumballMachine* machine) {
    printf("对不起，你还没有投入25分钱\n");
}

void soldOutStateTurnCrank(GumballMachine* machine) {
    printf("你转动了曲柄，但是没有糖果了\n");
}

void soldOutStateDispense(GumballMachine* machine) {
    printf("没有糖果发放\n");
}

// 状态操作实现：赢家状态
void winnerStateInsertQuarter(GumballMachine* machine) {
    printf("请稍等，我们正在发放糖果\n");
}

void winnerStateEjectQuarter(GumballMachine* machine) {
    printf("对不起，你已经转动了曲柄\n");
}

void winnerStateTurnCrank(GumballMachine* machine) {
    printf("转动两次曲柄不会得到另一颗糖果！\n");
}

void winnerStateDispense(GumballMachine* machine) {
    printf("恭喜你，你是赢家！你将得到两颗糖果！\n");
    
    if (machine->count > 0) {
        machine->count--;
        
        if (machine->count > 0) {
            machine->count--;
            printf("两颗糖果滚出来了\n");
        } else {
            printf("只发放了一颗糖果，糖果机已空\n");
        }
        
        machine->isWinner = false;
        
        if (machine->count > 0) {
            machine->hasQuarter = false;
            machine->state = &NO_QUARTER_STATE;
        } else {
            printf("Oops，糖果售罄了！\n");
            machine->state = &SOLD_OUT_STATE;
        }
    } else {
        printf("没有糖果发放\n");
        machine->state = &SOLD_OUT_STATE;
    }
}

// 测试程序
int main() {
    int i;
    // 初始化随机数种子
    srand(12345);
    
    // 创建并初始化糖果机，初始有5颗糖果
    GumballMachine machine;
    initGumballMachine(&machine, 5);
    
    printf("=== 测试糖果机 ===\n");
    printf("当前糖果数量: %d\n", machine.count);
    
    // 测试正常购买流程
    printf("\n-- 测试正常购买流程 --\n");
    machine.state->insertQuarter(&machine);
    machine.state->turnCrank(&machine);
    machine.state->dispense(&machine);
    printf("当前糖果数量: %d\n", machine.count);
    
    // 测试连续投入钱币
    printf("\n-- 测试连续投入钱币 --\n");
    machine.state->insertQuarter(&machine);
    machine.state->insertQuarter(&machine);
    machine.state->ejectQuarter(&machine);
    printf("当前糖果数量: %d\n", machine.count);
    
    // 测试多次购买直到售罄
    printf("\n-- 测试多次购买直到售罄 --\n");
    for (i = 0; i < 5; i++) {
        printf("\n购买尝试 %d:\n", i + 1);
        machine.state->insertQuarter(&machine);
        machine.state->turnCrank(&machine);
        machine.state->dispense(&machine);
        printf("当前糖果数量: %d\n", machine.count);
    }
    
    // 测试售罄状态
    printf("\n-- 测试售罄状态 --\n");
    machine.state->insertQuarter(&machine);
    machine.state->turnCrank(&machine);
    
    return 0;
}
