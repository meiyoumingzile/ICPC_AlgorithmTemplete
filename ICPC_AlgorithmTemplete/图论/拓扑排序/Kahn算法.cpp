#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
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
    void push(const int &b,const int &e,const int &val){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t);
    }
	void clear(){
        size=0;
        memset(head,-1,sizeof(head));
    }
};
Graphic g;

int du[MAX];//���������
bool Kahn(Graphic &g){//����ͼ���ڻ�����0
    rg int i,j,k,now;
    memset(du,0,sizeof(du));
    stack<int>st;
    for(i=1;i<=g.V;i++){
        for(j=g.head[i];j!=-1;j=g.edge[j].k){
            du[g.edge[j].e]++;
        }
    }
    for(i=1;i<=g.V;i++){
        if(du[i]==0)
            st.push(i);
    }
    while(!st.empty()){
        now=st.top();
        st.pop();
        printf("%d ",now);
        for(i=g.head[now];i!=-1;i=g.edge[i].k){
            if((--du[g.edge[i].e])==0){
                st.push(g.edge[i].e);
            }
        }
    }
    for(i=1;i<=g.V;i++){//����ǲ����޻�ͼ
        if(du[i]>0){
            return 0;
        }
    }
    return 1;
}

int main(int argc,char *argv[]){
	int i,u,v,val;
	/*
	����һ��ͼ������������޻�ͼ��������򣬷������ͼ���л�
	*/
	while(~scanf("%d%d",&g.V,&g.E)){
        g.clear();
        for(i=0;i<g.E;i++){
            scanf("%d%d",&u,&v);
            g.push(u,v,val);
        }
        if(Kahn(g)){
        }else{
            printf("����ͼ���ڻ�\n");
        }
	}
return 0;
}
/*
6 8
1 2
1 3
1 4
3 2
3 5
4 5
6 4
6 5

6 9
1 2
1 3
1 4
3 2
3 5
4 5
6 4
6 5
5 6
*/
