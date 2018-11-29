#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;
/*
�����3376Ϊ�������ݱȽ����⣬�������ݲ������໥����ıߣ��ڽӱ���Դ��淴��߱���Ż�����ʽǰ���ǿ�������������Ԫ�رߴ洢�෴�߷�ʽ�Ż���Ŀ��������o1ʱ���ҵ��෴�߶����ǵ���Ѱ�ҡ�
�����ǲ��������Ż��Ĵ���
*/
struct Edge{
    int b,e,v;
    Edge(){}
    Edge(int b,int e,int v){
        this->b=b;
        this->e=e;
        this->v=v;
    }
};
struct Dot{//bfs��
    int d,len;
    Dot(){}
    Dot(int d,int len){
        this->d=d;
        this->len=len;
    }
};
int V,E,S,T;//��������������յ�
vector<Edge>adList[MAX];//�ڽӱ�
Edge load[MAX];//����·����b������㣬e�������������ڽӱ��б��
int layer[MAX];
bool Dinic_bfs(){//�ֲ�,ֻ��Ҫ�ҵ�T�㼴��ֹͣ���Ҳ���T����false��D��Ϊ�˸��õĴ������������Ҫ���������У��Ҳ���T����false
    int i,minv=INF,b,e;
    queue<Dot>que;
    Dot now(S,0),next;
    memset(layer,-1,sizeof(layer));
    layer[S]=0;
    que.push(now);
    while(!que.empty()){
        now=que.front();
        que.pop();
        if(now.d==T)
            return 1;
        for(i=0;i<adList[now.d].size();i++){
            e=adList[now.d][i].e;
            if(layer[e]==-1&&adList[now.d][i].v>0){
                next.d=e;
                layer[e]=next.len=now.len+1;
                que.push(next);
            }
        }
    }
    return 0;
}
int Dinic_dfs(int now){//dfsѰ��·����load�������·����load[i].b����㣬e�������������ڽӱ��б�š�
    int i,j,k,e,pb,pe,val,minv,sumv=0;
    for(i=0;i<adList[now].size();i++){
        e=adList[now][i].e;
        val=adList[now][i].v;
        if(layer[e]==layer[now]+1){
            load[layer[now]]=Edge(now,i,val);
            if(e==T){//����¸������յ�
                for(j=0,minv=INF;j<=layer[now];j++){//����·��Ѱ����Сֵ
                     minv=min(minv,adList[load[j].b][load[j].e].v);
                }
                for(j=0;j<=layer[now];j++){//·���ϵ�ÿ��������
                    pb=load[j].b;
                    pe=adList[pb][load[j].e].e;
                    adList[pb][load[j].e].v-=minv;
                    for(k=0;k<adList[pe].size()&&adList[pe][k].e!=pb;k++);
                    if(k==adList[pe].size()){
                        Edge edge(pb,pe,minv);
                        adList[pe].push_back(edge);
                    }else{
                        adList[pe][k].v+=minv;
                    }
                }
                sumv+=minv;
            }else{
                sumv+=Dinic_dfs(e);
            }
        }
    }
    return sumv;//�����ҵ��Ŀ��еķ���Ȩֵ�ܺͣ�û����Ȼ����0
}
int Dinic(){
    int sumVal=0;
    while(Dinic_bfs()){//��ε���ֱ�����ֲܷ�
        sumVal+=Dinic_dfs(S);
    }
    return sumVal;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,b;
    scanf("%d%d%d%d",&V,&E,&S,&T);
    Edge edge;
    for(i=0;i<E;i++){
        scanf("%d%d%d",&edge.b,&edge.e,&edge.v);
        adList[edge.b].push_back(edge);
    }
    printf("%d\n",Dinic());
return 0;
}

