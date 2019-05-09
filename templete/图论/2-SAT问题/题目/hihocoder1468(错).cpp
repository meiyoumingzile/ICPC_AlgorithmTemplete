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
const int MAX=20010;
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
    Edge edge[40010];
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
};
Graphic g[2];
int inverse(int x){
    x--;
    return 1+(x^1);
}
int n,m;
int kind[MAX],qkind[MAX];
int q[2][MAX],qlen[2];
void push(cint id,int a){
    q[id][qlen[id]++]=a;
    qkind[a]=id+1;
}
bool getConnected(){
    rg int i,j,len,ii;
    memset(kind,0,sizeof kind);//kind��ʾ��û�б�ѡȡ,0��ʾû��ѡȡ
    memset(qkind,0,sizeof qkind);//qkind��ʾ�����ĸ����У�0��ʾ�ĸ����ж�����
    auto findNodes=[](cint i){
        qlen[0]=qlen[1]=0;
        int ii=inverse(i),j,k,h;
        push(0,i);
        push(1,ii);
        for(k=0;k<qlen[0];k++){//��������0
            //if(!is(inverse(q[0][k])))
             //   return 0;
            for(j=g[0].head[q[0][k]];j!=-1;j=g[0].edge[j].k){
                cint e=g[0].edge[j].e;
                int ee=inverse(e);
             //   if(!is(ee))
               //     return 0;
                if(qkind[e]==2||kind[e]==2){
                    return 0;
                }else if(qkind[e]==0&&kind[e]==0){
                    push(0,e);
                }
                if(qkind[ee]==1||kind[ee]==1){
                    return 0;
                }else if(qkind[ee]==0&&kind[ee]==0){
                    push(1,ee);
                }
            }
        }

        while(qlen[0])
            kind[q[0][--qlen[0]]]=1;
        while(qlen[1])
            kind[q[1][--qlen[1]]]=2;
        return 1;
    };
    for(i=1;i<=g[0].V;i+=2){
        if(kind[i]==0){
            if(!findNodes(i)){
                if(!findNodes(i))
                    return 0;
            }
        }
    }
    return 1;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,t,T,u,v;
    while(~scanf("%d%d",&n,&m)){
        g[0].clear();
        g[1].clear();
        g[0].V=g[1].V=n*2;
        for(i=0;i<m;i++){
            scanf("%d%d",&u,&v);//��u��v�г�ͻ,inverse(x)��ʾx�෴�ĵ㣬1��2�෴,3��4�෴,5��6�෴....
            g[0].push(u,inverse(v),1);
            g[0].push(v,inverse(u),1);

            g[1].push(inverse(v),u,1);
            g[1].push(inverse(u),v,1);
        }
        if(getConnected()){
            for(i=1;i<=g[1].V;i++){
                if(kind[i]==1)
                    printf("%d\n",i);
            }
        }else{
            printf("NIE\n");
        }
	}
return 0;
}
/*
3 4
6 1
2 4
1 3
5 4
*/
