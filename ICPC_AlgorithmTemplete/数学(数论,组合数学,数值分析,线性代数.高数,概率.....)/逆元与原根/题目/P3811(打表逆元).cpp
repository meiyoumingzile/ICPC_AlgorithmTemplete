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
const int MAX=3000010;
const int mod=1e9+7;
inline void scan(int &x){
    rg char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}

ll INV[MAX];
void getInv(ll MAX,ll p){//�����ܶ����Ԫ,p������
    INV[1] = 1;
    for (int i=2;i<MAX;i++) {
        INV[i]=(ll)(p-p/i)*INV[p%i]%p;
    }
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,t,T,n,p;
	scanf("%d%d",&n,&p);
	getInv(n+1,p);
    for(i=1;i<=n;i++){
        printf("%lld\n",INV[i]);
    }
return 0;
}

