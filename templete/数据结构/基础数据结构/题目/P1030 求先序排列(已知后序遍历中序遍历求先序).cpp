#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1010;
const int mod=1e9+7;
int N;
char s1[MAX],s2[MAX];
int inds1[MAX],inds2[MAX];
bool vis[MAX];

int getC(char a){
    return a-'A';
}

void dfs(int now){
    vis[now]=true;
    //printf("%d ",now);
    printf("%c",s1[now]);
    //getchar();
    int i;
    if(now-1>=0&&!vis[now-1]){
        int maxInd=-1;
        for(i=now-1;i>=0&&!vis[i];i--){
            maxInd=max(maxInd,inds2[getC(s1[i])]);
        }
        dfs(inds1[getC(s2[maxInd])]);
    }
    if(now+1<N&&!vis[now+1]){
        int maxInd=-1;
        for(i=now+1;i<N&&!vis[i];i++){
            maxInd=max(maxInd,inds2[getC(s1[i])]);
        }
        dfs(inds1[getC(s2[maxInd])]);
    }
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k;
    cin>>s1>>s2;
    N=strlen(s2);
    for(i=0;i<N;i++){
        inds1[getC(s1[i])]=i;
        inds2[getC(s2[i])]=i;
    }
    dfs(inds1[getC(s2[N-1])]);
return 0;
}
