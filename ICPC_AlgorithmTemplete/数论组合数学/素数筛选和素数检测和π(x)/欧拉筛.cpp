#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100000010;
const int mod=1e9+7;

bool vis[MAX];
int p[MAX];
int pCnt;
void getPrimes(int n){
    memset(vis,0,sizeof(vis));
    rg int i,j=0;
    pCnt=0;
    for(i=2;i<n;i++){
        if(!vis[i]){
            p[pCnt++]=i;
        }
        for(j=0;i*p[j]<n;j++){
            vis[i*p[j]]=1;
            if(i%p[j]==0){
                break;
            }
        }
    }
}

int main(int argc,char *argv[]){
    int n,i,j;
    //scanf("%d",&n);
   // n=100;
    getPrimes(MAX-10);
    /*printf("%d\n",pCnt);
    for(i=0;i<pCnt;i++){
        printf("%d ",p[i]);
    }*/
return 0;
}
