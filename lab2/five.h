#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"user.h"

//函数声明
void five(int chess[][8], FILE* fp,int* option);
int judge_five(int option, int chess[][8], FILE* fp, int row, int col);
int judege_suit_five(int option, int chess[][8], FILE* fp);

//五子棋游戏进入
void five(int chess[][8], FILE* fp,int* option) {
	int c_row, c_col;
	int select;
	while (true) {


		/*先进行判断看是否有可执行棋步*/
		if (!judege_suit_five(*option, chess, fp)) {
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

		if (!get_chess(option, chess, fp, &c_row, &c_col,2))
			return;//执行下棋操作，如果返回值为0，返回主菜单
		if (judge_five(*option, chess, fp, c_row, c_col)) {
			draw_c_board(chess);
			if (*option == 0) {
				printf("\n*************************************************************************");
				printf("\n黑棋五子连珠，黑棋胜！");
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
				printf("\n白棋五子连珠，白棋胜！");
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

//规则判定函数
int judge_five(int option, int chess[][8], FILE* fp, int row, int col) {
	int i, p,j;
	int flag = 0;
	if (option == 0) {//说明上局下的黑子
		/*竖直向上查找*/
		for (i = row - 1, j = 0; i >= 0; i--)
			if (chess[i][col] != 2)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*竖直向下查找*/
		for (i = row + 1, j = 0; i < 8; i++)
			if (chess[i][col] != 2)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*水平向右查找*/
		for (i = col + 1, j = 0; i < 8; i++)
			if (chess[row][i] != 2)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*水平向左查找*/
		for (i = col - 1, j = 0; i >= 0; i--)
			if (chess[row][i] != 2)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*左上角*/
		for (i = row - 1, p = col - 1, j = 0; i >= 0 && p >= 0; i--, p--)
			if (chess[i][p] != 2)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*左下角*/
		for (i = row + 1, p = col - 1, j = 0; i < 8 && p >= 0; i++, p--)
			if (chess[i][p] != 2)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*右上角*/
		for (i = row - 1, p = col + 1, j = 0; i >= 0 && p < 8; i--, p++)
			if (chess[i][p] != 2)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*右下角*/
		for (i = row + 1, p = col + 1,j=0; i < 8 && p < 8; i++, p++)
			if (chess[i][p] != 2)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
	}

	if (option == 1) {//说明上局下的白子
		/*竖直向上查找*/
		for (i = row - 1, j = 0; i >= 0; i--)
			if (chess[i][col] != 1)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*竖直向下查找*/
		for (i = row + 1, j = 0; i < 8; i++)
			if (chess[i][col] != 1)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*水平向右查找*/
		for (i = col + 1, j = 0; i < 8; i++)
			if (chess[row][i] != 1)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*水平向左查找*/
		for (i = col - 1, j = 0; i >= 0; i--)
			if (chess[row][i] != 1)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*左上角*/
		for (i = row - 1, p = col - 1, j = 0; i >= 0 && p >= 0; i--, p--)
			if (chess[i][p] != 1)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*左下角*/
		for (i = row + 1, p = col - 1, j = 0; i < 8 && p >= 0; i++, p--)
			if (chess[i][p] != 1)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*右上角*/
		for (i = row - 1, p = col + 1, j = 0; i >= 0 && p < 8; i--, p++)
			if (chess[i][p] != 1)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*右下角*/
		for (i = row + 1, p = col + 1, j = 0; i < 8 && p < 8; i++, p++)
			if (chess[i][p] != 1)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
	}
	return flag;
}

//判断是否有可执行棋步
int judege_suit_five(int option, int chess[][8], FILE* fp) {
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
