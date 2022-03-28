#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"user.h"

//��������
void gochess(int chess[][8], FILE* fp,int* option);
int judege_suit_go(int option, int chess[][8], FILE* fp);
int judge_go(int option, int chess[][8], FILE* fp, int row, int col);

//�Զ������壬���������γ�һ��+����ἴ�ɹ���

void gochess(int chess[][8], FILE* fp,int* option) {
	int c_row, c_col;
	int select;
	while (true) {


		/*�Ƚ����жϿ��Ƿ��п�ִ���岽*/
		if (!judege_suit_go(*option, chess, fp)) {
			printf("\n*************************************************************************");
			printf("\n������Ϸ������0�������������ַ��ؿ�ʼ�˵�:");
			scanf_s("%d", &select);
			if (select == 0) {
				printf("\n*************************************************************************\n");
				printf("\n��Ϸ������ллʹ�ã�");
				exit(0);
			}
			else
				return;
		}

		if (!get_chess(option, chess, fp, &c_row, &c_col,3))
			return;//ִ������������������ֵΪ0���������˵�
		if (judge_go(*option, chess, fp, c_row, c_col)) {
			draw_c_board(chess);
			if (*option == 0) {
				printf("\n*************************************************************************");
				printf("\n�����γ��������ߣ�����ʤ��");
				printf("\n*************************************************************************");
				printf("\n������Ϸ������0�������������ַ��ؿ�ʼ�˵�:");
				scanf_s("%d", &select);
				if (select == 0) {
					printf("\n*************************************************************************\n");
					printf("\n��Ϸ������ллʹ�ã�");
					exit(0);
				}
				else
					return;
			}
			if (*option == 1) {
				printf("\n*************************************************************************");
				printf("\n�����γ��������ߣ�����ʤ��");
				printf("\n*************************************************************************");
				printf("\n������Ϸ������0�������������ַ��ؿ�ʼ�˵�:");
				scanf_s("%d", &select);
				if (select == 0) {
					printf("\n*************************************************************************\n");
					printf("\n��Ϸ������ллʹ�ã�");
					exit(0);
				}
				else
					return;
			}
		}
	}
}


//�ж��Ƿ��п�ִ���岽
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
		printf("\n���߾��޺Ϸ��岽��ƽ�֣�");
		count_chess(chess);
		return 0;
	}
	else
		return 1;
}

int judge_go(int option, int chess[][8], FILE* fp, int row, int col) {
	int i;
	int flag = 0;
	if (option == 0) {//˵���Ͼ��µĺ���
		//�����ϲ���
		i = row - 1;
		if (i >= 0)
			if (chess[i][col] == 2 && col + 1 < 8)
				if (chess[i][col + 1] == 2)
					flag = 1;
		//�����²���
		i = row + 1;
		if (i < 8)
			if (chess[i][col] == 2 && col + 1 < 8)
				if (chess[i][col + 1] == 2)
					flag = 1;
		//���������
		i = col - 1;
		if (i >= 0)
			if (chess[row][i] == 2 && row - 1 >= 0)
				if (chess[row - 1][i] == 2)
					flag = 1;
	}
	if (option == 1) {//˵���Ͼ��µİ���
	    //�����ϲ���
		i = row - 1;
		if (i >= 0)
			if (chess[i][col] == 1 && col + 1 < 8)
				if (chess[i][col + 1] == 1)
					flag = 1;
		//�����²���
		i = row + 1;
		if (i < 8)
			if (chess[i][col] == 1 && col + 1 < 8)
				if (chess[i][col + 1] == 1)
					flag = 1;
		//���������
		i = col - 1;
		if (i >= 0)
			if (chess[row][i] == 1 && row - 1 >= 0)
				if (chess[row - 1][i] == 1)
					flag = 1;
	}
	return flag;
}
