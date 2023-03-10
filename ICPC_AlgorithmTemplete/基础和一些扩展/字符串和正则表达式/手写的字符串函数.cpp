#include<bits/stdc++.h>
using namespace std;

int __strcmp(const string &a,const string &b){//字符串比较大小,c的库函数有，是strcmp
    int i;
    for(i=0;i<a.size()&&i<b.size()&&a[i]==b[i];i++);
    if(i==a.size()&&i==b.size()){
        return 0;
    }else if(i==a.size()){
        return -1;
    }else if(i==b.size()){
        return 1;
    }else{
        return a[i]<b[i]?-1:1;
    }
}
vector<string> splite(const string &str,const string &a){//字符串切分,c的库函数没有
    int i,j=0,n=str.size(),m=a.size();
    string t="";
    vector<string>li;
    if(m==0){
        for(i=0;i<n;i++){
            li.push_back(str[i]+"");
        }
        return li;
    }
    for(i=0;i<n;i++){
        if(str[i]==a[j]){
            j++;
            if(j==m){
                li.push_back(t.substr(0,t.size()-m+1));
                t="";
                j=0;
                continue;
            }
        }else if(str[i]!=a[j]){
            j=0;
        }
        t+=str[i];
    }
    li.push_back(t);
    return li;
}
string tobin(int k,int up=-1){//把一个数字变成二进制字符串,up是固定多少位数
    string s="";
    stack<char>st;
    while(k){
        st.push(k%2+'0');
        k/=2;
    }
    while(st.size()<up){
        st.push('0');
    }
    while(!st.empty()){
        s+=st.top();
        st.pop();
    }
    return s;
}

char str[100];
int main(int argc,char *argv[]){
    string s,a,b;
    printf("%s\n",tobin(2112,20).c_str());
    scanf("%[^\n]",&str);
    printf("%s\n",str);
    vector<string>li=splite(str," ");
    for(int i=0;i<li.size();i++){
        cout<<li[i]<<endl;
    }
return 0;
}
/*
abcasdabc999abc00abc
*/
