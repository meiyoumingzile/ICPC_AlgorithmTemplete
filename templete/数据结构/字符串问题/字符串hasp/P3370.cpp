#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
#define rg register
#define cint const int &
#define cll const long long &
#define cdou const double &
#define cv2 const v2 &
#define dd double
typedef unsigned long long ull;
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=100010;
const int mod=1e9+7;

const ull base=255;
ull li[MAX];//ull���Ϳ����Զ�ȡģ
char s[MAX];
ull getHashKey(char *s){
    int i,len=strlen(s);
    ull ans=0;
    for(i=0;i<len;i++)
        ans=ans*base+ull(s[i]);
    return ans;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	int i,j,k,t,T,n,cnt=0;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%s",s);
        li[i]=getHashKey(s);
    }
    sort(li,li+n);
    for(cnt=i=1;i<n;i++){
        if(li[i]!=li[i-1]){
            cnt++;
        }
    }
    printf("%d\n",cnt);
return 0;
}

