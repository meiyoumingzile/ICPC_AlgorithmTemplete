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
const int MAX=210;
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
    Edge edge[2010];
    Graphic(){}
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
};
Graphic g;

bool vis[MAX];//����ǲ��Ǳ��ҹ���
int dfn[MAX],low[MAX];//dfn�������˳���ţ�low������ӽڵ�����С��
stack<int>st;
bool inSt[MAX];//�Ƿ���ջ����
int kind[MAX];//ĳ���������ĸ���ͨ����
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
        do{
            k=st.top();
            st.pop();
            inSt[k]=0;//�������³ɲ���ջ�
            kind[k]=newCnt;
        }while(k!=now);
        newCnt++;
    }
}

int n,m;
string getConnected(){
    rg int i,len;
    memset(vis,0,sizeof(vis));
    memset(dfn,0,sizeof(dfn));
    newCnt=0;
    for(i=1;i<=g.V;i++){
        if(vis[i]==0){
            len=1;
            tarjan(i,len);
        }
    }
    for(i=1;i<=n;i++){
        if(kind[i]==kind[n+i]){
            return "BAD";
        }
    }
    return "GOOD";
}
int toID(char a,cint id){
    return id+(a=='h'?0:n);
}
int inverse(cint id){//�Ե�ȡ��
    return id+(id<=n?n:-n);
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,t,T,u,v;
	char s1[10],s2[10];
	cin>>T;
	while(T--){
        g.clear();
        scanf("%d%d",&n,&m);
        g.V=n*2;
        for(i=0;i<m;i++){
            scanf("%s %s",s1,s2);
            u=atoi(s1+1);
            v=atoi(s2+1);
            u=toID(s1[0],u);
            v=toID(s2[0],v);
            g.push(u,inverse(v),1);
            g.push(v,inverse(u),1);
        }
        printf("%s\n",getConnected().c_str());
	}
return 0;
}

