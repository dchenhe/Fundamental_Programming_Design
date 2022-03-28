#pragma once
#include<stdio.h>
#include<stdlib.h>
#include"user.h"
int all_player = 0;

/*���������Ϸ��¼*/
struct player {
	int play_num;//�ڼ��μ�¼
	int play_type;
	int	p_chess[8][8];
	int option;
}player[50];

//��������
void draw_c_board(int chess[][8]);
int get_chess(int* option, int chess[][8], FILE* fp, int* c_row, int* c_col,int type);
int read_file(int chess[][8], FILE* fp,int *option);
void save_file(int chess[][8], FILE* fp, int type,int *option);

//8*8���̻���
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
				i_chess = 'o';//1��ʾ����
			else if (chess[row][col] == 2)
				i_chess = 'x';//2��ʾ����
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

//���庯��
int get_chess(int* option, int chess[][8], FILE* fp, int* c_row, int* c_col,int type ) {
	int row, col;
	system("cls");
	draw_c_board(chess);
	printf("\n*************************************************************************\n");
	printf("ע�⣺��������x������ӣ�o������ӣ�ͨ������ָ������������壨Ĭ�Ϻ������ߣ�\n������Ϸ���浵�����룺8 0\n�˳���Ϸ�����룺0 8\n�������˵�������9 0");
	printf("\n*************************************************************************\n");
	if (*option == 1) {
		printf("��������Ҫ�µĺ�������꣺�������ʽʾ����2 1 ���е�һ�����ִ����������ڶ���Ϊ�������м��ÿո������\n");
		scanf_s("%d %d", &row, &col);
		if (row == 8 && col == 0) {
			save_file(chess, fp, type,option);
			return 0;
		}
		else if (col == 8 && row == 0) {
			printf("\n\n����ѡ���˳���Ϸ����");
			exit(0);
		}
		else if (row == 9 && col == 0)
			return 0;
		while (row > 7 || row < 0 || col>7 || col < 0) {
			fflush(stdin);
			printf("\n*************************************************************************\n");
			printf("�Ƿ����룬���������룺");
			scanf_s("%d %d", &row, &col);
		}
		while (chess[row][col] != 0) {
			fflush(stdin);
			printf("\n*************************************************************************\n");
			printf("�Ƿ����룬���������룺");
			scanf_s("%d %d", &row, &col);
		}
		chess[row][col] = 2;//����2
		*option = 0;
	}
	else if (*option == 0) {
		printf("��������Ҫ�µİ�������꣺�������ʽʾ����2 1 ���е�һ�����ִ����������ڶ���Ϊ�������м��ÿո������\n");
		scanf_s("%d %d", &row, &col);
		if (row == 8 && col == 0) {
			save_file(chess, fp, type,option);
			return 0;
		}
		else if (col == 8 && row == 0) {
			system("cls");
			printf("*************************************************************************\n");
			printf("ллʹ�ã���Ϸ���˳���\n");
			printf("*************************************************************************\n");
			exit(0);
		}
		else if (row == 9 && col == 0)
			return 0;
		while (row > 7 || row < 0 || col>7 || col < 0) {
			fflush(stdin);
			printf("\n*************************************************************************\n");
			printf("�Ƿ����룬���������룺");
			scanf_s("%d %d", &row, &col);
		}
		while (chess[row][col] != 0) {
			fflush(stdin);
			printf("\n*************************************************************************\n");
			printf("�Ƿ����룬���������룺");
			scanf_s("%d %d", &row, &col);
		}
		chess[row][col] = 1;//����1
		*option = 1;
	}
	*c_row = row;
	*c_col = col;
	return 1;//����ִ���ж�
}

//��ȡ�浵����
int read_file(int chess[][8], FILE* fp,int *option) {
	system("cls");
	fopen_s(&fp, "alldata.txt", "rb+");//���ļ�
	/*�ж��Ƿ��һ��ʹ�ô�����������Ƚ��г�ʼ���û������Ȳ���������ֱ�Ӷ�ȡ*/
	int judge;
	judge = fgetc(fp);
	fclose(fp);//�ر��ļ�

	if (judge == EOF) {
		printf("û���κδ浵��¼��\n");
		printf("������������ϼ��˵���\n");
		getchar();
		getchar();
		return 0;
	}
	else {
		int j;
		int row, col;
		fopen_s(&fp, "alldata.txt", "rb+");//���´��ļ�
		fread(&all_player, 4, 1, fp);
		for (j = 0; j < all_player; j++)
			fread(&player[j], sizeof(struct player), 1, fp);
		j--;
		fclose(fp);
		printf("*************************************************************************\n");
		printf("�������д浵��¼���£�\n");
		for (int i = 0; i <= j; i++) {
			printf("�������ĵ�%d�δ浵�������Ϊ", player[i].play_num);
			if (player[i].play_type == 1)
				printf("��ת��");
			if (player[i].play_type == 2)
				printf("������");
			if (player[i].play_type == 3)
				printf("��������");
			printf("\n");
		}
		printf("*************************************************************************\n");
		printf("��������Ҫѡ���ȡ�Ĵ浵�ţ����֣�������0�����ϼ��˵�:");
		int select;
		scanf_s("%d", &select);
		if (select) {
			for (row = 0; row < 8; row++)
				for (col = 0; col < 8; col++)
					chess[row][col] = player[select-1].p_chess[row][col];
			*option = player[select - 1].option;
			printf("*************************************************************************\n");
			printf("�Ѷ�ȡ�浵��¼��\n");
			printf("�������������Ϸ��\n");
			getchar();
			getchar();
			return player[select-1].play_type;
		}
		else
			return 0;
	}
}

//�浵�˳�����
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