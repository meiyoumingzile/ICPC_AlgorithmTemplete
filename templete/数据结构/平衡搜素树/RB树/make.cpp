#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
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
bool cmp1(const v2 &a,const v2 &b){
    return a.y<b.y;
}
bool cmp2(const v2 &a,const v2 &b){
    return a.i<b.i;
}
v2 in[MAX];
int main(int argc,char *argv[]){
    //freopen("testdata.in","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("in4.in","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i,j,k,id,T=30,t;
    printf("%d\n",T);
    for(i=0;i<T;i++){
        printf("%d %d\n",rand()%2+1,rand()%100);
    }
return 0;
}
