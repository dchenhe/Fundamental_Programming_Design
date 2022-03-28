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
typedef std::multimap<int, CString>                freq_chsPair;//频次+中文的map，可实现嵌套
typedef std::multimap<int, CString>::iterator       intCSIt;//频次+中文的map 迭代器
typedef std::multimap<CString, freq_chsPair>             CStrfreq_chsMultimap;
typedef std::multimap<CString, freq_chsPair>::iterator  CSfreqIt;
typedef std::pair<CSfreqIt, CSfreqIt>             CStrfreq_chsMultimap_pair;


class pinyin
{

public:
    int FLAG = 0;

    CString p_str;

    CString user_l;

    //简拼模式
    BOOL sim_pinyin(CString strLine);

    //匹配模式
    BOOL match_pin(CString strLine);

    //全拼分割识别查找
    BOOL split_search(CString strLine);

    //声母 韵母比较
    BOOL sy_create();

	//a类型字典(汉字对应读音)初始化操作
	BOOL initialize_a();

	//b类型字典初始化操作
	BOOL initialize_b();

    //建立词典函数
    BOOL dic_progress();

    //预处理函数
    BOOL pre_progress();

    //建立全拼词典
    BOOL cre_full_dic();

    //建立简拼词典
    BOOL cre_sim_dic();

    //全拼词典Map
    CStrfreq_chsMultimap dic_f_map;

    //简拼词典map
    CStrfreq_chsMultimap dic_s_map;

    CStrCStrMultimap a_mapPinYin; //建立map_a;

    CStrCStrMultimap b_mapPinYin; //建立map_b;

    CStrCStrMultimap sy;//建立声母韵母map

private:
    CStrfreq_chsMultimap dic_map;
};

//a类字典初始化函数
BOOL pinyin::initialize_a() {
    CStdioFile sfile;
    char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
    setlocale(LC_CTYPE, "chs");//设定<ctpye.h>中字符处理方式

    if (!sfile.Open(_T("d://pinyin.txt"), CStdioFile::modeRead))//二进制读入打开拼音文件
    {
        return FALSE;
    }

    CString strLine;//定义字符串变量strLine
    while (sfile.ReadString(strLine))
    {
        if (!strLine.IsEmpty())
        {
            TCHAR split = ',';//以逗号为分割
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
        CString s(s_a.c_str());//wstring输入，再转化成string
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
                        printf("多音字");
                        break;
                    }
                    wcout << it->second.GetString();
                }//遇见多音字，取第一个音，并注明，最后将结果手工标注
            }
        }
        wcout << endl;
    }
    */ //测试用
   
    setlocale(LC_CTYPE, old_locale);
    free(old_locale);//还原区域设定
    return TRUE;
}

//b类字典初始化函数
BOOL pinyin::initialize_b() {
    CStdioFile sfile;
    char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
    setlocale(LC_CTYPE, "chs");//设定<ctpye.h>中字符处理方式

    if (!sfile.Open(_T("d://pinyin.txt"), CStdioFile::modeRead))//二进制读入打开拼音文件
    {
        return FALSE;
    }

    CString strLine;//定义字符串变量strLine
    while (sfile.ReadString(strLine))
    {
        if (!strLine.IsEmpty())
        {
            TCHAR split = ',';//以逗号为分割
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
        CString s(s_a.c_str());//wstring输入，再转化成string
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
                        printf("多音字");
                        break;
                    }
                    wcout << it->second.GetString();
                }//遇见多音字，取第一个音，并注明，最后将结果手工标注
            }
        }
        wcout << endl;
    }
    */ //测试用

    setlocale(LC_CTYPE, old_locale);
    free(old_locale);//还原区域设定
    return TRUE;
}

//建立词典map
BOOL pinyin::dic_progress() {
    ifstream sfile("d://data.txt");
    char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
    setlocale(LC_CTYPE, "chs");//设定<ctpye.h>中字符处理方式

    if (sfile.fail())
    {
        cout << "打开文件错误!" << endl;
        exit(0);
    }
    string str;
    while (!sfile.eof())
    {
        sfile >> str;
        CString strLine(str.c_str());//实现转换
        freq_chsPair freq_map;
        CString pin_str;//定义拼音字符串变量
        string temp(CW2A(strLine.GetString()));//把CString转换一下便于下面的操作
        //用库函数判断标点英语字母等
        if (ispunct(temp[0]) || isalpha(temp[0]) || isdigit(temp[0]) || isalnum(temp[0]) || isxdigit(temp[0]))
            continue;
        int b = strLine.GetLength();
        //if (b ==1)
           // continue;//单字
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
                }//遇见多音字，取第一个音
            }
            else//拼音都找不到跳过
            {
                flag_no = 1;
            }
        }
        if (flag_no)
            continue;//找不到注音的词直接舍弃
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
                it_a->second.insert(std::make_pair(++freq, strLine));//修改键值 频次加一
            }
            else {
                it_a->second.insert(std::make_pair(0, strLine));//如果只有读音相同则直接插入
            }
        }//如果有相同的词，则词频++，如果有相同的拼音，在拼音map中insert
        else {
            freq_map.insert(std::make_pair(0, strLine));
            dic_map.insert(std::make_pair(pin_str, freq_map));
            wcout << pin_str.GetString() << endl;
        }//没有相同拼音，插入一个新的freqmap
       
    }
    setlocale(LC_CTYPE, old_locale);
    free(old_locale);//还原区域设定
    return TRUE;
}

//预处理
BOOL pinyin::pre_progress() {
    //遍历map，并写入预处理文档
    CStdioFile file;
    char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
    setlocale(LC_CTYPE, "chs");//设定<ctpye.h>中字符处理方式
    file.Open(_T("d://sim_dic.txt"),CFile::modeCreate| CFile::modeWrite);
    //写入文件
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
    //关闭文件
    file.Close();
    setlocale(LC_CTYPE, old_locale);
    free(old_locale);//还原区域设定
    return TRUE;
}

//全拼词典建立
BOOL pinyin::cre_full_dic() {
    CStdioFile sfile;
    char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
    setlocale(LC_CTYPE, "chs");//设定<ctpye.h>中字符处理方式

    if (!sfile.Open(_T("d://dic.txt"), CStdioFile::modeRead))//二进制读入打开拼音文件
    {
        return FALSE;
    }

    CString strLine;//定义字符串变量strLine
    while (sfile.ReadString(strLine))
    {
        freq_chsPair freq_map;
        CString strKey, strValue, s_freq;
        if (!strLine.IsEmpty())
        {
            TCHAR split = ',';//以逗号为分割
            TCHAR split2 = '-';//以横杠分割
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
            }//如果有相同的拼音，在拼音map中insert
            else {
                freq_map.insert(std::make_pair(freq, strValue));
                dic_f_map.insert(std::make_pair(strKey, freq_map));
            }//没有相同拼音，插入一个新的freqmap
        }
    }
    sfile.Close();
    setlocale(LC_CTYPE, old_locale);
    free(old_locale);//还原区域设定
    return TRUE;
}

//简拼词典建立
BOOL pinyin::cre_sim_dic() {
    CStdioFile sfile;
    char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
    setlocale(LC_CTYPE, "chs");//设定<ctpye.h>中字符处理方式

    if (!sfile.Open(_T("d://sim_dic.txt"), CStdioFile::modeRead))//二进制读入打开拼音文件
    {
        return FALSE;
    }

    CString strLine;//定义字符串变量strLine
    while (sfile.ReadString(strLine))
    {
        freq_chsPair freq_map;
        CString strKey, strValue, s_freq;
        if (!strLine.IsEmpty())
        {
            TCHAR split = ',';//以逗号为分割
            TCHAR split2 = '-';//以横杠分割
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
            }//如果有相同的拼音，在拼音map中insert
            else {
                freq_map.insert(std::make_pair(freq, strValue));
                dic_s_map.insert(std::make_pair(strKey, freq_map));
            }//没有相同拼音，插入一个新的freqmap
        }
    }
    sfile.Close();
    setlocale(LC_CTYPE, old_locale);
    free(old_locale);//还原区域设定
    return TRUE;
}

//声母韵母构造匹配map;
BOOL pinyin::sy_create() {
    //暴力构造所有拼音组合map;
    
    //声母组合
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

    //韵母组合
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

    //建立组合
    CString sm[23] = { b,c,f,g,h,j,k,l,m,n,p,q,r,s,t,w,x,y,z,sh,zh,ch,d };
    CString ym[30] = { a,o,e,i,u,v,ai,ei,ui,ao,ou,iu,ie,ue,er,an,en,in,un,ang,eng,ing,ong,iao,ian,iang,uo,ia,iong,uan};


    //建立map;
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

//全拼读取识别以及字符串分割 返回查找值
BOOL pinyin::split_search(CString strLine) {
    char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
    setlocale(LC_CTYPE, "chs");//设定<ctpye.h>中字符处理方式
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
                    
                }//遇见多音字，取第一个音，并注明，最后将结果手工标注
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
                    //wcout << i << ":" << it_j->second.GetString() << " "; //first 是key , second 是 value
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
                    wcout << i << ":" << it_a->second.GetString() << " "; //first 是key , second 是 value
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
            //频次修改完成
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
        //否则迭代！
    }
    else {
        return FALSE;
    }
}

//拼音分割
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
    //先识别是不是单字词
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
        //返回迭代器
        p_str.Append(temp);
        CStrCStrIt it_a;
        CStrIterPair it = sy.equal_range(temp);
        //取出韵母
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
        
    }//双声母分割

    else {
        temp = str.Mid(i, 1);//单声母分割
        if (sy.count(temp) > 0) {
            //返回迭代器
            p_str.Append(temp);
            CStrCStrIt it_a;
            CStrIterPair it = sy.equal_range(temp);
            //取出韵母
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

//简拼部分
BOOL pinyin::sim_pinyin(CString strLine) {

    char* old_locale = _strdup(setlocale(LC_CTYPE, NULL));
    setlocale(LC_CTYPE, "chs");//设定<ctpye.h>中字符处理方式
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
                //wcout << i << ":" << it_j->second.GetString() << " "; //first 是key , second 是 value
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
            wcout << i << ":" << it_a->second.GetString() << " "; //first 是key , second 是 value
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
        //频次修改完成
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

