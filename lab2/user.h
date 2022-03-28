#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"inverse.h"
#include"five.h"
#include"gochess.h"
#include"chess.h"

//函数声明
void initial_game(int chess[][8], FILE* fp);
int select_game(int chess[][8], FILE* fp);

//游戏界面初始化
void initial_game(int chess[][8], FILE* fp) {
	int option = 1;//默认黑棋先手
	int i;
	int s;
	int select;
	for (int p = 0; p < 8; p++)
		for (int q = 0; q < 8; q++)
			chess[p][q] = 0;//棋局初始化
	while (true) {
		system("cls");
		printf("*************************************************************************\n");
		printf("                          欢迎进入棋类游戏\n");
		printf("                           1.开始新游戏\n");
		printf("                           2.读取存档\n");
		printf("                           3.退出游戏\n");
		printf("*************************************************************************\n");
		printf("                           请输入您的选择：（输入对应数字即可）");
		scanf_s("%d", &i);
		if (i == 1) {
			option = 1;
			for (int p = 0; p < 8; p++)
				for (int q = 0; q < 8; q++)
					chess[p][q] = 0;//棋局初始化
			s = select_game(chess, fp);
			if (s == 1) {
				inverse(chess, fp,&option);
				continue;
			}//翻转棋
			if (s == 2) {
				five(chess, fp,&option);
				continue;
			}//五子棋
			if (s == 3) {
				gochess(chess, fp,&option);
				continue;
			}//围棋
		}//选择游戏类型

		//读取存档
		else if (i == 2) {
			select=read_file(chess, fp,&option);
			if (select == 1) {
				inverse(chess, fp,&option);
				continue;
			}
			else if (select == 2) {
				five(chess, fp,&option);
				continue;
			}
			else if (select == 3) {
				gochess(chess, fp,&option);
				continue;
			}
			else
				continue;
		}
		else if (i == 3) {
			system("cls");
			printf("*************************************************************************\n");
			printf("谢谢使用！游戏已退出！\n");
			printf("*************************************************************************\n");
			exit(0);
		}
	}
}

//游戏种类选择
int select_game(int chess[][8],FILE *fp){
	int i;
	system("cls");
	printf("*************************************************************************\n");
	printf("                          请选择一种棋类游戏\n");
	printf("                           1.翻转棋\n");
	printf("                           2.五子棋\n");
	printf("                           3.创新折棋\n");
	printf("                           4.返回上级菜单\n");
	printf("*************************************************************************\n");
	printf("                           请输入您的选择：（输入对应数字即可）");
	scanf_s("%d", &i);
	while(i != 1 && i != 2 && i != 3 && i != 4) {
		printf("*************************************************************************\n");
		printf("                           非法输入，请重新输入：");
		scanf_s("%d", &i);
	}
	return i;
}
