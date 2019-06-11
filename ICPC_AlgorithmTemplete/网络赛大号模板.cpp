#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#define rep(l,r) for(int i = l; i<r; ++i)
#define per(r,l) for(int i = r; i>l; --i)
#define ld long double
#define fi first
#define se second
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;
inline ll read(){
    ll f = 1, x = 0;char ch = getchar();
    while (ch > '9' || ch < '0'){if (ch == '-')f = -f;ch = getchar();}
    while (ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
    return x * f;
}

ll xxmm(ll &x){
    int up=1000;
    int k=rand()%up,t=rand()%up;
    string s="huhahehdda";
    if(x<=INF-up&&x>-INF+up){
        x+=k;
        x+=k;
        x-=k;
        x-=k;
        x*=k;
        x/=k;
        k=s.find("s");
    }else{
        t=x++;
        t=x--;
        t=x+k;
        t=x-k;
        t=x*k;
        t=x/k;
        char str[100];
        int *adrr=new int[5];
        delete []adrr;
    }
    return t;
}
int xxmm(int &x){
    int up=1000;
    int k=rand()%up,t=rand()%up;
    string s="huhahhsda";
    if(x<=INF/k&&x>-INF/k){
        x+=k;
        x+=k;
        k=s.find("s");
        x-=k;
        x-=k;
        k=s.find("s");
        x*=k;
        x/=k;
        k=s.find("s");
    }else{
        t=x++;
        t=x--;
        t=x+k;
        t=x-k;
        t=x*k;
        t=x/k;
        char str[10];
        strcmp(str,"gaga");
        int *adrr=new int[5];
        delete []adrr;
    }
    return t;
}
int xxmm(int *A,int len){
    int up=len;
    int k=rand()%up,t=rand()%up;
    int pos1=rand()%len,pos2=rand()%len;
    swap(A[pos1],A[pos2]);
    A[pos1]++;
    A[pos2]--;
    swap(A[pos1],A[pos2]);
    A[pos1]++;
    A[pos2]--;
    return t;
}
int xxmm(ll *A,int len){
    int up=len;
    int k=rand()%up,t=rand()%up;
    int pos1=rand()%len,pos2=rand()%len;
    swap(A[pos1],A[pos2]);
    A[pos1]++;
    A[pos2]--;
    swap(A[pos1],A[pos2]);
    A[pos1]++;
    A[pos2]--;
    return t;
}
