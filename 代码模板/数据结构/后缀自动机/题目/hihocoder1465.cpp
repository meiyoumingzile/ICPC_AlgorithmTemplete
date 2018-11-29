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
const int MAX=1000010;
const int mod=1e9+7;

int U[MAX],L[MAX];
map<int,bool>vis;
const int CHARCNT=26;
inline int toInt(const char &a){
    return a-'a';
}
struct SAM{
    int root,last,size;
    int p[MAX*2],nodelen[MAX*2],son[MAX*2][CHARCNT],eplen[MAX*2],du[MAX*2];
    //eplen[i]�Ǳ��Ϊi�Ľڵ�endpos����Ԫ�ظ���,du��ֻ��pָ���ÿ���������
    SAM(){
       clear();
    }
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
int getLCS(char *s2){//������������Ӵ�
    int i,j,n,len2,now,f,maxLen=0,cnt=0;
    len2=strlen(s2);
    for(i=0;i<len2-1;i++)
        s2[i+len2]=s2[i];
    n=len2;
    len2=len2*2-1;
    vis.clear();
    U[0]=L[0]=0;//���[1,len2],0������ַ���
    now=0;//��ʼ����sam.root
    for(i=1;i<=len2;i++){
        f=toInt(s2[i-1]);
        if(sam.son[now][f]!=-1){//˵������һ���ַ����ţ�������Ȼ����һ����һ
            L[i]=L[i-1]+1;
            U[i]=now=sam.son[now][f];
        }else{//��������p������
            while(now!=-1&&sam.son[now][f]==-1)
                now=sam.p[now];
            if(now!=-1){//==-1˵��û����s[i]��β�Ĺ����ַ�
                L[i]=sam.nodelen[now]+1;
                U[i]=now=sam.son[now][f];
            }else{
                now=U[i]=L[i]=0;
            }
        }
        if(L[i]>=n){
            for(;sam.nodelen[sam.p[now]]>=n;now=sam.p[now]);
            L[i]=sam.nodelen[now];
            U[i]=now;
            if(!vis[U[i]]){
                vis[U[i]]=1;
                cnt+=sam.eplen[U[i]];
            }
        }
    }
    return cnt;
}
char str1[MAX],str2[MAX*2];
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	rg int i,n,len,q;
	scanf("%s",str1);
	len=strlen(str1);
    for(i=0;i<len;i++)
        sam.push(str1[i]);
    sam.getEplen();
	scanf("%d",&q);
	while(q--){
        scanf("%s",str2);
        printf("%d\n",getLCS(str2));
	}
return 0;
}
/*
sdssdsdaasdsadsaddawdadsads
sadsssasdsssssssssssssssssssssssssssssssss
*/
