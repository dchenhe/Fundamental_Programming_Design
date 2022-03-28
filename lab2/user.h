#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"inverse.h"
#include"five.h"
#include"gochess.h"
#include"chess.h"

//��������
void initial_game(int chess[][8], FILE* fp);
int select_game(int chess[][8], FILE* fp);

//��Ϸ�����ʼ��
void initial_game(int chess[][8], FILE* fp) {
	int option = 1;//Ĭ�Ϻ�������
	int i;
	int s;
	int select;
	for (int p = 0; p < 8; p++)
		for (int q = 0; q < 8; q++)
			chess[p][q] = 0;//��ֳ�ʼ��
	while (true) {
		system("cls");
		printf("*************************************************************************\n");
		printf("                          ��ӭ����������Ϸ\n");
		printf("                           1.��ʼ����Ϸ\n");
		printf("                           2.��ȡ�浵\n");
		printf("                           3.�˳���Ϸ\n");
		printf("*************************************************************************\n");
		printf("                           ����������ѡ�񣺣������Ӧ���ּ��ɣ�");
		scanf_s("%d", &i);
		if (i == 1) {
			option = 1;
			for (int p = 0; p < 8; p++)
				for (int q = 0; q < 8; q++)
					chess[p][q] = 0;//��ֳ�ʼ��
			s = select_game(chess, fp);
			if (s == 1) {
				inverse(chess, fp,&option);
				continue;
			}//��ת��
			if (s == 2) {
				five(chess, fp,&option);
				continue;
			}//������
			if (s == 3) {
				gochess(chess, fp,&option);
				continue;
			}//Χ��
		}//ѡ����Ϸ����

		//��ȡ�浵
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
			printf("ллʹ�ã���Ϸ���˳���\n");
			printf("*************************************************************************\n");
			exit(0);
		}
	}
}

//��Ϸ����ѡ��
int select_game(int chess[][8],FILE *fp){
	int i;
	system("cls");
	printf("*************************************************************************\n");
	printf("                          ��ѡ��һ��������Ϸ\n");
	printf("                           1.��ת��\n");
	printf("                           2.������\n");
	printf("                           3.��������\n");
	printf("                           4.�����ϼ��˵�\n");
	printf("*************************************************************************\n");
	printf("                           ����������ѡ�񣺣������Ӧ���ּ��ɣ�");
	scanf_s("%d", &i);
	while(i != 1 && i != 2 && i != 3 && i != 4) {
		printf("*************************************************************************\n");
		printf("                           �Ƿ����룬���������룺");
		scanf_s("%d", &i);
	}
	return i;
}
