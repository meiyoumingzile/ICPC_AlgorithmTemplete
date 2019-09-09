#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define cd Complex<double>
const int MAX=100010;
const double PI=acos(-1.0);
int N;
template <class Data>
struct Complex{
    Data real,imag;//real+imagi
    Complex(){
    }
    Complex(Data real,Data imag){
        sett(real,imag);
    }
    void sett(Data real,Data imag){
        this->real=real;
        this->imag=imag;
    }
    Complex operator + (const Complex &other){
        Complex tmp;
        tmp.sett(real+other.real,imag+other.imag);
        return tmp;
    }
    Complex operator - (const Complex &other){
        Complex tmp;
        tmp.sett(real-other.real,imag-other.imag);
        return tmp;
    }
    Complex operator * (const Complex &other){
        Complex tmp;
        tmp.sett(real*other.real-imag*other.imag,imag*other.real+real*other.imag);
        return tmp;
    }
    Complex operator / (const Complex &other){
        Complex tmp;
        double m=other.real*other.real+other.imag*other.imag;
        tmp.real=(real*other.real+imag*other.imag)/m;
        tmp.imag=(imag*other.real-real*other.imag)/m;
        return tmp;
    }
};
cd pow(cd a,ll n){
    cd ans(1,0);
    while(n){
        if(n&1)
            ans=ans*a;
        a=a*a;
        n/=2;
    }
    return ans;
}
cd x[MAX];
cd *F;


int seq[MAX];
int p2[30]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576};
void getSeq(int N){
    N--;
    int i,j,k,bit,n;
    for(bit=0,n=N;n;n/=2,bit++);
    for(i=1;i<=N;i++){
        for(j=k=0,n=i;n;n/=2,j++){
            if(n&1)
                k+=p2[bit-j-1];
        }
        seq[i]=k;
    }
}
cd getW(int n,int kind){
    double k=2*PI/n;
    cd ans(cos(k),-sin(k)*kind);
    return ans;
}

void FFT(const cd *x,int &N,int kind){//kind表示是否是逆变换，逆变换和正变换差不多
    int i,j,n,m;
    for(i=0;p2[i]<N;i++);
    N=p2[i];
    getSeq(N);
    F=new cd[N];
    cd *temp;
    for(i=0;i<N;i++)
        F[i]=x[seq[i]];
    for(n=2;n<=N;n*=2){
        cd wn=getW(n,kind);
        temp=new cd[N];
        m=n/2;
        for(i=0;i<N;i+=n){
            for(j=0;j<n;j++){
                temp[i+j]=F[i+j%m]+F[i+j%m+m]*pow(wn,j);
            }
        }
        delete F;
        F=temp;
    }
    if(kind==-1){
        for(i=0;i<N;i++){
            F[i].real/=N;
            F[i].imag/=N;
        }
    }
}

int main(){
    int i,j,k,n;
    while(~scanf("%d",&N)){
        for(i=0;i<N;i++){
            scanf("%lf%lf",&x[i].real,&x[i].imag);
        }
        FFT(x,N,1);
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
