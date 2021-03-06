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
const int MAX=1000010;
const int mod=1e9+7;
inline void scan(int &x){
    rg char c;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}
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
        rg int now=sz,next;
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
        rg int now,next,r=heap[1];
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
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,t,T,n;
	//printf("~~%d\n",que.sz);
	scanf("%d",&T);
	while(T--){
        scanf("%d",&k);
        if(k==1){
            scanf("%d",&n);
            que.push(n);
        }else if(k==2){
            printf("%d\n",que.heap[1]);
        }else if(k==3){
            que.pop();
        }
        //printf("~~%d\n",que.sz);
	}
return 0;
}

