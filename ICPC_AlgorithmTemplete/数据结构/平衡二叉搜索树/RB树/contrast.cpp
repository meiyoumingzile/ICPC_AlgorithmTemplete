#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;
int A[MAX];
int main(int argc,char *argv[]){
    char s1[100]="in3.out";
    char s2[100]="myout.out";
    freopen(s1,"r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("in1.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i,j,k,id,T,t;
    i=0;
    while(~scanf("%d",&A[i++]));
    freopen(s2,"r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    T=i;
    for(i=0;i<T;i++){
        scanf("%d",&k);
        if(k!=A[i]){
            printf("i=%d, %s:%d %s:%d\n",i,s1,A[i],s2,k);
            break;
        }
    }
return 0;
}
