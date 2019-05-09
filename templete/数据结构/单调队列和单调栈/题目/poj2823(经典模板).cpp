#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<deque>
//#include<windows.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;
struct v2{
    int x,y;
	v2(){}
	v2(const int &x,const int &y){
		sett(x,y);
	}
    void sett(const int &x,const int &y){
        this->x=x;
        this->y=y;
    }
};
/*template <class T>
struct deque{
    struct Node{
        T data;
        Node *next,*pre;
        Node(const T &data,Node *next=NULL,Node *pre=NULL){
            this->data=data;
            this->next=next;
            this->pre=pre;
            if(this->next){
                this->next->pre=this;
            }
            if(this->pre){
                this->pre->next=this;
            }
        }
    };
    Node *f,*b;
    deque(){
        f=b=NULL;
    }
    bool empty(){
        return f==NULL&&b==NULL;
    }
    T front(){
        return f->data;
    }
    T back(){
        return b->data;
    }
    void pop_front(){
        Node *t=f;
        f=f->next;
        if(f&&f->pre){
            f->pre=NULL;
        }else if(f==NULL){
            f=b=NULL;
        }
        delete t;
    }
    void pop_back(){
        Node *t=b;
        b=b->pre;
        if(b&&b->next){
            b->next=NULL;
        }else if(b==NULL){
            f=b=NULL;
        }
        delete t;
    }
    void push_front(const T &a){
        if(f){
            Node *t=f;
            f=new Node(a,t,NULL);
        }else{
            f=b=new Node(a);
        }
    }
    void push_back(const T &a){
        if(b){
            Node *t=b;
            b=new Node(a,NULL,t);
        }else{
            f=b=new Node(a);
        }
    }
    void clear(){
        f=b=NULL;
    }
    void println(){
        for(Node *i=f;i;i=i->next){
            printf("%d ",i->data.x);
        }printf("\n");
    }
};*/
int A[MAX];
v2 res[MAX];
deque<v2>que1;
deque<v2>que2;
inline int pushASC(deque<v2>& que,cint a,cint i,cint m){//升序，
    while(!que.empty()&&que.back().x>=a){
        que.pop_back();
    }
    que.push_back(v2(a,i));
    while(!que.empty()&&i-que.front().y>=m){
        que.pop_front();
    }
    //que.println();
    return que.front().x;
}
inline int pushDESC(deque<v2>& que,cint a,cint i,cint m){//升序，
    while(!que.empty()&&que.back().x<=a){
        que.pop_back();
    }
    que.push_back(v2(a,i));
    while(!que.empty()&&i-que.front().y>=m){
        que.pop_front();
    }
    return que.front().x;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	rg int i,j,k,t,T,n,m,a,b;
	while(~scanf("%d%d",&n,&m)){
        que1.clear();
        que2.clear();
        for(i=1;i<m;i++){
            scanf("%d",&A[i]);
            pushASC(que1,A[i],i,m);
            pushDESC(que2,A[i],i,m);
        }
        for(i=m;i<=n;i++){
            scanf("%d",&A[i]);
            a=pushASC(que1,A[i],i,m);
            b=pushDESC(que2,A[i],i,m);
            res[i].x=a;
            res[i].y=b;
        }
        for(i=m;i<=n;i++){
            printf("%d%c",res[i].x,i==n?'\n':' ');
        }
        for(i=m;i<=n;i++){
            printf("%d%c",res[i].y,i==n?'\n':' ');
        }
	}
return 0;
}

