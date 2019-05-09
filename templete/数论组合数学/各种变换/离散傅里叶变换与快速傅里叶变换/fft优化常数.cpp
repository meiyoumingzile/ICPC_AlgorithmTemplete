#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define cd Complex<double>
const int MAX=100010;
const double PI=acos(-1.0);
int N;
const double PI=acos(-1.0);
#define cd Complex
struct Complex{
    double r=0,i=0;//r+ii
    Complex(){}
    Complex(double r,double i){
        sett(r,i);
    }
    void sett(double r,double i){
        this->r=r;
        this->i=i;
    }
    Complex operator + (const Complex &other){
        Complex(r+other.r,i+other.i);
        return Complex(r+other.r,i+other.i);
    }
    Complex operator - (const Complex &other){
        return Complex(r-other.r,i-other.i);
    }
    Complex operator * (const Complex &other){
        return Complex(r*other.r-i*other.i,i*other.r+r*other.i);
    }
    Complex operator / (const Complex &other){
        double m=other.r*other.r+other.i*other.i;
        return Complex((r*other.r+i*other.i)/m,(i*other.r-r*other.i)/m);
    }
    Complex operator / (const double &other){
        return Complex(r/other,i/other);
    }
};

namespace FFT{//FFT准备较多，避免名称混淆，定义个命名空间，以后避免重名的麻烦
    cd powg[MAX*8];
    const int p2[30]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216};
    inline ll changeN(ll N){//把N变成2的整数次方，并且生成序列,返回p2数组的下标
        ll i;
        for(i=0;p2[i]<N;i++);
        return i;
    }
    inline cd getW(int n,int fp){//得到Wn
        double k=2*PI/n;
        cd ans(cos(k),-sin(k)*fp);
        return ans;
    }
    inline void fft(cd *x,int ni,int fp){//把原本数组变换
        register int i,j,m,k,bit,N=p2[ni],n=N>>1;
        register cd d,inv,G;
        cd *p,*q;
        for(i=0,j=0;i<N;++i){
            if(i<j) swap(x[i],x[j]);
            for(k=n;(j^=k)<k;k>>=1);
        }
        powg[0]=cd(1,0);
        bit=1;
        for(m=1;m<N;m=n){
            n=m<<1;
            G=getW(n,fp);
            for(i=1;i<m;i++)//提前预处理加速
                powg[i]=powg[i-1]*G;
            for(i=0;i<N;i+=n){
                p=x+i;
                q=x+i+m;//得到前一半和后一半地址
                for(j=0;j<m;++j){
                    d=q[j]*powg[j];
                    q[j]=p[j]-d;
                    p[j]=p[j]+d;
                }
            }
            ++bit;
        }
        if(fp==-1)
            for(i=0;i<N;i++)
                x[i]=x[i]/(double)N;
    }
    //x长度必须是2的整数倍,ni是2的多少次幂，N=p2[ni]表示x数组要FFT的长度, fp是-1表示逆变换， xlen是x有效长度不够补0，up新数组长度
    inline cd *fft(const cd *x,int ni,int fp,int xlen,int up){
        cd *F=new cd[up];
        memcpy(F,x,sizeof(cd)*xlen);
        fft(F,ni,fp);
        return F;
    }
    void conv(cd *a,cd *b,int ni){//求卷积,ni表示是2的多少次方
        fft(a,ni,1);
        fft(b,ni,1);
        for(int i=0;i<ni;++i) a[i] = a[i]*b[i];
        fft(a,ni,-1);
    }
};

cd x[MAX];
int main(){
    int i,j,k,n,ni;
    while(~scanf("%d",&N)){
        for(i=0;i<N;i++){
            scanf("%lf%lf",&x[i].real,&x[i].imag);
        }
        ni=FFT::changeN(N);
        cd *F=FFT::fft(x,ni);
        for(i=0;i<N;i++){
            printf("%.10lf %.10lf\n",F[i].real,F[i].imag);
        }
    }
return 0;
}
/*
8
1 2
3 4
5 6
7 8
9 -1
10 -2
16 -3
20 -4

*/
