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
const int MAX=1000010;
const int mod=9973;

struct M{
    int m,n;
    ll **mat;
    void init(int n,int m){
        this->n=n;
        this->m=m;
        mat=new  ll*[n];//////////������ά���飻
        for(int i=0;i<n;i++){
            mat[i]=new ll[m];
            memset(mat[i],0,sizeof(ll)*m);
        }
    }
    void del(){
        for(int i=0;i<m;i++){//�ͷŶ�ά���飻
            delete []mat[i];
        }
        delete []mat;
    }

    void print(){
        int i,j;
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                printf("%lld ",mat[i][j]);
            }printf("\n");
        }
    }

    void getIdmat(){
        for(int i=0;i<n;i++){
            mat[i][i]=1;
        }
    }
};

M matMul(M a,M b,ll mod){
    M c;
    if(a.m!=b.n){//��һ�����������m,Ҫ���ڵڶ������������ſ���
        printf("�����С���Ϸ���\n");
        return c;
    }
    int i,j,k,r;
    r=a.m;
    c.init(a.n,b.m);
    for(i=0;i<c.n;i++){
        for(j=0;j<c.m;j++){
            c.mat[i][j]=0;
            for(k=0;k<r;k++){//�������
                c.mat[i][j]+=a.mat[i][k]*b.mat[k][j];
                c.mat[i][j]%=mod;
            }
        }
     }
     return c;
}

M matPow(M a,ll k,ll mod){
    M e,c;
    if(a.n!=a.m){
        printf("�����С���Ϸ���\n");
        return e;
    }
    e.init(a.n,a.m);
    c.init(a.n,a.m);
    e.getIdmat();
    if(k==0){
        return e;
    }
    c=a;
    while(k){
        if(k%2==1){
            e=matMul(e,c,mod);
        }
        c=matMul(c,c,mod);
        k/=2;
    }
    return e;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i,j,T,n,k;
    ll ans;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        M a;
        a.init(n,n);
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                scanf("%lld",&a.mat[i][j]);
            }
        }
        M e=matPow(a,k,mod);
        //e.print();
        for(i=0,ans=0;i<n;i++){
            ans=(ans+e.mat[i][i])%mod;
        }
        printf("%lld\n",ans);
    }
return 0;
}
