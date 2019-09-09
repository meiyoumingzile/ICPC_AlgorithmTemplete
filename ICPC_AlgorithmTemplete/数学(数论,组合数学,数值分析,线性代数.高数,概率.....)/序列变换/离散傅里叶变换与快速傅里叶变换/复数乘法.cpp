#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define cd Complex<double>
const int MAX=10000;
const double PI=3.1415926;
int N;
template <class Data>
struct Complex{
    Data real,imag;//real+imagi
    Complex(){
    }
    Complex(Data real,Data imag){
        sett(real,imag);
    }
    void sett(Data real,Data imag){
        this->real=real;
        this->imag=imag;
    }
    Complex operator + (const Complex &other){
        Complex tmp;
        tmp.sett(real+other.real,imag+other.imag);
        return tmp;
    }
    Complex operator - (const Complex &other){
        Complex tmp;
        tmp.sett(real-other.real,imag-other.imag);
        return tmp;
    }
    Complex operator * (const Complex &other){
        Complex tmp;
        tmp.sett(real*other.real-imag*other.imag,imag*other.real+real*other.imag);
        return tmp;
    }
    Complex operator / (const Complex &other){
        Complex tmp;
        double m=other.real*other.real+other.imag*other.imag;
        tmp.real=(real*other.real+imag*other.imag)/m;
        tmp.imag=(imag*other.real-real*other.imag)/m;
        return tmp;
    }
};
cd pow(cd a,ll n){
    cd ans(1,0);
    while(n){
        if(n&1)
            ans=ans*a;
        a=a*a;
        n/=2;
    }
    return ans;
}

cd getW(int N){
    double k=2*PI/N;
    cd ans;
    ans.sett(cos(k),-sin(k));
    return ans;
}


int main(){
    int i,j,k,n;
    cd w=getW(4);
    w=w*w;
    printf("%.10lf %.10lf\n",w.real,w.imag);
    cd a,b,c;
    while(~scanf("%lf%lf%lf%lf",&a.real,&a.imag,&b.real,&b.imag)){
        c=a*b;
        printf("%.10lf %.10lf\n",c.real,c.imag);
    }
return 0;}
