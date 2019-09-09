#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100000010;
const int mod=1e9+7;
int p2[23]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304};
bool vis[MAX];
int prime[MAX];
int getPrimes(int n){
    memset(vis,1,sizeof(vis));
    int i,j,primeCount=0;
    vis[1]=0;
    for(i=2;i<n;i++){
        if(vis[i]){
            prime[primeCount++]=i;
        }
        for(j=0;i*prime[j]<n;j++){
            vis[i*prime[j]]=false;
            if(i%prime[j]==0){
                break;
            }
        }
    }
    return primeCount;
}


int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i,j,k;
    int pcnt=getPrimes(MAX);
    for(i=100;i<pcnt;i++){
        for(j=0;j<23;j++){
            if((prime[i]-1)%p2[j]!=0){
                break;
            }
        }
        if(j>20){
            printf("����P:%d: 2�����η�%d\n",prime[i],p2[j-1]);
        }
    }
return 0;
}
