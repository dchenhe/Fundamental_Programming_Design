/************************************************************************
��Ŀ������С����ɽկ��������
�����ߣ�191180044-�ζ��
�����ܣ�1������û��˿ں͹���Ա�˿�
		  2���û��˿ڣ�ע�ᡢ��¼�˺š���ϰ�Ѷ�ѡ�񡢴�����ϰ��¼
		  3������Ա�˿ڣ������ı������û������һ�
		  4) ͼ�ν��棬���õ��˻�����
		  6��ϵͳ�����ʵʱ����ÿ�ε���ϰ��¼
��ע��    
		  ����Ա�û�����admin
		  ����Ա���룺admin
		  ����ɾ�����ƶ������ı��ļ���ͼ�ν���jpg�ļ�
		  ����ǰ��װeasyxͼ�ο�
************************************************************************/

/*�⺯������*/
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<tchar.h>
#include<graphics.h>
#include<time.h>
#include<locale.h>


/*����ȫ�ֱ���*/
int all_players = 0;//�������û���ţ�Ҳ�����û�������
int login_player = 0;//�����¼���û����
int tough = 1;//�����Ѷ�ϵ��


/*ͼƬ����*/
IMAGE initial;
IMAGE users;
IMAGE admin;
IMAGE ini_admin_button;
IMAGE ini_user_login_button;
IMAGE ini_user_regi_button;
IMAGE ini_quit_button;
IMAGE user_begin_button;
IMAGE user_find_button;
IMAGE user_return_button;
IMAGE user_select_button;
IMAGE user_quit_button;
IMAGE admin_password_button;
IMAGE admin_quit_button;
IMAGE admin_return_button;
IMAGE admin_text_button;
IMAGE admin_record_button;
IMAGE ending;
IMAGE type_ing;
IMAGE type_return;
IMAGE type_save;
IMAGE type_quit;

/*������ϰ��¼�ṹ�����鶨��*/
struct type_record {
	double process;//������ֽ���
	int type_time;//�����������ʱ��
	int difficulty_coeffeicents;//��������ϰ���Ѷ�ϵ������Ϊ1���򵥣���2�����ѣ���3�����ѣ� 
};

/*�û��ṹ�����鶨��*/
struct get_player {
	wchar_t play_name[20]; //�����û���
	wchar_t play_password[20]; //�����û�����
	wchar_t play_password2[20];//�����û�����ĵڶ�������
	int player_num; //�����û����
	int player_type_times; //�����û�ʹ�ô��ֵĴ���
	type_record record[20];//�����û��Ĵ��ּ�¼
}player[50];

/*����Ա�ṹ�����鶨��*/
struct administrator {
	wchar_t admin_name[20]; //�������Ա��
	wchar_t admin_password[20]; //�������Ա����
}admin_login = { _T("admin"),_T("admin") };

//��������
void SaveFile(FILE* fp);
void user_login(FILE* fp);
void user_register(FILE* fp);
void ini_window(FILE* fp);
void admin_action(FILE* fp);
void admin_text_control(FILE* fp);
void admin_password_control(FILE* fp);
void been_user_login(FILE* fp);
void user_type_ing(FILE* fp);
void user_look_record(FILE* fp);
void user_type_select(FILE* fp);
void admin_password_control(FILE* fp);
void admin_look_record(FILE* fp);



/*�ļ����溯��*/
void SaveFile(FILE* fp)
{
	fopen_s(&fp, "alldata.txt", "rb+");
	//���ļ����ȫ�ֱ���
	fwrite(&all_players, 4, 1, fp);
	fwrite(&login_player, 4, 1, fp);
	//����û��ṹ������
	for (int i = 0; i < all_players; i++)
		fwrite(&player[i], sizeof(struct get_player), 1, fp);
	//�������Ա�ṹ������ 
	fwrite(&admin_login, sizeof(struct administrator), 1, fp);
	fclose(fp);
}

/*�˵���ʼ�����溯��*/
void ini_window(FILE* fp) {
	loadimage(&initial, L"initial.jpg");
	putimage(0, 0, &initial);
	MOUSEMSG msg;//������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ������
	while (true) // ��ѭ��,���������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��Ϊ��
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ

			/*ʵ�ֶ�̬��ť*/
			if (msg.x > 480 && msg.x < 860 && msg.y > 190 && msg.y < 310) {
				loadimage(&ini_user_login_button, L"ini_user_login_button.jpg");
				putimage(0, 0, &ini_user_login_button);
			}
			else if (msg.x > 480 && msg.x < 860 && msg.y > 360 && msg.y < 480) {
				loadimage(&ini_user_regi_button, L"ini_user_regi_button.jpg");
				putimage(0, 0, &ini_user_regi_button);
			}
			else if (msg.x > 480 && msg.x < 860 && msg.y > 540 && msg.y < 650) {
				loadimage(&ini_admin_button, L"ini_admin_button.jpg");
				putimage(0, 0, &ini_admin_button);
			}
			else if (msg.x > 1115 && msg.x < 1335 && msg.y > 540 && msg.y < 650) {
				loadimage(&ini_quit_button, L"ini_quit_button.jpg");
				putimage(0, 0, &ini_quit_button);
			}
			else {
				putimage(0, 0, &initial);
			}
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 480 && msg.x < 860 && msg.y > 190 && msg.y < 310) {
					loadimage(&ini_user_login_button, L"ini_user_login_button.jpg");
					putimage(0, 0, &ini_user_login_button);
					Sleep(100);
					user_login(fp);
					putimage(0, 0, &initial);
				}
				if (msg.x > 480 && msg.x < 860 && msg.y > 360 && msg.y < 480) {
					loadimage(&ini_user_regi_button, L"ini_user_regi_button.jpg");
					putimage(0, 0, &ini_user_regi_button);
					Sleep(100);
					user_register(fp);
					putimage(0, 0, &initial);
				}
				if (msg.x > 480 && msg.x < 860 && msg.y > 540 && msg.y < 650) {
					loadimage(&ini_admin_button, L"ini_admin_button.jpg");
					putimage(0, 0, &ini_admin_button);
					Sleep(100);
					admin_action(fp);
					putimage(0, 0, &initial);
				}
				if (msg.x > 1115 && msg.x < 1335 && msg.y > 540 && msg.y < 650) {
					loadimage(&ini_quit_button, L"ini_quit_button.jpg");
					putimage(0, 0, &ini_quit_button);
					Sleep(250);
					loadimage(&ending, L"ending.jpg");
					putimage(0, 0, &ending);
					Sleep(5000);
					exit(0);
				}
			}
		}
	}
}

/*�û���¼*/
void user_login(FILE* fp) {
	int i;
	wchar_t username[20];//����һ����ʱ�洢�û������ַ����� 
	wchar_t password[20];//����һ����ʱ�洢������ַ����� 

	InputBox(username, 10, _T("�������û���"));//��ʾ�û������û������������ʱ�洢�û������ַ�����
	for (i = 0; i < all_players; i++)
		if (wcscmp(username, player[i].play_name) == 0)//�ҵ��� 
		{
			login_player = i;//����õ�¼ѧ�������
			break;//����forѭ��
		}//��¼�����û�������Ӧ��ѧ����ţ�����¼���û�����Ӧ�ı�� 

	if (i >= all_players) {//˵��û���ҵ���Ӧ�û��� 
		MessageBox(NULL, _T("���û�������"), _T("�û���¼"), MB_ICONSTOP | MB_SETFOREGROUND);
		return;
	}

	//�ҵ��˴��û�����������������ģ�� 


	/*��������ģ��*/
	InputBox(password, 10, _T("����������"));//��ʾ�û��������룬�������ʱ�洢������ַ�����
	if (wcscmp(password, player[login_player].play_password) == 0)//������� 
	{
		MessageBox(NULL, _T("��¼�ɹ���"), _T("�û���¼"), MB_SETFOREGROUND);
		//�����ֱ�Ϊ����Ϣ��ӵ�еĴ��ڡ���Ϣ������ݡ���Ϣ��ı��⡢��־��(�����־��"��"(|)��������)
		//���Ĳ�����ʾ������Ϣ��Ϊǰ������
		been_user_login(fp);
		return;
	}//������������ģ�� 
	else {
		MessageBox(NULL, _T("�������"), _T("ѧ����¼"), MB_ICONSTOP | MB_SETFOREGROUND);
		return;
	}
}

/*�û�ע��*/
void user_register(FILE* fp) {
	/*�����û���*/
	int i;
	do {
		InputBox(player[all_players].play_name, 10, _T("�������û���"));//��ʾ�û������û���
		//�����������û���Ϣ���е����ݣ��Ƚ���������û����Ƿ���ڣ�������ڣ�ϵͳ������ʾ
		for (i = 0; i < all_players; i++)
		{
			if (wcscmp(player[i].play_name, player[all_players].play_name) == 0)
			{
				MessageBox(NULL, _T("���û��Ѿ����ڣ�������ע��"), _T("�����˻�"), MB_ICONSTOP | MB_SETFOREGROUND);//�����ʾ�������û�
				return;//����forѭ��
			}

		}
		if (i >= all_players)//˵��û���ҵ��ظ����û��� 
			break;
	} while (1);//����û����ظ���һֱѭ����ֱ�����ظ�ʱ����ѭ�� 
			   //�����û����������� 

  /*���������û�����*/
	do {
		InputBox(player[all_players].play_password, 10, _T("����������"));//��ʾ�û���������
		InputBox(player[all_players].play_password2, 10, _T("��ȷ������"));//��ʾ�û�ȷ������
		if (wcscmp(player[all_players].play_password, player[all_players].play_password2) != 0)//�����������벻��� 
			MessageBox(NULL, _T("�������벻һ�£�����������"), _T("�����˻�"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
		{
			MessageBox(NULL, _T("ע��ɹ���"), _T("�����˻�"), MB_SETFOREGROUND);
		   //��ʼ����ע���û�
			player[all_players].player_num = all_players;
			player[all_players].player_type_times = 0;//��ʼ����ϰ����Ϊ0
			all_players++;//������һ����Ҫע����û��ı��
			SaveFile(fp);//�����ļ����溯��
			break;
		}
	} while (1);
}

/*�ѵ�¼�û�����*/
void been_user_login(FILE* fp) {
	tough = 1;//δ�����Ѷ�ѡ��ʱĬ���Ѷ�Ϊ1��
	loadimage(&users, L"users.jpg");
	putimage(0, 0, &users);
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			/*ʵ�ֶ�̬��ť*/
			if (msg.x > 480 && msg.x < 860 && msg.y > 190 && msg.y < 310) {
				loadimage(&user_begin_button, L"user_begin_button.jpg");
				putimage(0, 0, &user_begin_button);
			}
			else if (msg.x > 480 && msg.x < 860 && msg.y > 360 && msg.y < 480) {
				loadimage(&user_select_button, L"user_select_button.jpg");
				putimage(0, 0, &user_select_button);
			}
			else if (msg.x > 480 && msg.x < 860 && msg.y > 540 && msg.y < 650) {
				loadimage(&user_find_button, L"user_find_button.jpg");
				putimage(0, 0, &user_find_button);
			}
			else if (msg.x > 1115 && msg.x < 1335 && msg.y > 540 && msg.y < 650) {
				loadimage(&user_quit_button, L"user_quit_button.jpg");
				putimage(0, 0, &user_quit_button);
			}
			else if (msg.x > 90 && msg.x < 310 && msg.y > 540 && msg.y < 650) {
				loadimage(&user_return_button, L"user_return_button.jpg");
				putimage(0, 0, &user_return_button);
			}
			else {
				putimage(0, 0, &users);
			}

			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 480 && msg.x < 860 && msg.y > 190 && msg.y < 310) {
					loadimage(&user_begin_button, L"user_begin_button.jpg");
					putimage(0, 0, &user_begin_button);
					Sleep(100);
					user_type_ing(fp);
					initgraph(1366, 700);
					putimage(0, 0, &users);
				}
				else if (msg.x > 480 && msg.x < 860 && msg.y > 360 && msg.y < 480) {
					loadimage(&user_select_button, L"user_select_button.jpg");
					putimage(0, 0, &user_select_button);
					Sleep(100);
					user_type_select(fp);
					initgraph(1366, 700);
					putimage(0, 0, &users);
				}
				else if (msg.x > 480 && msg.x < 860 && msg.y > 540 && msg.y < 650) {
					loadimage(&user_find_button, L"user_find_button.jpg");
					putimage(0, 0, &user_find_button);
					Sleep(100);
					user_look_record(fp);
					initgraph(1366, 700);
					putimage(0, 0, &users);
				}
				else if (msg.x > 1115 && msg.x < 1335 && msg.y > 540 && msg.y < 650) {
					loadimage(&user_quit_button, L"user_quit_button.jpg");
					putimage(0, 0, &user_quit_button);
					Sleep(250);
					loadimage(&ending, L"ending.jpg");
					putimage(0, 0, &ending);
					Sleep(5000);
					exit(0);
				}
				else if (msg.x > 90 && msg.x < 310 && msg.y > 540 && msg.y < 650) {
					loadimage(&user_return_button, L"user_return_button.jpg");
					putimage(0, 0, &user_return_button);
					Sleep(250);
					return ;
				}
			}
		}
	}
}

/*�Ѷ�ѡ��*/
void user_type_select(FILE* fp) {
	system("cls");//����̨��������
	closegraph();
	while (true) {
		printf("************************************************************************************\n");
		printf("���ã�����ѡ��������Ҫ��ϰ���Ѷ�ϵ����1.�� 2.�м� 3.���� (ֱ���������ּ���)");
		printf("\n************************************************************************************\n");
		scanf_s("%d", &tough);
		if (tough != 1 && tough != 2 && tough != 3)
			printf("\n�Ƿ�����,����������\n");
		else {
			printf("\nѡ��ɹ���");
			break;
		}
	}
	printf("\n************************************************************************************\n");
	printf("��������ص��û��˵�...");
	_getch();
	system("cls");//����̨��������
	return;
}

/*��ʼ��ϰ*/
void user_type_ing(FILE* fp) {
	system("cls");//����̨��������
	closegraph();
	int count = 0; //�Ƿ�
	int txt_char = 0;//�ı��ַ���
	char a[100000] = { "\0" };//�洢�����ַ�
	char c[100000] = { "\0" };//�洢�ı��ַ�
	int i = 0;//ѭ����������
	int practice_time;//��ϰʱ��
	double score;//���ճɼ�

	/*������ϰing*/
	FILE* fp_p;
	fopen_s(&fp_p, "123.txt", "r+");
	printf("************************************************************************************\n");
	printf("���濪ʼ������ϰ����ѡ����Ѷȵȼ���:%d(��δ�����Ѷ�ѡ��ϵͳĬ��1������ģʽ��),\n���������˴�ѡ��Ĵ�����ϰ�ı�:����Esc���������ֲ�����÷֣�\n",tough);
	if (tough == 1) {
		srand(time(0));//�������������
		int n = 20;
		while (n--) {
			c[i++] = 'a' + rand() % 26;
			printf("%c", c[i - 1]);
			c[i++] = ' ';
			printf("%c", c[i - 1]);
		}
		n = 20;
		while (n--) {
			c[i++] = 'A' + rand() % 26;
			printf("%c", c[i - 1]);
			if (n != 0) {
				c[i++] = ' ';
				printf("%c", c[i - 1]);
			}
		}
	}//��ģʽ �������20��Сд ��д��ĸ
	if (tough == 2) {
		fopen_s(&fp_p, "middle.txt", "r+");
		while (!feof(fp_p)) {
			fread(&c[i++], sizeof(char), 1, fp_p);
			printf("%c", c[i - 1]); //���ı��ж��벢�ڿ���̨��ӡ����
		}
		fclose(fp_p);
	}//�м�ģʽ ��������
	if (tough == 3) {
		fopen_s(&fp_p, "difficult.txt", "r+");
		while (!feof(fp_p)) {
			fread(&c[i++], sizeof(char), 1, fp_p);
			printf("%c", c[i - 1]); //���ı��ж��벢�ڿ���̨��ӡ����
		}
		fclose(fp_p);
	}//����ģʽ ��������
	for (i = 0; c[i] != '\0'; i++)
		txt_char++;
	printf("\n************************************************************************************\n");
	printf("���������ʼ���Ĵ�����ϰ");
	_getch();
	printf("\n************************************************************************************\n");
	printf("���ͣ�С�����������룺\n");
	i = 0;
	time_t start, end;//��ʱ��
	start = time(NULL);

	while (true) {
		fflush(stdin);//��ջ�����
		a[i++] = _getch();

		if (a[i - 1] == 0x1b) {
			printf("\n************************************************************************************\n");
			printf("������ϰ������");
			break; //��Esc����������ϰ
		}
		else if (a[i - 1] == 0x8) {
			printf("\b \b");
			a[i - 2] = '\0';
			a[i - 1] = '\0';
			i = i - 2;//�����˸���˸�
		}
		else if (i > txt_char) {
			printf("\n************************************************************************************\n");
			printf("���ѳ������ı����������Զ�����");
			break;//�����ı�����������������ϰ
		}
		else if (a[i - 1] == c[i - 1]) {
			printf("%c", a[i - 1]);//���ı�һ�£���ʾ���ַ�
		}
		else
			printf("*");//���ı���һ�£���*����
	}
	end = time(NULL);//������ʱ
	practice_time = difftime(end, start);//�õ�����ʱ��


	/*��ʼͳ��ing*/
	for (i = 0, count = 0; i < txt_char; i++) {
      	if (a[i] == c[i])
			count++;
	}
	score = (double)count / txt_char;
	score = score * 100.0;

	/*����ɼ����浵*/
	int player_type_times = player[login_player].player_type_times;
	player[login_player].player_type_times++;
	player[login_player].record[player_type_times].difficulty_coeffeicents = tough;
	player[login_player].record[player_type_times].process = score;
	player[login_player].record[player_type_times].type_time = practice_time;
	SaveFile(fp);
	printf("\n************************************************************************************\n");
	printf("������ȷ��:%lf%%\n���ֺ�ʱ:%ds", score, practice_time);
	printf("\n************************************************************************************\n");
	printf("��������ص��û��˵�...");
	_getch();
	system("cls");//����̨��������
	return;
}

/*�鿴�浵*/
void user_look_record(FILE* fp) {
	system("cls");//����̨��������
	closegraph();
	int type_times = player[login_player].player_type_times;
	printf("�𾴵��û�:");
	_wsetlocale(LC_ALL, L"chs");
	wprintf(L"%s", player[login_player].play_name);//��ע ���ַ��� �ַ��������wprintf
	printf(",���ã�\n\t������ϰ����Ϊ%d", type_times);
	printf("\n************************************************************************************\n");
	for (int i = 0; i < type_times; i++) {
		printf("\n��%d����ϰ:\n\t��ѡ�Ѷ�ϵ��:%d\n\t������ȷ��:%lf%%\t\n\t���ֺ�ʱ:%ds", i + 1, player[login_player].record[i].difficulty_coeffeicents, player[login_player].record[i].process, player[login_player].record[i].type_time);
	}
	printf("\n************************************************************************************\n");
	printf("��������ص��û��˵�...");
	_getch();
	system("cls");//����̨��������
	return;
}

/*����Ա��¼������*/
void admin_action(FILE* fp) {
	wchar_t adminname[20];//����һ����ʱ�洢�û������ַ����� 
	wchar_t adminpassword[20];//����һ����ʱ�洢������ַ����� 
	/*����Ա������*/
	InputBox(adminname, 10, _T("���������Ա��"));//��ʾ�û��������Ա�����������ʱ�洢����Ա�����ַ�����
	if (wcscmp(adminname, admin_login.admin_name) != 0) {//˵��û���ҵ���Ӧ����Ա�� 
		MessageBox(NULL, _T("�ù���Ա������"), _T("����Ա��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
		return;
	}
	/*����Ա��������*/
	InputBox(adminpassword, 10, _T("����������"));//��ʾ�û��������룬�������ʱ�洢������ַ�����
	if (wcscmp(adminpassword, admin_login.admin_password) == 0)//������� 
	{
		MessageBox(NULL, _T("��¼�ɹ���"), _T("����Ա��¼"), MB_SETFOREGROUND);
		loadimage(&admin, L"admin.jpg");
		putimage(0, 0, &admin);
		MOUSEMSG msg;//������������������Ϣ
		FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
		while (true) // ��ѭ��,ѭ�����������Ϣ
		{
			while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
			{
				msg = GetMouseMsg();//��ȡ�����Ϣ

				/*ʵ�ֶ�̬��ť*/
				if (msg.x > 480 && msg.x < 860 && msg.y > 190 && msg.y < 310) {
					loadimage(&admin_text_button, L"admin_text_button.jpg");
					putimage(0, 0, &admin_text_button);
				}
				else if (msg.x > 480 && msg.x < 860 && msg.y > 360 && msg.y < 480) {
					loadimage(&admin_password_button, L"admin_password_button.jpg");
					putimage(0, 0, &admin_password_button);
				}
				else if (msg.x > 480 && msg.x < 860 && msg.y > 540 && msg.y < 650) {
					loadimage(&admin_record_button, L"admin_record_button.jpg");
					putimage(0, 0, &admin_record_button);
				}
				else if (msg.x > 1115 && msg.x < 1335 && msg.y > 540 && msg.y < 650) {
					loadimage(&admin_quit_button, L"admin_quit_button.jpg");
					putimage(0, 0, &admin_quit_button);
				}
				else if (msg.x > 90 && msg.x < 310 && msg.y > 540 && msg.y < 650) {
					loadimage(&admin_return_button, L"admin_return_button.jpg");
					putimage(0, 0, &admin_return_button);
				}
				else {
					putimage(0, 0, &admin);
				}

				if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
				{
					if (msg.x > 480 && msg.x < 860 && msg.y > 190 && msg.y < 310) {
						loadimage(&admin_text_button, L"admin_text_button.jpg");
						putimage(0, 0, &admin_text_button);
						Sleep(100);
						admin_text_control(fp);
						initgraph(1366, 700);
						putimage(0, 0, &admin);
					}
					if (msg.x > 480 && msg.x < 860 && msg.y > 360 && msg.y < 480) {
						loadimage(&admin_password_button, L"admin_password_button.jpg");
						putimage(0, 0, &admin_password_button);
						Sleep(100);
						admin_password_control(fp);
					}
					if (msg.x > 480 && msg.x < 860 && msg.y > 540 && msg.y < 650) {
						loadimage(&admin_record_button, L"admin_record_button.jpg");
						putimage(0, 0, &admin_record_button);
						Sleep(100);
						admin_look_record(fp);
						initgraph(1366, 700);
						putimage(0, 0, &admin);
					}
					if (msg.x > 1115 && msg.x < 1335 && msg.y > 540 && msg.y < 650) {
						loadimage(&admin_quit_button, L"admin_quit_button.jpg");
						putimage(0, 0, &admin_quit_button);
						Sleep(250);
						loadimage(&ending, L"ending.jpg");
						putimage(0, 0, &ending);
						Sleep(5000);
						exit(0);
					}
					if (msg.x > 90 && msg.x < 310 && msg.y > 540 && msg.y < 650) {
						loadimage(&admin_return_button, L"admin_return_button.jpg");
						putimage(0, 0, &admin_return_button);
						Sleep(250);
						return;
					}
				}
			}
		}

	}
	else {
		MessageBox(NULL, _T("�ù���Ա������������µ�¼"), _T("����Ա��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
		return;
	}
}

/*����Ա�ı�������*/
void admin_text_control(FILE* fp) {
	system("cls");//����̨��������
	closegraph();
	int select_1;
	int select_2;
	int i = 0;
	int flag = 1;
	int m = 0;
	int n = 0;
	char save[10000] = { '\0' };
	char c[10000] = { '\0' };
	char temp_1[1000] = { '\0' };
	char temp_2[1000] = { '\0' };
	printf("\n************************************************************************************\n");
	printf("��ѡ������Ҫ������ı���1.middle�ı� 2.difficult�ı�������ֱ���������ּ��ɣ�\n��ע:�����ı���ȡ���������ĸģʽ�����޸�");
	printf("\n************************************************************************************\n");
	scanf_s("%d", &select_1);
	fflush(stdin);
	printf("************************************************************************************\n");
	printf("��ѡ������Ҫ��������ͣ�1.�޸� 2.���� 3.ɾ�� ������ֱ���������ּ��ɣ�");
	printf("\n************************************************************************************\n");
	scanf_s("%d", &select_2);
	fflush(stdin);
	FILE* fp_p;
	if (select_1 == 1 && select_2 == 1) {
		fopen_s(&fp_p, "middle.txt", "rb+");
		while (!feof(fp_p)) {
			fread(&c[i++], sizeof(char), 1, fp_p);
			printf("%c", c[i - 1]); //���ı��ж��벢�ڿ���̨��ӡ����
		}
		printf("\n************************************************************************************\n");
		printf("���������Ҫ�޸ĵ�ԭ�ı�����:");
		getchar();//�̵�һ���س���
		gets_s(temp_1);
		printf("************************************************************************************\n");
		printf("���������Ҫ�޸ĳ�ʲô����:");
		gets_s(temp_2);
		printf("************************************************************************************\n");
		for (i = 0; c[i]; i++) {
			save[n++] = c[i];
			if (c[i] == temp_1[0]) {
				m = i;
				int q;
				for (q = 0, flag = 1; temp_1[q]; q++) {
					if (c[i++] != temp_1[q]) {
						flag = 0;
						i = i - 1;
						break;
					}
				}
				if (flag) {
					i = i - 1;
					n = n - 1;
					for (q = 0; temp_2[q]; q++) {
						save[n++] = temp_2[q];
					}
				}
				else {
					int b = i - m;
					m = m + 1;
					for (; b; b--)
						save[n++] = c[m++];
				}
			}
		}
		fclose(fp_p);
		//��ʼд��
		fopen_s(&fp_p, "middle.txt", "w");
		for (i = 0; save[i]; i++)
			fprintf(fp_p, "%c", save[i]);
		fclose(fp_p);
		printf("�޸���ɣ��޸ĺ��ļ�����;\n");
		fopen_s(&fp_p, "middle.txt", "rb+");
		i = 0;
		while (!feof(fp_p)) {
			fread(&save[i++], sizeof(char), 1, fp_p);
			printf("%c", save[i - 1]); //���ı��ж��벢�ڿ���̨��ӡ����
		}
		fclose(fp);
		printf("\n************************************************************************************\n");
	}
	else if (select_1 == 1 && select_2 == 2) {
		fopen_s(&fp_p, "middle.txt", "rb+");
		while (!feof(fp_p)) {
			fread(&c[i++], sizeof(char), 1, fp_p);
			printf("%c", c[i - 1]); //���ı��ж��벢�ڿ���̨��ӡ����
		}
		printf("\n************************************************************************************\n");
		printf("���������Ҫ���ӵ��ı�����:");
		getchar();//�̵�һ���س���
		gets_s(temp_1);
		printf("************************************************************************************\n");
		for (i = 0; temp_1[i]; i++)
			fprintf(fp_p, "%c", temp_1[i]);
		fclose(fp_p);
		printf("������ɣ����Ӻ��ļ�����;\n");
		fopen_s(&fp_p, "middle.txt", "rb+");
		i = 0;
		while (!feof(fp_p)) {
			fread(&save[i++], sizeof(char), 1, fp_p);
			printf("%c", save[i - 1]); //���ı��ж��벢�ڿ���̨��ӡ����
		}
		fclose(fp);
		printf("\n************************************************************************************\n");
	}
	else if (select_1 == 1 && select_2 == 3) {
		fopen_s(&fp_p, "middle.txt", "rb+");
		while (!feof(fp_p)) {
			fread(&c[i++], sizeof(char), 1, fp_p);
			printf("%c", c[i - 1]); //���ı��ж��벢�ڿ���̨��ӡ����
		}
		printf("\n************************************************************************************\n");
		printf("���������Ҫɾ����ԭ�ı�����:");
		getchar();//�̵�һ���س���
		gets_s(temp_1);
		printf("************************************************************************************\n");
		for (i = 0; c[i]; i++) {
			save[n++] = c[i];
			if (c[i] == temp_1[0]) {
				m = i;
				int q;
				for (q = 0, flag = 1; temp_1[q]; q++) {
					if (c[i++] != temp_1[q]) {
						flag = 0;
						i = i - 1;
						break;
					}
				}
				if (flag) {
					i = i - 1;
					n = n - 1;
					save[n] = '\0';
				}

				else {
					int b = i - m;
					m = m + 1;
					for (; b; b--)
						save[n++] = c[m++];
				}
			}
		}
		fclose(fp_p);
		//��ʼд��
		fopen_s(&fp_p, "middle.txt", "w");
		for (i = 0; save[i]; i++)
			fprintf(fp_p, "%c", save[i]);
		fclose(fp_p);
		printf("ɾ����ɣ�ɾ�����ļ�����;\n");
		fopen_s(&fp_p, "middle.txt", "rb+");
		i = 0;
		while (!feof(fp_p)) {
			fread(&save[i++], sizeof(char), 1, fp_p);
			printf("%c", save[i - 1]); //���ı��ж��벢�ڿ���̨��ӡ����
		}
		fclose(fp);
		printf("\n************************************************************************************\n");
	}
	else if (select_1 == 2 && select_2 == 1) {
		fopen_s(&fp_p, "difficult.txt", "rb+");
		while (!feof(fp_p)) {
			fread(&c[i++], sizeof(char), 1, fp_p);
			printf("%c", c[i - 1]); //���ı��ж��벢�ڿ���̨��ӡ����
		}
		printf("\n************************************************************************************\n");
		printf("���������Ҫ�޸ĵ�ԭ�ı�����:");
		getchar();//�̵�һ���س���
		gets_s(temp_1);
		printf("************************************************************************************\n");
		printf("���������Ҫ�޸ĳ�ʲô����:");
		gets_s(temp_2);
		printf("************************************************************************************\n");
		for (i = 0; c[i]; i++) {
			save[n++] = c[i];
			if (c[i] == temp_1[0]) {
				m = i;
				int q;
				for (q = 0, flag = 1; temp_1[q]; q++) {
					if (c[i++] != temp_1[q]) {
						flag = 0;
						i = i - 1;
						break;
					}
				}
				if (flag) {
					i = i - 1;
					n = n - 1;
					for (q = 0; temp_2[q]; q++) {
						save[n++] = temp_2[q];
					}
				}
				else {
					int b = i - m;
					m = m + 1;
					for (; b; b--)
						save[n++] = c[m++];
				}
			}
		}
		fclose(fp_p);
		//��ʼд��
		fopen_s(&fp_p, "difficult.txt", "w");
		for (i = 0; save[i]; i++)
			fprintf(fp_p, "%c", save[i]);
		fclose(fp_p);
		printf("�޸���ɣ��޸ĺ��ļ�����;\n");
		fopen_s(&fp_p, "difficult.txt", "rb+");
		i = 0;
		while (!feof(fp_p)) {
			fread(&save[i++], sizeof(char), 1, fp_p);
			printf("%c", save[i - 1]); //���ı��ж��벢�ڿ���̨��ӡ����
		}
		fclose(fp);
		printf("\n************************************************************************************\n");
	}
	else if (select_1 == 2 && select_2 == 2) {
		fopen_s(&fp_p, "difficult.txt", "rb+");
		while (!feof(fp_p)) {
			fread(&c[i++], sizeof(char), 1, fp_p);
			printf("%c", c[i - 1]); //���ı��ж��벢�ڿ���̨��ӡ����
		}
		printf("\n************************************************************************************\n");
		printf("���������Ҫ���ӵ��ı�����:");
		getchar();//�̵�һ���س���
		gets_s(temp_1);
		printf("************************************************************************************\n");
		for (i = 0; temp_1[i]; i++)
			fprintf(fp_p, "%c", temp_1[i]);
		fclose(fp_p);
		printf("������ɣ����Ӻ��ļ�����;\n");
		fopen_s(&fp_p, "difficult.txt", "rb+");
		i = 0;
		while (!feof(fp_p)) {
			fread(&save[i++], sizeof(char), 1, fp_p);
			printf("%c", save[i - 1]); //���ı��ж��벢�ڿ���̨��ӡ����
		}
		fclose(fp);
		printf("\n************************************************************************************\n");
	}
	else if (select_1 == 2 && select_2 == 3) {
		fopen_s(&fp_p, "difficult.txt", "rb+");
		while (!feof(fp_p)) {
			fread(&c[i++], sizeof(char), 1, fp_p);
			printf("%c", c[i - 1]); //���ı��ж��벢�ڿ���̨��ӡ����
		}
		printf("\n************************************************************************************\n");
		printf("���������Ҫɾ����ԭ�ı�����:");
		getchar();//�̵�һ���س���
		gets_s(temp_1);
		printf("************************************************************************************\n");
		for (i = 0; c[i]; i++) {
			save[n++] = c[i];
			if (c[i] == temp_1[0]) {
				m = i;
				int q;
				for (q = 0, flag = 1; temp_1[q]; q++) {
					if (c[i++] != temp_1[q]) {
						flag = 0;
						i = i - 1;
						break;
					}
				}
				if (flag) {
					i = i - 1;
					n = n - 1;
					save[n] = '\0';
				}

				else {
					int b = i - m;
					m = m + 1;
					for (; b; b--)
						save[n++] = c[m++];
				}
			}
		}
		fclose(fp_p);
		//��ʼд��
		fopen_s(&fp_p, "difficult.txt", "w");
		for (i = 0; save[i]; i++)
			fprintf(fp_p, "%c", save[i]);
		fclose(fp_p);
		printf("ɾ����ɣ�ɾ�����ļ�����;\n");
		fopen_s(&fp_p, "difficult.txt", "rb+");
		i = 0;
		while (!feof(fp_p)) {
			fread(&save[i++], sizeof(char), 1, fp_p);
			printf("%c", save[i - 1]); //���ı��ж��벢�ڿ���̨��ӡ����
		}
		fclose(fp);
		printf("\n************************************************************************************\n");
	}
	else {
		printf("�Ƿ����룡\n");
	}
	printf("��������ص��û��˵�...");
	_getch();
	system("cls");//����̨��������
}

/*����Ա�û������һغ���*/
void admin_password_control(FILE* fp) {
	int i;
	wchar_t username[20];//����һ����ʱ�洢�û������ַ�����
	InputBox(username, 10, _T("�������û���"));//��ʾ�û������û������������ʱ�洢�û������ַ�����
	for (i = 0; i < all_players; i++)
		if (wcscmp(username, player[i].play_name) == 0)//�ҵ��� 
		{
			login_player = i;//����õ�¼ѧ�������
			break;//����forѭ��
		}//��¼�����û�������Ӧ��ѧ����ţ�����¼���û�����Ӧ�ı�� 

	if (i >= all_players) {//˵��û���ҵ���Ӧ�û��� 
		MessageBox(NULL, _T("���û�������"), _T("�û��һ�����"), MB_ICONSTOP | MB_SETFOREGROUND);
		return;
	}

	//�ҵ��˴��û�����������������ģ�� 

  /*���������û�����*/
	do{
		InputBox(player[login_player].play_password, 10, _T("����������"));//��ʾ�û���������
		InputBox(player[login_player].play_password2, 10, _T("��ȷ������"));//��ʾ�û�ȷ������
		if (wcscmp(player[login_player].play_password, player[login_player].play_password2) != 0)//�����������벻��� 
			MessageBox(NULL, _T("�������벻һ�£�����������"), _T("��������"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
		{
			MessageBox(NULL, _T("���óɹ���"), _T("��������"), MB_SETFOREGROUND);
			SaveFile(fp);//�����ļ����溯��
			break;
		}
	} while (1);
}

/*���¹��� ����Ա�ɲ�ѯ�����û���ϰ��¼�������û�����ϰ��¼*/
void admin_look_record(FILE* fp) {
	system("cls");//����̨��������
	closegraph();
	if (all_players == 0)
		printf("�����û���¼\n");
	else {
		printf("�˴��ֳ������û�%d��,����ּ�¼�ֱ����£�\n", all_players);
		for (int i = 0; i < all_players; i++) {
			int type_times = player[i].player_type_times;
			_wsetlocale(LC_ALL, L"chs");
			wprintf(L"%s", player[i].play_name);//��ע ���ַ��� �ַ��������wprintf
			printf("����ϰ����Ϊ%d", type_times);
			printf("\n************************************************************************************\n");
			for (int q = 0; q < type_times; q++) {
				printf("\n��%d����ϰ:\n\t��ѡ�Ѷ�ϵ��:%d\n\t������ȷ��:%lf%%\t\n\t���ֺ�ʱ:%ds", q + 1, player[i].record[q].difficulty_coeffeicents, player[i].record[q].process, player[i].record[q].type_time);
			}
			printf("\n************************************************************************************\n");
		}
		printf("�Ƿ���Ҫ�����û�����ϰ��¼?1.�� 2.���������ּ��ɣ�");
		printf("\n************************************************************************************\n");
		int y_n;
		int i;
		int flag=1;
		wchar_t username[20];//����һ����ʱ�洢�û������ַ�����
		scanf_s("%d", &y_n);
		if (y_n == 1) {
			printf("\n************************************************************************************\n");
			printf("��������Ҫ���õ��û����û���:");
			_wsetlocale(LC_ALL, L"chs");
			wscanf_s(L"%s", username,20);
			printf("\n************************************************************************************\n");
			for (i = 0; i < all_players; i++)
				if (wcscmp(username, player[i].play_name) == 0)//�ҵ��� 
				{
					player[i].player_type_times = 0;//���øü�¼
					SaveFile(fp);
					printf("���óɹ���");
					flag = 0;
					printf("\n************************************************************************************\n");
				}//��¼�����û�������Ӧ��ѧ����ţ�����¼���û�����Ӧ�ı�� 
			if (i >= all_players&&flag) {//˵��û���ҵ���Ӧ�û��� 
				printf("���û������ڣ�");
				printf("\n************************************************************************************\n");
			}
		}
		else if (y_n == 2)
			printf("\n************************************************************************************\n");
		else {
			printf("�Ƿ����룡");
			printf("\n************************************************************************************\n");
		}
	}
	printf("��������ص�����Ա�˵�...");
	_getch();
	system("cls");//����̨��������
	return;
}

/*main����*/
int main() {
	FILE* fp;
	fopen_s(&fp, "alldata.txt", "rb+");//���ļ�

	/*�ж��Ƿ��һ��ʹ�ô�����������Ƚ��г�ʼ���û������Ȳ���������ֱ�Ӷ�ȡ*/
	int judge;
	judge = fgetc(fp);
	fclose(fp);//�ر��ļ�
	if (judge == EOF) 
		SaveFile(fp);
	else {
		fopen_s(&fp, "alldata.txt", "rb+");//���´��ļ�
		fread(&all_players, 4, 1, fp);
		fread(&login_player, 4, 1, fp);
		/*�����û��ṹ������*/
		for (int i = 0; i < all_players; i++)
			fread(&player[i], sizeof(struct get_player), 1, fp);
	}
	fclose(fp);
	initgraph(1366, 700);//���ڴ�С
	ini_window(fp);//�����ҳ��
	return 0;
}
