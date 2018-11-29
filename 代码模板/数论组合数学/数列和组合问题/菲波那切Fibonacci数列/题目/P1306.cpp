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
        mat=new  ll*[n];//////////建立二维数组；
        for(int i=0;i<n;i++){
            mat[i]=new ll[m];
            memset(mat[i],0,sizeof(ll)*m);
        }
    }
    void del(){
        for(int i=0;i<m;i++){//释放二维数组；
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
    if(a.m!=b.n){//第一个矩阵的列数m,要等于第二个矩阵行数才可以
        printf("矩阵大小不合法！\n");
        return c;
    }
    int i,j,k,r;
    r=a.m;
    c.init(a.n,b.m);
    for(i=0;i<c.n;i++){
        for(j=0;j<c.m;j++){
            c.mat[i][j]=0;
            for(k=0;k<r;k++){//矩阵的行
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
        printf("矩阵大小不合法！\n");
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
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
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
