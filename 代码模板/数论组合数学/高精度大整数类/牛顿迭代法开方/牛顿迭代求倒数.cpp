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

int getDight(int n){
    int i;
    for(i=0;n!=0;n/=10,i++);
    return i;
}

double fen(double n){
    printf("%.14f\n",1/n);
    double i=0.0000089015,j;
    for(j=0;j<18;j++){
        printf("%.12f ",n*i);
        i=(2-n*i)*i;
    }
    return i;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    double n,m,t;
    ll a,i,j,k;
   while( cin>>n)
    printf("%.12f\n",fen(n));
return 0;
}
