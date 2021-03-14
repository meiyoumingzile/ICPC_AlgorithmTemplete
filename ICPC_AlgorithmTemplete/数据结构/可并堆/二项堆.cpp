#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
#define cdou const double &
#define cv2 const v2 &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;

struct Node{
    int val,dis,son[2],p;
    int com(const Node &b){
        if(val==b.val)
            return 0;
        return val>b.val?1:-1;
    }
};
struct Mheap{//����Ѳ���һ���ѣ���һȺ�ѣ���ʼ��n����ɢ�Ľڵ㣬���Ǹ�������һ����
    const int NO=-INF;//�����Ѿ���ɾ���ĵ��val
    Node node[MAX];
    void clear(){
        memset(node,0,sizeof(node));
    }
    int __merge(int x,int y){//�ϲ��Ը�x�͸�y���ڽڵ�Ķ�
        if(x==0||y==0)//��һ���ǿվͲ��ܺϲ���,���ز��ǿյ�
            return x?x:y;
        if(node[x].com(node[y])==1||(node[x].com(node[y])==0&&x>y))
            swap(x,y);
        int &xl=node[x].son[0];
        int &xr=node[x].son[1];
        xr=__merge(xr,y);
        node[xr].p=x;//�ҵĸ�����x
        if(node[xl].dis<node[xr].dis)
            swap(xl,xr);
        node[x].dis=node[xr].dis+1;
        return x;
    }
    int merge(int x,int y){//�ϲ���x���ڵ����y���ڵ����ڵĶѣ�x��y���[1,n],f���ظ��ڵ��ţ��ϲ����ɹ�����0
        if(node[x].val!=NO&&node[y].val!=NO&&x!=y){
            x=getRoot(x);
            y=getRoot(y);
            return __merge(x,y);
        }
        return 0;
    }
    int getRoot(int x){//�ҵ������x�ĵ�ģ����ڵ�
        while(node[x].p)
            x=node[x].p;
        return x;
    }
    int pop(int x){//����ڵ�x�������ĸ�,����ɾ����˭�Ǹ�
        x=getRoot(x);
        node[x].val=NO;//��ʾ����㲻����
        int &xl=node[x].son[0];
        int &xr=node[x].son[1];
        node[xl].p=node[xr].p=0;
        return merge(xl,xr);
    }
};
Mheap que;

int main(int argc,char *argv[]){
	int i,k,n,m,b,e;
	//que.clear();
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
        scanf("%d",&que.node[i].val);//����n������
	}
	for(i=0;i<m;i++){
        scanf("%d",&k);
        if(k==1){
            scanf("%d%d",&b,&e);//�ϲ����Ϊb�ͱ��Ϊe���ڵĶ�
            que.merge(b,e);
        }else if(k==2){
            scanf("%d",&b);
            if(que.node[b].val!=que.NO){//��û�б�ɾ��
                b=que.getRoot(b);
                printf("%d\n",que.node[b].val);
                que.pop(b);
            }else{//Ҫ�ҵı�ɾ�������-1��
                printf("-1\n");
            }
        }
	}
return 0;
}
