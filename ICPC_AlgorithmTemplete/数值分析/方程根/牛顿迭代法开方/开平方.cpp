#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;
const double h=0x5f3759df;


ll mysqrt(ll n){
    double i=10000000,j;
    do{
        printf("%f\n",i);
        i=(i+n/i)/2;
        j=i*i-n;
    }while(abs(i*i-n)>inf);
    return i;
}
int getDight(int n){
    int i;
    for(i=0;n!=0;n/=10,i++);
    return i;
}
double fen(double n){
    printf("%.14lf\n",1/n);
    double i=1/pow(10.0,getDight(n)+1),j;
    for(j=0;j<15;j++){
        i=(2-n*i)*i;
        printf("%.12lf ",i);
    }
    return i;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    double n,m,t;
    ll a,i,j,k;
    cin>>n;
    printf("%lld\n",mysqrt(n));
return 0;
}
