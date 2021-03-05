#include<bits/stdc++.h>
#define LL long long
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;

struct v2{
    ll x,y;

    void sett(ll x,ll y){
        this->x=x;
        this->y=y;
    }
    bool operator == (const v2 &t){
         return (t.x==this->x&&t.y==this->y);
    }
};

ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}

struct ExGcd{
    v2 ans0;
    ll g;
    void init(ll a,ll b){
        this->g=gcd(a,b);
        this->ans0=ex_gcd(a,b);
    }
    v2 ex_gcd(ll a,ll b){//a,b��ͬʱΪ0����չŷ�����,a,bҪôͬ��Ҫôͬ������Ч��
        v2 ans;
        if(b==0){
            ans.sett(1,0);
        }else{
            v2 next=ex_gcd(b,a%b);
            ans.x=next.y;
            ans.y=next.x-(a/b)*next.y;
        }
        return ans;
    }

    //������չŷ������ҳ�1����������ҵ�������
    v2 getOther(ll a,ll b,ll t){//��ʾ���£�t����������
        v2 ans;

        ans.x=ans0.x+b/g*t;
        ans.y=ans0.y-a/g*t;

        return ans;
    }

    v2 getInEq(ll a,ll b,ll c,ll t){//t=0�õ����������� ax+by==c�ĵ�0����
        v2 ans;

        if(c%g!=0){
            ans.sett(INF,INF);
        }else{
            ans.x=c/g*ans0.x;
            ans.y=c/g*ans0.y;
            ans.x+=b/g*t;
            ans.y-=a/g*t;
        }
        return ans;
    }
};


int main(int argc,char *argv[]){
    //freopen("debug\\in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("debug\\out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//OJ���еĵط����ܼ���仰
    ll i,j,t,a,b,c,n2;
    ExGcd ex;
    while(1){
        scanf("%lld%lld%lld",&a,&b,&c);
        ex.init(a,b);
        v2 ans=ex.getInEq(a,b,c,0);
        printf("%lldx+%lldy==%lld\n",a,b,c);
        if(ans.x!=INF){
            printf("%lld %lld\n",ans.x,ans.y);
            printf("����һ��t\n");
            while(~scanf("%lld",&t)){
                v2 ans1=ex.getInEq(a,b,c,t);
                printf("��%lld����%lld %lld\n",t,ans1.x,ans1.y);
            }
        }else{
            printf("�޽�\n");
        }
    }
return 0;
}
