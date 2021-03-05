// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;

#define FOR(a,b,c) for(int a=(b),a##_end__=(c);a<a##_end__;++a)
#define mul(a,b) ((long long)(a)*(b)%Mod)
#define Mod 998244353
template<class T>inline bool chkmin(T&a,T const&b){return a>b?a=b,true:false;}
template<class T>inline bool chkmax(T&a,T const&b){return a<b?a=b,true:false;}
const int M=100005;
int A[M],B[M],C[M],D[M];
int n,m;
long long Pow(long long x,int k){
    long long res=1;
    for(;k;k>>=1,(x*=x)%=Mod)
        if(k&1) (res*=x)%=Mod;
    return res;
}
namespace Poly{
    const int M=1<<18|5;
    int a[M],b[M],c[M],w[M];
    void DFT(int *a,int n,int p){
        for(int i=0,j=0;i<n;++i){
            if(i<j) swap(a[i],a[j]);
            for(int k=n>>1;(j^=k)<k;k>>=1);
        }
        w[0]=1;
        for(int i=1;i<n;i<<=1){
            long long wn=Pow(3,Mod-1+p*(Mod-1)/(i<<1));

            for(int j=i-2;j>=0;j-=2) w[j+1]=wn*(w[j]=w[j>>1])%Mod;
            for(int j=0;j<n;j+=i<<1){
                int *p=a+j,*q=a+i+j;
                FOR(k,0,i){
                    long long x=1LL*q[k]*w[k];
                    q[k]=(p[k]-x)%Mod;
                    p[k]=(p[k]+x)%Mod;
                }
            }
        }
        if(p>0) return;
        long long inv=Pow(n,Mod-2);
        FOR(i,0,n) a[i]=inv*a[i]%Mod;
    }
    int calc(int m){
        int n=1;
        while(n<m) n<<=1;
        return n;
    }
    void multiply(int *A,int *B,int *C,int n,int m){
        FOR(i,0,n) a[i]=A[i];
        FOR(i,0,m) b[i]=B[i];
        n=calc(m+=n);
        DFT(a,n,1),DFT(b,n,1);
        FOR(i,0,n) a[i]=mul(a[i],b[i]);
        DFT(a,n,-1);
        FOR(i,0,m) C[i]=a[i];
        FOR(i,0,n) a[i]=b[i]=0;
    }
    void inverse(int *A,int *B,int m){
        int stk[20],top=0,n=calc(m<<1);
        for(int n=m;n>1;n=n+1>>1) stk[top++]=n;
        b[0]=Pow(A[0],Mod-2);
        while(top){
            int m=stk[--top],n=calc(m<<1);
            FOR(i,0,n) a[i]=i<m?A[i]:0;
            DFT(a,n,1),DFT(b,n,1);
            FOR(i,0,n) b[i]=b[i]*(2-mul(a[i],b[i]))%Mod;
            DFT(b,n,-1);
            FOR(i,m,n) b[i]=0;
        }
        FOR(i,0,m) B[i]=b[i];
        FOR(i,0,n) a[i]=b[i]=0;
    }
    void division(int *A,int *B,int *C,int n,int m){
        int l=calc(n<<1);
        FOR(i,0,m) c[i]=B[m-i-1];
        inverse(c,c,n-m+1);
        FOR(i,0,n) a[i]=A[n-i-1];
        DFT(a,l,1),DFT(c,l,1);
        FOR(i,0,l) c[i]=mul(c[i],a[i]);
        DFT(c,l,-1);
        FOR(i,0,n-m+1) C[i]=c[n-m-i];
        FOR(i,0,l) a[i]=c[i]=0;
    }
    void modular(int *A,int *B,int *C,int *D,int n,int m){
        division(A,B,C,n,m);
        multiply(B,C,c,m,n-m+1);
        FOR(i,0,m-1) D[i]=(A[i]-c[i])%Mod;
        FOR(i,0,calc(n+1)) c[i]=0;
    }
}

int main(){
    scanf("%d %d",&n,&m);
    FOR(i,0,n+1) scanf("%d",&A[i]);
    FOR(i,0,m+1) scanf("%d",&B[i]);
    Poly::modular(A,B,C,D,n+1,m+1);
    FOR(i,0,n-m+1) printf("%d ",(C[i]+Mod)%Mod);
    puts("");
    FOR(i,0,m) printf("%d ",(D[i]+Mod)%Mod);
    puts("");
    return 0;
}
