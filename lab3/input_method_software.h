#pragma once
#include<map>
#include<ctype.h>
#include<stdio.h>
#include<afx.h>
#include<locale.h>
#include<iostream>
#include<fstream>
#define user_max 10000

using namespace std;


BOOL you = TRUE;

typedef std::multimap<CString, CString>             CStrCStrMultimap;
typedef std::multimap<CString, CString>::iterator   CStrCStrIt;
typedef std::pair<CStrCStrIt, CStrCStrIt>            CStrIterPair;
typedef std::multimap<int, CString>                freq_chsPair;//Ƶ��+���ĵ�map����ʵ��Ƕ��
typedef std::multimap<int, CString>::iterator       intCSIt;//Ƶ��+���ĵ�map ������
typedef std::multimap<CString, freq_chsPair>             CStrfreq_chsMultimap;
typedef std::multimap<CString, freq_chsPair>::iterator  CSfreqIt;
typedef std::pair<CSfreqIt, CSfreqIt>             CStrfreq_chsMultimap_pair;


class pinyin
{

public:
    int FLAG = 0;

    CString p_str;

    CString user_l;

    //��ƴģʽ
    BOOL sim_pinyin(CString strLine);

    //ƥ��ģʽ
    BOOL match_pin(CString strLine);

    //ȫƴ�ָ�ʶ�����
    BOOL split_search(CString strLine);

    //��ĸ ��ĸ�Ƚ�
    BOOL sy_create();

	//a�����ֵ�(���ֶ�Ӧ����)��ʼ������
	BOOL initialize_a();

	//b�����ֵ��ʼ������
	BOOL initialize_b();

    //�����ʵ亯��
    BOOL dic_progress();

    //Ԥ������
    BOOL pre_progress();

    //����ȫƴ�ʵ�
    BOOL cre_full_dic();

    //������ƴ�ʵ�
    BOOL cre_sim_dic();

    //ȫƴ�ʵ�Map
    CStrfreq_chsMultimap dic_f_map;

    //��ƴ�ʵ�map
    CStrfreq_chsMultimap dic_s_map;

    CStrCStrMultimap a_mapPinYin; //����map_a;

    CStrCStrMultimap b_mapPinYin; //����map_b;

    CStrCStrMultimap sy;//������ĸ��ĸmap

private:
    CStrfreq_chsMultimap dic_map;
};

//a���ֵ��ʼ������
BOOL pinyin::initialize_a() {
    CStdioFile sfile;
    char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
    setlocale(LC_CTYPE, "chs");//�趨<ctpye.h>���ַ�����ʽ

    if (!sfile.Open(_T("d://pinyin.txt"), CStdioFile::modeRead))//�����ƶ����ƴ���ļ�
    {
        return FALSE;
    }

    CString strLine;//�����ַ�������strLine
    while (sfile.ReadString(strLine))
    {
        if (!strLine.IsEmpty())
        {
            TCHAR split = ',';//�Զ���Ϊ�ָ�
            int nBlank = strLine.Find(split);
            CString strKey, strValue;
            strValue = strLine.Left(nBlank);
            for (int i = strLine.GetLength(); i > nBlank;i--) {
                strKey = strLine.Mid(i,1);
                a_mapPinYin.insert(std::make_pair(strKey, strValue));

            }
        }
    }
    sfile.Close();
    /*while (TRUE) {
        wstring s_a;
        wcin >> s_a;
        CString s(s_a.c_str());//wstring���룬��ת����string
        int b = s.GetLength();
        for (int i = 0; i < b; ++i)
        {
            CString cChar = CString(s.GetAt(i));

            if (a_mapPinYin.count(cChar) > 0)
            {
                CStrIterPair cCharValue = a_mapPinYin.equal_range(cChar);
                int flag = 0;
                for (CStrCStrIt it = cCharValue.first; it != cCharValue.second; ++it,flag++)
                {
                    if (flag) {
                        printf("������");
                        break;
                    }
                    wcout << it->second.GetString();
                }//���������֣�ȡ��һ��������ע������󽫽���ֹ���ע
            }
        }
        wcout << endl;
    }
    */ //������
   
    setlocale(LC_CTYPE, old_locale);
    free(old_locale);//��ԭ�����趨
    return TRUE;
}

//b���ֵ��ʼ������
BOOL pinyin::initialize_b() {
    CStdioFile sfile;
    char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
    setlocale(LC_CTYPE, "chs");//�趨<ctpye.h>���ַ�����ʽ

    if (!sfile.Open(_T("d://pinyin.txt"), CStdioFile::modeRead))//�����ƶ����ƴ���ļ�
    {
        return FALSE;
    }

    CString strLine;//�����ַ�������strLine
    while (sfile.ReadString(strLine))
    {
        if (!strLine.IsEmpty())
        {
            TCHAR split = ',';//�Զ���Ϊ�ָ�
            int nBlank = strLine.Find(split);
            CString strKey, strValue;
            strKey = strLine.Left(nBlank);
            for (int i = strLine.GetLength(); i > nBlank; i--) {
                strValue = strLine.Mid(i, 1);
                b_mapPinYin.insert(std::make_pair(strKey, strValue));
            }
        }
    }
    sfile.Close();
    /*while (TRUE) {
        wstring s_a;
        wcin >> s_a;
        CString s(s_a.c_str());//wstring���룬��ת����string
        int b = s.GetLength();
        for (int i = 0; i < b; ++i)
        {
            CString cChar = CString(s.GetAt(i));

            if (a_mapPinYin.count(cChar) > 0)
            {
                CStrIterPair cCharValue = a_mapPinYin.equal_range(cChar);
                int flag = 0;
                for (CStrCStrIt it = cCharValue.first; it != cCharValue.second; ++it,flag++)
                {
                    if (flag) {
                        printf("������");
                        break;
                    }
                    wcout << it->second.GetString();
                }//���������֣�ȡ��һ��������ע������󽫽���ֹ���ע
            }
        }
        wcout << endl;
    }
    */ //������

    setlocale(LC_CTYPE, old_locale);
    free(old_locale);//��ԭ�����趨
    return TRUE;
}

//�����ʵ�map
BOOL pinyin::dic_progress() {
    ifstream sfile("d://data.txt");
    char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
    setlocale(LC_CTYPE, "chs");//�趨<ctpye.h>���ַ�����ʽ

    if (sfile.fail())
    {
        cout << "���ļ�����!" << endl;
        exit(0);
    }
    string str;
    while (!sfile.eof())
    {
        sfile >> str;
        CString strLine(str.c_str());//ʵ��ת��
        freq_chsPair freq_map;
        CString pin_str;//����ƴ���ַ�������
        string temp(CW2A(strLine.GetString()));//��CStringת��һ�±�������Ĳ���
        //�ÿ⺯���жϱ��Ӣ����ĸ��
        if (ispunct(temp[0]) || isalpha(temp[0]) || isdigit(temp[0]) || isalnum(temp[0]) || isxdigit(temp[0]))
            continue;
        int b = strLine.GetLength();
        //if (b ==1)
           // continue;//����
        int flag_no;
        for (int i = 0; i < b; ++i)
        {
            flag_no = 0;
            CString cChar = CString(strLine.GetAt(i));

            if (a_mapPinYin.count(cChar) > 0)
            {
                CStrIterPair cCharValue = a_mapPinYin.equal_range(cChar);
                int flag = 0;
                for (CStrCStrIt it = cCharValue.first; it != cCharValue.second; ++it, flag++)
                {
                    if (flag) {
                        
                        break;
                    }
                    pin_str.AppendFormat(it->second.Mid(0,1));
                   // pin_str.AppendFormat(L"'");
                }//���������֣�ȡ��һ����
            }
            else//ƴ�����Ҳ�������
            {
                flag_no = 1;
            }
        }
        if (flag_no)
            continue;//�Ҳ���ע���Ĵ�ֱ������
        if (dic_map.find(pin_str) != dic_map.end()) {
            int fla;
            CSfreqIt it_a;
            it_a = dic_map.find(pin_str);
            intCSIt it;
            for (it = it_a->second.begin(),fla=0; it != it_a->second.end(); it++) {
                if (it->second.Compare(strLine) == 0) {
                    fla = 1;
                    break;
                }
            }
            if (fla) {
                int freq = it->first;
                it_a->second.erase(freq);
                it_a->second.insert(std::make_pair(++freq, strLine));//�޸ļ�ֵ Ƶ�μ�һ
            }
            else {
                it_a->second.insert(std::make_pair(0, strLine));//���ֻ�ж�����ͬ��ֱ�Ӳ���
            }
        }//�������ͬ�Ĵʣ����Ƶ++���������ͬ��ƴ������ƴ��map��insert
        else {
            freq_map.insert(std::make_pair(0, strLine));
            dic_map.insert(std::make_pair(pin_str, freq_map));
            wcout << pin_str.GetString() << endl;
        }//û����ͬƴ��������һ���µ�freqmap
       
    }
    setlocale(LC_CTYPE, old_locale);
    free(old_locale);//��ԭ�����趨
    return TRUE;
}

//Ԥ����
BOOL pinyin::pre_progress() {
    //����map����д��Ԥ�����ĵ�
    CStdioFile file;
    char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
    setlocale(LC_CTYPE, "chs");//�趨<ctpye.h>���ַ�����ʽ
    file.Open(_T("d://sim_dic.txt"),CFile::modeCreate| CFile::modeWrite);
    //д���ļ�
    CSfreqIt it_a;
    intCSIt it;
    for (it_a = pinyin::dic_map.begin(); it_a != pinyin::dic_map.end(); it_a++) {
        for (it = it_a->second.begin(); it != it_a->second.end(); it++) {
            CString str;
            CString num;
            str.Append(it_a->first);
            str.Append(_T(","));
            str.Append(it->second);
            str.Append(_T("-"));
            num.Format(_T("%d"), it->first);
            str.Append(num);
            str.Append(_T("\n"));
            file.Seek(0, CFile::end);
            file.WriteString(str);
        }
    }
    //�ر��ļ�
    file.Close();
    setlocale(LC_CTYPE, old_locale);
    free(old_locale);//��ԭ�����趨
    return TRUE;
}

//ȫƴ�ʵ佨��
BOOL pinyin::cre_full_dic() {
    CStdioFile sfile;
    char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
    setlocale(LC_CTYPE, "chs");//�趨<ctpye.h>���ַ�����ʽ

    if (!sfile.Open(_T("d://dic.txt"), CStdioFile::modeRead))//�����ƶ����ƴ���ļ�
    {
        return FALSE;
    }

    CString strLine;//�����ַ�������strLine
    while (sfile.ReadString(strLine))
    {
        freq_chsPair freq_map;
        CString strKey, strValue, s_freq;
        if (!strLine.IsEmpty())
        {
            TCHAR split = ',';//�Զ���Ϊ�ָ�
            TCHAR split2 = '-';//�Ժ�ָܷ�
            int nBlank = strLine.Find(split);
            int b_b = strLine.Find(split2);
            int freq;
            strKey = strLine.Left(nBlank);
            strValue = strLine.Mid(nBlank+1, b_b - nBlank - 1);
            s_freq = strLine.Right(b_b);
            freq = _ttoi(s_freq);
            if (dic_map.find(strKey) != dic_map.end()) {
                int fla;
                CSfreqIt it_a;
                it_a = dic_map.find(strKey);
                (it_a->second).insert(std::make_pair(freq, strValue));
            }//�������ͬ��ƴ������ƴ��map��insert
            else {
                freq_map.insert(std::make_pair(freq, strValue));
                dic_f_map.insert(std::make_pair(strKey, freq_map));
            }//û����ͬƴ��������һ���µ�freqmap
        }
    }
    sfile.Close();
    setlocale(LC_CTYPE, old_locale);
    free(old_locale);//��ԭ�����趨
    return TRUE;
}

//��ƴ�ʵ佨��
BOOL pinyin::cre_sim_dic() {
    CStdioFile sfile;
    char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
    setlocale(LC_CTYPE, "chs");//�趨<ctpye.h>���ַ�����ʽ

    if (!sfile.Open(_T("d://sim_dic.txt"), CStdioFile::modeRead))//�����ƶ����ƴ���ļ�
    {
        return FALSE;
    }

    CString strLine;//�����ַ�������strLine
    while (sfile.ReadString(strLine))
    {
        freq_chsPair freq_map;
        CString strKey, strValue, s_freq;
        if (!strLine.IsEmpty())
        {
            TCHAR split = ',';//�Զ���Ϊ�ָ�
            TCHAR split2 = '-';//�Ժ�ָܷ�
            int nBlank = strLine.Find(split);
            int b_b = strLine.Find(split2);
            int freq;
            strKey = strLine.Left(nBlank);
            strValue = strLine.Mid(nBlank+1, b_b - nBlank - 1);
            s_freq = strLine.Right(b_b);
            freq = _ttoi(s_freq);
            if (dic_map.find(strKey) != dic_map.end()) {
                int fla;
                CSfreqIt it_a;
                it_a = dic_map.find(strKey);
                (it_a->second).insert(std::make_pair(freq, strValue));
            }//�������ͬ��ƴ������ƴ��map��insert
            else {
                freq_map.insert(std::make_pair(freq, strValue));
                dic_s_map.insert(std::make_pair(strKey, freq_map));
            }//û����ͬƴ��������һ���µ�freqmap
        }
    }
    sfile.Close();
    setlocale(LC_CTYPE, old_locale);
    free(old_locale);//��ԭ�����趨
    return TRUE;
}

//��ĸ��ĸ����ƥ��map;
BOOL pinyin::sy_create() {
    //������������ƴ�����map;
    
    //��ĸ���
    CString d = "d";
    CString b = "b";
    CString c = "c";
    CString f = "f";
    CString g = "g";
    CString h = "h";
    CString j = "j";
    CString k = "k";
    CString l = "l";
    CString m = "m";
    CString n = "n";
    CString p = "p";
    CString q = "q";
    CString r = "r";
    CString s = "s";
    CString t = "t";
    CString w = "w";
    CString x = "x";
    CString y = "y";
    CString z = "z";
    CString sh = "sh";
    CString zh = "zh";
    CString ch = "ch";

    //��ĸ���
    CString a = "a";
    CString o = "o";
    CString e = "e";
    CString i = "i";
    CString u = "u";
    CString v = "v";
    CString ai = "ai";
    CString ei = "ei";
    CString ui = "ui";
    CString ao = "ao";
    CString ou = "ou";
    CString iu = "iu";
    CString ie = "ie";
    CString ue = "ue";
    CString er = "er";
    CString an = "an";
    CString en = "en";
    CString in = "in";
    CString un = "un";
    CString ang = "ang";
    CString eng = "eng";
    CString ing = "ing";
    CString ong = "ong";
    CString iao = "iao";
    CString ian = "ian";
    CString iang = "iang";
    CString uo = "uo";
    CString ia = "ia";
    CString iong = "iong";
    CString uan = "uan";

    //�������
    CString sm[23] = { b,c,f,g,h,j,k,l,m,n,p,q,r,s,t,w,x,y,z,sh,zh,ch,d };
    CString ym[30] = { a,o,e,i,u,v,ai,ei,ui,ao,ou,iu,ie,ue,er,an,en,in,un,ang,eng,ing,ong,iao,ian,iang,uo,ia,iong,uan};


    //����map;
    int ta;
    int tb;
    for (ta = 0; ta < 23; ta++) {
        for (tb = 0; tb < 30; tb++) {
           /* if (ta == 0) {
                if (tb == 2 || tb == 5 || tb == 8 || tb == 10 || tb == 13 || tb == 14 || tb == 18 || tb == 22 || tb == 25 || tb == 26 || tb == 27)
                    continue;
                sy.insert(std::make_pair(sm[ta], ym[tb]));
            }
            else if (ta == 22) {
                
                sy.insert(std::make_pair(sm[ta], ym[tb]));
            }
            else if (ta == 1 || ta == 13 || ta == 21 || ta == 19) {
                if (tb == 1 || tb == 5 || tb == 7 || tb == 11 || tb == 12 || tb == 13 || tb == 14 || tb == 17 || tb == 21 || tb == 23 || tb == 24 || tb == 25 || tb == 27)
                    continue;
                sy.insert(std::make_pair(sm[ta], ym[tb]));
            }
            else if (ta == 2) {
                if (tb == 26 || tb == 25 || tb == 1 || tb == 2 || tb == 3 || tb == 5 || tb == 6 || tb == 11 || tb == 12 || tb == 13 || tb == 14 || tb == 17 || tb == 27 || tb == 24 || tb == 18 || tb == 21 || tb == 22 || tb == 23)
                    continue;
                sy.insert(std::make_pair(sm[ta], ym[tb]));
            }
            else if (ta == 3 || ta == 4 || tb == 6) {
                if (tb == 25 || tb == 1 || tb == 3 || tb == 5 || tb == 11 || tb == 12 || tb == 13 || tb == 14 || tb == 17 || tb == 21 || tb == 23 || tb == 24 || tb == 27)
                    continue;
                sy.insert(std::make_pair(sm[ta], ym[tb]));
            }
            else if (ta == 5) {
                if (tb == 26 || tb == 1 || tb == 2 || tb == 5 || tb == 6 || tb == 7 || tb == 8 || tb == 9 || tb == 10 || tb == 14 || tb == 15 || tb == 16 || tb == 18 || tb == 22)
                    continue;
                sy.insert(std::make_pair(sm[ta], ym[tb]));
            }
            else if (ta == 7 || ta == 9) {
                if (ta == 7 && (tb == 1 || tb == 8 || tb == 14))
                    continue;
                else if (tb == 1 || tb == 8 || tb == 14 || tb == 27)
                    continue;
                sy.insert(std::make_pair(sm[ta], ym[tb]));
            }
            else if (ta == 8 || ta == 10)
            {
                if (tb == 2 || tb == 5 || tb == 8 || tb == 13 || tb == 14 || tb == 18 || tb == 22 || tb == 25 || tb == 26)
                    continue;
                sy.insert(std::make_pair(sm[ta], ym[tb]));
            }
            else if (ta == 11) {
                if (tb == 0 || tb == 1 || tb == 2 || tb == 5 || tb == 6 || tb == 7 || tb == 8 || tb == 9 || tb == 10 || tb == 14 || tb == 15 || tb == 16 || tb == 19 || tb == 20 || tb == 22 || tb == 26)
                    continue;
                sy.insert(std::make_pair(sm[ta], ym[tb]));
            }
            else if (ta == 12) {
                if (tb == 0 || tb == 1 || tb == 5 || tb == 6 || tb == 7 || tb == 8 || tb == 11 || tb == 12 || tb == 13 || tb == 14 || tb == 17 || tb == 21 || tb == 23 || tb == 24 || tb == 25 || tb == 27)
                    continue;
                sy.insert(std::make_pair(sm[ta], ym[tb]));
            }
            else if (ta == 14) {
                if (tb == 1 || tb == 5 || tb == 11 || tb == 13 || tb == 14 || tb == 25 || tb == 27)
                    continue;
                sy.insert(std::make_pair(sm[ta], ym[tb]));
            }
            else if (ta == 15) {
                if (tb == 2 || tb == 3 || tb == 5 || tb == 8 || tb == 9 || tb == 10 || tb == 11 || tb == 12 || tb == 13 || tb == 14 || tb == 17 || tb == 18 || tb == 21 || tb == 22 || tb == 23 || tb == 24 || tb == 25 || tb == 26 || tb == 27)
                    continue;
                sy.insert(std::make_pair(sm[ta], ym[tb]));
            }
            else if (ta == 16) {
                if (tb == 0 || tb == 1 || tb == 2 || tb == 5 || tb == 6 || tb == 7 || tb == 8 || tb == 9 || tb == 10 || tb == 14 || tb == 15 || tb == 16 || tb == 19 || tb == 20 || tb == 22 || tb == 26)
                    continue;
                sy.insert(std::make_pair(sm[ta], ym[tb]));
            }
            else if (ta == 17) {
                if (tb == 1 || tb == 5 || tb == 6 || tb == 7 || tb == 8 || tb == 11 || tb == 14 || tb == 16 || tb == 20 || tb == 22 || tb == 23 || tb == 24 || tb == 25 || tb == 26 || tb == 27)
                    continue;
                sy.insert(std::make_pair(sm[ta], ym[tb]));
            }
            else if (ta == 18 || ta == 20) {
                if (tb == 1 || tb == 5 || tb == 11 || tb == 12 || tb == 13 || tb == 14 || tb == 17 || tb == 21 || tb == 23 || tb == 24 || tb == 25 || tb == 27)
                    continue;
                sy.insert(std::make_pair(sm[ta], ym[tb]));
            }
            */
            sy.insert(std::make_pair(sm[ta], ym[tb]));
        }
    }
return TRUE;
}

//ȫƴ��ȡʶ���Լ��ַ����ָ� ���ز���ֵ
BOOL pinyin::split_search(CString strLine) {
    char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
    setlocale(LC_CTYPE, "chs");//�趨<ctpye.h>���ַ�����ʽ
    int n;
    freq_chsPair freq_map;
    n = strLine.Find(L"'");
    int w = strLine.GetLength();
    if (n != -1) {
        if (w==n+1) {
            b_mapPinYin.find(strLine.Left(n));
            CString cChar;
            cChar.Empty();
            cChar.Append(strLine.Left(n));

            if (b_mapPinYin.count(cChar) > 0)
            {
                CString save_str[1000];
                CStrIterPair cCharValue = b_mapPinYin.equal_range(cChar);
                int flag = 0;
                int i = 0;
                for (CStrCStrIt it = cCharValue.first; it != cCharValue.second; ++it, flag++,i++)
                {
                    wcout << i << ":" << it->second.GetString() << " ";
                    save_str[i].Empty();
                    save_str[i] = it->second.GetString();
                    
                }//���������֣�ȡ��һ��������ע������󽫽���ֹ���ע
                int user;
            printf_s("\n");
            scanf_s("%d", &user);
            user_l.Append(save_str[user]);
                return TRUE;
            }
            else
                return FALSE;
        }
        if (!strLine.Right(1).Compare(L"'"));
        else
            strLine.Append(_T("'"));
        if (dic_f_map.count(strLine) > 0)
        {
            CString save_str[100];
            CStrfreq_chsMultimap_pair cCharValue = dic_f_map.equal_range(strLine);
            int flag = 0;
            int i = 0;
            freq_chsPair tem_map;
            for (CSfreqIt it = (--(cCharValue.second)); ; --it, flag++)
            {

                intCSIt it_a = (it->second).end();
                intCSIt it_j = (it->second).begin();

                for (; it_j != it_a; it_j++) {
                    //wcout << i << ":" << it_j->second.GetString() << " "; //first ��key , second �� value
                    tem_map.insert(std::make_pair(it_j->first, it_j->second));
                    // save_str[i] = it_j->second.GetString();
                }
                if (it == cCharValue.first)
                    break;
            }//
            ++(cCharValue.second);
                intCSIt it_a = --(tem_map.end());
                intCSIt it_j = tem_map.begin();

                for (; ; it_a--, i++) {
                    wcout << i << ":" << it_a->second.GetString() << " "; //first ��key , second �� value
                    save_str[i].Empty();
                    save_str[i] = it_a->second.GetString();
                    if (it_a == it_j)
                        break;
                }
            //

            int user;
            printf_s("\n");
            scanf_s("%d", &user);
            if (user == 1024)
                goto end;
            user_l.Append(save_str[user]);
            i = 0;
            int flag_t = 1;

            for (CSfreqIt it =--( cCharValue.second);flag_t ; --it, flag++)
            {
                
                
                intCSIt it_a = it->second.begin();
                intCSIt it_b = it->second.end();
    

                for (; flag_t&&it_a!=it->second.end(); it_a--, i++) {
                    if (!(it_a->second).Compare(save_str[user])) {
                        int freq = it_a->first + 10000;
                        it->second.insert(std::make_pair(freq, it_a->second));
                        it->second.erase(it_a->first);
                        flag_t = 0;
                        break;
                    }
                }
                if (it == cCharValue.first)
                    break;
            }
            //Ƶ���޸����
            return TRUE;
        }
        else {
        end:
            FLAG = 1;
            int i = 0;
            CString spli[50];
            int q;
            for (i = 0; !strLine.IsEmpty(); i++) {
                if (i == 0) {
                    q = strLine.Find(L"'");
                    spli[i] = strLine.Left(q);
                    spli[i].Append(L"'");
                }
                else {
                    spli[i].Append(strLine.GetString());
                }
                if (pinyin::split_search(spli[i]) == FALSE)
                    return FALSE;
                if (i == 0) {
                    strLine = strLine.Mid(q + 1);
                }
                else
                    return TRUE;
            }
            return TRUE;
        }
        //���������
    }
    else {
        return FALSE;
    }
}

//ƴ���ָ�
BOOL pinyin::match_pin(CString str) {
    int i = 0;
    CString temp;
    if (str.IsEmpty()) {
        return TRUE;
    }

    CString dan_zi[11]{ L"a",L"ai",L"an",L"ang",L"ao",L"e",L"en",L"eng",L"er",L"o",L"ou" };
    CString dz_1 = str.Mid(i, 1);
    CString dz_2 = str.Mid(i, 2);
    CString dz_3 = str.Mid(i, 3);
    //��ʶ���ǲ��ǵ��ִ�
    for (i = 0; i < 11; i++) {
        if (!dz_3.Compare(dan_zi[i])) {
            p_str.Append(dz_3);
            p_str.Append(L"'");
            if (pinyin::match_pin(str.Mid(3)))
                return TRUE;
            else
                break;
        }
    }
    for (i = 0; i < 11; i++) {
        if (!dz_2.Compare(dan_zi[i])) {
            p_str.Append(dz_2);
            p_str.Append(L"'");
            if (pinyin::match_pin(str.Mid(2)))
                return TRUE;
            else
                break;
        }
    }
    for (i = 0; i < 11; i++) {
        if (!dz_1.Compare(dan_zi[i])) {
            p_str.Append(dz_1);
            p_str.Append(L"'");
            if (pinyin::match_pin(str.Mid(1)))
                return TRUE;
            else
                break;
        }
    }


    i = 0;
    temp = str.Mid(i, 2);
    if (sy.count(temp)>0) {
        //���ص�����
        p_str.Append(temp);
        CStrCStrIt it_a;
        CStrIterPair it = sy.equal_range(temp);
        //ȡ����ĸ
        i++;
        i++;
        CString ty_1, ty_2, ty_3;
        ty_1 = str.Mid(i, 1);
        ty_2 = str.Mid(i, 2);
        ty_3 = str.Mid(i, 3);
        for (it_a = it.first; it_a != it.second; it_a++) {
            if (!ty_3.Compare(it_a->second)) {
                p_str.Append(ty_3);
                p_str.Append(L"'");
                if (pinyin::match_pin(str.Mid(5)))
                    return TRUE;
                else
                    break;
            }
        }
        for (it_a = it.first; it_a != it.second; it_a++) {
            if (!ty_2.Compare(it_a->second)) {
                p_str.Append(ty_2);
                p_str.Append(L"'");
                if (pinyin::match_pin(str.Mid(4)))
                    return TRUE;
                else
                    break;
            }
        }
        for (it_a = it.first; it_a != it.second; it_a++) {
            if (!ty_1.Compare(it_a->second)) {
                p_str.Append(ty_1);
                p_str.Append(L"'");
                if (pinyin::match_pin(str.Mid(3)))
                    return TRUE;
                else
                    break;
            }
        }
        
    }//˫��ĸ�ָ�

    else {
        temp = str.Mid(i, 1);//����ĸ�ָ�
        if (sy.count(temp) > 0) {
            //���ص�����
            p_str.Append(temp);
            CStrCStrIt it_a;
            CStrIterPair it = sy.equal_range(temp);
            //ȡ����ĸ
            i++;
            CString ty_1, ty_2, ty_3;
            ty_1 = str.Mid(i, 1);
            ty_2 = str.Mid(i, 2);
            ty_3 = str.Mid(i, 3);
            for (it_a = it.first; it_a != it.second; it_a++) {
                if (!ty_3.Compare(it_a->second)) {
                    p_str.Append(ty_3);
                    p_str.Append(L"'");
                    if (pinyin::match_pin(str.Mid(4)))
                        return TRUE;
                    else
                        break;
                }
            }
            for (it_a = it.first; it_a != it.second; it_a++) {
                if (!ty_2.Compare(it_a->second)) {
                    p_str.Append(ty_2);
                    p_str.Append(L"'");
                    if (pinyin::match_pin(str.Mid(3)))
                        return TRUE;
                    else
                        break;
                }
            }
            for (it_a = it.first; it_a != it.second; it_a++) {
                if (!ty_1.Compare(it_a->second)) {
                    p_str.Append(ty_1);
                    p_str.Append(L"'");
                    if (pinyin::match_pin(str.Mid(2)))
                        return TRUE;
                    else
                        break;
                }
            }
        
    
        }
        else
            return FALSE;
    }
    return TRUE;
}

//��ƴ����
BOOL pinyin::sim_pinyin(CString strLine) {

    char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
    setlocale(LC_CTYPE, "chs");//�趨<ctpye.h>���ַ�����ʽ
    freq_chsPair freq_map;
    int w = strLine.GetLength();

    if (dic_s_map.count(strLine) > 0 )
    {
        CString save_str[1000];
        CStrfreq_chsMultimap_pair cCharValue = dic_s_map.equal_range(strLine);
        int flag = 0;
        int i = 0;
        freq_chsPair tem_map;
        for (CSfreqIt it = (--(cCharValue.second)); ; --it, flag++)
        {

            intCSIt it_a = (it->second).end();
            intCSIt it_j = (it->second).begin();

            for (; it_j != it_a; it_j++) {
                //wcout << i << ":" << it_j->second.GetString() << " "; //first ��key , second �� value
                tem_map.insert(std::make_pair(it_j->first, it_j->second));
                // save_str[i] = it_j->second.GetString();
            }
            if (it == cCharValue.first)
                break;
        }//
        ++(cCharValue.second);
        intCSIt it_a = --(tem_map.end());
        intCSIt it_j = tem_map.begin();

        for (; ; it_a--, i++) {
            wcout << i << ":" << it_a->second.GetString() << " "; //first ��key , second �� value
            save_str[i].Empty();
            save_str[i] = it_a->second.GetString();
            if (it_a == it_j)
                break;
        }
        //

        int user;
        printf_s("\n");
        scanf_s("%d", &user);
        if (user == 1024)
            goto end;
        user_l.Append(save_str[user]);
        i = 0;
        int flag_t = 1;

        for (CSfreqIt it = --(cCharValue.second); flag_t; --it, flag++)
        {


            intCSIt it_a = it->second.begin();
            intCSIt it_b = it->second.end();


            for (; flag_t && it_a != it->second.end(); it_a--, i++) {
                if (!(it_a->second).Compare(save_str[user])) {
                    int freq = it_a->first + 10000;
                    it->second.insert(std::make_pair(freq, it_a->second));
                    it->second.erase(it_a->first);
                    flag_t = 0;
                    break;
                }
            }
            if (it == cCharValue.first)
                break;
        }
        //Ƶ���޸����
        return TRUE;
    }

    else {
    end:
        FLAG = 1;
        int i = 0;
        CString spli[50];
        int q;
        for (i = 0; !strLine.IsEmpty(); i++) {
            if (i == 0)
                spli[i] = strLine.Mid(i, 1);
            else 
                spli[i] = strLine;
            if (pinyin::sim_pinyin(spli[i]) == FALSE)
                return FALSE;
            if (i > 0)
                return TRUE;
            strLine = strLine.Mid(i+1);
        }
        return TRUE;
    }
    return TRUE;
}

