#include <iostream>
#include <regex>
#include <bits/stdc++.h>
using namespace std;


int main() {
    string s = "fox The quick brown fox jumps over fox the lazy dog.";

    // �ж�һ���ַ����Ƿ�ƥ��ָ����������ʽ
//    regex pattern("fox.*dog");
//    if (regex_match(s, pattern)) {
//        cout << "ƥ��!" << endl;
//    } else {
//        cout <<"ûƥ��";
//    }
    regex pattern("fox");
    int k=regex_search(s, pattern);
     cout<<k<<endl;
    return 0;
}
/*
std::regex_match()ƥ��
std::regex_replace()�滻
std::regex_search()�ָ�
std::sregex_iterator��std::sregex_token_iterator
������ʽ����������ʵ��������ʽ�ĵ����������������һ���ַ���������ƥ��������ʽ���Ӵ���
*/



