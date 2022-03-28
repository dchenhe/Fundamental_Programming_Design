#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"user.h"
int all_player = 0;

/*定义玩家游戏记录*/
struct player {
	int play_num;//第几次记录
	int play_type;
	int	p_chess[8][8];
	int option;
}player[50];

//函数声明
void draw_c_board(int chess[][8]);
int get_chess(int* option, int chess[][8], FILE* fp, int* c_row, int* c_col,int type);
int read_file(int chess[][8], FILE* fp,int *option);
void save_file(int chess[][8], FILE* fp, int type,int *option);

//8*8棋盘绘制
void draw_c_board(int chess[][8]) {
	system("cls");
	char i_chess;
	for (int i = 0; i < 8; ++i) {
		printf("   %d", i);
	}
	printf("\n");
	printf("  ");
	for (int i = 0; i < 8; ++i) {
		printf("----");
	}
	printf("\n");
	for (int row = 0; row < 8; ++row) {
		printf("%d|", row);
		for (int col = 0; col < 8; ++col) {
			if (chess[row][col] == 1)
				i_chess = 'o';//1表示白子
			else if (chess[row][col] == 2)
				i_chess = 'x';//2表示黑子
			else i_chess = ' ';
			printf(" %c |", i_chess);
		}
		printf("\n");
		if (row != 7) {
			printf("  ");
			for (int i = 0; i < 8; i++)
				printf("---|");
			printf("\n");
		}
		if (row == 7) {
			printf("  ");
			for (int i = 0; i < 8; i++)
				printf("----");
			printf("\n");
		}
	}
}

//下棋函数
int get_chess(int* option, int chess[][8], FILE* fp, int* c_row, int* c_col,int type ) {
	int row, col;
	system("cls");
	draw_c_board(chess);
	printf("\n*************************************************************************\n");
	printf("注意：本棋盘中x代表黑子，o代表白子，通过输入指定坐标进行下棋（默认黑棋先走）\n结束游戏并存档请输入：8 0\n退出游戏请输入：0 8\n返回主菜单请输入9 0");
	printf("\n*************************************************************************\n");
	if (*option == 1) {
		printf("请输入您要下的黑棋的坐标：（输入格式示例：2 1 其中第一个数字代表行数，第二个为列数，中间用空格隔开）\n");
		scanf_s("%d %d", &row, &col);
		if (row == 8 && col == 0) {
			save_file(chess, fp, type,option);
			return 0;
		}
		else if (col == 8 && row == 0) {
			printf("\n\n您已选择退出游戏！！");
			exit(0);
		}
		else if (row == 9 && col == 0)
			return 0;
		while (row > 7 || row < 0 || col>7 || col < 0) {
			fflush(stdin);
			printf("\n*************************************************************************\n");
			printf("非法输入，请重新输入：");
			scanf_s("%d %d", &row, &col);
		}
		while (chess[row][col] != 0) {
			fflush(stdin);
			printf("\n*************************************************************************\n");
			printf("非法输入，请重新输入：");
			scanf_s("%d %d", &row, &col);
		}
		chess[row][col] = 2;//黑棋2
		*option = 0;
	}
	else if (*option == 0) {
		printf("请输入您要下的白棋的坐标：（输入格式示例：2 1 其中第一个数字代表行数，第二个为列数，中间用空格隔开）\n");
		scanf_s("%d %d", &row, &col);
		if (row == 8 && col == 0) {
			save_file(chess, fp, type,option);
			return 0;
		}
		else if (col == 8 && row == 0) {
			system("cls");
			printf("*************************************************************************\n");
			printf("谢谢使用！游戏已退出！\n");
			printf("*************************************************************************\n");
			exit(0);
		}
		else if (row == 9 && col == 0)
			return 0;
		while (row > 7 || row < 0 || col>7 || col < 0) {
			fflush(stdin);
			printf("\n*************************************************************************\n");
			printf("非法输入，请重新输入：");
			scanf_s("%d %d", &row, &col);
		}
		while (chess[row][col] != 0) {
			fflush(stdin);
			printf("\n*************************************************************************\n");
			printf("非法输入，请重新输入：");
			scanf_s("%d %d", &row, &col);
		}
		chess[row][col] = 1;//白棋1
		*option = 1;
	}
	*c_row = row;
	*c_col = col;
	return 1;//继续执行判断
}

//读取存档函数
int read_file(int chess[][8], FILE* fp,int *option) {
	system("cls");
	fopen_s(&fp, "alldata.txt", "rb+");//打开文件
	/*判断是否第一次使用此软件，若是先进行初始化用户人数等操作，否则直接读取*/
	int judge;
	judge = fgetc(fp);
	fclose(fp);//关闭文件

	if (judge == EOF) {
		printf("没有任何存档记录！\n");
		printf("按任意键返回上级菜单！\n");
		getchar();
		getchar();
		return 0;
	}
	else {
		int j;
		int row, col;
		fopen_s(&fp, "alldata.txt", "rb+");//重新打开文件
		fread(&all_player, 4, 1, fp);
		for (j = 0; j < all_player; j++)
			fread(&player[j], sizeof(struct player), 1, fp);
		j--;
		fclose(fp);
		printf("*************************************************************************\n");
		printf("您的所有存档记录如下：\n");
		for (int i = 0; i <= j; i++) {
			printf("这是您的第%d次存档，您这局为", player[i].play_num);
			if (player[i].play_type == 1)
				printf("翻转棋");
			if (player[i].play_type == 2)
				printf("五子棋");
			if (player[i].play_type == 3)
				printf("创新折棋");
			printf("\n");
		}
		printf("*************************************************************************\n");
		printf("请输入您要选择读取的存档号（数字），输入0返回上级菜单:");
		int select;
		scanf_s("%d", &select);
		if (select) {
			for (row = 0; row < 8; row++)
				for (col = 0; col < 8; col++)
					chess[row][col] = player[select-1].p_chess[row][col];
			*option = player[select - 1].option;
			printf("*************************************************************************\n");
			printf("已读取存档记录！\n");
			printf("按任意键进入游戏！\n");
			getchar();
			getchar();
			return player[select-1].play_type;
		}
		else
			return 0;
	}
}

//存档退出函数
void save_file(int chess[][8], FILE* fp, int type,int *option) {
	int row, col;
	fopen_s(&fp, "alldata.txt", "rb+");
	all_player++;
	fwrite(&all_player, 4, 1, fp);
	player[all_player - 1].play_num = all_player;
	player[all_player - 1].play_type = type;
	player[all_player - 1].option = *option;
	for (row = 0; row < 8; row++)
		for (col = 0; col < 8; col++)
			player[all_player - 1].p_chess[row][col]= chess[row][col];
	for (int j = 0; j < all_player; j++)
		fwrite(&player[j], sizeof(struct player), 1, fp);
	fclose(fp);
}