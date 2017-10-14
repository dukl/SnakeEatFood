
#ifndef _SNAKE_H_H_H  
#define _SNAKE_H_H_H  
  
//调节游戏界面大小，这里设置为15*15  
int const COL = 15;  
int const ROW = 15;  
  
//蛇节点  
typedef struct Node  
{  
    int x;  
    int y;  
    struct Node *pre;  
    struct Node *next;  
}NODE, *pNODE;  
  
//食物  
typedef struct Food  
{  
    int x;  
    int y;  
    char c;  
}FOOD, *pFOOD;  
  
//初始化，创建蛇的第一节  
pNODE InitSnake(void);  
  
//初始化食物成员  
FOOD InitFood(void);  
  
//蛇运动函数  
int MoveSnake(pNODE pHead, char c);  
  
//检查键盘按键  
char KbHit(char orient);  
  
//蛇吃到食物处理函数  
pNODE SnakeEatFood(pNODE pHead, pFOOD pFood);  
  
//打印游戏界面函数  
void Print(pNODE pHead, FOOD food);  
  
//游戏结束，释放内存函数  
void FreeMemory(pNODE *ppHead);  
  
#endif