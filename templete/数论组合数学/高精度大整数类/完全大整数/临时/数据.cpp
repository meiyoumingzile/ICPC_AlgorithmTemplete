#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;

struct v2{
    double x,y;
    v2(){}
    v2(double x,double y){
        sett(x,y);
    }
    void sett(double x,double y){
        this->x=x;
        this->y=y;
    }
};
v2 cir[2000],dot[2000];
bool cmp(const v2 &a,const v2 &b){
    return a.x<b.x;
}

void makeData(int n,int m){
    srand(time(NULL));
    int i;
    printf("%d\n",n);
    for(i=0;i<n;i++){
        printf("%d %d\n",rand()%1000,rand()%1000);
    }
    printf("%d\n",m);
    for(i=0;i<m;i++){
        printf("%d %d\n",rand()%1000,rand()%1000);
    }
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    freopen("in.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,T,n,m;
	scanf("%d %d",&n,&m);
	makeData(n,m);
return 0;
}

