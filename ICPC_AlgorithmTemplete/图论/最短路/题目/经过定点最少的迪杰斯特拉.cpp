#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int INF=2147483647;
const int MAXDOT=10010;
const int mod=1e9+7;

struct Edge{//��ʾ�ߣ���������ߴӡ�b����e;w��Ȩֵ
    int b,e,val;
    void sett(int b,int e,int val){
        this->b=b;
        this->e=e;
        this->val=val;
    }
};
struct number{
    int i,dis;
    bool operator < (const number &a) const {
        return dis>a.dis;//��Сֵ����
    }
    void sett(int i,int dis){
        this->i=i;
        this->dis=dis;
    }
};
vector<Edge>adList[MAXDOT];//�ڽӱ�adList[i][j]��ʾ���ΪI�ĵ㵽�����Ե���ĵ�j���ߵ���Ϣ��j��0��ʼ
int dist[MAXDOT];//��ʾ��㵽���Ϊi�ĵ�����·����ʼֵ��INF��
priority_queue<number>que;
//bool vis[MAXDOT];//��ʾ��û��������У�//0��ʾ��û��ӹ�
int last[MAXDOT];//��ʾ��ǰ�����·���µ���һ�������ĸ�������������·��
int pathcnt[MAXDOT];//��ʾ��ǰ�����·���µ�·�������Ķ�����
int N,M,S,E;//N�ǵ������M�Ǳ߸�����B������ţ�E���յ�ı��

void Dijkstra(int start,int N){//���ƹ���,���㷨����޸����ߵ�ͼ
    int i,j,k;
    number now,next;
    now.sett(start,0);//���ڳ�ʼֵ
    for(i=1;i<=N;i++)
        dist[i]=INF;
    dist[start]=0;
    pathcnt[start]=1;
    que.push(now);
    while(!que.empty()){
        now=que.top();
        que.pop();
        for(i=0;i<adList[now.i].size();i++){//��ʾ������ǰ���ܵ�������е�
            next.i=adList[now.i][i].e;
            next.dis=now.dis+adList[now.i][i].val;
            if(dist[next.i]>next.dis || dist[next.i]==next.dis&&pathcnt[next.i]>pathcnt[now.i]+1){//��һ�������ֵ������õ���ֵ�Ÿ���
                dist[next.i]=next.dis;
                que.push(next);
                last[next.i]=now.i;
                pathcnt[next.i]=pathcnt[now.i]+1;
            }
        }
    }
}

int main(int argc,char *argv[]){
    int i,j,k;
    Edge w;
    cin>>N>>M>>S>>E;
    for(i=0;i<M;i++){
        scanf("%d%d%d",&w.b,&w.e,&w.val);
        adList[w.b].push_back(w);
    }
    Dijkstra(S,N);
    for(i=1;i<=N;i++){
        printf("%d%c",dist[i],i==N?'\n':' ');
    }
    for(i=E;i!=0;i=last[i]){
        printf("%d ",i);
    }
return 0;
}
/*
4 5 1 4
1 2 1
1 3 3
1 4 10
2 3 2
3 4 7

*/
