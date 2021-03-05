#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+9;

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
            printf("%lld",mat[i][0]);
            for(j=1;j<m;j++){
                printf(" %lld",mat[i][j]);
            }printf("\n");
        }
    }

    void getIdmat(){
        for(int i=0;i<n;i++){
            mat[i][i]=1;
        }
    }
};

M matMul(const M &a,const M &b,ll mod){
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
M matMul(const M &a,ll b,ll mod){
    M c;
    int i,j,k,r;
    c.init(a.n,a.m);
    for(i=0;i<c.n;i++){
        for(j=0;j<c.m;j++){
            c.mat[i][j]=a.mat[i][j]*b%mod;
        }
    }
    return c;
}

M matPow(const M &a,ll k,ll mod){
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
    ll n;
    cin>>n;
    M a0,m;
    m.init(2,2);
    a0.init(1,2);
    a0.mat[0][1]=1;
    m.mat[0][0]=1;
    m.mat[0][1]=1;
    m.mat[1][0]=1;
    M ans=matPow(m,n,mod);
    ans=matMul(a0,ans,mod);
    printf("%lld\n",ans.mat[0][0]);
return 0;
}

