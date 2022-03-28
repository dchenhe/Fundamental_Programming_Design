#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"chess.h"
#include"user.h"

//��������
void inverse(int chess[][8], FILE* fp,int *option);
void count_chess(int chess[][8]);
int judege_suit_inverse(int* option, int chess[][8], FILE* fp);
int judge_inverse(int option, int chess[][8], FILE* fp, int row, int col);

//��ת����Ϸ����
void inverse(int chess[][8], FILE* fp,int *option) {
	int c_row, c_col;
	int select;
	if (chess[3][3] == 0) {
		chess[3][3] = 1;//�����1��ʾ���� 2��ʾ����
		chess[3][4] = 2;
		chess[4][3] = 2;
		chess[4][4] = 1;
	}//�޴浵 ���з�ת���ʼ��������ֱ�ӿ�ʼ����
	while (true) {

		/*�Ƚ����жϿ��Ƿ��п�ִ���岽*/
		if (!judege_suit_inverse(option, chess, fp)) {
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

		if (!get_chess(option, chess, fp, &c_row, &c_col,1))
			return;//ִ������������������ֵΪ0���������˵�
		if (!judge_inverse(*option, chess, fp, c_row, c_col)) {
			printf("\n*************************************************************************\n");
			printf("���Ϸ��岽�������²����� �����������~");
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

//���������Ӽ�������
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
		printf("\n����ʣ����������ͬ��ƽ�֣�");
	else if (w > b)
		printf("\n�������Ӷ࣬����ʤ��");
	else
		printf("\n�������Ӷ࣬����ʤ��");
}

//�ж��Ƿ��п�ִ���岽
int judege_suit_inverse(int* option, int chess[][8], FILE* fp) {
	int i, p;
	int flag_b = 0, flag_w = 0;
	for (int row = 0; row < 8; row++)
		for (int col = 0; col < 8; col++) {
			if (chess[row][col] != 0)
				continue;
			/*��ֱ���ϲ���*/
			for (i = row - 1; i >= 0; i--)
				if (chess[i][col] == 2 || chess[i][col] == 0)
					break;
			if (chess[i][col] != 0 && i >= 0 && i != row - 1) {
				flag_b = 1;
			}
			/*��ֱ���²���*/
			for (i = row + 1; i < 8; i++)
				if (chess[i][col] == 2 || chess[i][col] == 0)
					break;
			if (chess[i][col] != 0 && i < 8 && i != row + 1) {
				flag_b = 1;
			}
			/*ˮƽ���Ҳ���*/
			for (i = col + 1; i < 8; i++)
				if (chess[row][i] == 2 || chess[row][i] == 0)
					break;
			if (chess[row][i] != 0 && i < 8 && i != col + 1) {
				flag_b = 1;
			}
			/*ˮƽ�������*/
			for (i = col - 1; i >= 0; i--)
				if (chess[row][i] == 2 || chess[row][i] == 0)
					break;
			if (chess[row][i] != 0 && i >= 0 && i != col - 1) {
				flag_b = 1;
			}
			/*���Ͻ�*/
			for (i = row - 1, p = col - 1; i >= 0 && p >= 0; i--, p--)
				if (chess[i][p] == 2 || chess[i][p] == 0)
					break;
			if (chess[i][p] != 0 && i >= 0 && p >= 0 && i != row - 1 && p != col - 1) {
				flag_b = 1;
			}
			/*���½�*/
			for (i = row + 1, p = col - 1; i < 8 && p >= 0; i++, p--)
				if (chess[i][p] == 2 || chess[i][p] == 0)
					break;
			if (chess[i][p] != 0 && i < 8 && p >= 0 && i != row + 1 && p != col - 1) {
				flag_b = 1;
			}
			/*���Ͻ�*/
			for (i = row - 1, p = col + 1; i >= 0 && p < 8; i--, p++)
				if (chess[i][p] == 2 || chess[i][p] == 0)
					break;
			if (chess[i][p] != 0 && i >= 0 && p < 8 && i != row - 1 && p != col + 1) {
				flag_b = 1;
			}
			/*���½�*/
			for (i = row + 1, p = col + 1; i < 8 && p < 8; i++, p++)
				if (chess[i][p] == 2 || chess[i][p] == 0)
					break;
			if (chess[i][p] != 0 && i < 8 && p < 8 && i != row + 1 && p != col + 1) {
				flag_b = 1;
			}


			/*��ֱ���ϲ���*/
			for (i = row - 1; i >= 0; i--)
				if (chess[i][col] == 1 || chess[i][col] == 0)
					break;
			if (chess[i][col] != 0 && i >= 0 && i != row - 1) {
				flag_w = 1;
			}
			/*��ֱ���²���*/
			for (i = row + 1; i < 8; i++)
				if (chess[i][col] == 1 || chess[i][col] == 0)
					break;
			if (chess[i][col] != 0 && i < 8 && i != row + 1) {
				flag_w = 1;
			}
			/*ˮƽ���Ҳ���*/
			for (i = col + 1; i < 8; i++)
				if (chess[row][i] == 1 || chess[row][i] == 0)
					break;
			if (chess[row][i] != 0 && i < 8 && i != col + 1) {
				flag_w = 1;
			}
			/*ˮƽ�������*/
			for (i = col - 1; i >= 0; i--)
				if (chess[row][i] == 1 || chess[row][i] == 0)
					break;
			if (chess[row][i] != 0 && i >= 0 && i != col - 1) {
				flag_w = 1;
			}
			/*���Ͻ�*/
			for (i = row - 1, p = col - 1; i >= 0 && p >= 0; i--, p--)
				if (chess[i][p] == 1 || chess[i][p] == 0)
					break;
			if (chess[i][p] != 0 && i >= 0 && p >= 0 && i != row - 1 && p != col - 1) {
				flag_w = 1;
			}
			/*���½�*/
			for (i = row + 1, p = col - 1; i < 8 && p >= 0; i++, p--)
				if (chess[i][p] == 1 || chess[i][p] == 0)
					break;
			if (chess[i][p] != 0 && i < 8 && p >= 0 && i != row + 1 && p != col - 1) {
				flag_w = 1;
			}
			/*���Ͻ�*/
			for (i = row - 1, p = col + 1; i >= 0 && p < 8; i--, p++)
				if (chess[i][p] == 1 || chess[i][p] == 0)
					break;
			if (chess[i][p] != 0 && i >= 0 && p < 8 && i != row - 1 && p != col + 1) {
				flag_w = 1;
			}
			/*���½�*/
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
			printf("\n���߾��޺Ϸ��岽��");
			count_chess(chess);
			return 0;
		}
		else if (flag_b) {
			draw_c_board(chess);
			fflush(stdin);
			printf("�����Ѿ�û�кϷ��岽���ɺ����������\n�����������");
			getchar();
			getchar();
			*option = 1;
			return 1;
		}
		else if (flag_w) {
			draw_c_board(chess);
			fflush(stdin);
			printf("�����Ѿ�û�кϷ��岽���ɰ����������\n�����������");
			getchar();
			getchar();
			*option = 0;
			return 1;
		}
}

//�����ж�����
int judge_inverse(int option,int chess[][8], FILE* fp,int row,int col) {
	int i,p,q,j;
	int flag=0;
	if (option == 0) {//˵���Ͼ��µĺ���
		/*��ֱ���ϲ���*/
		for (i = row - 1; i >= 0; i--)
			if (chess[i][col] == 2|| chess[i][col] == 0)
				break;
		if (chess[i][col] != 0 && i >= 0&&i!=row-1) {
			for (j = row - 1; j > i; j--)
				chess[j][col] = 2;
			flag = 1;
		}
		/*��ֱ���²���*/
		for (i = row + 1; i<8; i++)
			if (chess[i][col] == 2 || chess[i][col] == 0)
				break;
		if (chess[i][col] != 0 && i < 8 && i != row + 1) {
			for (j = row + 1; j < i; j++)
				chess[j][col] = 2;
			flag = 1;
		}
		/*ˮƽ���Ҳ���*/
		for (i = col + 1; i < 8; i++)
			if (chess[row][i] == 2 || chess[row][i] == 0)
				break;
		if (chess[row][i] != 0 && i < 8 && i != col + 1) {
			for (j = col + 1; j < i; j++)
				chess[row][j] = 2;
			flag = 1;
		}
		/*ˮƽ�������*/
		for (i = col - 1; i >=0; i--)
			if (chess[row][i] == 2 || chess[row][i] == 0)
				break;
		if (chess[row][i] != 0 && i >= 0 && i != col - 1) {
			for (j = col - 1; j > i; j--)
				chess[row][j] = 2;
			flag = 1;
		}
		/*���Ͻ�*/
		for (i = row - 1,p=col-1; i >= 0&&p>=0; i--,p--)
			if (chess[i][p] == 2 || chess[i][p] == 0)
				break;
		if (chess[i][p] != 0 && i >= 0&&p>=0 && i != row - 1&&p!=col-1) {
			for (j = row - 1,q=col-1; j > i&&q>p; j--,q--)
				chess[j][q] = 2;
			flag = 1;
		}
		/*���½�*/
		for (i = row + 1, p = col - 1; i < 8 && p >= 0; i++, p--)
			if (chess[i][p] == 2 || chess[i][p] == 0)
				break;
		if (chess[i][p] != 0 && i < 8 && p >= 0 && i != row + 1 && p != col - 1) {
			for (j = row + 1,q = col - 1; j < i&& q > p; j++, q--)
				chess[j][q] = 2;
			flag = 1;
		}
		/*���Ͻ�*/
		for (i = row - 1, p = col + 1; i >= 0 && p < 8; i--, p++)
			if (chess[i][p] == 2 || chess[i][p] == 0)
				break;
		if (chess[i][p] != 0 && i >= 0 && p < 8 && i != row - 1 && p != col + 1) {
			for (j = row - 1,q = col + 1; j > i&&q < p; j--, q++)
				chess[j][q] = 2;
			flag = 1;
		}
		/*���½�*/
		for (i = row + 1, p = col + 1; i < 8 && p < 8; i++, p++)
			if (chess[i][p] == 2 || chess[i][p] == 0)
				break;
		if (chess[i][p] != 0 && i < 8 && p < 8 && i != row + 1 && p != col + 1) {
			for (j = row + 1,q = col + 1; j < i&&q < p; j++, q++)
				chess[j][q] = 2;
			flag = 1;
		}
	}
	if (option == 1) {//˵���Ͼ��µİ���
		/*��ֱ���ϲ���*/
		for (i = row - 1; i >= 0; i--)
			if (chess[i][col] == 1 || chess[i][col] == 0)
				break;
		if (chess[i][col] != 0 && i >= 0 && i != row - 1) {
			for (j = row - 1; j > i; j--)
				chess[j][col] = 1;
			flag = 1;
		}
		/*��ֱ���²���*/
		for (i = row + 1; i < 8; i++)
			if (chess[i][col] == 1 || chess[i][col] == 0)
				break;
		if (chess[i][col] != 0 && i < 8 && i != row + 1) {
			for (j = row + 1; j < i; j++)
				chess[j][col] = 1;
			flag = 1;
		}
		/*ˮƽ���Ҳ���*/
		for (i = col + 1; i < 8; i++)
			if (chess[row][i] == 1 || chess[row][i] == 0)
				break;
		if (chess[row][i] != 0 && i < 8 && i != col + 1) {
			for (j = col + 1; j < i; j++)
				chess[row][j] = 1;
			flag = 1;
		}
		/*ˮƽ�������*/
		for (i = col - 1; i >= 0; i--)
			if (chess[row][i] == 1 || chess[row][i] == 0)
				break;
		if (chess[row][i] != 0 && i >= 0 && i != col - 1) {
			for (j = col - 1; j > i; j--)
				chess[row][j] = 1;
			flag = 1;
		}
		/*���Ͻ�*/
		for (i = row - 1, p = col - 1; i >= 0 && p >= 0; i--, p--)
			if (chess[i][p] == 1 || chess[i][p] == 0)
				break;
		if (chess[i][p] != 0 && i >= 0 && p >= 0 && i != row - 1 && p != col - 1) {
			for (j = row - 1,q = col - 1; j > i&&q > p; j--, q--)
				chess[j][q] = 1;
			flag = 1;
		}
		/*���½�*/
		for (i = row + 1, p = col - 1; i < 8 && p >= 0; i++, p--)
			if (chess[i][p] == 1 || chess[i][p] == 0)
				break;
		if (chess[i][p] != 0 && i < 8 && p >= 0 && i != row + 1 && p != col - 1) {
			for (j = row + 1, q = col - 1; j < i&&q > p; j++, q--)
				chess[j][q] = 1;
			flag = 1;
		}
		/*���Ͻ�*/
		for (i = row - 1, p = col + 1; i >= 0 && p < 8; i--, p++)
			if (chess[i][p] == 1 || chess[i][p] == 0)
				break;
		if (chess[i][p] != 0 && i >= 0 && p < 8 && i != row - 1 && p != col + 1) {
			for (j = row - 1, q = col + 1; j > i&&q < p; j--, q++)
				chess[j][q] = 1;
			flag = 1;
		}
		/*���½�*/
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
