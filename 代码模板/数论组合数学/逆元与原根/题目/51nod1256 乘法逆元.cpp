#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;

void exgcd(ll a,ll b,ll &d,ll &x,ll &y){//����Ԫ
    if(!b){
        d=a;//���ݷ���ax-py=1���˴�aӦ�õ���1����˵��û����Ԫ
        x=1;
        y=0;
    }else{
        exgcd(b,a%b,d,y,x);
        y-=x*(a/b);
    }
}
ll getinv(ll  a,ll p){//������Ԫ,��չŷ����÷�,p���κ��������淽��û������
    ll  d,x,y;
    exgcd(a, p, d, x, y);
    return d==1?(x+p)%p:-1;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    ll n,m,ans;
    scanf("%lld%lld",&n,&m);
    ans=getinv(n,m);
    printf("%lld\n",ans);
return 0;
}

