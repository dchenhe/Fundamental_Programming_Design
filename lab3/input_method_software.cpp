#include "pinyin.h"
#include<stdio.h>



int main() {
	pinyin new_p;
	//�ֵ佨��
	//new_p.initialize_a();
	//Ԥ����
	//new_p.dic_progress();
	//new_p.pre_progress();
	//��������ĸ
	new_p.sy_create();

	new_p.initialize_b();
	//����ȫƴ
	new_p.cre_full_dic();
	//������ƴ
	new_p.cre_sim_dic();
	new_p.user_l.Empty();
	while (TRUE) {
		system("cls");
		printf("********�𾴵��û����ã���ӭ����ƴ�����뷨������escape�˳����򣬼���1024���е��ֲ�ѯ������������ƴ��!************\n");
		printf("����simple�����ƴ��complex����ȫƴ,return����ȫ����ѡ��\n");
		while (TRUE) {
			new_p.p_str.Empty();
			new_p.FLAG = 0;
			new_p.user_l.Empty();
			wstring s_a;
			wcin >> s_a;
			CString s(s_a.c_str());//wstring���룬��ת����string
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
					//���ж���û�зָ�����û����˵ok
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
