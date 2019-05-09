#include<stdio.h>
#include<string.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;

int arr[100];
bool vis[100];
ll pow(ll a,ll n){
    ll ans=1;
    while(n){
        if(n&1){
            ans*=a;
        }
        n>>=1;
        a=a*a;
    }
    return ans;
}

void replacement(int *arr,int n){
    int k=arr[n];
    for(int i=n;i>1;i--){
        arr[i]=arr[i-1];
    }
    arr[1]=k;
}
int getLoopSectionCnt(int *arr,int n){
    int cnt=0,i,j;
    memset(vis,0,sizeof(vis));
    for(i=1;i<=n;i++){
        if(vis[i]==0){
            for(j=i;vis[j]==0;j=arr[j]){
                vis[j]=1;
            }
            cnt++;
        }
    }
    return cnt;
}

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
	ll i,j,k,T,n,a,dn,ans;
    while(~scanf("%lld",&n)&&n>-1){
        if(n==0){
            printf("0\n");
            continue;
        }
        dn=n>>1;
        for(i=1;i<=n;i++)
            arr[i]=i;
        ans=pow(3,n);
        for(i=1;i<n;i++){
            replacement(arr,n);
            k=getLoopSectionCnt(arr,n);
            ans+=pow(3,k);
        }
        if(n&1){
            a=pow(3,1+dn)*n;
        }else{
            a=pow(3,2+(n-2)/2)*dn+pow(3,dn)*dn;
        }
        ans+=a;
        ans/=n<<1;
        printf("%lld\n",ans);
    }
return 0;
}

