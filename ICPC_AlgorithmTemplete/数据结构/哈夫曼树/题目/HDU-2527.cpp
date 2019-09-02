#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;

struct Heap{
    int heap[MAX];
    int sz;//sz代表数组长度，sz-1是堆中元素个数
    Heap(){
        clear();
    }
    void clear(){
        sz=1;
    }
    void push(int x){
        int now=sz,next;
        heap[sz++]=x;
        while(now>1){
            next=now>>1;
            if(heap[now]>=heap[next])//比较函数,小顶堆
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
            if(next<sz&&heap[next+1]<heap[next])//比较函数,小顶堆
                next++;
            if(heap[now]<=heap[next])//比较函数,小顶堆
                return r;
            swap(heap[now],heap[next]);
            now=next;
        }
        return r;
    }
    int top(){
        return heap[1];
    }
    int size(){
        return sz-1;
    }
    bool empty(){
        return sz<=1;
    }
};
Heap que;
char str[MAX];
int ind[30];
int toint(char a){
    return a-'a';
}
int main(int argc,char *argv[]){
	int i,j,k,t,T,n,m,len,a,b,lastind,sum;
	cin>>T;
    while(T--){
        scanf("%d%s",&m,str);
        len=strlen(str);
        que.clear();
        memset(ind,0,sizeof(ind));
        sum=n=0;
        for(i=0;i<len;i++){
            ind[toint(str[i])]++;
        }
        for(i=0;i<30;i++){
            if(ind[i])
                que.push(ind[i]);
            n+=ind[i];
        }
        sum=n;
        if(que.size()==1){//特判
            sum=que.top();
        }else{
            while(que.size()>1){
                a=que.top();
                que.pop();
                b=que.top();
                que.pop();
                que.push(a+b);
                sum+=a+b;
            }
            sum-=n;
        }
        printf("%s\n",sum<=m?"yes":"no");
    }
return 0;
}

