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
    int y,m,d;
    static int day[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	Date(){}
	Date(const int &y,const int &m,const int &d){
		sett(y,m,d);
	}
    void sett(const int &y,const int &m,const int &d){
        this->y=y;
        this->m=m;
        this->d=d;
    }
    bool isLeap(){
        if(y%400==0)
            return 1;
        if(y%100==0)
            return 0;
        return y%4==0;
    }
    Date add(int daycnt){

    }
    Date sub(int daycnt){

    }
};


int main(int argc,char *argv[]){
	int i,j,k,t,T,n,m;

return 0;
}

