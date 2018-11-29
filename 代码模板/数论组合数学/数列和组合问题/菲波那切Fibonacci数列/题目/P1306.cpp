#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000000;
const int mod=1e8;

ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}

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
    ll n,m,g;
    M m1,m2,a;
    m1.init(1,2);
    m1.mat[0][0]=1;
    m1.mat[0][1]=1;
    a.init(2,2);
    a.mat[0][0]=0;
    a.mat[0][1]=1;
    a.mat[1][0]=1;
    a.mat[1][1]=1;
    m2.init(1,2);
    while(~scanf("%lld%lld",&n,&m)){
        if(n<3||m<3){
            printf("1\n");
        }else{
            g=gcd(n,m);
            m2.mat[0][1]=1;
            if(g>2){
                m2=matMul(m1,matPow(a,g-2,mod),mod);
            }
            printf("%lld\n",m2.mat[0][1]);
        }
    }
return 0;
}
