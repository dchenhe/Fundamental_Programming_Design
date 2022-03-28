#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"user.h"

//��������
void five(int chess[][8], FILE* fp,int* option);
int judge_five(int option, int chess[][8], FILE* fp, int row, int col);
int judege_suit_five(int option, int chess[][8], FILE* fp);

//��������Ϸ����
void five(int chess[][8], FILE* fp,int* option) {
	int c_row, c_col;
	int select;
	while (true) {


		/*�Ƚ����жϿ��Ƿ��п�ִ���岽*/
		if (!judege_suit_five(*option, chess, fp)) {
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

		if (!get_chess(option, chess, fp, &c_row, &c_col,2))
			return;//ִ������������������ֵΪ0���������˵�
		if (judge_five(*option, chess, fp, c_row, c_col)) {
			draw_c_board(chess);
			if (*option == 0) {
				printf("\n*************************************************************************");
				printf("\n�����������飬����ʤ��");
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
				printf("\n�����������飬����ʤ��");
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

//�����ж�����
int judge_five(int option, int chess[][8], FILE* fp, int row, int col) {
	int i, p,j;
	int flag = 0;
	if (option == 0) {//˵���Ͼ��µĺ���
		/*��ֱ���ϲ���*/
		for (i = row - 1, j = 0; i >= 0; i--)
			if (chess[i][col] != 2)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*��ֱ���²���*/
		for (i = row + 1, j = 0; i < 8; i++)
			if (chess[i][col] != 2)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*ˮƽ���Ҳ���*/
		for (i = col + 1, j = 0; i < 8; i++)
			if (chess[row][i] != 2)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*ˮƽ�������*/
		for (i = col - 1, j = 0; i >= 0; i--)
			if (chess[row][i] != 2)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*���Ͻ�*/
		for (i = row - 1, p = col - 1, j = 0; i >= 0 && p >= 0; i--, p--)
			if (chess[i][p] != 2)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*���½�*/
		for (i = row + 1, p = col - 1, j = 0; i < 8 && p >= 0; i++, p--)
			if (chess[i][p] != 2)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*���Ͻ�*/
		for (i = row - 1, p = col + 1, j = 0; i >= 0 && p < 8; i--, p++)
			if (chess[i][p] != 2)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*���½�*/
		for (i = row + 1, p = col + 1,j=0; i < 8 && p < 8; i++, p++)
			if (chess[i][p] != 2)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
	}

	if (option == 1) {//˵���Ͼ��µİ���
		/*��ֱ���ϲ���*/
		for (i = row - 1, j = 0; i >= 0; i--)
			if (chess[i][col] != 1)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*��ֱ���²���*/
		for (i = row + 1, j = 0; i < 8; i++)
			if (chess[i][col] != 1)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*ˮƽ���Ҳ���*/
		for (i = col + 1, j = 0; i < 8; i++)
			if (chess[row][i] != 1)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*ˮƽ�������*/
		for (i = col - 1, j = 0; i >= 0; i--)
			if (chess[row][i] != 1)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*���Ͻ�*/
		for (i = row - 1, p = col - 1, j = 0; i >= 0 && p >= 0; i--, p--)
			if (chess[i][p] != 1)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*���½�*/
		for (i = row + 1, p = col - 1, j = 0; i < 8 && p >= 0; i++, p--)
			if (chess[i][p] != 1)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*���Ͻ�*/
		for (i = row - 1, p = col + 1, j = 0; i >= 0 && p < 8; i--, p++)
			if (chess[i][p] != 1)
				break;
			else
				j++;
		if (j>=4) {
			flag = 1;
		}
		/*���½�*/
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

//�ж��Ƿ��п�ִ���岽
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
		printf("\n���߾��޺Ϸ��岽��ƽ�֣�");
		count_chess(chess);
		return 0;
	}
	else
		return 1;
}
