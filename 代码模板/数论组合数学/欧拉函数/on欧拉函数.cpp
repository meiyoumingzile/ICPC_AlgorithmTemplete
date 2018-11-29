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
#include<set>
#include<windows.h>
using namespace std;
//std::ios::sync_with_stdio(false);
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LL long long
#define ll long long
#define ll __int64
#define lld I64d
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;

//�õ�һ����ŷ������
ll getEu(ll N){//���ݹ�ʽ
    ll i,j,n=N,ans=N,m=1;
    for(i=2;n!=1;i++){
        if(n%i==0){
            while(n%i==0)
                n/=i;
            ans/=i;
            m*=i-1;
        }
    }
    if(ans==N){
        return N-1;
    }
    return ans*m;
}


struct getEuler{//��һ���o(n)����������˳����ɸ��ŷ��ɸ��
    bool *flag;///�������
    int *phi;///ŷ������ֵ��
    int *prime;///����
    int cnt;
    void getPhi(int MAX){
        cnt = 0;
        int i,j;
        flag=new bool[MAX];
        phi=new int[MAX];
        prime=new int[MAX];
        memset(flag,1,sizeof(bool)*MAX);//1����������
        memset(phi,-1,sizeof(int)*MAX);//1����������
        phi[1] = 1;
        for(i=2;i<MAX;i++){
            if(flag[i]){
                prime[cnt++]=i;
                phi[i]=i-1;//������ŷ�������Ǳ���-1
            }
            for(j=0;j<cnt&&i*prime[j]<=MAX;j++){//����֮ǰ�õ���ÿ������
                flag[i*prime[j]]= false;///�����ı���������i*p[j]��������
                if(i%prime[j]==0){///����imodp==0, phi(i * p) == p * phi(i)
                    phi[i*prime[j]] =prime[j]*phi[i];
                    break;//��breakΪ�˼��٣������������Ѿ������һ�������ں���������4*2���겻�ù�4*3=12,12��������6ȥ����
                }else{//������ܳ�����
                    phi[i*prime[j]]=(prime[j]-1)*phi[i];///i mod p != 0, ��ô phi(i * p) == phi(i) * (p-1)
                }
            }
            /*for(j=2;j<40;j++){
                printf("%d:%d ",j,phi[j]);
            }
            system("pause");*/
        }
    }
};
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//OJ���еĵط����ܼ���仰
    ll n;
    getEuler e;
    e.getPhi(MAX);
    printf("%d\n",e.cnt);

    while(~scanf("%lld",&n)){
        printf("%d %lld\n",e.phi[n],getEu(n));
    }
return 0;
}
