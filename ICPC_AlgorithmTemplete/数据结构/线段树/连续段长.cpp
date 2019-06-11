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
const int MAX=50010;
const int mod=1e9+7;
struct Node{
    int r,l,x,y,len;
    int dis(){
        return r-l;
    }
    bool con(){//区间内部是否联通
        return x==dis();
    }
};
struct LineTree{//区间是左闭 左开[)
    Node tree[MAX*4];
    void buildTree(int now,int l,int r){//建树,lz==INF代表没有标记，lz是正代表右lz
        tree[now].l=l;
        tree[now].r=r;
        tree[now].len=tree[now].x=tree[now].y= tree[now].dis();
        if(r-l<=1){
            return;
        }
        int mid=(l+r)/2,next=now*2;
        buildTree(next,l,mid);
        buildTree(next+1,mid,r);
    }
    void mergeSon(cint now){
        Node &t=tree[now];
        cint next=now<<1;
        t.len=max(tree[next].len,tree[next+1].len);
        t.len=max(t.len,tree[next].y+tree[next+1].x);
        if(tree[next].con()){
            t.x=tree[next].dis()+tree[next+1].x;
        }else{
            t.x=tree[next].x;
        }
        if(tree[next+1].con()){
            t.y=tree[next+1].dis()+tree[next].y;
        }else{
            t.y=tree[next+1].y;
        }
    }
    void pop(int now,int l){
        Node &t=tree[now];
        cint mid=(t.r+t.l)>>1,next=now<<1;
        if(t.l==l&&t.r==l+1){
            tree[now].len=tree[now].x=tree[now].y=0;
        }else{
            if(mid<=l){
                pop(next+1,l);
            }else{
                pop(next,l);
            }
            mergeSon(now);
        }
    }
    void push(int now,int l){
        Node &t=tree[now];
        cint mid=(t.r+t.l)>>1,next=now<<1;
        if(t.l==l&&t.r==l+1){
            tree[now].len=tree[now].x=tree[now].y=1;
        }else{
            if(mid<=l){
                push(next+1,l);
            }else{
                push(next,l);
            }
            mergeSon(now);
        }
    }
    int search(int now,int l){
        Node &t=tree[now];
        cint mid=(t.r+t.l)>>1,next=now<<1;
        if(t.con()||t.r-t.l==1){//t.con()只对根节点有效
            return t.len;
        }else{
            if(l>=tree[next].r-tree[next].y&&l<tree[next+1].l+tree[next+1].x){
                return tree[next].y+tree[next+1].x;
            }else if(l<mid){
                return search(next,l);
            }else{
                return search(next+1,l);
            }
        }
    }
};
LineTree tr;
stack<int>st;
int main(int argc,char *argv[]){
	int i,j,k,t,T,n,m,x;
	char c;
	while(~scanf("%d%d",&n,&m)){
        tr.buildTree(1,0,n);
        for(i=0;i<m;i++){
            getchar();
            scanf("%c",&c);
            if(c=='D'){
                scanf("%d",&x);
                st.push(x);
                tr.pop(1,x-1);
            }else if(c=='Q'){
                scanf("%d",&x);
                printf("%d\n",tr.search(1,x-1));
            }else if(c=='R'){
                if(!st.empty()){
                    x=st.top();
                    st.pop();
                    tr.push(1,x-1);
                }
            }
        }
    }
return 0;
}

