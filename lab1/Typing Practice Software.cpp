/************************************************************************
项目：打字小程序（山寨打字王）
开发者：191180044-何东宸
程序功能：1）设计用户端口和管理员端口
		  2）用户端口：注册、登录账号、练习难度选择、打字练习记录
		  3）管理员端口：打字文本管理、用户密码找回
		  4) 图形界面，良好的人机交互
		  6）系统会进行实时保存每次的练习记录
备注：    
		  管理员用户名：admin
		  管理员密码：admin
		  请勿删除或移动数据文本文件，图形界面jpg文件
		  请提前安装easyx图形库
************************************************************************/

/*库函数定义*/
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<tchar.h>
#include<graphics.h>
#include<time.h>
#include<locale.h>


/*定义全局变量*/
int all_players = 0;//定义总用户序号（也即总用户人数）
int login_player = 0;//定义登录的用户序号
int tough = 1;//定义难度系数


/*图片定义*/
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

/*打字练习记录结构体数组定义*/
struct type_record {
	double process;//定义打字进度
	int type_time;//定义打字所花时间
	int difficulty_coeffeicents;//定义所练习的难度系数，分为1（简单），2（较难），3（最难） 
};

/*用户结构体数组定义*/
struct get_player {
	wchar_t play_name[20]; //定义用户名
	wchar_t play_password[20]; //定义用户密码
	wchar_t play_password2[20];//定义用户输入的第二次密码
	int player_num; //定义用户序号
	int player_type_times; //定义用户使用打字的次数
	type_record record[20];//定义用户的打字记录
}player[50];

/*管理员结构体数组定义*/
struct administrator {
	wchar_t admin_name[20]; //定义管理员名
	wchar_t admin_password[20]; //定义管理员密码
}admin_login = { _T("admin"),_T("admin") };

//函数声明
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



/*文件保存函数*/
void SaveFile(FILE* fp)
{
	fopen_s(&fp, "alldata.txt", "rb+");
	//向文件输出全局变量
	fwrite(&all_players, 4, 1, fp);
	fwrite(&login_player, 4, 1, fp);
	//输出用户结构体数据
	for (int i = 0; i < all_players; i++)
		fwrite(&player[i], sizeof(struct get_player), 1, fp);
	//输出管理员结构体数组 
	fwrite(&admin_login, sizeof(struct administrator), 1, fp);
	fclose(fp);
}

/*菜单初始化界面函数*/
void ini_window(FILE* fp) {
	loadimage(&initial, L"initial.jpg");
	putimage(0, 0, &initial);
	MOUSEMSG msg;//定义变量鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区
	while (true) // 主循环,监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行为真
		{
			msg = GetMouseMsg();//获取鼠标消息

			/*实现动态按钮*/
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
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
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

/*用户登录*/
void user_login(FILE* fp) {
	int i;
	wchar_t username[20];//定义一个临时存储用户名的字符数组 
	wchar_t password[20];//定义一个临时存储密码的字符数组 

	InputBox(username, 10, _T("请输入用户名"));//提示用户输入用户名，输入给临时存储用户名的字符数组
	for (i = 0; i < all_players; i++)
		if (wcscmp(username, player[i].play_name) == 0)//找到了 
		{
			login_player = i;//保存该登录学生的序号
			break;//跳出for循环
		}//记录输入用户名所对应的学生编号，即登录的用户所对应的编号 

	if (i >= all_players) {//说明没有找到对应用户名 
		MessageBox(NULL, _T("该用户不存在"), _T("用户登录"), MB_ICONSTOP | MB_SETFOREGROUND);
		return;
	}

	//找到了此用户名，进入输入密码模块 


	/*输入密码模块*/
	InputBox(password, 10, _T("请输入密码"));//提示用户输入密码，输入给临时存储密码的字符数组
	if (wcscmp(password, player[login_player].play_password) == 0)//密码符合 
	{
		MessageBox(NULL, _T("登录成功！"), _T("用户登录"), MB_SETFOREGROUND);
		//参数分别为：消息框拥有的窗口、消息框的内容、消息框的标题、标志集(多个标志用"与"(|)符号连接)
		//最后的参数表示设置消息框为前景窗口
		been_user_login(fp);
		return;
	}//结束密码输入模块 
	else {
		MessageBox(NULL, _T("密码错误"), _T("学生登录"), MB_ICONSTOP | MB_SETFOREGROUND);
		return;
	}
}

/*用户注册*/
void user_register(FILE* fp) {
	/*输入用户名*/
	int i;
	do {
		InputBox(player[all_players].play_name, 10, _T("请输入用户名"));//提示用户输入用户名
		//接下来查找用户信息表中的内容，比较新输入的用户名是否存在，如果存在，系统给出提示
		for (i = 0; i < all_players; i++)
		{
			if (wcscmp(player[i].play_name, player[all_players].play_name) == 0)
			{
				MessageBox(NULL, _T("该用户已经存在，请重新注册"), _T("创建账户"), MB_ICONSTOP | MB_SETFOREGROUND);//输出提示，提醒用户
				return;//跳出for循环
			}

		}
		if (i >= all_players)//说明没有找到重复的用户名 
			break;
	} while (1);//如果用户名重复则一直循环，直到不重复时跳出循环 
			   //输入用户名函数结束 

  /*下面设置用户密码*/
	do {
		InputBox(player[all_players].play_password, 10, _T("请设置密码"));//提示用户输入密码
		InputBox(player[all_players].play_password2, 10, _T("请确认密码"));//提示用户确认密码
		if (wcscmp(player[all_players].play_password, player[all_players].play_password2) != 0)//两次输入密码不相等 
			MessageBox(NULL, _T("两次输入不一致，请重新输入"), _T("创建账户"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
		{
			MessageBox(NULL, _T("注册成功！"), _T("创建账户"), MB_SETFOREGROUND);
		   //初始化此注册用户
			player[all_players].player_num = all_players;
			player[all_players].player_type_times = 0;//初始化练习次数为0
			all_players++;//代表下一个将要注册的用户的编号
			SaveFile(fp);//调用文件保存函数
			break;
		}
	} while (1);
}

/*已登录用户界面*/
void been_user_login(FILE* fp) {
	tough = 1;//未进行难度选择时默认难度为1级
	loadimage(&users, L"users.jpg");
	putimage(0, 0, &users);
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			/*实现动态按钮*/
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

			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
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

/*难度选择*/
void user_type_select(FILE* fp) {
	system("cls");//控制台清屏函数
	closegraph();
	while (true) {
		printf("************************************************************************************\n");
		printf("您好，请您选择您所需要练习的难度系数：1.简单 2.中级 3.困难 (直接输入数字即可)");
		printf("\n************************************************************************************\n");
		scanf_s("%d", &tough);
		if (tough != 1 && tough != 2 && tough != 3)
			printf("\n非法输入,请重新输入\n");
		else {
			printf("\n选择成功！");
			break;
		}
	}
	printf("\n************************************************************************************\n");
	printf("按任意键回到用户菜单...");
	_getch();
	system("cls");//控制台清屏函数
	return;
}

/*开始练习*/
void user_type_ing(FILE* fp) {
	system("cls");//控制台清屏函数
	closegraph();
	int count = 0; //记分
	int txt_char = 0;//文本字符数
	char a[100000] = { "\0" };//存储输入字符
	char c[100000] = { "\0" };//存储文本字符
	int i = 0;//循环辅助变量
	int practice_time;//练习时间
	double score;//最终成绩

	/*打字练习ing*/
	FILE* fp_p;
	fopen_s(&fp_p, "123.txt", "r+");
	printf("************************************************************************************\n");
	printf("下面开始打字练习，您选择的难度等级是:%d(若未进行难度选择，系统默认1级（简单模式）),\n以下是您此次选择的打字练习文本:（按Esc键结束打字并计算得分）\n",tough);
	if (tough == 1) {
		srand(time(0));//设置随机数种子
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
	}//简单模式 随机生成20个小写 大写字母
	if (tough == 2) {
		fopen_s(&fp_p, "middle.txt", "r+");
		while (!feof(fp_p)) {
			fread(&c[i++], sizeof(char), 1, fp_p);
			printf("%c", c[i - 1]); //从文本中读入并在控制台打印出来
		}
		fclose(fp_p);
	}//中级模式 单词输入
	if (tough == 3) {
		fopen_s(&fp_p, "difficult.txt", "r+");
		while (!feof(fp_p)) {
			fread(&c[i++], sizeof(char), 1, fp_p);
			printf("%c", c[i - 1]); //从文本中读入并在控制台打印出来
		}
		fclose(fp_p);
	}//困难模式 文章输入
	for (i = 0; c[i] != '\0'; i++)
		txt_char++;
	printf("\n************************************************************************************\n");
	printf("按任意键开始您的打字练习");
	_getch();
	printf("\n************************************************************************************\n");
	printf("加油！小宝贝！请输入：\n");
	i = 0;
	time_t start, end;//计时器
	start = time(NULL);

	while (true) {
		fflush(stdin);//清空缓存区
		a[i++] = _getch();

		if (a[i - 1] == 0x1b) {
			printf("\n************************************************************************************\n");
			printf("打字练习结束！");
			break; //按Esc结束打字练习
		}
		else if (a[i - 1] == 0x8) {
			printf("\b \b");
			a[i - 2] = '\0';
			a[i - 1] = '\0';
			i = i - 2;//输入退格键退格
		}
		else if (i > txt_char) {
			printf("\n************************************************************************************\n");
			printf("您已超过该文本字数，已自动结束");
			break;//超过文本字数，结束打字练习
		}
		else if (a[i - 1] == c[i - 1]) {
			printf("%c", a[i - 1]);//与文本一致，显示该字符
		}
		else
			printf("*");//与文本不一致，用*代替
	}
	end = time(NULL);//结束计时
	practice_time = difftime(end, start);//得到打字时间


	/*开始统计ing*/
	for (i = 0, count = 0; i < txt_char; i++) {
      	if (a[i] == c[i])
			count++;
	}
	score = (double)count / txt_char;
	score = score * 100.0;

	/*输出成绩并存档*/
	int player_type_times = player[login_player].player_type_times;
	player[login_player].player_type_times++;
	player[login_player].record[player_type_times].difficulty_coeffeicents = tough;
	player[login_player].record[player_type_times].process = score;
	player[login_player].record[player_type_times].type_time = practice_time;
	SaveFile(fp);
	printf("\n************************************************************************************\n");
	printf("打字正确率:%lf%%\n打字耗时:%ds", score, practice_time);
	printf("\n************************************************************************************\n");
	printf("按任意键回到用户菜单...");
	_getch();
	system("cls");//控制台清屏函数
	return;
}

/*查看存档*/
void user_look_record(FILE* fp) {
	system("cls");//控制台清屏函数
	closegraph();
	int type_times = player[login_player].player_type_times;
	printf("尊敬的用户:");
	_wsetlocale(LC_ALL, L"chs");
	wprintf(L"%s", player[login_player].play_name);//备注 宽字符集 字符串输出用wprintf
	printf(",您好：\n\t您的练习次数为%d", type_times);
	printf("\n************************************************************************************\n");
	for (int i = 0; i < type_times; i++) {
		printf("\n第%d次练习:\n\t所选难度系数:%d\n\t打字正确率:%lf%%\t\n\t打字耗时:%ds", i + 1, player[login_player].record[i].difficulty_coeffeicents, player[login_player].record[i].process, player[login_player].record[i].type_time);
	}
	printf("\n************************************************************************************\n");
	printf("按任意键回到用户菜单...");
	_getch();
	system("cls");//控制台清屏函数
	return;
}

/*管理员登录及界面*/
void admin_action(FILE* fp) {
	wchar_t adminname[20];//定义一个临时存储用户名的字符数组 
	wchar_t adminpassword[20];//定义一个临时存储密码的字符数组 
	/*管理员名输入*/
	InputBox(adminname, 10, _T("请输入管理员名"));//提示用户输入管理员名，输入给临时存储管理员名的字符数组
	if (wcscmp(adminname, admin_login.admin_name) != 0) {//说明没有找到对应管理员名 
		MessageBox(NULL, _T("该管理员不存在"), _T("管理员登录"), MB_ICONSTOP | MB_SETFOREGROUND);
		return;
	}
	/*管理员密码输入*/
	InputBox(adminpassword, 10, _T("请输入密码"));//提示用户输入密码，输入给临时存储密码的字符数组
	if (wcscmp(adminpassword, admin_login.admin_password) == 0)//密码符合 
	{
		MessageBox(NULL, _T("登录成功！"), _T("管理员登录"), MB_SETFOREGROUND);
		loadimage(&admin, L"admin.jpg");
		putimage(0, 0, &admin);
		MOUSEMSG msg;//定义变量，保存鼠标消息
		FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
		while (true) // 主循环,循环监听鼠标信息
		{
			while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
			{
				msg = GetMouseMsg();//获取鼠标消息

				/*实现动态按钮*/
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

				if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
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
		MessageBox(NULL, _T("该管理员密码错误，请重新登录"), _T("管理员登录"), MB_ICONSTOP | MB_SETFOREGROUND);
		return;
	}
}

/*管理员文本管理函数*/
void admin_text_control(FILE* fp) {
	system("cls");//控制台清屏函数
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
	printf("请选择您需要处理的文本：1.middle文本 2.difficult文本：（请直接输入数字即可）\n备注:简易文本采取随机生成字母模式无需修改");
	printf("\n************************************************************************************\n");
	scanf_s("%d", &select_1);
	fflush(stdin);
	printf("************************************************************************************\n");
	printf("请选择您需要处理的类型：1.修改 2.增加 3.删除 ：（请直接输入数字即可）");
	printf("\n************************************************************************************\n");
	scanf_s("%d", &select_2);
	fflush(stdin);
	FILE* fp_p;
	if (select_1 == 1 && select_2 == 1) {
		fopen_s(&fp_p, "middle.txt", "rb+");
		while (!feof(fp_p)) {
			fread(&c[i++], sizeof(char), 1, fp_p);
			printf("%c", c[i - 1]); //从文本中读入并在控制台打印出来
		}
		printf("\n************************************************************************************\n");
		printf("请键入您需要修改的原文本内容:");
		getchar();//吞掉一个回车键
		gets_s(temp_1);
		printf("************************************************************************************\n");
		printf("请键入您需要修改成什么内容:");
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
		//开始写入
		fopen_s(&fp_p, "middle.txt", "w");
		for (i = 0; save[i]; i++)
			fprintf(fp_p, "%c", save[i]);
		fclose(fp_p);
		printf("修改完成！修改后文件如下;\n");
		fopen_s(&fp_p, "middle.txt", "rb+");
		i = 0;
		while (!feof(fp_p)) {
			fread(&save[i++], sizeof(char), 1, fp_p);
			printf("%c", save[i - 1]); //从文本中读入并在控制台打印出来
		}
		fclose(fp);
		printf("\n************************************************************************************\n");
	}
	else if (select_1 == 1 && select_2 == 2) {
		fopen_s(&fp_p, "middle.txt", "rb+");
		while (!feof(fp_p)) {
			fread(&c[i++], sizeof(char), 1, fp_p);
			printf("%c", c[i - 1]); //从文本中读入并在控制台打印出来
		}
		printf("\n************************************************************************************\n");
		printf("请键入您需要增加的文本内容:");
		getchar();//吞掉一个回车键
		gets_s(temp_1);
		printf("************************************************************************************\n");
		for (i = 0; temp_1[i]; i++)
			fprintf(fp_p, "%c", temp_1[i]);
		fclose(fp_p);
		printf("增加完成！增加后文件如下;\n");
		fopen_s(&fp_p, "middle.txt", "rb+");
		i = 0;
		while (!feof(fp_p)) {
			fread(&save[i++], sizeof(char), 1, fp_p);
			printf("%c", save[i - 1]); //从文本中读入并在控制台打印出来
		}
		fclose(fp);
		printf("\n************************************************************************************\n");
	}
	else if (select_1 == 1 && select_2 == 3) {
		fopen_s(&fp_p, "middle.txt", "rb+");
		while (!feof(fp_p)) {
			fread(&c[i++], sizeof(char), 1, fp_p);
			printf("%c", c[i - 1]); //从文本中读入并在控制台打印出来
		}
		printf("\n************************************************************************************\n");
		printf("请键入您需要删除的原文本内容:");
		getchar();//吞掉一个回车键
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
		//开始写入
		fopen_s(&fp_p, "middle.txt", "w");
		for (i = 0; save[i]; i++)
			fprintf(fp_p, "%c", save[i]);
		fclose(fp_p);
		printf("删除完成！删除后文件如下;\n");
		fopen_s(&fp_p, "middle.txt", "rb+");
		i = 0;
		while (!feof(fp_p)) {
			fread(&save[i++], sizeof(char), 1, fp_p);
			printf("%c", save[i - 1]); //从文本中读入并在控制台打印出来
		}
		fclose(fp);
		printf("\n************************************************************************************\n");
	}
	else if (select_1 == 2 && select_2 == 1) {
		fopen_s(&fp_p, "difficult.txt", "rb+");
		while (!feof(fp_p)) {
			fread(&c[i++], sizeof(char), 1, fp_p);
			printf("%c", c[i - 1]); //从文本中读入并在控制台打印出来
		}
		printf("\n************************************************************************************\n");
		printf("请键入您需要修改的原文本内容:");
		getchar();//吞掉一个回车键
		gets_s(temp_1);
		printf("************************************************************************************\n");
		printf("请键入您需要修改成什么内容:");
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
		//开始写入
		fopen_s(&fp_p, "difficult.txt", "w");
		for (i = 0; save[i]; i++)
			fprintf(fp_p, "%c", save[i]);
		fclose(fp_p);
		printf("修改完成！修改后文件如下;\n");
		fopen_s(&fp_p, "difficult.txt", "rb+");
		i = 0;
		while (!feof(fp_p)) {
			fread(&save[i++], sizeof(char), 1, fp_p);
			printf("%c", save[i - 1]); //从文本中读入并在控制台打印出来
		}
		fclose(fp);
		printf("\n************************************************************************************\n");
	}
	else if (select_1 == 2 && select_2 == 2) {
		fopen_s(&fp_p, "difficult.txt", "rb+");
		while (!feof(fp_p)) {
			fread(&c[i++], sizeof(char), 1, fp_p);
			printf("%c", c[i - 1]); //从文本中读入并在控制台打印出来
		}
		printf("\n************************************************************************************\n");
		printf("请键入您需要增加的文本内容:");
		getchar();//吞掉一个回车键
		gets_s(temp_1);
		printf("************************************************************************************\n");
		for (i = 0; temp_1[i]; i++)
			fprintf(fp_p, "%c", temp_1[i]);
		fclose(fp_p);
		printf("增加完成！增加后文件如下;\n");
		fopen_s(&fp_p, "difficult.txt", "rb+");
		i = 0;
		while (!feof(fp_p)) {
			fread(&save[i++], sizeof(char), 1, fp_p);
			printf("%c", save[i - 1]); //从文本中读入并在控制台打印出来
		}
		fclose(fp);
		printf("\n************************************************************************************\n");
	}
	else if (select_1 == 2 && select_2 == 3) {
		fopen_s(&fp_p, "difficult.txt", "rb+");
		while (!feof(fp_p)) {
			fread(&c[i++], sizeof(char), 1, fp_p);
			printf("%c", c[i - 1]); //从文本中读入并在控制台打印出来
		}
		printf("\n************************************************************************************\n");
		printf("请键入您需要删除的原文本内容:");
		getchar();//吞掉一个回车键
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
		//开始写入
		fopen_s(&fp_p, "difficult.txt", "w");
		for (i = 0; save[i]; i++)
			fprintf(fp_p, "%c", save[i]);
		fclose(fp_p);
		printf("删除完成！删除后文件如下;\n");
		fopen_s(&fp_p, "difficult.txt", "rb+");
		i = 0;
		while (!feof(fp_p)) {
			fread(&save[i++], sizeof(char), 1, fp_p);
			printf("%c", save[i - 1]); //从文本中读入并在控制台打印出来
		}
		fclose(fp);
		printf("\n************************************************************************************\n");
	}
	else {
		printf("非法输入！\n");
	}
	printf("按任意键回到用户菜单...");
	_getch();
	system("cls");//控制台清屏函数
}

/*管理员用户密码找回函数*/
void admin_password_control(FILE* fp) {
	int i;
	wchar_t username[20];//定义一个临时存储用户名的字符数组
	InputBox(username, 10, _T("请输入用户名"));//提示用户输入用户名，输入给临时存储用户名的字符数组
	for (i = 0; i < all_players; i++)
		if (wcscmp(username, player[i].play_name) == 0)//找到了 
		{
			login_player = i;//保存该登录学生的序号
			break;//跳出for循环
		}//记录输入用户名所对应的学生编号，即登录的用户所对应的编号 

	if (i >= all_players) {//说明没有找到对应用户名 
		MessageBox(NULL, _T("该用户不存在"), _T("用户找回密码"), MB_ICONSTOP | MB_SETFOREGROUND);
		return;
	}

	//找到了此用户名，进入重置密码模块 

  /*下面重置用户密码*/
	do{
		InputBox(player[login_player].play_password, 10, _T("请重置密码"));//提示用户输入密码
		InputBox(player[login_player].play_password2, 10, _T("请确认密码"));//提示用户确认密码
		if (wcscmp(player[login_player].play_password, player[login_player].play_password2) != 0)//两次输入密码不相等 
			MessageBox(NULL, _T("两次输入不一致，请重新输入"), _T("密码重置"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
		{
			MessageBox(NULL, _T("重置成功！"), _T("密码重置"), MB_SETFOREGROUND);
			SaveFile(fp);//调用文件保存函数
			break;
		}
	} while (1);
}

/*创新功能 管理员可查询所有用户练习记录并重置用户的练习记录*/
void admin_look_record(FILE* fp) {
	system("cls");//控制台清屏函数
	closegraph();
	if (all_players == 0)
		printf("暂无用户记录\n");
	else {
		printf("此打字程序共有用户%d人,其打字记录分别如下：\n", all_players);
		for (int i = 0; i < all_players; i++) {
			int type_times = player[i].player_type_times;
			_wsetlocale(LC_ALL, L"chs");
			wprintf(L"%s", player[i].play_name);//备注 宽字符集 字符串输出用wprintf
			printf("的练习次数为%d", type_times);
			printf("\n************************************************************************************\n");
			for (int q = 0; q < type_times; q++) {
				printf("\n第%d次练习:\n\t所选难度系数:%d\n\t打字正确率:%lf%%\t\n\t打字耗时:%ds", q + 1, player[i].record[q].difficulty_coeffeicents, player[i].record[q].process, player[i].record[q].type_time);
			}
			printf("\n************************************************************************************\n");
		}
		printf("是否需要重置用户的练习记录?1.是 2.否（输入数字即可）");
		printf("\n************************************************************************************\n");
		int y_n;
		int i;
		int flag=1;
		wchar_t username[20];//定义一个临时存储用户名的字符数组
		scanf_s("%d", &y_n);
		if (y_n == 1) {
			printf("\n************************************************************************************\n");
			printf("请输入需要重置的用户的用户名:");
			_wsetlocale(LC_ALL, L"chs");
			wscanf_s(L"%s", username,20);
			printf("\n************************************************************************************\n");
			for (i = 0; i < all_players; i++)
				if (wcscmp(username, player[i].play_name) == 0)//找到了 
				{
					player[i].player_type_times = 0;//重置该记录
					SaveFile(fp);
					printf("重置成功！");
					flag = 0;
					printf("\n************************************************************************************\n");
				}//记录输入用户名所对应的学生编号，即登录的用户所对应的编号 
			if (i >= all_players&&flag) {//说明没有找到对应用户名 
				printf("该用户不存在！");
				printf("\n************************************************************************************\n");
			}
		}
		else if (y_n == 2)
			printf("\n************************************************************************************\n");
		else {
			printf("非法输入！");
			printf("\n************************************************************************************\n");
		}
	}
	printf("按任意键回到管理员菜单...");
	_getch();
	system("cls");//控制台清屏函数
	return;
}

/*main函数*/
int main() {
	FILE* fp;
	fopen_s(&fp, "alldata.txt", "rb+");//打开文件

	/*判断是否第一次使用此软件，若是先进行初始化用户人数等操作，否则直接读取*/
	int judge;
	judge = fgetc(fp);
	fclose(fp);//关闭文件
	if (judge == EOF) 
		SaveFile(fp);
	else {
		fopen_s(&fp, "alldata.txt", "rb+");//重新打开文件
		fread(&all_players, 4, 1, fp);
		fread(&login_player, 4, 1, fp);
		/*读入用户结构体数据*/
		for (int i = 0; i < all_players; i++)
			fread(&player[i], sizeof(struct get_player), 1, fp);
	}
	fclose(fp);
	initgraph(1366, 700);//窗口大小
	ini_window(fp);//进入初页面
	return 0;
}
