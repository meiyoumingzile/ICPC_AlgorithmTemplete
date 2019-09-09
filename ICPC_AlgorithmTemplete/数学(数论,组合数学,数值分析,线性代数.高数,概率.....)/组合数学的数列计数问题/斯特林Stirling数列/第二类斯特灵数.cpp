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
const int INF=1<<30;
const int MAX=1010;
const int mod=1e9+7;
ll s[MAX][MAX];
void init(){//������Ϊ�Ƕ�ͼ�滮
    int i,j;
    memset(s,0,sizeof(s));
    s[1][1]=1;
    for(i=2;i<=MAX-1;i++)
        for(j=1;j<=i;j++){
            s[i][j]=s[i-1][j-1]+j*s[i-1][j];
            if(s[i][j]>=mod)
            s[i][j]%=mod;
        }
}


int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int n,m;
    init();
    while(~scanf("%d%d",&n,&m)){//n>m
        printf("%lld\n",s[n][m]);
    }
return 0;
}
