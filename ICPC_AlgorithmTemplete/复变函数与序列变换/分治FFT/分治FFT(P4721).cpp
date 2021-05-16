#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=998244353;

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
namespace FFT{//FFT׼���϶࣬�������ƻ���������������ռ䣬�Ժ�����������鷳
    cd wn[MAX*4];
    const int p2[30]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216};
    inline ll changeN(ll N){//��N���2�������η���������������,����p2������±�
        ll i;
        for(i=0;p2[i]<N;i++);
        return i;
    }

    void getwn(int n){
        for(int i=0;i<n;i++)wn[i] = cd(cos(2*PI/n*i),sin(2*PI/n*i));
    }
    inline void fft(cd *x,int ni,int fp){//��ԭַ����fft�任Ҫ�����鳤��Ҫ����p2[ni]
        int i,j,m,k,N=p2[ni],n=N>>1;
        cd d,inv,G;
        cd *p,*q;
        for(i=0,j=0;i<N;++i){//�׵��㷨
            if(i<j)swap(x[i],x[j]);
            for(k=n;(j^=k)<k;k>>=1);
        }
        for(m=1;m<N;m=n){
            n=m<<1;
            for(i=0;i<N;i+=n){
                p=x+i;
                q=x+i+m;//�õ�ǰһ��ͺ�һ���ַ
                for(j=0;j<m;++j){
                    cd d=wn[N/n*j]*q[j];
                    q[j]=p[j]-d;
                    p[j]=p[j]+d;
                }
            }
        }
        if(fp==-1){
            m=N>>1;
            for(i=1;i<m;i++)
                swap(x[i],x[N-i]);
            for(i=0;i<N;i++)
                x[i]=x[i]/N;
        }
    }
    void convolution(int *x,int n,int *y,int m,int *ans){//����,��֪x�����y���飬nΪx��y�������ֵ����ans
        int i,ni=changeN(max(n,m));
        int N=p2[ni];
        cd *xx=new cd[N];
        cd *yy=new cd[N];
        for(i=0;i<n;i++){
            xx[i]=cd(x[i],0);
        }
        for(i=0;i<m;i++){
            yy[i]=cd(y[i],0);
        }
        fft(xx,ni,1);
        fft(yy,ni,1);
        for(i=0;i<N;i++){
            xx[i]=xx[i]*yy[i];
        }
        fft(xx,ni,-1);
        for(i=0;i<N;i++){
            ans[i]=xx[i].r+0.1;
        }
        delete xx;
        delete yy;
    }
    void divConvolution(ll *x,ll *y,int l,int r){//����ξ����������FFT����֪x���飬��y������[l,r)
        if(l>=r)
            return;
        int mid=(l+r)/2,len=(r-l+1);
        int n=mid-l,m=r-mid;
        divConvolution(x,y,l,mid);
        int i,ni=changeN(max(n,m));
        int N=p2[ni];
        cd *xx=new cd[N];
        cd *yy=new cd[N];
        for(i=0;i<n;i++){
            xx[i]=cd(x[l+i],0);
            yy[i]=cd(y[l+i],0);
        }
        fft(xx,ni,1);
        fft(yy,ni,1);
        for(i=0;i<N;i++){
            yy[i]=xx[i]*yy[i];
        }
        fft(yy,ni,-1);
        for(i=0;i<m;i++){
            y[mid+i]=yy[i].r+0.1;
            //y[i]%=mod;
        }
        delete xx;
        delete yy;
        divConvolution(x,y,mid,r);
    }
};



int main(int argc,char *argv[]){
	int i,j,k,t,T,n,m;

return 0;
}

