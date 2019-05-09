#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
#define cdou const double &
#define cv2 const v2 &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;
const int MATSIZE=3;
struct M{
    int m,n;
    ll mat[MATSIZE][MATSIZE];
    M(int n,int m){
        init(n,m);
    }
    void init(int n,int m){
        this->n=n;
        this->m=m;
        memset(mat,0,sizeof(mat));
    }
    void getIdmat(){
        for(int i=0;i<n;i++){
            mat[i][i]=1;
        }
    }
};

M matMul(const M &a,const M &b,ll mod){
    M c(a.n,b.m);
    if(a.m!=b.n){//第一个矩阵的列数m,要等于第二个矩阵行数才可以
        printf("矩阵大小不合法！\n");
        return c;
    }
    int i,j,k,r;
    r=a.m;
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
    M c(a.n,a.m);
    int i,j,k,r;
    for(i=0;i<c.n;i++){
        for(j=0;j<c.m;j++){
            c.mat[i][j]=a.mat[i][j]*b%mod;
        }
    }
    return c;
}

M matPow(const M &a,ll k,cll mod){
    M e(a.n,a.m),c(a.n,a.m);
    if(a.n!=a.m){
        printf("矩阵大小不合法！\n");
        return e;
    }
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
	ll T,n;
	M m(3,3);
    m.mat[0][0]=0;m.mat[0][1]=0;m.mat[0][2]=1;
    m.mat[1][0]=1;m.mat[1][1]=0;m.mat[1][2]=0;
    m.mat[2][0]=0;m.mat[2][1]=1;m.mat[2][2]=1;
    M a0(1,3);
    a0.mat[0][0]=a0.mat[0][1]=a0.mat[0][2]=1;
    M ans(1,3),pm(1,3);
    cin>>T;
    while(T--){
        scanf("%lld",&n);
        if(n<4){
            printf("%lld\n",a0.mat[0][n-1]);
        }else{
            pm=matPow(m,n-3,mod);
            ans=matMul(a0,pm,mod);
            printf("%lld\n",ans.mat[0][2]);
        }
    }
return 0;
}

