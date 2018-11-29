#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<map>
#include<set>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
const int inv2=500000004;
const int INF=2139062143;////2139062143
const int MAX=2010;
const int mod=1e9+7;

struct Edge{
    int e,val,k;
    Edge(){}
    Edge(const int &e,const int &val,const int &k){
        this->e=e;
        this->val=val;
        this->k=k;
    }
};
struct Graphic{
    int V,E,S,T,size=0;
    int head[MAX];
    Edge edge[MAX*5];
    Graphic(){
    }
    void push(const int &b,const int &e,const int &val){
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
    void pushMin(const int &b,const int &e,const int &val){//�����������ڸ��³���С�������޸��������
        rg int i;
        for(i=head[b];i!=-1&&edge[i].e!=e;i=edge[i].k);
        if(i==-1){
            push(b,e,val);
        }else{
            edge[i].val=min(edge[i].val,val);
        }
    }
};
Graphic g;

int dist[MAX];//ά�������������ڶ�̬�滮��dp���飻�����������ʵ��ȡ���ڵ��������ͬ,�±����㣬һ���1��ʼ
int updateTimes[MAX];

bool SPFA(int start,Graphic &g){//start������ţ�V�ǵ����
    rg int i,j,now;
    queue<int>que;
    dist[start]=0;
    que.push(start);
    while(!que.empty()){
        now=que.front();
        que.pop();
        for(i=g.head[now];i!=-1;i=g.edge[i].k){
            cint endDot=g.edge[i].e;
            if(dist[now]+g.edge[i].val<dist[endDot]){
                dist[endDot]=dist[now]+g.edge[i].val;
                que.push(endDot);
                if(++updateTimes[endDot]>=g.V){
                    return 0;
                }
            }
        }
    }
    return 1;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	rg int i,j,k,t,T,n,w,u,v,val,mindis,s=1;
	scanf("%d",&T);
    while(T--){
        scanf("%d%d",&g.V,&g.E);
        g.clear();
        for(i=0;i<g.E;i++){
            scanf("%d%d%d",&u,&v,&val);
            if(val<0){
                g.pushMin(u,v,val);
            }else{
                g.pushMin(u,v,val);
                g.pushMin(v,u,val);
            }
        }
        memset(updateTimes,0,sizeof(updateTimes));
        memset(dist,127,sizeof(dist));
        for(i=1;i<=g.V;i++){
            if(updateTimes[i]==0){
                if(SPFA(i,g)==0){
                    break;
                }
            }
        }
        if(i==g.V+1){
            printf("N0\n");
        }else{
            printf("YE5\n");
        }
    }
return 0;
}

