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
    Node *son=NULL,*sibling=NULL;//�������ֵ�
    Node(int val){
        this->val=val;
        du=0;
    }
    void addChild(Node *node){
        if(son){//�ж���
            Node *now=son;
            while(now->sibling){
                now=now->sibling;
            }
            now->sibling=node;
        }else{
           son=node;
        }
        du++;
    }
};
struct Mheap{//����Ѳ���һ���ѣ���һȺ�ѣ���ʼ��n����ɢ�Ľڵ㣬���Ǹ�������һ����
    const int NO=-INF;//�����Ѿ���ɾ���ĵ��val
    Node *root[100];//����Ϊi�����ĸ�
    int topRootID,up;
    void init(int n){
        up=n;
        for(int i=0;i<100;i++){
            root[i]=NULL;
        }
        topRootID=-1;
    }
    Node* __merge(Node *x,Node *y){//�ϲ��Ը�x�͸�y���ڽڵ�Ķ�,Ҫ�������ͬ,���ظ�
        if(x->du!=y->du){
            return NULL;
        }else if(x->val<y->val){
            x->addChild(y);
            return x;
        }else{
            y->addChild(x);
            return y;
        }
    }
    void addNode(Node *x){//����ڵ�
        Node *now=x;
        while(root[now->du]){
            int du=now->du;
            now=__merge(now,root[now->du]);
            root[du]=NULL;
        }
        root[now->du]=now;
       // printf("%d-%d",topRootID,now->du);
        if(topRootID<0||root[topRootID]==NULL||root[topRootID]->val > root[now->du]->val){
            topRootID=now->du;
        }
    }

    void push(int val){
        addNode(new Node(val));
    }
    int top(){
        if(topRootID<0){
            return INF;
        }
        return root[topRootID]->val;
    }
    int pop(){//����ڵ�x�������ĸ�,����ɾ����˭�Ǹ�
        if(topRootID<0){
            return INF;
        }
        Node *x=root[topRootID];
        root[topRootID]=NULL;
        int minVal=INF;
        for(int i=0;i<up;i++){//ѡ����С�ĸ�
            if(root[i]&&minVal>root[i]->val){
                topRootID=i;
                minVal=root[i]->val;
            }
        }
        if(minVal==INF){//��Ϊ��
            topRootID=-1;
        }
        if(x->son){
            Node *next;
            for(Node *now=x->son;now;now=next){
                next=now->sibling;
                now->sibling=NULL;
                addNode(now);
            }
        }
        int val=x->val;
        delete x;
        return val;
    }
    void merge(Mheap &other){//����һ������Ѻϲ����Լ�
        if(other.topRootID<0){
            return;
        }
        Node *next;
        for(int i=0;i<other.up;i++){
            if(other.root[i]){
                addNode(other.root[i]);
            }
        }
    }
};
Mheap que;

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
