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

const int MAX=110;
bool vis[MAX];
int seq[MAX];
int N;
void print(){
    for(int i=1;i<=N;i++){
        printf("%d ",i);
    }printf("\n");
    for(int i=1;i<=N;i++){
        printf("%d ",seq[i]);
    }printf("\n");
}

void dfs(int len){
    if(len==N){
        print();
        return;
    }
    int i,j;
    for(i=1;i<=N;i++){
        if(vis[i]==false){
            vis[i]=true;
            seq[len+1]=i;
            dfs(len+1);
            vis[i]=false;
        }
    }
}

int main(int argc,char *argv[]){

    int i,j;
    while(~scanf("%d",&N)){
        memset(vis,0,sizeof(vis));
        dfs(0);
    }
return 0;
}
