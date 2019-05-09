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
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k;
    int pcnt=getPrimes(MAX);
    for(i=100;i<pcnt;i++){
        for(j=0;j<23;j++){
            if((prime[i]-1)%p2[j]!=0){
                break;
            }
        }
        if(j>20){
            printf("质数P:%d: 2整数次方%d\n",prime[i],p2[j-1]);
        }
    }
return 0;
}
