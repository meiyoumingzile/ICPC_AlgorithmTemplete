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
const int MAX=10010;
const int mod=1e9+7;
/*
����һ��n����m��������ͼ��ÿ������һ��Ȩֵ����һ��·����ʹ·�������ĵ�Ȩֵ֮�������ֻ��Ҫ������Ȩֵ�͡�
�����ξ���һ���߻���һ���㣬���ǣ��ظ������ĵ㣬Ȩֵֻ����һ�Ρ�
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
struct Graphic{
    int V,E,S,T,size;
    int head[MAX];
    Edge edge[100010];
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
Graphic g,g1;

bool vis[MAX],inSt[MAX];//����ǲ��Ǳ��ҹ���,inSt�Ƿ���ջ����
int dfn[MAX],low[MAX];//dfn�������˳���ţ�low������ӽڵ�����С��
stack<int>st;
int kind[MAX],kval[MAX],dval[MAX];//ĳ���������ĸ���ͨ����
int newCnt=0;
void tarjan(int now,int &len){//�ݹ���룬dot������[1,V]��ʼ�����ԣ���Ҫע����ܲ��ᱻ���ߵ���len�������
    int i,j,k,next;
    st.push(now);
    dfn[now]=low[now]=len++;
    inSt[now]=1;
    vis[now]=1;
    for(i=g.head[now];i!=-1;i=g.edge[i].k){
        next=g.edge[i].e;
        if(dfn[next]==0&&vis[next]==0){//��dfn����dfs��vis�����ж���û�߹�
            tarjan(next,len);
              //�ݹ�ĸ���low,����low�Ķ��壬���ĸ��ڵ�now,Ӧ���Ƕ��ӵ�����С�ģ�ÿ��dfs��������¸��ڵ�now
            low[now]=min(low[now],low[next]);
        }else if(inSt[next]==1){
            low[now]=min(low[now],low[next]);
        }else{//�ų���inSt[next]==0&&vis[next]==1���Ǿ�ʲô������
        }
    }
    if(dfn[now]==low[now]){//û���¹�low,˵����ǿ��ͨ�������������Ϊ��ʼ.��Щ��������ջ���ģ���ô��ջ����Ԫ��ֱ��������ǰ��now
        newCnt++;
        do{
            k=st.top();
            st.pop();
            inSt[k]=0;//�������³ɲ���ջ�
            kind[k]=newCnt;
            kval[newCnt]+=dval[k];
        }while(k!=now);
    }
}

int n,m;
void getConnected(){
    int i,j,len;
    //memset(vis,0,sizeof(vis));
   // memset(dfn,0,sizeof(dfn));
    newCnt=0;
    for(i=1;i<=g.V;i++){
        if(vis[i]==0){
            len=1;
            tarjan(i,len);
        }
    }
    g1.V=newCnt;
    for(i=1;i<=g.V;i++){//���������������ڲ�ͬ��ͨ�����ͼӱߣ���Ȼ��ô����Ȼ���ر�
        for(j=g.head[i];j!=-1;j=g.edge[j].k){
            cint e=g.edge[j].e;
            if(kind[i]!=kind[e]){
                g1.push(kind[i],kind[e],1);
            }
        }
    }
}
int rem[MAX];
int dfs(cint now){
    if(rem[now]!=0){
        return rem[now];
    }
    rg int i,j,k,maxVal=0;
    for(i=g1.head[now];i!=-1;i=g1.edge[i].k){
        cint e=g1.edge[i].e;
        maxVal=max(maxVal,dfs(e));
    }
    rem[now]=max(rem[now],maxVal+kval[now]);
    return rem[now];
}
int main(int argc,char *argv[]){
	int i,u,v,a,b,maxVal;
	scanf("%d%d",&n,&m);
	g.clear();
	g1.clear();
    g.V=n;
    for(i=1;i<=n;i++){
        scanf("%d",&dval[i]);
    }
    for(i=0;i<m;i++){
        scanf("%d%d",&u,&v);
        g.push(u,v,1);
    }
    getConnected();
    maxVal=-1;
    for(i=1;i<=g1.V;i++){
        dfs(i);
        maxVal=max(maxVal,rem[i]);
    }
    printf("%d\n",maxVal);
return 0;
}
