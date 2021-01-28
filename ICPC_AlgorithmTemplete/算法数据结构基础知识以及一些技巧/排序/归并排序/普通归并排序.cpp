#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=100010;
const int mod=1e9+7;
int A[MAX],t[MAX];
void mergeSort(int *as, int left, int right){//[b,e]之间,t是临时数组
    if(left==right)
        return;
    int mid=(left+right)/2;
    mergeSort(as,left,mid);
    mergeSort(as,mid+1,right);
    int i=left,j=mid+1,k=left;
    while(i<=mid&&j<=right)
        t[k++]=as[i]<as[j]?as[i++]:as[j++];
    while(i<=mid)
        t[k++]=as[i++];
    while(j<=right)
        t[k++]=as[j++];
    for(i=left;i<=right;i++)
        as[i]=t[i];
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
    mergeSort(A,0,N-1);
    for(i=0;i<N;i++){
        printf("%d ",A[i]);
    }
return 0;
}
/*
5
4 2 4 5 1
*/
