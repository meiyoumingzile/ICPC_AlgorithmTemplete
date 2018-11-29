#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<map>
#include<set>
//#include<windows.h>
using namespace std;
//std::ios::sync_with_stdio(false);
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LL long long
#define ll long long
#define inf 1e-5
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;


int dp[MAX];
int A[MAX];
vector<int>g[MAX];
vector<int>li[MAX];

int sum(int now){
    if(!dp[now]){
        int i,j,k,add1=0,add2=0;
        for(i=0;i<li[now].size();i++){
            k=li[now][i];
            add2+=sum(k);
            for(j=0;j<li[k].size();j++){
                add1+=sum(li[k][j]);
            }
        }
        dp[now]=max(add1+A[now],add2);
    }
    return dp[now];
}

void getTree(int now,int last){
    int i,j;
    for(i=0;i<g[now].size();i++){
        if(g[now][i]!=last){
            li[now].push_back(g[now][i]);
            getTree(g[now][i],now);
        }
    }
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int n;
    int i,j,k,b,e,maxdp;
    cin>>n;
    for(i=1;i<=n;i++){
        scanf("%d",&A[i]);
    }
    for(i=1;i<n;i++){
        scanf("%d%d",&b,&e);
        g[b].push_back(e);
        g[e].push_back(b);
    }
    getTree(1,-1);
    for(i=1,maxdp=0;i<=n;i++){
        maxdp=max(maxdp,sum(i));
    }
    printf("%d\n",maxdp);
return 0;
}
