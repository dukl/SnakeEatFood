#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
#include <conio.h>  
#include <Windows.h>  
#include "snake.h"//主函数(main)中调用的函数的声明在snake.h头文件中。由struct（结构体）打包存储FOOD和Snake信息
//主函数  
int main(void)  
{  
    char orien = 'a', get_char;  
    int game_over = 0;  
  
    FOOD food = InitFood();  
    pNODE head = InitSnake();  
  
    while (1)  
    {  
        head = SnakeEatFood(head, &food); //snake吃到食物后添加一节 
        get_char = KbHit(orien);  //获得按键操作
        if (27 == get_char)  //27代表xx的ascii码
        {  
            game_over = 1;  //是否结束游戏的标志
            break;  
        }  
        else  
            orien = get_char;     
        game_over = MoveSnake(head, orien);  //移动（现在的移动，所有的信息由链表存储，尚未图形化显示）
        if (game_over)  
            break;  
          
        system("cls");  
        Print(head, food);  
        Sleep(100); //ms级，刷屏间隔时间  
    }  
    if (game_over)  
    {  
        printf("游戏结束！\n");  
  
        FreeMemory(&head);  //释放分配的所有链表内存（防止内存泄露）
        if (NULL == head)  
            printf("内存释放成功！\n");  
        else  
            printf("内存释放失败！\n");  
    }  
    getch();  
    return 0;  
}  
//初始化，创建蛇的第一节  
pNODE InitSnake(void)  
{  
    pNODE pHead = (pNODE)malloc(sizeof(NODE));  //链表头（存snake头部信息）
    srand((unsigned)(time(NULL)+1));  //新的随机数种子
  
    if (NULL == pHead)  
    {  
        printf("内存分配失败！\n");  
        exit(-1);  
    }  
      
    pHead->x = rand() % ROW;  
    pHead->y = rand() % COL;  
    pHead->next = NULL;  
    pHead->pre = NULL;  
  
    return pHead;  
}  
//初始化食物成员  
FOOD InitFood(void)  
{  
    FOOD food;  
    srand((unsigned)time(NULL));  //随机数种子
  
    food.x = rand() % ROW;  //生成0~14之间的随机数
    food.y = rand() % COL;  //生成0~14之间的随机数
    food.c = 65 + rand()%26;  //控制台出现的随机两个字符
  
    return food;  
}  
//蛇吃到食物处理函数  
pNODE SnakeEatFood(pNODE pHead, pFOOD pFood)  
{  
    pNODE p_add = NULL, pt = NULL, rear = NULL;  
      
    if (pFood->x == pHead->x && pFood->y == pHead->y) //snake头和food在同一位置 
    {  
        p_add = (pNODE)malloc(sizeof(NODE));  //分配内存，存snake的新添的一节尾巴的信息
        if (NULL == p_add)  
        {  
            printf("内存分配失败！\n");  
            exit(-1);  
        }  
  
        pt = pHead;  
        while (pt->next != NULL)  
        {  
            pt = pt->next;  
        }  
        p_add->pre = pt;  
        p_add->next = NULL;  
        pt->next = p_add;  
  
        *pFood = InitFood();  
        //不让食物出现在蛇头的位置上  
        pt = pHead;  
        while (pt != NULL)  
        {  
            if (pFood->x == pHead->x && pFood->y == pHead->y)  
            {  
                *pFood = InitFood();  
                break;  
            }  
            pt = pt->next;  
        }  
    }  
  
    return pHead;  
}  
//检查键盘按键  
char KbHit(char orient)  
{     
    char c;  
  
    if (kbhit())  
    {  
        c = getch();  //从键盘获得字符    
        if (orient != 'd' && c == 'a')  
        {  
            orient = c;  
        }  
        else if (orient != 'a' && c == 'd')  
        {  
            orient = c;  
        }  
        else if (orient != 'w' && c == 's')  
        {  
            orient = c;  
        }  
        else if (orient != 's' && c == 'w')  
        {  
            orient = c;  
        }  
        else if (27 == c)  
        {  
            orient = c;  
        }  
    }  
  
    return orient;  
}  
//蛇运动函数  
int MoveSnake(pNODE pHead, char c)  
{  
    INT game_over = 0;  //INT 即 int
    pNODE pt = pHead;  
  
    //让pt指向蛇尾  
    while (pt->next != NULL)  
    {  
        pt = pt->next;  
    }  
  
    //从蛇尾向向蛇头前进  
    while(pt != pHead)  
    {  
        pt->x = pt->pre->x;  
        pt->y = pt->pre->y;  
        pt = pt->pre;  
    }  
  
    if ('d' == c)  //右移
    {  
        pHead->x += 1;  
        if (pHead->x >= ROW)  
        {  
            pHead->x -= ROW;  
        }  
    }  
  
    if ('a' == c)  //左移
    {  
        pHead->x -= 1;  
        if (pHead->x < 0)  
        {  
            pHead->x += ROW;  
        }  
    }  
      
    if ('s' == c)  
    {  
        pHead->y += 1;  
        if (pHead->y >= COL)  
        {  
            pHead->y -= COL;  
        }  
    }  
  
    if ('w' == c)  
    {  
        pHead->y -= 1;  
        if (pHead->y < 0)  
        {  
            pHead->y += COL;  
        }  
    }  
  
    //当蛇头碰到蛇身，游戏结束  
    pt = pHead->next;  
    while (pt != NULL)  
    {  
        if (pt->x == pHead->x && pt->y == pHead->y)  
        {  
            game_over = 1;  
        }  
        pt = pt->next;  
    }  
  
    return game_over;  
}  
//打印游戏界面函数  
void Print(pNODE pHead, FOOD food)  
{  
    int row = 0, col = 0, flag = 0;  
    pNODE pt = NULL;  
  
    printf("  方向控制——上:w 下:s 左:a 右:d(Esc退出)\n  ");  
    for (row=0; row<ROW; row++)  
    {  
        printf("—");  
    }  
    putchar('\n');  
  
    for (col=0; col<COL; col++)  
    {  
        printf(" |");  
        for (row=0; row<ROW; row++)  
        {  
            pt = pHead;  
            flag = 0;  
            //打印出蛇  
            while (pt != NULL)  
            {  
                if (row == pt->x && col == pt->y)  
                {  
                    if (pt == pHead)  
                        printf("■");  
                    else  
                        printf("□");  
                    flag = 1;  
                    break;  
                }  
                pt = pt->next;  
            }  
            //打印出食物或两个空格  
            if (0 == flag)  
            {  
                if (row == food.x && col == food.y)  
                {  
                    putchar(food.c);  
                    putchar(food.c);  
                    continue;  
                }  
                printf("  ");  
            }         
        }  
        printf("|");  
        putchar('\n');  
    }  
      
    printf("  ");  
    for (row=0; row<ROW; row++)  
    {  
        printf("—");  
    }  
    putchar('\n');  
}  
//释放内存函数  
void FreeMemory(pNODE *ppHead)  
{  
    pNODE p_delete = NULL, pt = NULL;  
  
    while (*ppHead != NULL)  
    {  
        pt = (*ppHead)->next;  
        if (pt != NULL)  
        {  
            pt->pre = NULL;  
        }     
        p_delete = *ppHead;  
        free(p_delete);  
        p_delete = NULL;  
        *ppHead = pt;  
    }  
}  