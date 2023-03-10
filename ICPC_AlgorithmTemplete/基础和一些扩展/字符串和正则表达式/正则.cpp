#include <iostream>
#include <regex>
#include <bits/stdc++.h>
using namespace std;


int main() {
    string s = "fox The quick brown fox jumps over fox the lazy dog.";

    // 判断一个字符串是否匹配指定的正则表达式
//    regex pattern("fox.*dog");
//    if (regex_match(s, pattern)) {
//        cout << "匹配!" << endl;
//    } else {
//        cout <<"没匹配";
//    }
    regex pattern("fox");
    int k=regex_search(s, pattern);
     cout<<k<<endl;
    return 0;
}
/*
std::regex_match()匹配
std::regex_replace()替换
std::regex_search()分割
std::sregex_iterator和std::sregex_token_iterator
正则表达式迭代器，来实现正则表达式的迭代操作，例如遍历一个字符串中所有匹配正则表达式的子串。
*/



