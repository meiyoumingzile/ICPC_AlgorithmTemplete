#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
#define cdou const double &
#define cv2 const v2 &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;

int A[MAX],B[MAX],ind[MAX],tail[MAX];
int bin_up(int *d,int ex,int left,int right){//从小到大的数组,找一个小于ex的最后一个数
    if(left==right-1){
        if(d[left]<=ex){//不减子序列
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
int getLCS(int n){
    int i,ind,maxLen=1;
    tail[1]=B[0];//tail从1开始
    for(i=1;i<n;i++){
        ind=bin_up(tail,B[i],1,maxLen+1);
        tail[ind+1]=B[i];
        if(ind==maxLen){
            maxLen++;
        }
    }
    return maxLen;
}
int main(int argc,char *argv[]){
	int i,n;
	scanf("%d",&n);
	for(i=0;i<n;i++){
        scanf("%d",&A[i]);
        ind[A[i]]=i;
	}
	for(i=0;i<n;i++){
        scanf("%d",&B[i]);
        B[i]=ind[B[i]];//用索引替换
	}
    printf("%d\n",getLCS(n));
return 0;
}

