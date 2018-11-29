#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=100010;
const int mod=1e9+7;
int A[MAX];

void mysort(int *as, int left, int right){//[b,e]之间
    int i=left,j=right;
    int m=as[(j+i)/2];
    while(i<=j){
        while(as[i]<m)
            i++;
        while(as[j]>m)
            j--;
        if(i<=j){
            swap(as[i],as[j]);
            i++;j--;
        }
    }
    if(i<right)
        mysort(as,i,right);
    if(left<j)
        mysort(as,left,j);
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int N,i,j;
    scanf("%d",&N);
    for(i=0;i<N;i++){
        scanf("%d",&A[i]);
    }
    mysort(A,0,N-1);
    printf("%d",A[0]);
    for(i=1;i<N;i++){
        printf(" %d",A[i]);
    }
return 0;
}
