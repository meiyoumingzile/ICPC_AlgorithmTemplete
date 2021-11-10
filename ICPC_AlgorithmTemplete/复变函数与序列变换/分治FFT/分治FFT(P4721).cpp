#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2 = 500000004;
const int INF = 2147483647;////2139062143
const int MAX = 1000010;
const int mod = 998244353;

namespace ntt{//ntt׼���϶࣬�������ƻ���������������ռ䣬�Ժ�����������鷳
    int P=998244353;
    ll powg[MAX];
    int p2[30]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216};
    int grn[30]={1,998244352,911660635,372528824,929031873,452798380,922799308,781712469,476477967,166035806,258648936,584193783,63912897,350007156,666702199,968855178,629671588,24514907,996173970,363395222,565042129,733596141};
    int grninv[30]={1,998244352,86583718,509520358,337190230,87557064,609441965,135236158,304459705,685443576,381598368,335559352,129292727,358024708,814576206,708402881,283043518,3707709,121392023,704923114,950391366,428961804};
    ll quickmi(ll a,ll b,ll P){
        ll ans=1;
        for(a%=P;b;b>>=1,a=a*a%P)
            if(b&1)
                ans=ans*a%P;
        return ans;
    }
    ll changeN(ll N){//��N���2�������η���������������,����p2������±�
        ll i;
        for(i=0;p2[i]<N;i++);
        return i;
    }
    void ntt_init(int p,int up=30){//��ʼ��ntt�Ĳ�������
        P=P;
        p2[0]=grn[0]=grninv[0]=1;
        for(int i=0;i<up;i++){
            p2[i]=p2[i-1]*2;
        }

    }
    void ntt(ll *F,int ni,int fp){//��ԭ������任
        int i,j,m,k,bit,N=p2[ni],n=N>>1;
        ll d,inv,G;
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

    ll *cloneArr(ll *x,int l,int r,int N){//����һ�ݸ����汾���飬����ΪN
        ll *xx = new ll[N];
        for(int i=l;i<r;i++){//x����ֱ�Ӹ���һ�ݸ����汾
			xx[i-l] = x[i];
		}
		for(int i=r-l;i<N;i++){
			xx[i] = 0;
		}
		return xx;
	}
	void divConvolution(ll *x, ll *y, int l, int r) {//����ξ����������ntt����֪x���飬��y������[l,r)
	    //printf("%d %d\n",l,r);
		if(r-l<=1)//����಻���κ���
			return;
		int mid =(l + r)/2;
		divConvolution(x, y, l, mid);//������
		int i, ni = changeN(r-l);
		int N = p2[ni];
		ll *xx =cloneArr(x,1,r-l,N);//x����ֱ�Ӹ���һ�ݸ����汾
		ll *yy =cloneArr(y,l,mid,N);//y���鸴��ǰ�벿��

		ntt(xx,ni,1);
		ntt(yy,ni,1);
		for (i = 0; i<N; i++) {
			yy[i] =  yy[i]*xx[i]%mod;
		}
		ntt(yy, ni, -1);
		for (i = mid; i<r; i++) {
			y[i] = (y[i]+yy[i-l-1])%mod;
		}
		delete xx;
		delete yy;
        divConvolution(x, y, mid, r);//�ݹ��ұ�
	}
};

ll g[MAX],f[MAX];
int main(int argc, char *argv[]) {
	int i, j, k, t, T, n, m;
    cin>>n;
    for(i=1;i<n;i++){
        scanf("%lld",&g[i]);
    }
    f[0]=1;
    ntt::divConvolution(g,f,0,n);
    for(i=0;i<n;i++){
        printf("%lld ",f[i]);
    }
	return 0;
}
/*
4
3 1 2
*/
