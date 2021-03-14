#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=5002;
const int mod=1e9+7;
struct Edge{
    int e,k;
    double val;
    Edge(){}
    Edge(const int &e,const double &val,const int &k){
        this->e=e;
        this->val=val;
        this->k=k;
    }
    bool operator < (const Edge &a) const {
        return val>a.val;//��Сֵ����
    }
};
struct Graphic{
    int V,E,S,T,size=0;
    int head[MAX];
    Edge edge[MAX*40];
    void push(const int &b,const int &e,const double &val){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t);
    }
	void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
	void println(){
        int i,j,next;
        for(i=1;i<=V;i++){
            printf("%d:::",i);
            for(j=head[i];j!=-1;j=edge[j].k){
                printf("%d ",edge[j].e);
            }printf("\n");
        }
    }
};

double dist[MAX];//��ʾ��㵽���Ϊi�ĵ�����·����ʼֵ��INF��
priority_queue<Edge>que;//e����㣬val�������·
int preNode[MAX];//��ʾ��ǰ�����·���µ���һ�������ĸ�������������·��
void Dijkstra(const Graphic &g,int start){
    //���ƹ���,���㷨����޸����ߵ�ͼ
    int i,j,k;
    Edge now,next;
    for(i=0;i<=g.V;i++){
        dist[i]=2147483647.0;
    }
    now.e=start;//���ڳ�ʼֵ
    now.val=0;
    dist[start]=0;
    que.push(now);
    while(!que.empty()){
        now=que.top();
        que.pop();
        if(now.val!=dist[now.e])//���Ż�����ʡ��
            continue;
        for(i=g.head[now.e];i!=-1;i=g.edge[i].k){//��ʾ������ǰ���ܵ�������е�
            next.e=g.edge[i].e;
            next.val=now.val+g.edge[i].val;
            if(dist[next.e]>next.val&&now.e!=next.e){//��һ�������ֵ������õ���ֵ�Ÿ���
                dist[next.e]=next.val;
                preNode[next.e]=now.e;
                que.push(next);
            }
        }
    }
}




struct Node{
    int val,dis,son[2],p;
    int com(const Node &b){
        if(val==b.val)
            return 0;
        return val>b.val?1:-1;
    }
};
struct  Persistent_Mheap{
   /* const int NO=-INF;//�����Ѿ���ɾ���ĵ��val
    Node node[MAX];
    void init(){
        memset(node,0,sizeof(node));
    }
    int __merge(int x,int y){//�ϲ��Ը�x�͸�y���ڽڵ�Ķ�
        if(x==0||y==0)//��һ���ǿվͲ��ܺϲ���,���ز��ǿյ�
            return x?x:y;
        if(node[x].com(node[y])==1||(node[x].com(node[y])==0&&x>y))
            swap(x,y);
        int &xl=node[x].son[0];
        int &xr=node[x].son[1];
        xr=__merge(xr,y);
        node[xr].p=x;//�ҵĸ�����x
        if(node[xl].dis<node[xr].dis)
            swap(xl,xr);
        node[x].dis=node[xr].dis+1;
        return x;
    }
    int merge(int x,int y){//�ϲ���x���ڵ����y���ڵ����ڵĶѣ�x��y���[1,n],f���ظ��ڵ��ţ��ϲ����ɹ�����0
        if(node[x].val!=NO&&node[y].val!=NO&&x!=y){
            x=getRoot(x);
            y=getRoot(y);
            return __merge(x,y);
        }
        return 0;
    }
    int getRoot(int x){//�ҵ������x�ĵ�ģ����ڵ�
        while(node[x].p)
            x=node[x].p;
        return x;
    }
    int pop(int x){//����ڵ�x�������ĸ�,����ɾ����˭�Ǹ�
        x=getRoot(x);
        node[x].val=NO;//��ʾ����㲻����
        int &xl=node[x].son[0];
        int &xr=node[x].son[1];
        node[xl].p=node[xr].p=0;
        return merge(xl,xr);
    }*/
};
Persistent_Mheap mhead;
Graphic g,ig;

int main(int argc,char *argv[]){
	int i,j,k,u,v,ans;
    double val,sumVal;
	g.clear();
	ig.clear();
	//que.clear();
    scanf("%d%d%lf",&g.V,&g.E,&sumVal);
    ig.E=g.E;
    ig.V=g.V;
    for(i=0;i<g.E;i++){
        scanf("%d%d%lf",&u,&v,&val);
        g.push(u,v,val);
        ig.push(v,u,val);

    }
    Dijkstra(ig,ig.V);//���յ��ҷ������·
    ig.println();
    for(i=1;i<=g.V;i++){
        printf("%d ",preNode[i]);
    }
   // printf("%d\n",ans);
return 0;
}
