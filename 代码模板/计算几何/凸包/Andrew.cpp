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
    double x,y;
    int i;
	v2(){}
	v2(const double &x,const double &y){
		sett(x,y);
	}
    void sett(const double &x,const double &y){
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
bool lineFp(const v2 &a,const v2 &b,const v2 &c){//在上面返回1，在线下返回0
    v2 ba(b.x-a.x,b.y-a.y),ca(c.x-a.x,c.y-a.y);
    double ans=ba.x*ca.y-ba.y*ca.x;//叉积
    if(ans==0){//a靠后b靠前,后小前大就
        return a.i<b.i;
    }
    return ans<0;
}
int li[MAX],liLen;
inline void ConvexHull(v2 *d,int len,int fp){//求点集d凸包，fp是0代表上凸包，1代表下凸包
    rg int i,k,j;
    liLen=0;
    li[liLen++]=0;
    li[liLen++]=1;
    for(i=2;i<len;i++){
        if(d[i].x!=d[i-1].x||d[i].y!=d[i-1].y){
            while(liLen>1&&(fp^lineFp(d[i],d[li[liLen-1]],d[li[liLen-2]]))){
                liLen--;
            }
            li[liLen++]=i;
        }
    }
}

int main(int argc,char *argv[]){
   // freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,n;
	while(~scanf("%d",&n)){
        for(i=0;i<n;i++){
            scanf("%lf%lf",&A[i].x,&A[i].y);
            A[i].i=i;
        }
        sort(A,A+n,cmp);
        ConvexHull(A,n,0);//求上凸包
        for(i=0;i<liLen;i++){//求上凸包
            printf("%d ",A[li[i]].i);
        }printf("\n");
        ConvexHull(A,n,1);//求下凸包
        for(i=0;i<liLen;i++){//求上凸包
            printf("%d ",A[li[i]].i);
        }printf("\n");
	}
return 0;
}
/*
5
4 8
4 12
5 9.3
7 8
7 0
*/
