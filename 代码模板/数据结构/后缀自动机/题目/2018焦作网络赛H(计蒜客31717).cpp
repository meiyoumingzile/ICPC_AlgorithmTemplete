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

const int CHARCNT=26;
inline int toInt(const char &a){
    return a-'A';
}
struct SAM{
    int root,last,size;
    int p[MAX*2],nodelen[MAX*2],son[MAX*2][CHARCNT],eplen[MAX*2],du[MAX*2];
    //eplen[i]�Ǳ��Ϊi�Ľڵ�endpos����Ԫ�ظ���,du��ֻ��pָ���ÿ���������
    SAM(){}
    void clear(){//��ʼ��
        root=last=0;//���ڵ�����0
        memset(son[0],-1,sizeof(son[0]));
        memset(du,0,sizeof(du));
        p[0]=-1;
        nodelen[0]=0;
        size=1;
    }
    int addNode(int len,bool isMain){//���ձ��˳����ӽڵ�
        int sz=size++;
        memset(son[sz],-1,sizeof(son[sz]));
        nodelen[sz]=len;
        eplen[sz]=isMain;
        return sz;
    }
    int push(const char &a){
        int f=toInt(a),now,node,q,nq;
        node=addNode(nodelen[last]+1,1);
        for(now=last;now!=-1&&son[now][f]==-1;now=p[now]){
            son[now][f]=node;
        }
        if(now!=-1){
            q=son[now][f];
            if(nodelen[now]+1==nodelen[q]){
                p[node]=q;
                du[q]++;
            }else{
                nq=addNode(nodelen[now]+1,0);
                memcpy(son[nq], son[q], sizeof son[q]);
                p[nq]=p[q];
                p[q]=p[node]=nq;
                du[nq]+=2;
                while(now!=-1&&son[now][f]==q){
                    son[now][f]= nq;
                    now=p[now];
                }
            }
        }else{
             p[node]=root;
             du[root]++;
        }
        last=node;
        return nodelen[node]- nodelen[p[node]];
    }
    int getStrCnt(int x){
        return nodelen[x]- nodelen[p[x]];
    }
    void getEplen(){//��׺�Զ���������������eplen
        rg int i,now;
        stack<int>st;
        for(i=1;i<size;i++){
            if(du[i]==0)
                st.push(i);
        }
        while(!st.empty()){
            now=st.top();
            st.pop();
            eplen[p[now]]+=eplen[now];
            if(--du[p[now]]==0){
                st.push(p[now]);
            }
        }
    }
};

SAM sam;
char str[MAX];
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	rg int i,n,l,r,len;
	ll cnt;
	while(~scanf("%s",str)){
        scanf("%d%d",&l,&r);
        sam.clear();
        len=strlen(str);
        for(i=0;i<len;i++){
            sam.push(str[i]);
        }
        sam.getEplen();
        cnt=0;
        for(i=1;i<sam.size;i++){
            if(sam.eplen[i]>=l&&sam.eplen[i]<=r){
                cnt+=sam.getStrCnt(i);
            }
        }
        printf("%lld\n",cnt);
	}
return 0;
}
/*
AAA 2 3
ABAB 2 2
*/
