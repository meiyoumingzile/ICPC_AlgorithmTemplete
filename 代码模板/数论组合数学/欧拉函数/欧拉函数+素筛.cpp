#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
#define ll long long
const int MAX=1010;


int pCnt;
bool vis[MAX];
int prime[MAX];
int phi[MAX];
void getPrime(int N){
    int i,j,k;
    pCnt=0;
    phi[1]=1;
    for(i=2;i<N;i++){
        if(!vis[i]){
            prime[pCnt++]=i;
            phi[i]=i-1;//如果i是素数，phi[i]=i-1
        }
        for(j=0;i*prime[j]<N;j++){
            k=i*prime[j];
            vis[k]=true;
            if(i%prime[j]==0){
                //i mod p = 0, 那么phi(i * p)=p * phi(i)
                phi[k]=phi[i]*prime[j];
                break;
            }else{
                 //i mod p ≠0,  那么phi(i * p)=phi(i) * (p-1)，p是素数
                 phi[k]=phi[i]*(prime[j]-1);
            }
        }
    }
}

ll getEu(ll N){//根据公式，求一个数欧拉函数值,且数据较大有必要用筛法先求出素数,如果打表求很多个用下面的筛选方法
    ll i,n=N,ans=N,m=1;
    for(i=0;n!=1&&i<pCnt;i++){
        if(n%prime[i]==0){
            while(n%prime[i]==0)
                n/=prime[i];
            ans/=prime[i];
            m*=prime[i]-1;
        }
    }
    if(n>1){
        ans/=n;
        m*=n-1;
    }
    return ans*m;
}

/*ll getEu(ll N){//根据公式，求一个数欧拉函数值，且数据较大有必要用筛法先求出素数,如果打表求很多个用下面的筛选方法
    ll i,j,n=N,ans=N,m=1;
    for(i=2;n!=1;i++){
        if(n%i==0){
            while(n%i==0)
                n/=i;
            ans/=i;
            m*=i-1;
        }
    }
    if(ans==N){
        return N-1;
    }
    return ans*m;
}*/


int main(){
    int i,j,n,a,b;
    getPrime(MAX);//由于还要筛欧拉函数，大约2.2秒出结果,只筛素数1秒
    printf("欧拉函数有：\n");
    for(i=1;i<200;i++){
        printf("%d:%d\n",i,phi[i]);
    }
    return 0;
}
