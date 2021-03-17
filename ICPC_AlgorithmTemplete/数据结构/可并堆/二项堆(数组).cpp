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

struct Node{
    int val,du;
    int son,sibling;//�������ֵ�
    Node(int val){
        this->val=val;
        du=0;
        son=sibling=0;
    }
};
struct Mheap{//����Ѳ���һ���ѣ���һȺ�ѣ���ʼ��n����ɢ�Ľڵ㣬���Ǹ�������һ����
    const int NO=-INF;//�����Ѿ���ɾ���ĵ��val
    int root[100];//����Ϊi�����ĸ�
    Node tree[MAX];
    int topRootID,up,tlen;
    void init(int n){
        up=n;
        memset(root,-1,sizeof root);
        topRootID=-1;
        tlen=1;
    }
    void addChild(int x,int y){//��y����x�Ķ���
        if(tree[x].son){//�ж���
            int now=tree[x].son;
            while(tree[now].sibling){
                now=tree[now].sibling;
            }
            tree[now].sibling=y;
        }else{
           tree[x].son=y;
        }
        tree[x].du++;
    }
    int __merge(int x,int y){//�ϲ��Ը�x�͸�y���ڽڵ�Ķ�,Ҫ�������ͬ,���ظ�
        if(tree[x].du!=tree[y].du){
            return -1;
        }else if(tree[x].val<tree[y].val){
            addChild(x,y);
            return x;
        }else{
            addChild(y,x);
            return y;
        }
    }
    void addNode(int x){//����ڵ�
        int now=x;
        while(root[tree[now].du]){
            int du=tree[now].du;
            now=__merge(now,root[tree[now].du]);
            root[du]=-1;
        }
        int du=tree[now].du;
        root[du]=now;
        if(topRootID<0||root[topRootID]<0||tree[root[topRootID]].val > tree[root[du]].val){
            topRootID=du;
        }
    }

    void push(int val){
        addNode(tlen++);
    }
    int top(){
        if(topRootID<0){
            return INF;
        }
        return tree[root[topRootID]].val;
    }
    int pop(){//����ڵ�x�������ĸ�,����ɾ����˭�Ǹ�
        if(topRootID<0){
            return INF;
        }
        int x=root[topRootID];
        root[topRootID]=0;
        int minVal=INF;
        for(int i=0;i<up;i++){//ѡ����С�ĸ�
            int ri=root[i];
            if(ri&&minVal>tree[ri].val){
                topRootID=i;
                minVal=tree[ri].val;
            }
        }
        if(minVal==INF){//��Ϊ��
            topRootID=-1;
        }
        if(tree[x].son){
            int next;
            for(int now=tree[x].son;now;now=next){
                next=tree[now].sibling;
                tree[now].sibling=0;
                addNode(now);
            }
        }
        return tree[x].val;
    }

};
Mheap que();

int main(int argc,char *argv[]){
	int i,k,n,m,val,x,y;
	scanf("%d",&m);
	que.init(64);
	for(i=0;i<m;i++){
        scanf("%d",&k);
        if(k==1){
            scanf("%d",&val);//����
            que.push(val);
        }else if(k==2){
            printf("%d\n",que.top());
        }else if(k==3){
            que.pop();
        }
        //printf("::%d %d\n",que.top(),que.topRootID);
	}
return 0;
}
/*


*/
