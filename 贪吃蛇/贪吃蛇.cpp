// 贪吃蛇.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
int map[20][20];
int foodx;
int foody;
int headx;
int heady;
int direct = 0;
int bodylong=1;
void initmap();
void printmap();
void setbody();
int gogogo();
void setfood();
struct sbody
{
	int x;
	int y;
	struct sbody* next;
};
struct sbody *body;
int main()
{
	int goon = 1;
	body = (struct sbody*)malloc(sizeof(struct sbody));
	body->x = 10;
	body->y = 10;
	headx = 10;
	heady = 10;
	body->next = NULL;
	srand(time(NULL));
	initmap();
	setfood();
	printf("按任意键开始\n");
	getch();
	while (goon == 1)
	{
		initmap();
		setbody();
		printmap();
		if (kbhit()!=0)
		{
			switch (getch())
			{
			case '8':
				direct = 0;
				break;
			case '5':
				direct = 2;
				break;
			case '4':
				direct = 3;
				break;
			case '6':
				direct = 1;
				break;
			}
		}
		goon=gogogo();
		Sleep(100);
	}
	printf("死了\n");
	return 0;
}
void initmap()
{
	int i, j;
	for (i = 0; i <= 19; i++)
	{
		for (j = 0; j <= 19; j++)
		{
			map[i][j] = 0;
		}
	}
	for (i = 0; i <= 19; i++)
	{
		map[i][0] = 1;
		map[i][19] = 1;
		map[0][i] = 1;
		map[19][i] = 1;
	}
	map[foodx][foody] = 3;
}
void printmap()
{
	int i, j;
	system("cls");
	for (j = 0; j <= 19; j++)
	{
		for (i = 0; i <= 19; i++)
		{
			switch (map[i][j])
			{
			case 0:
				printf("  ");
				break;
			case 1:
				printf("╊");
				break;
			case 2:
				printf("▉");
				break;
			case 3:
				printf("×");
				break;
			}
		}
		printf("\n");
	}
	printf("\n蛇身长度：%d\n", bodylong);
}
void setbody()
{
	struct sbody *t;
	initmap();
	t = body;
	while (t != NULL)
	{
		map[t->x][t->y] = 2;
		t = t->next;
	}
}
int gogogo()
{
	int nextx;
	int nexty;
	struct sbody *t;
	t = body;
	switch (direct)
	{
	case 0:
		nextx = headx;
		nexty = heady - 1;
		break;
	case 1:
		nextx = headx+1;
		nexty = heady ;
		break;
	case 2:
		nextx = headx;
		nexty = heady + 1;
		break;
	case 3:
		nextx = headx-1;
		nexty = heady ;
		break;
	}
	if (nextx < 0 || nexty < 0 || nextx>19 || nexty>19)
	{
		return 0;
	}
	
	switch (map[nextx][nexty])
	{
	case 0:
		while (t->next != NULL)
		{
			t->x = t->next->x;
			t->y = t->next->y;
			t = t->next;
		}
		t->x = nextx;
		t->y = nexty;
		break;
	case 1:
		return 0;
		break;
	case 2:
		return 0;
		break;
	case 3:
		while (t ->next!= NULL)
		{
			t = t->next;
		}
		t->next = (struct sbody*)malloc(sizeof(struct sbody));
		t = t->next;
		t->x = nextx;
		t->y = nexty;
		t->next = NULL;
		bodylong++;
		setfood();
		break;
	}
	headx = nextx;
	heady = nexty;
	return 1;
}
void setfood()
{
	int trynum = 0;
	int tryx;
	int tryy;
	int ifsuc=0;
	int i, j;
	while (trynum<=100)
	{
		tryx = rand() % 20;
		tryy = rand() % 20;
		if (map[tryx][tryy] == 0)
		{
			ifsuc = 1;
			break;
		}
		trynum++;
	}
	if (ifsuc == 0)
	{
		for (i = 0; i <= 19; i++)
		{
			for (j = 0; j <= 19; j++)
			{
				if (map[i][j] == 0)
					break;
			}
		}
		tryx = i;
		tryy = j;
	}
	map[tryx][tryy] = 3;
	foodx = tryx;
	foody = tryy;
}
