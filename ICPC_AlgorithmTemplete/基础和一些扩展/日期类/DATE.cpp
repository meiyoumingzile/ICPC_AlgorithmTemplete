#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;

struct Date{
    int y[3],h[3];//y代表年月日，h代表时分秒
    static int day[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	Date(){}
	Date(const int &y,const int &m,const int &d){
		sett(y,m,d,0,0,0);
	}
	Date(const int &y,const int &m1,const int &d,const int &h,const int &m2,const int &s){
		sett(y,m1,d,h,m2,s);
	}
    void sett(const int &y,const int &m1,const int &d,const int &h,const int &m2,const int &s){
        this->y[0]=y;
        this->y[1]=m1;
        this->y[2]=d;
        this->y[0]=h;
        this->y[1]=m2;
        this->y[2]=s;
    }
    bool isLeap(){
        if(y[0]%400==0)
            return 1;
        if(y[1]%100==0)
            return 0;
        return y[2]%4==0;
    }
    Date add(int daycnt){//日期加上秒数

    }
    Date sub(int daycnt){

    }
	Date sub(int daycnt){

    }
    static toDay(int s){//秒转换日
        return s/
    }
};


int main(int argc,char *argv[]){
	int i,j,k,t,T,n,m;

return 0;
}

