#include<bits/stdc++.h>
#define LL long long
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;


ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}

ll exgcd(ll a,ll b,ll &x,ll &y){  //��һ��д�����������Լ��
    if(!b){
        x=1;y=0;return a;
    }
    int e=exgcd(b,a%b,x,y);
    int kkz=x;x=y;y=kkz-a/b*y;
    return e;
}


int main(int argc,char *argv[]){
    //freopen("debug\\in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("debug\\out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//OJ���еĵط����ܼ���仰
    ll i,j,t,a,b,c,p,g,x,y;

    while(1){
        scanf("%lld%lld",&a,&p);//��a��p����Ԫ��������Ԫ����������a��p���ʣ�������ax-py=1�޽���ԪҲ�Ͳ�����
        g=exgcd(a,p,x,y);
        if(1%g!=0){//1%gcd(a,p)��=0�޽⣬������չŷ����ýⲻ�����̵ķ���
            printf("�޽⣡��\n");
        }else{
            printf("%lld\n",x);
        }
    }
return 0;
}
