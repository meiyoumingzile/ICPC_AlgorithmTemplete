#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<map>
#include<bitset>
using namespace std;
//std::ios::sync_with_stdio(false);
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LL long long
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;

ll exgcd(ll a,ll b,ll &x,ll &y){  //��һ��д�����������Լ��
    if(!b){
        x=1;y=0;return a;
    }
    int e=exgcd(b,a%b,x,y);
    int kkz=x;x=y;y=kkz-a/b*y;
    return e;
}

int main(int argc,char *argv[]){//��������ó������ҵ�һ��д��
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//OJ���еĵط����ܼ���仰
    ll i,j,k,a,b,c,ans,n2,x,y,g,dm;
    while(scanf("%lld%lld%lld%lld",&a,&b,&c,&k),a|b|c|k){//������|������ж�0
        n2=(ll)1<<k;
        if(a==b){
            ans=0;
        }else{
            x=0;y=0;
            g=exgcd(n2,c,x,y);
            if((b-a)%g!=0){
                printf("FOREVER\n",ans);
                continue;
            }
            dm=n2/g;
            /*����
            ����,y����չŷ�����ax+by=gcd;��һ���⣬��ôy*(b-a)/g��Ӧ����ax+by=c������̵Ľ�
            b/g���Ե���x�Ľ����a/g���Ե���y���
            ������n2*x+c*y=b-a;
            �������У�y����Ҫ�ģ���Ŀ�е�dm=n2/gcd(a,b),���Ե��������
            ������Ҫ�Һ�0������������ģ�����%dmһ�£����0���ҵģ�
            +dm����Ϊ����Ǹ��ľͼӵ���һ������
            ��ԭ����������ʱ����ֶ��ˣ���Ҫ��%dmһ��
            ����һ����ôд���ܺõİѺܶ�����ϲ�������b-a���ڻ���С��0
            */
            ans=((y*(b-a)/g%dm)+dm)%dm;
        }
        printf("%lld\n",ans);
    }
return 0;
}
