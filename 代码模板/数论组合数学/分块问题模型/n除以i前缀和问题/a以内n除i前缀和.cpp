#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;

ll cmp(ll x){//����ĺ�������sum(cmp(n/i)),i����[1,m]�ĺ�
    return x;
}
ll divSum(ll n,ll m){//sum(n/i),i�ķ�Χ�ǣ�[1,m]
    if(m>n)
        m=n;
    ll ans=0,i,j,k,sqrtn=(ll)sqrt(n);
    if(m<=sqrtn){//С�ڵ���sqrtn�����
        for(i=1;i<=m;i++){
            ans+=cmp(n/i);
        }
    }else{
        for(i=1;i<=sqrtn;i++){//������[1,sqrtn]
            ans+=cmp(n/i);
        }
        k=n/sqrtn-sqrtn;
        if(sqrtn+k>=m){//��(sqrtn,n/sqrtn]
            ans+=(m-sqrtn)*cmp(sqrtn);//
            return ans;
        }//��������(n/sqrtn,n]��
        i=sqrtn+k+1;
        j=sqrtn;
        ans+=k*cmp(sqrtn);//
        while(j>1){
            k=n/(j-1)-n/j;
            j--;
            if(i+k<=m){
                ans+=cmp(n/i)*k;//
                i+=k;
            }else{
                ans+=cmp(n/i)*(m-i+1);//
                return ans;
            }
        }
    }
    return ans;
}
ll vio(ll n,ll m){
    if(n<m){
        printf("����");
        return -1;
    }
    ll ans=0,i;
    for(i=1;i<=m;i++){
        ans+=n/i;
    }
    return ans;
}
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    ll n,m;
    while(~scanf("%lld%lld",&n,&m)){
        printf("%lld\n",divSum(n,m));
    }
return 0;
}
/*
8392265052 8392265052 9169135979
*/
