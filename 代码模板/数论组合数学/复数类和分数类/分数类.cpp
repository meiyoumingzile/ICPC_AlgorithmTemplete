#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;

ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}
struct Fra{
    ll a,b,g;//b�Ƿ�ĸ��a�Ƿ���

    void sett(ll a,ll b){
        this->a=a;
        this->b=b;
        getg();
    }
    double toDouble(){
        return a/(double)b;
    }
    void getg(){
        g=gcd(a,b);
    }
    void red(){//Լ��,��Ҫ�ȼ���gcd
        a/=g;
        b/=g;
        g=1;
    }
    Fra static toFra(int n){
        Fra f;
        f.sett(n,1);
        return f;
    }
    int compare(Fra &t){
        if(t.g>1)
            t.red();
        if(g>1)
            red();
        if(t.b==b){
            if(t.a==a)
                return 0;
            return a>t.a?1:-1;
        }else{
            ll gt=gcd(b,t.b);
            return a/gt*t.b>t.a/gt*b?1:-1;
        }
    }
    int compare(int t){
        Fra f=toFra(t);
        return compare(f);
    }
};

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i,j,n,k,a,b;
    printf("%.10lf %.10lf",9997/10000.0,9998/10000.0);
    Fra fa,fb;
    fa.sett(4,6);
    while(~scanf("%lld%lld",&fb.a,&fb.b)){
        fb.getg();
        printf("%d\n",fa.compare(fb));
    }

return 0;
}
