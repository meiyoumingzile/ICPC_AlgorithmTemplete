#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;

char str1[MAX],str2[MAX];
void rands(char *s,int n){//nС��1e5
    memset(s,0,sizeof(s));
    for(int i=0;i<n;i++){
        s[i]=rand()%26+'a';
    }
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    freopen("test4.in","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    srand(time(NULL));//�е�OJ���ܼ���仰
	rg int i,n,len,k;
    n=10;
    len=1e5;
    k=n;
    printf("%d\n",n);
    while(n>k){
        rands(str1,len);
        rands(str2,len/4);
        printf("%s\n%s\n",str1,str2);
        n--;
    }
    while(n--){
        rands(str1,len);
        rands(str2,len);
        printf("%s\n%s\n",str1,str2);
    }

return 0;
}
/*
sdssdsdaasdsadsaddawdadsads
sadsssasdsssssssssssssssssssssssssssssssss
*/
