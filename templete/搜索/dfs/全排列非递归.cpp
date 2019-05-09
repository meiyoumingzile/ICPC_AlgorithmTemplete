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
#include<bitset>
using namespace std;
//std::ios::sync_with_stdio(false);
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LL long long
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=110;
const int mod=1e9+7;
bool vis[MAX];
int seq[MAX];
int N;
void print(){
    for(int i=1;i<=N;i++){
        printf("%d ",seq[i]);
    }printf("\n");
}
void dfs(){
    memset(vis,0,sizeof(vis));
    int i,j,now;
    stack<int>st;//栈保持当前数值
    st.push(1);
    seq[1]=1;
    vis[1]=true;
    while(!st.empty()){
        if(st.size()>=N){
            print();
        }
        j=st.top()+1;
        for(i=j;i<=N;i++){
            if(vis[i]==false){
                vis[i]=true;
                st.push(i);
                seq[st.size()]=i;
                break;
            }
        }
        if(i>N){
            now=st.top();
            vis[now]=false;
            st.pop();
        }

    }
}

int main(int argc,char *argv[]){
    //freopen("debug\\in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("debug\\out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//OJ上有的地方不能加这句话
    int i,j;
    while(~scanf("%d",&N)){
        dfs();
    }
return 0;
}
