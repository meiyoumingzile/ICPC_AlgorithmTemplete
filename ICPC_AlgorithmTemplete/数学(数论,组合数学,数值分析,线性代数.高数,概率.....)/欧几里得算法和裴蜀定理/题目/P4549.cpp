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

ll gcd(ll a,ll b){//��ͨ�����Լ��
    return b?gcd(b,a%b):a;
}
ll A[100];
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,t,T,n;
	ll ans;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%lld",&A[i]);
    }
    ans=abs(A[0]);
    if(n>1){
        for(i=1;i<n;i++){
            ans=gcd(ans,abs(A[i]));
        }
    }
    printf("%lld\n",ans);
return 0;
}

