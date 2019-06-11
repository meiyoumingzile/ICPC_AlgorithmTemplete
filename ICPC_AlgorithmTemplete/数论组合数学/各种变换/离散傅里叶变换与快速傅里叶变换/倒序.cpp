#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=2000010;
const int mod=1e9+7;
int seq[MAX];
int p2[30];
void getSeq(int N){
    N--;
    int i,j,k,bit,n;
    for(bit=0,n=N;n;n/=2,bit++);
    p2[0]=1;
    for(i=1;i<bit;i++){
        p2[i]=p2[i-1]*2;
    }
    for(i=1;i<N;i++){
        for(j=k=0,n=i;n;n/=2,j++){
            if(n%2==1){
                k+=p2[bit-j-1];
            }
        }
        seq[i]=k;
    }
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,n;
    while(~scanf("%d",&n)){
        getSeq(n);
        for(i=0;i<n;i++){
           //printf("%d: %d\n",i,seq[i]);
        }
    }
return 0;
}
