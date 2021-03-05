#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=20010;
const int mod=1e9+7;
const float EARTH_RADIUS = 6370.996; // 地球半径系数
const float PI = 3.1415926;
struct v2{
    float x,y;
    v2(){}
    v2(float x,float y){
        sett(x,y);
    }
    void sett(float x,float y){
        this->x=x;
        this->y=y;
    }
};
v2 cir[MAX],dot[MAX];
float ansDis[MAX], edge2[MAX];
bool cmp(const v2 &a,const v2 &b){
    return a.x<b.x;
}

float getDis(const v2 &a,const v2 &b){
    float c=a.x-b.x,d=a.y-b.y;
    return sqrt(c*c+d*d);
}
float getDis2(const v2 &a,const v2 &b){
    float c=a.x-b.x,d=a.y-b.y;
    return c*c+d*d;
}
float a2b2_c2(const v2 &c,const v2 &b,const v2 &a){
    return a.x*a.x+a.y*a.y-a.x*(b.x+c.x)-a.y*(b.y+c.y)+b.x*c.x+b.y*c.y;
}
float getCirDis(const v2 *cir,int circnt,const v2 &d){
    register int i,j,k;
    register float ang=0,sumAng=0,d1,d2;
    for(i=0;i<circnt-1;i++){
        d1=getDis(d,cir[i]);
        d2=getDis(d,cir[i+1]);
        ang=(d1*d1+d2*d2-edge2[i])/(2*d1*d2);
        sumAng+=ang;
    }

    if(abs(sumAng-360.0)<inf){

    }
}

void calc(v2 *cir,v2 *dot,int circnt,int dotcnt){
    int i,j,k;
    for(i=0;i<circnt-1;i++){
        edge2[i]=getDis2(cir[i],cir[i+1]);
    }
    edge2[i]=getDis2(cir[i],cir[0]);
    for(i=0;i<dotcnt;i++){
        ansDis[i]=getCirDis(cir,circnt,dot[i]);
    }
}

int main(int argc,char *argv[]){
    freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
	int i,j,k,T,n,m;
	scanf("%d",&n);
	for(i=0;i<n;i++){
        scanf("%f%f",&cir[i].x,&cir[i].y);
	}
	scanf("%d",&m);
	for(i=0;i<m;i++){
        scanf("%f%f",&dot[i].x,&dot[i].y);
	}
	calc(cir,dot,n,m);
return 0;
}

