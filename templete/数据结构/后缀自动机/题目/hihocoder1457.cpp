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

const int CHARCNT=11;
inline int toInt(const char &a){
    return a-'0';
}
struct SAM{
    int root,last,size;
    int p[MAX*2],nodelen[MAX*2],son[MAX*2][CHARCNT],unsublen[2*MAX],sum[2*MAX],du[MAX*2];
    //unsublen[i]��ʾroot��i����':'��·���������������������sum[i]��i���ʾ�ַ������ļӺ�Ҳ�����������������du��ֻ��sonָ��Ĳ�����':'ָ���ÿ���������
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
        return sz;
    }
    int push(const char &a){
        rg int f=toInt(a),now,node,q,nq,i;
        node=addNode(nodelen[last]+1,1);
        for(now=last;now!=-1&&son[now][f]==-1;now=p[now]){
            if(f!=10)
                du[node]++;
            son[now][f]=node;
        }
        if(now!=-1){
            q=son[now][f];
            if(nodelen[now]+1==nodelen[q]){
                p[node]=q;
            }else{
                nq=addNode(nodelen[now]+1,0);
                for(i=0;i<CHARCNT-1;i++){
                    son[nq][i]=son[q][i];
                    if(son[q][i]!=-1)
                        du[son[q][i]]++;
                }
                p[nq]=p[q];
                p[q]=p[node]=nq;
                while(now!=-1&&son[now][f]==q){
                    son[now][f]= nq;
                    if(f!=10){
                        du[nq]++;
                        du[q]--;
                    }
                    now=p[now];
                }
            }
        }else{
             p[node]=root;
        }
        last=node;
        return nodelen[node]- nodelen[p[node]];
    }
    void getAdd(){//��׺�Զ��������������������ַ�����ͬ�Ӵ��Ӻ�
        rg int i,now;
        ll ans;
        memset(unsublen,0,sizeof unsublen);
        memset(sum,0,sizeof sum);
        unsublen[0]=1;
        stack<int>st;
        for(i=0;i<size;i++){
            if(du[i]==0)
                st.push(i);
        }
        while(!st.empty()){
            now=st.top();
            st.pop();
            for(i=0;i<10;i++){
                cint n=son[now][i];
                if(n!=-1){
                    unsublen[n]=(unsublen[n]+unsublen[now])%mod;
                    ans=(10ll*sum[now]%mod+(ll)i*unsublen[now]%mod)%mod;
                    sum[n]=(sum[n]+ans)%mod;
                    if(--du[n]==0){
                        st.push(n);
                    }
                }
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
	rg int i,n,len=0;
	scanf("%d",&n);
	while(n--){
        scanf("%s",str+len);
        len=strlen(str)+1;
        str[len-1]=':';
	}
	len--;
    for(i=0;i<len;i++){
        n=sam.push(str[i]);
    }
    sam.getAdd();
    ll ans=0;
    for(i=1;i<sam.size;i++){
        ans=(ans+sam.sum[i])%mod;
    }
    printf("%lld\n",ans);
return 0;
}
