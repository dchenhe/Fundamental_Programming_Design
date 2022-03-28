#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"user.h"

//函数声明
void gochess(int chess[][8], FILE* fp,int* option);
int judege_suit_go(int option, int chess[][8], FILE* fp);
int judge_go(int option, int chess[][8], FILE* fp, int row, int col);

//自定义折棋，三个棋子形成一竖+下左横即成功！

void gochess(int chess[][8], FILE* fp,int* option) {
	int c_row, c_col;
	int select;
	while (true) {


		/*先进行判断看是否有可执行棋步*/
		if (!judege_suit_go(*option, chess, fp)) {
			printf("\n*************************************************************************");
			printf("\n结束游戏请输入0，输入其余数字返回开始菜单:");
			scanf_s("%d", &select);
			if (select == 0) {
				printf("\n*************************************************************************\n");
				printf("\n游戏结束，谢谢使用！");
				exit(0);
			}
			else
				return;
		}

		if (!get_chess(option, chess, fp, &c_row, &c_col,3))
			return;//执行下棋操作，如果返回值为0，返回主菜单
		if (judge_go(*option, chess, fp, c_row, c_col)) {
			draw_c_board(chess);
			if (*option == 0) {
				printf("\n*************************************************************************");
				printf("\n黑棋形成三棋折线，黑棋胜！");
				printf("\n*************************************************************************");
				printf("\n结束游戏请输入0，输入其余数字返回开始菜单:");
				scanf_s("%d", &select);
				if (select == 0) {
					printf("\n*************************************************************************\n");
					printf("\n游戏结束，谢谢使用！");
					exit(0);
				}
				else
					return;
			}
			if (*option == 1) {
				printf("\n*************************************************************************");
				printf("\n白棋形成三棋折线，白棋胜！");
				printf("\n*************************************************************************");
				printf("\n结束游戏请输入0，输入其余数字返回开始菜单:");
				scanf_s("%d", &select);
				if (select == 0) {
					printf("\n*************************************************************************\n");
					printf("\n游戏结束，谢谢使用！");
					exit(0);
				}
				else
					return;
			}
		}
	}
}


//判断是否有可执行棋步
int judege_suit_go(int option, int chess[][8], FILE* fp) {
	int row, col, flag = 1;
	for (row = 0; row < 8; row++)
		for (col = 0; col < 8; col++)
			if (chess[row][col] == 0) {
				flag = 0;
				break;
			}
	if (flag) {
		draw_c_board(chess);
		printf("\n两者均无合法棋步！平局！");
		count_chess(chess);
		return 0;
	}
	else
		return 1;
}

int judge_go(int option, int chess[][8], FILE* fp, int row, int col) {
	int i;
	int flag = 0;
	if (option == 0) {//说明上局下的黑子
		//先向上查找
		i = row - 1;
		if (i >= 0)
			if (chess[i][col] == 2 && col + 1 < 8)
				if (chess[i][col + 1] == 2)
					flag = 1;
		//再向下查找
		i = row + 1;
		if (i < 8)
			if (chess[i][col] == 2 && col + 1 < 8)
				if (chess[i][col + 1] == 2)
					flag = 1;
		//再向左查找
		i = col - 1;
		if (i >= 0)
			if (chess[row][i] == 2 && row - 1 >= 0)
				if (chess[row - 1][i] == 2)
					flag = 1;
	}
	if (option == 1) {//说明上局下的白子
	    //先向上查找
		i = row - 1;
		if (i >= 0)
			if (chess[i][col] == 1 && col + 1 < 8)
				if (chess[i][col + 1] == 1)
					flag = 1;
		//再向下查找
		i = row + 1;
		if (i < 8)
			if (chess[i][col] == 1 && col + 1 < 8)
				if (chess[i][col + 1] == 1)
					flag = 1;
		//再向左查找
		i = col - 1;
		if (i >= 0)
			if (chess[row][i] == 1 && row - 1 >= 0)
				if (chess[row - 1][i] == 1)
					flag = 1;
	}
	return flag;
}
