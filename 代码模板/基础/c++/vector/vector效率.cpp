#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=10000010;
const int mod=1e9+7;
int p[MAX],q[MAX];

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,T,a,b;

	for(i=0;i<MAX;i++){
        p[i]=i;
	}

	cin>>a>>b;
	printf("%d\n",a+b);
return 0;
}

