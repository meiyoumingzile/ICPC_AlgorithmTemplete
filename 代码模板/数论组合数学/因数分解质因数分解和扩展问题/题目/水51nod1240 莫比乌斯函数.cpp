#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;

int p[MAX];
bool vis[MAX];
int pcnt;
void getPrime(){
    pcnt=0;
    memset(vis,0,sizeof(vis));
    int i,j,k;
    for(i=2;i<MAX;i++){
        if(vis[i]==0){
            p[pcnt++]=i;
        }
        for(j=0;i*p[j]<MAX;j++){
            vis[i*p[j]]=1;
            if(i%p[j]==0){
                break;
            }
        }
    }

}
int getmiu(int n){
    int i,j,cnt=0;
    for(i=0;i<pcnt&&n>1;i++){
        for(j=0;n%p[i]==0;j++,n/=p[i]);
        if(j>0){
            cnt++;
            if(j>1){
                return 0;
            }
        }
    }
    if(n>1)
        cnt++;
    return cnt%2?-1:1;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    getPrime();
    int n;
    cin>>n;
    printf("%d\n",getmiu(n));
return 0;
}

