#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"chess.h"
#include"user.h"

//函数声明
void inverse(int chess[][8], FILE* fp,int *option);
void count_chess(int chess[][8]);
int judege_suit_inverse(int* option, int chess[][8], FILE* fp);
int judge_inverse(int option, int chess[][8], FILE* fp, int row, int col);

//翻转棋游戏进入
void inverse(int chess[][8], FILE* fp,int *option) {
	int c_row, c_col;
	int select;
	if (chess[3][3] == 0) {
		chess[3][3] = 1;//棋局中1表示白子 2表示黑子
		chess[3][4] = 2;
		chess[4][3] = 2;
		chess[4][4] = 1;
	}//无存档 进行翻转棋初始化，否则直接开始下棋
	while (true) {

		/*先进行判断看是否有可执行棋步*/
		if (!judege_suit_inverse(option, chess, fp)) {
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

		if (!get_chess(option, chess, fp, &c_row, &c_col,1))
			return;//执行下棋操作，如果返回值为0，返回主菜单
		if (!judge_inverse(*option, chess, fp, c_row, c_col)) {
			printf("\n*************************************************************************\n");
			printf("不合法棋步！请重新操作！ 按任意键继续~");
			if (*option == 1)
				*option = 0;
			else
				*option = 1;
			chess[c_row][c_col] = 0;
			getchar();
			getchar();
			continue;
		};
	}
}

//棋盘上棋子计数函数
void count_chess(int chess[][8]) {
	int w=0,b=0,space=0;
	for (int row = 0; row < 8; row++)
		for (int col = 0; col < 8; col++) {
			if (chess[row][col] == 1)
				w++;
			else if (chess[row][col] == 2)
				b++;
			else
				space++;
		}
	if (w == b)
		printf("\n两者剩余棋子数相同！平局！");
	else if (w > b)
		printf("\n白棋棋子多，白棋胜！");
	else
		printf("\n黑棋棋子多，黑棋胜！");
}

//判断是否有可执行棋步
int judege_suit_inverse(int* option, int chess[][8], FILE* fp) {
	int i, p;
	int flag_b = 0, flag_w = 0;
	for (int row = 0; row < 8; row++)
		for (int col = 0; col < 8; col++) {
			if (chess[row][col] != 0)
				continue;
			/*竖直向上查找*/
			for (i = row - 1; i >= 0; i--)
				if (chess[i][col] == 2 || chess[i][col] == 0)
					break;
			if (chess[i][col] != 0 && i >= 0 && i != row - 1) {
				flag_b = 1;
			}
			/*竖直向下查找*/
			for (i = row + 1; i < 8; i++)
				if (chess[i][col] == 2 || chess[i][col] == 0)
					break;
			if (chess[i][col] != 0 && i < 8 && i != row + 1) {
				flag_b = 1;
			}
			/*水平向右查找*/
			for (i = col + 1; i < 8; i++)
				if (chess[row][i] == 2 || chess[row][i] == 0)
					break;
			if (chess[row][i] != 0 && i < 8 && i != col + 1) {
				flag_b = 1;
			}
			/*水平向左查找*/
			for (i = col - 1; i >= 0; i--)
				if (chess[row][i] == 2 || chess[row][i] == 0)
					break;
			if (chess[row][i] != 0 && i >= 0 && i != col - 1) {
				flag_b = 1;
			}
			/*左上角*/
			for (i = row - 1, p = col - 1; i >= 0 && p >= 0; i--, p--)
				if (chess[i][p] == 2 || chess[i][p] == 0)
					break;
			if (chess[i][p] != 0 && i >= 0 && p >= 0 && i != row - 1 && p != col - 1) {
				flag_b = 1;
			}
			/*左下角*/
			for (i = row + 1, p = col - 1; i < 8 && p >= 0; i++, p--)
				if (chess[i][p] == 2 || chess[i][p] == 0)
					break;
			if (chess[i][p] != 0 && i < 8 && p >= 0 && i != row + 1 && p != col - 1) {
				flag_b = 1;
			}
			/*右上角*/
			for (i = row - 1, p = col + 1; i >= 0 && p < 8; i--, p++)
				if (chess[i][p] == 2 || chess[i][p] == 0)
					break;
			if (chess[i][p] != 0 && i >= 0 && p < 8 && i != row - 1 && p != col + 1) {
				flag_b = 1;
			}
			/*右下角*/
			for (i = row + 1, p = col + 1; i < 8 && p < 8; i++, p++)
				if (chess[i][p] == 2 || chess[i][p] == 0)
					break;
			if (chess[i][p] != 0 && i < 8 && p < 8 && i != row + 1 && p != col + 1) {
				flag_b = 1;
			}


			/*竖直向上查找*/
			for (i = row - 1; i >= 0; i--)
				if (chess[i][col] == 1 || chess[i][col] == 0)
					break;
			if (chess[i][col] != 0 && i >= 0 && i != row - 1) {
				flag_w = 1;
			}
			/*竖直向下查找*/
			for (i = row + 1; i < 8; i++)
				if (chess[i][col] == 1 || chess[i][col] == 0)
					break;
			if (chess[i][col] != 0 && i < 8 && i != row + 1) {
				flag_w = 1;
			}
			/*水平向右查找*/
			for (i = col + 1; i < 8; i++)
				if (chess[row][i] == 1 || chess[row][i] == 0)
					break;
			if (chess[row][i] != 0 && i < 8 && i != col + 1) {
				flag_w = 1;
			}
			/*水平向左查找*/
			for (i = col - 1; i >= 0; i--)
				if (chess[row][i] == 1 || chess[row][i] == 0)
					break;
			if (chess[row][i] != 0 && i >= 0 && i != col - 1) {
				flag_w = 1;
			}
			/*左上角*/
			for (i = row - 1, p = col - 1; i >= 0 && p >= 0; i--, p--)
				if (chess[i][p] == 1 || chess[i][p] == 0)
					break;
			if (chess[i][p] != 0 && i >= 0 && p >= 0 && i != row - 1 && p != col - 1) {
				flag_w = 1;
			}
			/*左下角*/
			for (i = row + 1, p = col - 1; i < 8 && p >= 0; i++, p--)
				if (chess[i][p] == 1 || chess[i][p] == 0)
					break;
			if (chess[i][p] != 0 && i < 8 && p >= 0 && i != row + 1 && p != col - 1) {
				flag_w = 1;
			}
			/*右上角*/
			for (i = row - 1, p = col + 1; i >= 0 && p < 8; i--, p++)
				if (chess[i][p] == 1 || chess[i][p] == 0)
					break;
			if (chess[i][p] != 0 && i >= 0 && p < 8 && i != row - 1 && p != col + 1) {
				flag_w = 1;
			}
			/*右下角*/
			for (i = row + 1, p = col + 1; i < 8 && p < 8; i++, p++)
				if (chess[i][p] == 1 || chess[i][p] == 0)
					break;
			if (chess[i][p] != 0 && i < 8 && p < 8 && i != row + 1 && p != col + 1) {
				flag_w = 1;
			}
		}
		if (flag_b && flag_w)
			return 1;
		else if(flag_b==0&&flag_w==0) {
			draw_c_board(chess);
			printf("\n两者均无合法棋步！");
			count_chess(chess);
			return 0;
		}
		else if (flag_b) {
			draw_c_board(chess);
			fflush(stdin);
			printf("白棋已经没有合法棋步，由黑棋继续落子\n按任意键继续");
			getchar();
			getchar();
			*option = 1;
			return 1;
		}
		else if (flag_w) {
			draw_c_board(chess);
			fflush(stdin);
			printf("黑棋已经没有合法棋步，由白棋继续落子\n按任意键继续");
			getchar();
			getchar();
			*option = 0;
			return 1;
		}
}

//规则判定函数
int judge_inverse(int option,int chess[][8], FILE* fp,int row,int col) {
	int i,p,q,j;
	int flag=0;
	if (option == 0) {//说明上局下的黑子
		/*竖直向上查找*/
		for (i = row - 1; i >= 0; i--)
			if (chess[i][col] == 2|| chess[i][col] == 0)
				break;
		if (chess[i][col] != 0 && i >= 0&&i!=row-1) {
			for (j = row - 1; j > i; j--)
				chess[j][col] = 2;
			flag = 1;
		}
		/*竖直向下查找*/
		for (i = row + 1; i<8; i++)
			if (chess[i][col] == 2 || chess[i][col] == 0)
				break;
		if (chess[i][col] != 0 && i < 8 && i != row + 1) {
			for (j = row + 1; j < i; j++)
				chess[j][col] = 2;
			flag = 1;
		}
		/*水平向右查找*/
		for (i = col + 1; i < 8; i++)
			if (chess[row][i] == 2 || chess[row][i] == 0)
				break;
		if (chess[row][i] != 0 && i < 8 && i != col + 1) {
			for (j = col + 1; j < i; j++)
				chess[row][j] = 2;
			flag = 1;
		}
		/*水平向左查找*/
		for (i = col - 1; i >=0; i--)
			if (chess[row][i] == 2 || chess[row][i] == 0)
				break;
		if (chess[row][i] != 0 && i >= 0 && i != col - 1) {
			for (j = col - 1; j > i; j--)
				chess[row][j] = 2;
			flag = 1;
		}
		/*左上角*/
		for (i = row - 1,p=col-1; i >= 0&&p>=0; i--,p--)
			if (chess[i][p] == 2 || chess[i][p] == 0)
				break;
		if (chess[i][p] != 0 && i >= 0&&p>=0 && i != row - 1&&p!=col-1) {
			for (j = row - 1,q=col-1; j > i&&q>p; j--,q--)
				chess[j][q] = 2;
			flag = 1;
		}
		/*左下角*/
		for (i = row + 1, p = col - 1; i < 8 && p >= 0; i++, p--)
			if (chess[i][p] == 2 || chess[i][p] == 0)
				break;
		if (chess[i][p] != 0 && i < 8 && p >= 0 && i != row + 1 && p != col - 1) {
			for (j = row + 1,q = col - 1; j < i&& q > p; j++, q--)
				chess[j][q] = 2;
			flag = 1;
		}
		/*右上角*/
		for (i = row - 1, p = col + 1; i >= 0 && p < 8; i--, p++)
			if (chess[i][p] == 2 || chess[i][p] == 0)
				break;
		if (chess[i][p] != 0 && i >= 0 && p < 8 && i != row - 1 && p != col + 1) {
			for (j = row - 1,q = col + 1; j > i&&q < p; j--, q++)
				chess[j][q] = 2;
			flag = 1;
		}
		/*右下角*/
		for (i = row + 1, p = col + 1; i < 8 && p < 8; i++, p++)
			if (chess[i][p] == 2 || chess[i][p] == 0)
				break;
		if (chess[i][p] != 0 && i < 8 && p < 8 && i != row + 1 && p != col + 1) {
			for (j = row + 1,q = col + 1; j < i&&q < p; j++, q++)
				chess[j][q] = 2;
			flag = 1;
		}
	}
	if (option == 1) {//说明上局下的白子
		/*竖直向上查找*/
		for (i = row - 1; i >= 0; i--)
			if (chess[i][col] == 1 || chess[i][col] == 0)
				break;
		if (chess[i][col] != 0 && i >= 0 && i != row - 1) {
			for (j = row - 1; j > i; j--)
				chess[j][col] = 1;
			flag = 1;
		}
		/*竖直向下查找*/
		for (i = row + 1; i < 8; i++)
			if (chess[i][col] == 1 || chess[i][col] == 0)
				break;
		if (chess[i][col] != 0 && i < 8 && i != row + 1) {
			for (j = row + 1; j < i; j++)
				chess[j][col] = 1;
			flag = 1;
		}
		/*水平向右查找*/
		for (i = col + 1; i < 8; i++)
			if (chess[row][i] == 1 || chess[row][i] == 0)
				break;
		if (chess[row][i] != 0 && i < 8 && i != col + 1) {
			for (j = col + 1; j < i; j++)
				chess[row][j] = 1;
			flag = 1;
		}
		/*水平向左查找*/
		for (i = col - 1; i >= 0; i--)
			if (chess[row][i] == 1 || chess[row][i] == 0)
				break;
		if (chess[row][i] != 0 && i >= 0 && i != col - 1) {
			for (j = col - 1; j > i; j--)
				chess[row][j] = 1;
			flag = 1;
		}
		/*左上角*/
		for (i = row - 1, p = col - 1; i >= 0 && p >= 0; i--, p--)
			if (chess[i][p] == 1 || chess[i][p] == 0)
				break;
		if (chess[i][p] != 0 && i >= 0 && p >= 0 && i != row - 1 && p != col - 1) {
			for (j = row - 1,q = col - 1; j > i&&q > p; j--, q--)
				chess[j][q] = 1;
			flag = 1;
		}
		/*左下角*/
		for (i = row + 1, p = col - 1; i < 8 && p >= 0; i++, p--)
			if (chess[i][p] == 1 || chess[i][p] == 0)
				break;
		if (chess[i][p] != 0 && i < 8 && p >= 0 && i != row + 1 && p != col - 1) {
			for (j = row + 1, q = col - 1; j < i&&q > p; j++, q--)
				chess[j][q] = 1;
			flag = 1;
		}
		/*右上角*/
		for (i = row - 1, p = col + 1; i >= 0 && p < 8; i--, p++)
			if (chess[i][p] == 1 || chess[i][p] == 0)
				break;
		if (chess[i][p] != 0 && i >= 0 && p < 8 && i != row - 1 && p != col + 1) {
			for (j = row - 1, q = col + 1; j > i&&q < p; j--, q++)
				chess[j][q] = 1;
			flag = 1;
		}
		/*右下角*/
		for (i = row + 1, p = col + 1; i < 8 && p < 8; i++, p++)
			if (chess[i][p] == 1 || chess[i][p] == 0)
				break;
		if (chess[i][p] != 0 && i < 8 && p < 8 && i != row + 1 && p != col + 1) {
			for (j = row + 1, q = col + 1; j < i&&q < p; j++, q++)
				chess[j][q] = 1;
			flag = 1;
		}
	}
	return flag;
}
