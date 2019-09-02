#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define cint const int &
const int INF=2147483647;////2139062143
const int MAX=100010;
int A[MAX],ind[MAX];
void cntSort(int *A,int n){//A数组元素都是非负数，且小于MAX
    memset(ind,0,sizeof(ind));
    int i,j;
    for(i=0;i<n;i++){
        ind[A[i]]++;
    }
    for(i=j=0;i<MAX;i++){
        while(ind[i]--){
            A[j++]=i;
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
	cntSort(A,n);
	for(i=0;i<n;i++){
        printf("%d ",A[i]);
	}
return 0;
}
/*
5
4 2 4 5 1
*/
