// luogu-judger-enable-o2
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#define rg register
const int inv2=500000004;
const int INF=2147483647;
const int MAX=4000010;
const int mod=998244353;

namespace NTT{//FFT׼���϶࣬�������ƻ���������������ռ䣬�Ժ�����������鷳
    const int P=998244353;
    ll powg[MAX];
    const int p2[30]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216};
    const int grn[30]={1,998244352,911660635,372528824,929031873,452798380,922799308,781712469,476477967,166035806,258648936,584193783,63912897,350007156,666702199,968855178,629671588,24514907,996173970,363395222,565042129,733596141};
    const int grninv[30]={1,998244352,86583718,509520358,337190230,87557064,609441965,135236158,304459705,685443576,381598368,335559352,129292727,358024708,814576206,708402881,283043518,3707709,121392023,704923114,950391366,428961804};
    inline ll quickmi(ll a,ll b,ll P){
        ll ans=1;
        for(a%=P;b;b>>=1,a=a*a%P)
            if(b&1)
                ans=ans*a%P;
        return ans;
    }
    inline ll changeN(ll N){//��N���2�������η���������������,����p2������±�
        ll i;
        for(i=0;p2[i]<N;i++);
        return i;
    }
    inline void ntt(ll *F,int ni,int fp,int xlen){//��ԭ������任
        register int i,j,m,k,bit,N=p2[ni],n=N>>1;
        register ll d,inv,G;
        ll *temp,*p,*q;
        for(i=0,j=0;i<N;++i){
            if(i<j) swap(F[i],F[j]);
            for(k=n;(j^=k)<k;k>>=1);
        }
        powg[0]=1;
        bit=1;
        for(m=1;m<N;m=n){
            n=m<<1;
            G=fp==1?grn[bit]:grninv[bit];
            for(i=1;i<m;++i)//��ǰԤ�������
                powg[i]=powg[i-1]*G%P;
            for(i=0;i<N;i+=n){
                p=F+i;
                q=F+i+m;//�õ�ǰһ��ͺ�һ���ַ
                for(j=0;j<m;++j){
                    d=q[j]*powg[j]%P;
                    q[j]=(p[j]-d+P)%P;
                    p[j]=(p[j]+d)%P;
                }
            }
            ++bit;
        }
        if(fp==-1){
            ll invN=quickmi(N,P-2,P);
            for(i=0;i<N;++i)
                F[i]=F[i]*invN%P;
        }

    }
    //x���ȱ�����2��������,ni��2�Ķ��ٴ��ݣ�N=p2[ni]��ʾx����ҪFFT�ĳ���, fp��-1��ʾ��任�� xlen��x��Ч���Ȳ�����0��up�����鳤��
    inline ll *ntt(const ll *x,int ni,int fp,int xlen,int up){
        ll *F=new ll[up];
        memcpy(F,x,sizeof(ll)*xlen);
        memset(F+xlen,0,sizeof(ll)*(p2[ni]-xlen));
        ntt(F,ni,fp,xlen);
        return F;
    }
};



ll *getInv(const ll *A,int lenA){//��A�������棬lenA����A����
    int i,ni,N,n;
    ll *B;
    if(lenA<=1){
        B=new ll[2];
        B[0]=NTT::quickmi(A[0],NTT::P-2,NTT::P);
        B[1]=0;
        return B;
    }
    B=getInv(A,(lenA+1)>>1);
    ni=NTT::changeN(lenA*2);
    n=NTT::p2[ni];
    N=NTT::p2[ni+1];
    ll *F1=NTT::ntt(A,ni+1,1,lenA,N);//Ҫ����ǳ˻���������Ӧ�������ߺͣ�������ni+1
    ll *F2=NTT::ntt(B,ni+1,1,lenA,N);
    for(i=0;i<N;i++)
        F1[i]=F1[i]*F2[i]%mod*F2[i]%mod;
    ll *x=NTT::ntt(F1,ni+1,-1,N,N);
    for(i=0;i<n;i++)
        x[i]=(2*B[i]%mod-x[i]+mod)%mod;
    memset(x+lenA,0,sizeof(ll)*(N-lenA));
    delete []B;
    delete []F1;
    delete []F2;
    B=x;
    return B;
}
ll *nttmul(ll *a,ll* b,int lena,int lenb){
    int i,n,ni,N,len;
    len=lena+lenb-1;
    ni=NTT::changeN(len+1);
    N=NTT::p2[ni];
    ll *F1=NTT::ntt(a,ni,1,lena,N);//Ҫ����ǳ˻���������Ӧ�������ߺͣ�������ni+1
    ll *F2=NTT::ntt(b,ni,1,lenb,N);
    for(i=0;i<N;i++){
        F1[i]=F1[i]*F2[i]%mod;
    }
    NTT::ntt(F1,ni,-1,N);
    memset(F1+len,0,sizeof(ll)*(N-len));
    delete []F2;
    return F1;
}
ll *getDiv(ll *A,ll *B,const int lena,const int lenb,ll *ansMod){
    int i,j,k,ni,N,M;
    k=lena-lenb+1;
    ni=NTT::changeN(k);
    M=NTT::p2[ni];
    ll *na=new ll[max(M,lena)];
    ll *nb=new ll[max(M,lenb)];
    for(i=0;i<lena;i++)
        na[i]=A[lena-i-1];
    for(i=0;i<lenb;i++)
        nb[i]=B[lenb-i-1];
    for(i=lenb;i<M;i++)
        nb[i]=0;
    ll *nbinv=getInv(nb,k);
    ll *c=nttmul(na,nbinv,k,k);
    for(i=0;i<(k>>1);i++){
        swap(c[i],c[k-i-1]);
    }
    ll *mulArr=nttmul(c,B,k,lenb);
    for(i=0;i<lenb-1;i++){
        ansMod[i]=(A[i]-mulArr[i]+mod)%mod;
    }
    delete []mulArr;
    return c;
}
ll A[MAX],B[MAX],D[MAX];
int main(int argc,char *argv[]){
   // freopen("���ݶ���ʽ����//testdata1.in","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("���ݶ���ʽ����//myout.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i,j,k,T,n,m,ni;
    scanf("%d%d",&n,&m);
    n++;
    m++;
    for(i=0;i<n;i++){
        scanf("%lld",&A[i]);
    }
    for(i=0;i<m;i++){
        scanf("%lld",&B[i]);
    }
    ll *C=getDiv(A,B,n,m,D);
    k=n-m+1;
    for(i=0;i<k;i++){
        printf("%lld%c",C[i],i==k-1?'\n':' ');
    }

    for(i=0;i<m-1;i++){
        printf("%lld%c",D[i],i==m-2?'\n':' ');
    }
return 0;
}
/*
4 2
-1 0 0 0 1
-1 0 1
*/
