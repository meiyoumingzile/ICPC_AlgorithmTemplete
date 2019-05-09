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
const int mod=142857;

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
        clear();
    }
    void push(const int &b,const int &e,const int &val){
        int t=head[b];
        head[b]=size;
        edge[size++]=Edge(e,val,t);
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
Graphic g;

int du[MAX],vir[MAX];//���������
ll Kahn(Graphic &g){//����ͼ���ڻ�����0
    rg int i,j,k,now;
    ll sum=0;
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
        for(i=g.head[now];i!=-1;i=g.edge[i].k){

            vir[g.edge[i].e]+=vir[now];
            vir[g.edge[i].e]%=mod;
            if((--du[g.edge[i].e])==0){
                st.push(g.edge[i].e);
            }
        }
    }
    for(i=1;i<=g.V;i++){
        sum=(sum+vir[i])%mod;
    }
    return sum;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	rg int i,j,k,t,T,n,u,v,val;
    g.clear();
    scanf("%d%d%d",&g.V,&g.E,&k);
    memset(vir,0,sizeof(vir));
    for(i=0;i<k;i++){
        scanf("%d",&u);
        vir[u]++;
    }
    for(i=0;i<g.E;i++){
        scanf("%d%d",&u,&v);
        g.push(u,v,0);
    }
    printf("%lld\n",Kahn(g));
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
