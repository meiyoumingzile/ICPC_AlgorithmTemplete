#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#define rg register
const int inv2=500000004;
const int INF=2147483647;
const int MAX=2000010;
const int mod=1e9+7;

namespace NTT{//FFT׼���϶࣬�������ƻ���������������ռ䣬�Ժ�����������鷳
    const int P=1e9+7;
    ll powg[MAX];
    int *seq[25];
    int seqSize[25];
    const int p2[30]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216};
    const int grn[30]={1,1000000006,694969654,233939221,850153601,410273365,70568353,896703593,418923782,376965048,80677378,403647879,188324199,231374250,662406845,19945454,427497125,363665645,162861709,486465643,380534669,281016459};
    const int grninv[30]={1,1000000006,525151758,566626863,630744615,840235484,822979621,950696814,68344034,876980455,856898045,962301030,15264921,622960887,827496651,360704903,632508602,104226761,505863558,290141121,350813334,2870323};

    inline void rader(int *x,int N){//������2��������
        register int i,j,k;
        for(i=0;i<N;++i)
            x[i]=i;
        for(j=0,i=0;i<N-1;++i){
            if(i<j){
               swap(x[i],x[j]);
            }
            k=N>>1;
            while(j>=k){
                j-=k;
                k>>=1;
            }
            j+=k;
        }
    }
    inline ll quickmi(ll a,ll b,ll P){
        ll ans=1;
        for(a%=P;b;b>>=1,a=a*a%P)
            if(b&1)
                ans=ans*a%P;
        return ans;
    }
    inline void getSeq(int i){
        int N=p2[i];
        if(seqSize[i]==0){//��ֹ�������ͬ���򣬵��ǻ�����һ��ռ�
            seq[i]=new int[N+1];
            seqSize[i]=N;
            rader(seq[i],N);
        }
    }
    inline ll changeN(ll N){//��N���2�������η���������������,����p2������±�
        ll i;
        for(i=0;p2[i]<N;i++);
        getSeq(i);
        return i;
    }
    //x���ȱ�����2��������,ni��2�Ķ��ٴ��ݣ�N=p2[ni]��ʾx����ҪFFT�ĳ���, fp��-1��ʾ��任�� xlen��x��Ч���Ȳ�����0��up�����鳤��
    inline ll* ntt(const ll *x,int ni,int fp,int xlen=MAX,int up=MAX){
        register int i,j,n,m,bit,now,N=p2[ni];
        register ll d,inv,b,G,Gn;
        ll *temp,*F;
        F=new ll[up];
        for(i=0;i<N;++i)
            F[i]=seq[ni][i]<xlen?x[seq[ni][i]]:0;
        for(n=2,bit=1;n<=N;n<<=1,++bit){
            temp=new ll[up];
            m=n>>1;
            powg[0]=1;
            G=fp==1?grn[bit]:grninv[bit];
            for(i=1;i<m;++i){//��ǰԤ�������
                powg[i]=powg[i-1]*G%P;
            }
            for(i=0;i<N;i+=n){
                for(j=0;j<m;++j){
                    d=F[i+j+m]*powg[j]%P;
                    temp[i+j]=(F[i+j]+d)%P;
                    temp[i+j+m]=(F[i+j]-d+P)%P;//���ù�ʽ�����˷�����
                }
            }
            delete []F;
            F=temp;
        }
        if(fp==-1){
            ll invN=quickmi(N,P-2,P);
            for(i=0;i<N;++i){
                F[i]=F[i]*invN%P;
            }
        }
        return F;
    }
};

ll *nttcalc(ll *a,ll*b,int ni){//a��b����Ҫ��������У�ni����Ҫ����2�Ķ��ٴη�
    int i,n,N;
    n=NTT::p2[ni];
    N=NTT::p2[ni+1];
    NTT::getSeq(ni+1);
    ll *F1=NTT::ntt(a,ni+1,1,n,N);//Ҫ����ǳ˻���������Ӧ�������ߺͣ�������ni+1
    ll *F2=NTT::ntt(b,ni+1,1,n,N);
    ll *F3=new ll[N];
    for(i=0;i<N;i++){
        F3[i]=F1[i]*F2[i]%mod*F2[i]%mod;
    }

    ll *x=NTT::ntt(F3,ni+1,-1,N,N);
    for(i=0;i<n;i++){
        x[i]=(2*b[i]%mod-x[i]+mod)%mod;
    }
    memset(x+n,0,sizeof(ll)*n);
    delete []F1;
    delete []F2;
    delete []F3;
    return x;
}

ll *getInv(ll *A,int lenA){//��A�������棬lenA����A����
    int i,j,ni,n,M;
    ll *B,*B1;
    ni=NTT::changeN(lenA);
    M=NTT::p2[ni];
    B=new ll[1];
    B[0]=NTT::quickmi(A[0],NTT::P-2,NTT::P);
    for(i=0;NTT::p2[i]<=M;i++){
        B1=nttcalc(A,B,i);
        delete []B;
        B=B1;
        for(j=0;j<NTT::p2[i];j++){
            printf("%lld ",B[j]);
        }printf("\n");
    }
    return B;
}

ll A[MAX];
inline void read(ll &x){
    ll f=1;//�������
    x=0;//���㣨�����Ǳ��bug���п��ܴ�����ʱxû�й��㣩
    char s=getchar();//�����һ���ַ�
    while(s<'0'||s>'9'){
        if(s=='-')//����ֱ�Ӱ�f=-1���п�������Ĳ���'-'�����������߰���Ķ���
            f=-1;
        s=getchar();//������
    }
    while(s>='0'&&s<='9'){
        x=x*10+s-'0';
        s=getchar();
    }
    x*=f;//�ı�����
}
inline void print(ll x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)//ֻҪx����2λ�������ͼ����ֽ�
        print(x/10);//����ݹ����ջ����x��ÿһλ�ǵ������ģ����ڵݹ飬��Ҳʵ�ڽ��Ͳ��������λȥ��������ǵĵݹ���Ͱɣ�
    putchar(x%10+'0');//�����Ҫ��int�ͱ�Ϊchar�ͣ���'0'���ɣ�
}
int main(int argc,char *argv[]){
    //freopen("���ݶ���ʽ����//in1.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("���ݶ���ʽ����//out1.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    ll i,j,k,T,n,ni;
    read(n);
    for(i=0;i<n;i++){
        read(A[i]);
    }
    ll *B=getInv(A,n);

    print(B[0]);

    for(i=1;i<n;i++){
        putchar(' ');
        print(B[i]);
    }
return 0;
}
/*
5
1 6 3 4 9
7
21 2 423235 212441277 12 21 777
*/
