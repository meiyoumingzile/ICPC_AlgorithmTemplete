#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=998244353;

namespace NTT{//FFT׼���϶࣬�������ƻ���������������ռ䣬�Ժ�����������鷳
    const int P=998244353;
    ll powg[MAX*8];
    int *seq[25];
    int seqSize[25];
    const int p2[30]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216};
    const int grn[30]={1,998244352,911660635,372528824,929031873,452798380,922799308,781712469,476477967,166035806,258648936,584193783,63912897,350007156,666702199,968855178,629671588,24514907,996173970,363395222,565042129,733596141};
    const int grninv[30]={1,998244352,86583718,509520358,337190230,87557064,609441965,135236158,304459705,685443576,381598368,335559352,129292727,358024708,814576206,708402881,283043518,3707709,121392023,704923114,950391366,428961804};
    void rader(int *x,int N){//������2��������
        int i,j,k;
        for(i=0;i<N;i++){
            x[i]=i;
        }
        for(j=0,i=0;i<N-1;i++){
            if(i<j){
               swap(x[i],x[j]);
            }
            k=N/2;
            while(j>=k){
                j-=k;
                k/=2;
            }
            j+=k;
        }
    }
    ll quickmi(ll a,ll b,ll P){
        ll ans=1;
        for(a%=P;b;b>>=1,a=a*a%P)
            if(b&1)
                ans=ans*a%P;
        return ans;
    }
    void getSeq(int i){
        int N=p2[i];
        if(seqSize[i]==0){//��ֹ�������ͬ���򣬵��ǻ�����һ��ռ�
            seq[i]=new int[N+1];
            seqSize[i]=N;
            rader(seq[i],N);
        }
    }
    ll changeN(ll N){//��N���2�������η���������������,����p2������±�
        ll i;
        for(i=0;p2[i]<N;i++);
        getSeq(i);
        return i;
    }
    //x���ȱ�����2��������,ni��2�Ķ��ٴ��ݣ�N=p2[ni]��ʾx����ҪFFT�ĳ���, fp��-1��ʾ��任�� xlen��x��Ч���Ȳ�����0��up�����鳤��
    ll* ntt(const ll *x,int ni,int fp,int xlen=MAX,int up=MAX){
        int i,j,n,m,bit,now,N=p2[ni];
        ll d,inv,b,G,Gn;
        ll *temp,*F;
        F=new ll[up];
        for(i=0;i<N;i++)
            F[i]=seq[ni][i]<xlen?x[seq[ni][i]]:0;
        for(n=2,bit=1;n<=N;n*=2,bit++){
            temp=new ll[up];
            m=n/2;
            powg[0]=1;
            G=fp==1?grn[bit]:grninv[bit];
            for(i=1;i<m;i++){//��ǰԤ�������
                powg[i]=powg[i-1]*G%P;
            }
            for(i=0;i<N;i+=n){
                for(j=0;j<m;j++){
                    b=F[i+j];
                    d=F[i+j+m]*powg[j]%P;
                    temp[i+j]=(b+d)%P;
                    temp[i+j+m]=(b-d+P)%P;//���ù�ʽ�����˷�����
                }
            }
            delete []F;
            F=temp;
        }
        if(fp==-1){
            ll invN=quickmi(N,P-2,P);
            for(i=0;i<N;i++){
                F[i]=F[i]*invN%P;
            }
        }
        return F;
    }
};

ll *nttmul(ll *a,ll*b,int lena,int lenb,int ni){
    int i,j,k,N;
    N=NTT::p2[ni+1];
    NTT::getSeq(ni+1);
    ll *F1=NTT::ntt(a,ni+1,1,lena,N);
    ll *F2=NTT::ntt(b,ni+1,1,lenb,N);
    ll *F3=new ll[N];
    for(i=0;i<N;i++){
        F3[i]=F1[i]*F2[i]%NTT::P;
    }
    ll *x=NTT::ntt(F3,ni+1,-1,N,N);
    delete []F1;
    delete []F2;
    delete []F3;
    return x;
}
ll A[MAX];
ll *getInv(ll *A,int lenA){//��A�������棬lenA����A����
    int i,j,k,ni,N,n,n2,M;
    ll *B,B1,B2;
    ni=NTT::changeN(lenA);
    M=NTT::p2[ni];
    B=new ll[1];
    B[0]=NTT::quickmi(A[0],NTT::P-2,NTT::P);
    for(i=0;NTT::p2[i]<=M;i++){
        n=NTT::p2[i];
        ll *B1=nttmul(A,B,n,n,i);
        for(j=0;j<n;j++){
            B1[j]=(-B1[j]+mod)%mod;
        }
        B1[0]=(B1[0]+2)%mod;
        ll *B2=nttmul(B,B1,n,n,i);
        delete []B;
        delete []B1;
        B=B2;
        for(j=0;j<NTT::p2[i];j++){
            printf("%lld ",B[j]);
        }printf("..\n");
    }
    return B;
}

int main(int argc,char *argv[]){
    freopen("���ݶ���ʽ����//in1.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    freopen("���ݶ���ʽ����//ac1.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i,j,k,T,n;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%lld",&A[i]);
    }
    ll* ans=getInv(A,n);
    printf("%lld",ans[0]);
    for(i=1;i<n;i++){
        printf(" %lld",ans[i]);
    }printf("\n");
return 0;
}
/*
5
1 6 3 4 9
*/
