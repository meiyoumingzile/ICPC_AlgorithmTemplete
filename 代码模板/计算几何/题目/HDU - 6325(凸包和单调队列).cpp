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
const int MAX=200010;
const int mod=1e9+7;

struct v2{
    int x,y,i;
	v2(){}
	v2(const int &x,const int &y){
		sett(x,y);
	}
    void sett(const int &x,const int &y){
        this->x=x;
        this->y=y;
    }
};
v2 A[MAX];

bool cmp(const v2 &a,const v2 &b){
    if(a.x==b.x){
        if(a.y==b.y){
            return a.i<b.i;
        }
        return a.y>b.y;
    }
    return a.x<b.x;
}
bool lineFp(const v2 &a,const v2 &b,const v2 &c){//�����淵��1�������·���0
    v2 ba(b.x-a.x,b.y-a.y),ca(c.x-a.x,c.y-a.y);
    ll ans=(ll)ba.x*(ll)ca.y-(ll)ba.y*(ll)ca.x;
    if(ans==0){//a����b��ǰ,��Сǰ���
        return a.i<b.i;
    }
    return ans<0;
}
int li[MAX],liLen;
inline void ConvexHull(v2 *d,int len){
    rg int i,k,j;
    liLen=0;
    li[liLen++]=0;
    li[liLen++]=1;
    for(i=2;i<len;i++){
        if(d[i].x!=d[i-1].x||d[i].y!=d[i-1].y){
            while(liLen>1&&lineFp(d[i],d[li[liLen-1]],d[li[liLen-2]])){
                liLen--;
            }
            li[liLen++]=i;
        }
    }
}

deque<int>que;
int main(int argc,char *argv[]){
   // freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	rg int i,j,k,t,T,n,resLen,m;
	cin>>T;
	while(T--){
        scanf("%d",&n);
        for(i=0;i<n;i++){
            scanf("%d%d",&A[i].x,&A[i].y);
            A[i].i=i;
        }
        sort(A,A+n,cmp);
        ConvexHull(A,n);//��͹������ǹ��ߵ㣬�洢����͹���ϵĵ�
        printf("1");
        for(i=1;i<liLen;i++){
            printf(" %d",A[li[i]].i+1);
        }printf("\n");
	}
return 0;
}
/*

*/
