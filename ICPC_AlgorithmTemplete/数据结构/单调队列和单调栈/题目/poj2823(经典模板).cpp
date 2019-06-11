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
inline int pushASC(deque<v2>& que,cint a,cint i,cint m){//����
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
inline int pushDESC(deque<v2>& que,cint a,cint i,cint m){//����
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
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
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

