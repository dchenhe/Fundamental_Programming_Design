#include "pinyin.h"
#include<stdio.h>



int main() {
	pinyin new_p;
	//字典建立
	//new_p.initialize_a();
	//预处理
	//new_p.dic_progress();
	//new_p.pre_progress();
	//建立声韵母
	new_p.sy_create();

	new_p.initialize_b();
	//建立全拼
	new_p.cre_full_dic();
	//建立简拼
	new_p.cre_sim_dic();
	new_p.user_l.Empty();
	while (TRUE) {
		system("cls");
		printf("********尊敬的用户您好，欢迎来到拼音输入法，键入escape退出程序，键入1024进行单字查询，请输入您的拼音!************\n");
		printf("输入simple进入简拼，complex进入全拼,return返回全、简选择\n");
		while (TRUE) {
			new_p.p_str.Empty();
			new_p.FLAG = 0;
			new_p.user_l.Empty();
			wstring s_a;
			wcin >> s_a;
			CString s(s_a.c_str());//wstring输入，再转化成string
			if (!s.Compare(L"simple")) {
				while (TRUE) {
					new_p.FLAG = 0;
					new_p.user_l.Empty();
					wstring s_a;
					wcin >> s_a;
					CString s(s_a.c_str());
					if (!s.Compare(L"return"))
						break;
					new_p.sim_pinyin(s);
					wcout << new_p.user_l.GetString() << endl;
					if (new_p.FLAG) {
						freq_chsPair freq;
						freq.insert(std::make_pair(10000, new_p.user_l));
						new_p.dic_s_map.insert(std::make_pair(s, freq));
					}
				}
			}
			else if (!s.Compare(L"escape")) {
				exit(0);
			}
			else {
				while (TRUE) {
					new_p.FLAG = 0;
					new_p.p_str.Empty();
					new_p.user_l.Empty();
					wstring s_a;
					wcin >> s_a;
					CString s(s_a.c_str());
					if (!s.Compare(L"return"))
						break;
					//先判断有没有分隔符，没有再说ok
					int n = s.Find(L"'");
					if (n == -1) {
						new_p.match_pin(s);
						new_p.split_search(new_p.p_str);
					}
					else {
						new_p.split_search(s);
					}
					wcout << new_p.user_l.GetString() << endl;
					if (new_p.FLAG) {
						freq_chsPair freq;
						freq.insert(std::make_pair(10000, new_p.user_l));
						if (n == -1)
							new_p.dic_f_map.insert(std::make_pair(new_p.p_str, freq));
						else
							new_p.dic_f_map.insert(std::make_pair(s, freq));
					}
				}
			}
			break;
		}
	}
}
