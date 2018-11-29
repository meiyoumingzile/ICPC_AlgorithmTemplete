#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define cd Complex<double>
const int MAX=100010;
const double PI=acos(-1.0);
int N;
template <class Data>
struct Complex{
    Data *real,*imag;//real+imagi
    Complex(Data real=0,Data imag=0){
        this->real=new Data[1];
        this->imag=new Data[1];
        this->sett(real,imag);
    }
    Complex(int n){
        real=new Data[n];
        imag=new Data[n];
    }
    ~Complex(){
        delete []real;
        delete []imag;
    }
    void sett(const cd *b,int i=0,int j=0){
        real[i]=b->real[j];
        imag[i]=b->imag[j];
    }
    void sett(Data real,Data imag,int i=0){
        this->real[i]=real;
        this->imag[i]=imag;
    }
};
void add(cd *e,const cd *a,const cd *b,int k=0,int i=0,int j=0){
    e->sett(a->real[i]+b->real[j],a->imag[i]+b->imag[j],k);
}
void sub(cd *e,const cd *a,const cd *b,int k=0,int i=0,int j=0){
    e->sett(a->real[i]-b->real[j],a->imag[i]-b->imag[j],k);
}
void mul(cd *e,const cd *a,const cd *b,int k=0,int i=0,int j=0){
    e->sett(a->real[i]*b->real[j]-a->imag[i]*b->imag[j],a->imag[i]*b->real[j] + a->real[i]*b->imag[j],k);
}
void div(cd *e,const cd *a,double b,int k=0,int i=0){
    e->sett(a->real[i]/b,a->imag[i]/b,k);
}
namespace FFT{//FFT׼���϶࣬�������ƻ���������������ռ䣬�Ժ�����������鷳
    int *seq[25];//��������
    int seqSize[25];//�������鳤��
    const int p2[30]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216};
    void rader(int *x,int N){//������2��������
        int i,j,k;
        for(i=0;i<N;i++){
            x[i]=i;
        }
        for(j=0,i=0;i<N-1;i++){
            if(i<j)
               swap(x[i],x[j]);
            k=N/2;
            while(j>=k){
                j-=k;
                k/=2;
            }
            j+=k;
        }
    }
    cd *getW(int n,int fp){//�õ�Wn
        double k=2*PI/n;
        cd *e=new cd();
        e->sett(cos(k),-sin(k)*fp);
        return e;
    }
    ll changeN(ll N){//��N���2�������η���������������,����p2������±�
        ll i;
        for(i=0;p2[i]<N;i++);
        N=p2[i];
        if(seqSize[i]==0){
            seq[i]=new int[N+1];
            seqSize[i]=N;
            rader(seq[i],N);
        }
        return i;
    }

    cd *fft(const cd *x,int ni,int fp=1,int up=MAX,int xlen=MAX){//��ά���鷽ʽʵ��x���ȱ�����2��������,ni��2�Ķ��ٴ��ݣ�x����һ��Ҫ����>=p2[ni],������ܳ���Խ�磬fp��1���任��-1��ʾ��任��up�����鳤��,xlen��ԭ�����鳤��
        int i,j,n,m,bit,now,N=p2[ni];
        cd *G,*d;
        cd *temp,*F;
        d=new cd(0,0);
        F=new cd(up);
        cd *powg=new cd(up);
        for(i=0;i<N;i++){
            if(seq[ni][i]<xlen){
                F->sett(x,i,seq[ni][i]);
            }else{
                F->sett(0,0,i);
            }
        }
        for(n=2,bit=1;n<=N;n*=2,bit++){
            temp=new cd(up);
            m=n/2;
            powg->sett(1,0,0);
            G=getW(n,fp);
            for(i=1;i<m;i++)//��ǰԤ�������
                mul(powg,powg,G,i,i-1,0);
            for(i=0;i<N;i+=n){
                for(j=0;j<m;j++){
                    mul(d,F,powg,0,i+j+m,j);
                    add(temp,F,d,i+j,i+j,0);
                    sub(temp,F,d,i+j+m,i+j,0);
                }
            }
            delete F;
            delete G;
            F=temp;
        }
        if(fp==-1)
            for(i=0;i<N;i++)
                div(F,F,N,i,i);
        delete powg;
        delete d;
        return F;
    }
};

cd *x=new cd(MAX);
int main(){
    int i,j,k,n,ni;
    while(~scanf("%d",&N)){
        for(i=0;i<N;i++){
            scanf("%lf%lf",&x->real[i],&x->imag[i]);
        }
        ni=FFT::changeN(N);
        cd *F=FFT::fft(x,ni);
        for(i=0;i<N;i++){
            printf("%.10lf %.10lf\n",F->real[i],F->imag[i]);
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
