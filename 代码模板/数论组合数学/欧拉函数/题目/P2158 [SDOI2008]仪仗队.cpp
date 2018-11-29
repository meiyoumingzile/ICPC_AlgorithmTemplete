#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ll __int64
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;

struct getEuler{//快一点的o(n)方法，可以顺便素筛
    bool *flag;///标记数组
    int *phi;///欧拉函数值，i的欧拉函数值=phi[i]
    int *p;///素因子的值
    int cnt;
    void getPhi(int MAX){
        cnt = 0;
        flag=new bool[MAX];
        phi=new int[MAX];
        p=new int[MAX];
        memset(flag, true, sizeof(bool)*MAX);

        phi[1] = 1;
        for(int i=2; i<MAX; i++){
            if(flag[i]){
                p[cnt++] = i;
                phi[i] = i-1;///素数的欧拉函数值是素数 - 1
            }
            for(int j=0; j<cnt; j++){
                if(i*p[j] > MAX)
                    break;
                flag[i*p[j]] = false;///素数的倍数，所以i*p[j]不是素数
                if(i%p[j] == 0){///性质：i mod p == 0, 那么 phi(i * p) == p * phi(i)
                    phi[i*p[j]] = p[j] * phi[i];
                    break;
                }else{
                    phi[i*p[j]] = (p[j]-1) * phi[i];///i mod p != 0, 那么 phi(i * p) == phi(i) * (p-1)
                }
            }
        }
    }
};

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int n,i,j,ans;
    getEuler eu;

    while(~scanf("%d",&n)){
        eu.getPhi(n+1);
        for(i=1,ans=0;i<n;i++){
            ans+=eu.phi[i];
        }
        printf("%d\n",ans*2+1);
    }
return 0;
}
