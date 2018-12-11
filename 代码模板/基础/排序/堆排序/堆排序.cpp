#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define cint const int &
const int INF=2147483647;////2139062143
const int MAX=100010;
int A[MAX];
struct Heap{
    int heap[MAX];
    int sz;//sz代表数组长度，sz-1是堆中元素个数
    Heap(){
        clear();
    }
    void clear(){
        sz=1;
    }
    void push(cint x){
        int now=sz,next;
        heap[sz++]=x;
        while(now>1){
            next=now>>1;
            if(heap[now]>=heap[next])//比较函数
                return;
            swap(heap[now],heap[next]);
            now=next;
        }
    }
    int pop(){//弹出元素，如果没有返回INF
        if(sz==1)
            return INF;
        int now,next,r=heap[1];
        heap[1]=heap[--sz];//注意是sz--,而不是--sz
        now=1;
        while(now*2<=sz){
            next=now*2;
            if(next<sz&&heap[next+1]<heap[next])////比较函数
                next++;
            if(heap[now]<=heap[next])//比较函数
                return r;
            swap(heap[now],heap[next]);
            now=next;
        }
        return r;
    }
    int size(){
        return sz-1;
    }
    bool empty(){
        return sz<=1;
    }
};
Heap que;
void heapSort(int *A,int n){
    que.clear();
    int i,j;
    for(i=0;i<n;i++){
        que.push(A[i]);
    }
    for(i=0;i<n;i++){
        A[i]=que.pop();
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
	heapSort(A,n);
	for(i=0;i<n;i++){
        printf("%d ",A[i]);
	}
return 0;
}
/*
5
4 2 4 5 1
*/
