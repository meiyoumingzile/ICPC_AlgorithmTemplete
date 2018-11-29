
#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define cd Complex
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;
const double PI=acos(-1.0);

struct Complex{
    double real=0,imag=0;//real+imagi
    Complex(){}
    Complex(double real,double imag){
        sett(real,imag);
    }
    void sett(double real,double imag){
        this->real=real;
        this->imag=imag;
    }
    Complex operator + (const Complex &other){
        Complex(real+other.real,imag+other.imag);
        return Complex(real+other.real,imag+other.imag);
    }
    Complex operator - (const Complex &other){
        return Complex(real-other.real,imag-other.imag);
    }
    Complex operator * (const Complex &other){
        return Complex(real*other.real-imag*other.imag,imag*other.real+real*other.imag);
    }
    Complex operator / (const Complex &other){
        double m=other.real*other.real+other.imag*other.imag;
        return Complex((real*other.real+imag*other.imag)/m,(imag*other.real-real*other.imag)/m);
    }
    Complex operator / (const double &other){
        return Complex(real/other,imag/other);
    }
};
inline cd getWI(int n,int fp){//得到Wn
    double k=2*PI/64;
    cd ans(cos(k*n),-sin(k*n)*fp);
    return ans;
}
inline cd getW(int n,int fp){//得到Wn
    double k=2*PI/n;
    cd ans(cos(k),-sin(k)*fp);
    return ans;
}
void println(int n,int k){
    cd c=getW(n,1),ans(1,0);
    cd d=getWI(n,1);
    for(int i=0;i<k;i++){
        ans=ans*c;
    }
    printf("%lf %lf || %lf %lf\n",ans.real,ans.imag,d.real,d.imag);
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
	int i,j,k,T,n;
	n=65;
	for(i=0;i<n;i++){
        printf("%d:",i);
        println(i,1);
	}
	while(1){
        cin>>n>>k;
        println(n,k);
	}
return 0;
}

