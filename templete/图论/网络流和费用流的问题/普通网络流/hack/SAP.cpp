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
const int MAX=10010;
const int mod=1e9+7;
/*
�����3376Ϊ��������������ʽǰ����ʵ��
*/
struct Edge{
    int e,val,k;
    Edge(){}
    Edge(const int &e,const int &val,const int &k){
        this->e=e;
        this->val=val;
        this->k=k;
    }
};
struct Graphic{//��ʽǰ����ʵ��
    int V,E,S,T;//��������������յ�
    int size;
    int head[MAX];
    Edge edge[250010];
    Graphic(){}
    void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
    void push(const int &b,const int &e,const int &val){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t);
    }
    void fpush(const int &b,const int &e,const int &val){
        push(b,e,val);
        push(e,b,0);
    }
};
Graphic g;
Edge p[MAX];//����·����p[i]�����ϸ��ڵ�
int layer[MAX],gap[MAX],cur[MAX];//cur�ǵ�ǰ���Ż�
void SAP_bfs(Graphic &g){//��������ֲ㣬
    queue<int>que;
    int now=g.T;
    memset(layer,-1,sizeof(layer));
    memset(gap,0,sizeof(gap));
    layer[g.T]=0;
    que.push(now);
    gap[0]++;
    while(!que.empty()){
        now=que.front();
        que.pop();
        for(int i=g.head[now];i!=-1;i=g.edge[i].k){
            int e=g.edge[i].e;
            if(layer[e]==-1&&g.edge[i].val==0){
                layer[e]=layer[now]+1;
                gap[layer[e]]++;
                que.push(e);
            }
        }
    }
}

ll SAP(){//dfsѰ��·����load�������·����load[i].b����㣬e�������������ڽӱ��б�š�
    int i,j,k,u,v,now,next,minVal;
    ll sumVal=0;
    SAP_bfs(g);
    for(i=1;i<=g.V;i++)
        cur[i]=g.head[i];//��ǰ����d[i] = d[j] + 1�ıߵ�Ϊ��һ����
    now=g.S;
    p[g.S].e=g.S;
    while(layer[g.S]<g.V){//ĳ������������µĴ��ڵ����ܵ�����˵��һ�������˶ϲ㣬�˳�ѭ��
        for(i=cur[now];i!=-1;i=g.edge[i].k){//����������û�п����ߵ�
            next=g.edge[i].e;
            if(g.edge[i].val>0&&layer[now]==layer[next]+1){
                break;
            }
        }
        if(i!=-1){//�ҵ�һ�������ߵ�·
            p[next].e=now;
            p[next].k=i;
            now=next;
            if(now==g.T){
                for(v=g.T,minVal=INF;v!=g.S;v=u){
                    u=p[v].e;
                    minVal=min(minVal,g.edge[p[v].k].val);
                }
                sumVal+=minVal;
                for(v=g.T;v!=g.S;v=u){
                    /*
                    printf("%d ",v);//�˴��õ�·��
                    */
                    u=p[v].e;
                    k=p[v].k;
                    g.edge[k].val-=minVal;
                    g.edge[k^1].val+=minVal;
                }//printf("%d\n",v);//�˴��õ�·��
                now=g.S;

            }
        }else{
            minVal=g.V;
            cur[now]=g.head[now];
            for(i=g.head[now];i!=-1;i=g.edge[i].k){//Ѱ��һ����С�ı�
                next=g.edge[i].e;
                if(g.edge[i].val>0&&layer[next]<minVal&&layer[next]!=-1)
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
char c;
void scan(int &x){
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}
int main(int argc,char *argv[]){
    //freopen("hack1.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("wa.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,b,e,val;
	while(~scanf("%d%d%d%d",&g.V,&g.E,&g.S,&g.T)){
	    g.clear();
        for(i=0;i<g.E;i++){
            scan(b);scan(e);scan(val);
            g.push(b,e,val);
            g.push(e,b,0);
        }
        printf("%lld\n",SAP());
	}
return 0;
}

