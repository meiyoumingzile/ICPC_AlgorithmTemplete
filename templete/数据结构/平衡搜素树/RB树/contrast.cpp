#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;
int A[MAX];
int main(int argc,char *argv[]){
    char s1[100]="in3.out";
    char s2[100]="myout.out";
    freopen(s1,"r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("in1.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i,j,k,id,T,t;
    i=0;
    while(~scanf("%d",&A[i++]));
    freopen(s2,"r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    T=i;
    for(i=0;i<T;i++){
        scanf("%d",&k);
        if(k!=A[i]){
            printf("i=%d, %s:%d %s:%d\n",i,s1,A[i],s2,k);
            break;
        }
    }
return 0;
}
