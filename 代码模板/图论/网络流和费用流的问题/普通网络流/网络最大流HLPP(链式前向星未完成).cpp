#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=10010;
const int mod=1e9+7;
/*
�����3376Ϊ��������������ʽǰ����ʵ��
*/
struct Edge{
    int e,val,k;
    Edge(){}
    Edge(int e,int val,int k){
        this->e=e;
        this->val=val;
        this->k=k;
    }
};
struct Graphic{//��ʽǰ����ʵ��
    int V,E,S,T;//��������������յ�
    int size=0;
    int head[MAX];
    Edge edge[250010];
    Graphic(){
        memset(head,-1,sizeof(head));
    }
    void push(int b,int e,int val){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t);
    }
};
Graphic g;
Edge p[MAX];//����·����p[i]�����ϸ��ڵ�
int layer[MAX];
int gap[MAX];
void HLPP_bfs(Graphic &g){//��������ֲ㣬
    register int i,minVal=INF;
    queue<int>que;
    int now=g.T,next;
    memset(layer,-1,sizeof(layer));
    memset(gap,0,sizeof(gap));
    layer[g.T]=0;
    que.push(now);
    gap[0]++;
    while(!que.empty()){
        now=que.front();
        que.pop();
        for(i=g.head[now];i!=-1;i=g.edge[i].k){
            int &e=g.edge[i].e;
            if(layer[e]==-1&&g.edge[i].val==0){
                next=e;
                layer[e]=layer[now]+1;
                gap[layer[e]]++;
                que.push(next);
            }
        }
    }
}
ll HLPP(){//dfsѰ��·����load�������·����load[i].b����㣬e�������������ڽӱ��б�š�
    register int i,j,k,u,v,now,next,minVal;
    ll sumVal=0;
    HLPP_bfs(g);
    now=g.S;
    p[g.S].e=g.S;
    while(layer[g.S]<g.V){//ĳ������������µĴ��ڵ����ܵ�����˵��һ�������˶ϲ㣬�˳�ѭ��
        for(i=g.head[now];i!=-1;i=g.edge[i].k){//����������û�п����ߵ�
            next=g.edge[i].e;
            if(g.edge[i].val>0&&layer[now]==layer[next]+1){
                break;
            }
        }
        if(i!=-1){
            p[next].e=now;
            p[next].val=i;
            now=next;
            if(now==g.T){
                for(v=g.T,minVal=INF;v!=g.S;v=u){
                    u=p[v].e;
                    minVal=min(minVal,g.edge[p[v].val].val);
                }
                sumVal+=minVal;
                for(v=g.T;v!=g.S;v=u){
                    u=p[v].e;
                    k=p[v].val;
                    g.edge[k].val-=minVal;
                    g.edge[k^1].val+=minVal;
                }
                now=g.S;
            }
        }else{
            minVal=g.V-1;
            for(i=g.head[now];i!=-1;i=g.edge[i].k){//Ѱ��һ����С�ı�
                next=g.edge[i].e;
                if(g.edge[i].val>0&&layer[next]<minVal)
                    minVal=layer[next];
            }
            if(--gap[layer[now]]==0)//�Ҳ����ɸı�Ļ��߳��ֶϲ�
                break;
            layer[now]=minVal+1;
            gap[layer[now]]++;
            now=p[now].e;//�˳�һ��
        }
    }
    return sumVal;//�����ҵ��Ŀ��еķ���Ȩֵ�ܺͣ�û����Ȼ����0
}
void print(Graphic &g){
    for(int i=1;i<=g.V;i++){
        for(int j=g.head[i];j!=-1;j=g.edge[j].k){
            if(g.edge[j].val>0){
                printf("(%d %d %d)",i,g.edge[j].e,g.edge[j].val);
            }
            //printf("(%d %d %d) ",i,g.edge[j].e,g.edge[j].val);
        }printf("\n");
    }
}

int main(int argc,char *argv[]){
    //freopen("testdata.in","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("myout.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,b,e,val;
    scanf("%d%d%d%d",&g.V,&g.E,&g.S,&g.T);
    for(i=0;i<g.E;i++){
        scanf("%d%d%d",&b,&e,&val);
        g.push(b,e,val);
        g.push(e,b,0);
    }
    printf("%lld\n",HLPP());
return 0;
}

