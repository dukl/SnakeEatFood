
#ifndef _SNAKE_H_H_H  
#define _SNAKE_H_H_H  
  
//������Ϸ�����С����������Ϊ15*15  
int const COL = 15;  
int const ROW = 15;  
  
//�߽ڵ�  
typedef struct Node  
{  
    int x;  
    int y;  
    struct Node *pre;  
    struct Node *next;  
}NODE, *pNODE;  
  
//ʳ��  
typedef struct Food  
{  
    int x;  
    int y;  
    char c;  
}FOOD, *pFOOD;  
  
//��ʼ���������ߵĵ�һ��  
pNODE InitSnake(void);  
  
//��ʼ��ʳ���Ա  
FOOD InitFood(void);  
  
//���˶�����  
int MoveSnake(pNODE pHead, char c);  
  
//�����̰���  
char KbHit(char orient);  
  
//�߳Ե�ʳ�ﴦ����  
pNODE SnakeEatFood(pNODE pHead, pFOOD pFood);  
  
//��ӡ��Ϸ���溯��  
void Print(pNODE pHead, FOOD food);  
  
//��Ϸ�������ͷ��ڴ溯��  
void FreeMemory(pNODE *ppHead);  
  
#endif