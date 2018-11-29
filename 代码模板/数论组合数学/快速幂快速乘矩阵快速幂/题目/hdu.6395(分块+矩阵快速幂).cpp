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
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;

const int MATSIZE=3;
struct M{
    int m,n;
    ll mat[MATSIZE][MATSIZE];
    M(cint n,cint m){
        init(n,m);
    }
    void init(cint n,cint m){
        this->n=n;
        this->m=m;
        memset(mat,0,sizeof(mat));
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
        memset(mat,0,sizeof(mat));
        for(int i=0;i<n;i++){
            mat[i][i]=1;
        }
    }
};

M matMul(const M &a,const M &b,cll mod){
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
M matMul(const M &a,ll b,cll mod){
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
M a0(1,3),a(3,3);
ll A , B, C, D, P;

void ANSnext(M &ANS,cll n,cll i){
    ll k=(C*ANS.mat[0][0]%mod+D*ANS.mat[0][1]%mod+n/i)%mod;
    ANS.mat[0][0]=ANS.mat[0][1];
    ANS.mat[0][1]=k;
}

M divSum(cll n,cll m){//sum(n/i),i的范围是，[1,m]
    M ANS=a0;
    ll i,j,k,h,sqrtn;
    M an(3,3);
    if(m<3){
        return ANS;
    }
    sqrtn=(ll)sqrt(n);
    h=n/sqrtn+1;
    if(m<=h){//小于等于sqrtn的情况
        for(i=3;i<=m;i++){
            ANSnext(ANS,n,i);
        }
        return ANS;
    }else{
        for(i=3;i<=h;i++){
            ANSnext(ANS,n,i);
        }
        ANS.mat[0][2]=n/h;
        i=h;
        j=sqrtn;
        while(j>1){
            k=n/(j-1)-n/j;
            j--;
            if(i+k<=m){
                an=matPow(a,k-1,mod);
                ANS=matMul(ANS,an,mod);//
                ANSnext(ANS,n,i+k);
                ANS.mat[0][2]--;
                i+=k;
            }else{
                an=matPow(a,m-i,mod);
                ANS=matMul(ANS,an,mod);//
                return ANS;
            }

        }
    }
    an=matPow(a,m-n-1,mod);
    ANS=matMul(ANS,an,mod);//
    return ANS;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	ll i,j,k,T,t, n;
	M ans(1,3);
	cin>>T;
    while(T--){
        scanf("%lld%lld%lld%lld%lld%lld",&A,&B,&C,&D,&P,&n);//求n-1次方
        a0.mat[0][0]=A;a0.mat[0][1]=B;a0.mat[0][2]=0;
        a.mat[0][0]=a.mat[0][2]=0;a.mat[0][1]=C;
        a.mat[1][0]=1;a.mat[1][1]=D;a.mat[1][2]=0;
        a.mat[2][0]=0;a.mat[2][1]=1;a.mat[2][2]=1;
        if(n<3){
            printf("%lld\n",a0.mat[0][n-1]);
            continue;
        }

        ans=divSum(P,n);
        printf("%lld\n",ans.mat[0][1]);
    }
return 0;
}
/*
55
3 2 2 2 100 200
*/
