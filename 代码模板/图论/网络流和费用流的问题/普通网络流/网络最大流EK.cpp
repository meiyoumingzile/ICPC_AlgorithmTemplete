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

struct Edge{
    int b,e,v;
    Edge(){}
    Edge(int b,int e,int v){
        this->b=b;
        this->e=e;
        this->v=v;
    }
};
void printG(){

}
int V,E,S,T;//��������������յ�
vector<Edge>adList[MAX];//�ڽӱ�
Edge p[MAX];//�����ҵ����ڵ㣬b����ǰ���ڵ㣬e�������ڽӱ��ţ�v����������Ȩֵ
int EKbfs(){//Edmonds-Karp�㷨
    int i,j,k,now,minv=INF,b,e;
    queue<int>que;
    memset(p,0,sizeof(p));
    p[S].b=-1;
    que.push(S);
    while(!que.empty()){
        now=que.front();
        que.pop();
        if(now==T){
            for(i=T;i!=S;i=p[i].b)
                minv=min(p[i].v,minv);
            for(i=T;i!=S;i=b){//���ӷ����
                b=p[i].b;
                e=p[i].e;
                adList[b][e].v-=minv;
                for(j=0;j<adList[i].size()&&adList[i][j].e!=b;j++);
                if(j==adList[i].size()){
                    Edge edge(i,b,minv);
                    adList[i].push_back(edge);
                }else{
                    adList[i][j].v+=minv;
                }
            }
            return minv;
        }
        for(i=0;i<adList[now].size();i++){
            k=adList[now][i].e;
            if(p[k].b==0&&adList[now][i].v>0){
                p[k].b=now;
                p[k].e=i;
                p[k].v=adList[now][i].v;
                que.push(k);
            }
        }
    }
    return -1;
}
int EdmondsKarp(){
    int sumVal,k;
    for(sumVal=0,k=0;k!=-1;k=EKbfs()){
        sumVal+=k;
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

    printf("%d",EdmondsKarp());
return 0;
}

