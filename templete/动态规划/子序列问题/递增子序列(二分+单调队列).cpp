#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=100010;
const int mod=1e9+7;
int tail2[MAX];//tail[i]表示长度为i的子序列最小末尾,递增子序列
int tail1[MAX];//tail[i]表示长度为i的子序列最大末尾,不增子序列
int A[MAX];
//给定序列，输出它的不增子序列长度，和递增子序列长度
int bin_down(int *d,int ex,int left,int right){//从大到小的数组,找一个大于等于ex的最后一个数
    if(left==right-1){
        if(d[left]>=ex){//注意=，是不增子序列
            return left;
        }else{
            return left-1;
        }
    }
    int mid=(left+right)/2;
    if(d[mid]>=ex){
        return bin_down(d,ex,mid,right);
    }else{
        return bin_down(d,ex,left,mid);
    }
}

int bin_up(int *d,int ex,int left,int right){//从小到大的数组,找一个小于ex的最后一个数
    if(left==right-1){
        if(d[left]<ex){//注意是严格递增的子序列
            return left;
        }else{
            return left-1;
        }
    }
    int mid=(left+right)/2;
    if(d[mid]>ex){
        return bin_up(d,ex,left,mid);
    }else{
        return bin_up(d,ex,mid,right);
    }
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int i=0,j,k,n,a,maxLen1=1,maxLen2=1,ind;
    while(~scanf("%d",&A[i++]));
    n=i-1;
    tail1[1]=tail2[1]=A[0];
    for(i=1;i<n;i++){
        ind=bin_down(tail1,A[i],1,maxLen1+1);
        tail1[ind+1]=A[i];
        if(ind==maxLen1){
            maxLen1++;
        }

        ind=bin_up(tail2,A[i],1,maxLen2+1);
        tail2[ind+1]=A[i];
        if(ind==maxLen2){
            maxLen2++;
        }
    }
    printf("%d\n%d\n",maxLen1,maxLen2);
return 0;
}
