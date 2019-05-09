#include<stdio.h>
#include<vector>
#include<string.h>
#include<algorithm>//写bits/stdc++.h可能超时啊，为什么呢不知道，我这里没问题
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;

struct v2{
    char c;
    int cnt=1;
};

char str[20];
vector<v2>li;
char nowStr[20];
int len;
void dfs(int step){
    int i,j,k;
    if(step==len){
        for(i=0;i<len;i++){
            printf("%c",nowStr[i]);
        }printf("\n");
        return;
    }
    for(i=0;i<li.size();i++){
        if(li[i].cnt){
            li[i].cnt--;
            nowStr[step]=li[i].c;
            dfs(step+1);
            li[i].cnt++;
        }
    }
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j;
    scanf("%s",str);

    len=strlen(str);
    sort(str,str+len);
    for(i=0;i<len;i++){
        for(j=0;j<li.size();j++){
            if(li[j].c==str[i]){
                li[j].cnt++;
                break;
            }
        }
        if(j==li.size()){
            v2 a;
            a.c=str[i];
            li.push_back(a);
        }
    }
    dfs(0);
return 0;
}

