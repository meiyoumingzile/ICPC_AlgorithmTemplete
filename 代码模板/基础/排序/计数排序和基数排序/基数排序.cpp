#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define cint const int &
const int INF=2147483647;////2139062143
const int MAX=100010;
int A[MAX];
queue<int>li[10];
ll p10[10];
void radixSort(int *A,int n){//非负数
    int i,j,k;
    p10[0]=1;
    for(i=1;i<10;i++)
        p10[i]=p10[i-1]*10;
    for(k=0;k<10;k++){
        for(i=0;i<n;i++){
            li[A[i]/p10[k]%10].push(A[i]);
        }
        for(i=j=0;i<10;i++){
            while(!li[i].empty()){
                A[j++]=li[i].front();
                li[i].pop();
            }
        }
    }
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,t,T,n,m;
	scanf("%d",&n);
	for(i=0;i<n;i++){
        scanf("%d",&A[i]);
	}
	radixSort(A,n);
	for(i=0;i<n;i++){
        printf("%d ",A[i]);
	}
return 0;
}
/*
5
42121 22 42 54 1213
*/
