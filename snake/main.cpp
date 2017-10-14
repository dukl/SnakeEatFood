#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
#include <conio.h>  
#include <Windows.h>  
#include "snake.h"//������(main)�е��õĺ�����������snake.hͷ�ļ��С���struct���ṹ�壩����洢FOOD��Snake��Ϣ
//������  
int main(void)  
{  
    char orien = 'a', get_char;  
    int game_over = 0;  
  
    FOOD food = InitFood();  
    pNODE head = InitSnake();  
  
    while (1)  
    {  
        head = SnakeEatFood(head, &food); //snake�Ե�ʳ������һ�� 
        get_char = KbHit(orien);  //��ð�������
        if (27 == get_char)  //27����xx��ascii��
        {  
            game_over = 1;  //�Ƿ������Ϸ�ı�־
            break;  
        }  
        else  
            orien = get_char;     
        game_over = MoveSnake(head, orien);  //�ƶ������ڵ��ƶ������е���Ϣ������洢����δͼ�λ���ʾ��
        if (game_over)  
            break;  
          
        system("cls");  
        Print(head, food);  
        Sleep(100); //ms����ˢ�����ʱ��  
    }  
    if (game_over)  
    {  
        printf("��Ϸ������\n");  
  
        FreeMemory(&head);  //�ͷŷ�������������ڴ棨��ֹ�ڴ�й¶��
        if (NULL == head)  
            printf("�ڴ��ͷųɹ���\n");  
        else  
            printf("�ڴ��ͷ�ʧ�ܣ�\n");  
    }  
    getch();  
    return 0;  
}  
//��ʼ���������ߵĵ�һ��  
pNODE InitSnake(void)  
{  
    pNODE pHead = (pNODE)malloc(sizeof(NODE));  //����ͷ����snakeͷ����Ϣ��
    srand((unsigned)(time(NULL)+1));  //�µ����������
  
    if (NULL == pHead)  
    {  
        printf("�ڴ����ʧ�ܣ�\n");  
        exit(-1);  
    }  
      
    pHead->x = rand() % ROW;  
    pHead->y = rand() % COL;  
    pHead->next = NULL;  
    pHead->pre = NULL;  
  
    return pHead;  
}  
//��ʼ��ʳ���Ա  
FOOD InitFood(void)  
{  
    FOOD food;  
    srand((unsigned)time(NULL));  //���������
  
    food.x = rand() % ROW;  //����0~14֮��������
    food.y = rand() % COL;  //����0~14֮��������
    food.c = 65 + rand()%26;  //����̨���ֵ���������ַ�
  
    return food;  
}  
//�߳Ե�ʳ�ﴦ����  
pNODE SnakeEatFood(pNODE pHead, pFOOD pFood)  
{  
    pNODE p_add = NULL, pt = NULL, rear = NULL;  
      
    if (pFood->x == pHead->x && pFood->y == pHead->y) //snakeͷ��food��ͬһλ�� 
    {  
        p_add = (pNODE)malloc(sizeof(NODE));  //�����ڴ棬��snake�������һ��β�͵���Ϣ
        if (NULL == p_add)  
        {  
            printf("�ڴ����ʧ�ܣ�\n");  
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
        //����ʳ���������ͷ��λ����  
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
//�����̰���  
char KbHit(char orient)  
{     
    char c;  
  
    if (kbhit())  
    {  
        c = getch();  //�Ӽ��̻���ַ�    
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
//���˶�����  
int MoveSnake(pNODE pHead, char c)  
{  
    INT game_over = 0;  //INT �� int
    pNODE pt = pHead;  
  
    //��ptָ����β  
    while (pt->next != NULL)  
    {  
        pt = pt->next;  
    }  
  
    //����β������ͷǰ��  
    while(pt != pHead)  
    {  
        pt->x = pt->pre->x;  
        pt->y = pt->pre->y;  
        pt = pt->pre;  
    }  
  
    if ('d' == c)  //����
    {  
        pHead->x += 1;  
        if (pHead->x >= ROW)  
        {  
            pHead->x -= ROW;  
        }  
    }  
  
    if ('a' == c)  //����
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
  
    //����ͷ����������Ϸ����  
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
//��ӡ��Ϸ���溯��  
void Print(pNODE pHead, FOOD food)  
{  
    int row = 0, col = 0, flag = 0;  
    pNODE pt = NULL;  
  
    printf("  ������ơ�����:w ��:s ��:a ��:d(Esc�˳�)\n  ");  
    for (row=0; row<ROW; row++)  
    {  
        printf("��");  
    }  
    putchar('\n');  
  
    for (col=0; col<COL; col++)  
    {  
        printf(" |");  
        for (row=0; row<ROW; row++)  
        {  
            pt = pHead;  
            flag = 0;  
            //��ӡ����  
            while (pt != NULL)  
            {  
                if (row == pt->x && col == pt->y)  
                {  
                    if (pt == pHead)  
                        printf("��");  
                    else  
                        printf("��");  
                    flag = 1;  
                    break;  
                }  
                pt = pt->next;  
            }  
            //��ӡ��ʳ��������ո�  
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
        printf("��");  
    }  
    putchar('\n');  
}  
//�ͷ��ڴ溯��  
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