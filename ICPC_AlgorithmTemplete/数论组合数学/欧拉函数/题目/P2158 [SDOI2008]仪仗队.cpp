#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ll __int64
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;

struct getEuler{//��һ���o(n)����������˳����ɸ
    bool *flag;///�������
    int *phi;///ŷ������ֵ��i��ŷ������ֵ=phi[i]
    int *p;///�����ӵ�ֵ
    int cnt;
    void getPhi(int MAX){
        cnt = 0;
        flag=new bool[MAX];
        phi=new int[MAX];
        p=new int[MAX];
        memset(flag, true, sizeof(bool)*MAX);

        phi[1] = 1;
        for(int i=2; i<MAX; i++){
            if(flag[i]){
                p[cnt++] = i;
                phi[i] = i-1;///������ŷ������ֵ������ - 1
            }
            for(int j=0; j<cnt; j++){
                if(i*p[j] > MAX)
                    break;
                flag[i*p[j]] = false;///�����ı���������i*p[j]��������
                if(i%p[j] == 0){///���ʣ�i mod p == 0, ��ô phi(i * p) == p * phi(i)
                    phi[i*p[j]] = p[j] * phi[i];
                    break;
                }else{
                    phi[i*p[j]] = (p[j]-1) * phi[i];///i mod p != 0, ��ô phi(i * p) == phi(i) * (p-1)
                }
            }
        }
    }
};

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int n,i,j,ans;
    getEuler eu;

    while(~scanf("%d",&n)){
        eu.getPhi(n+1);
        for(i=1,ans=0;i<n;i++){
            ans+=eu.phi[i];
        }
        printf("%d\n",ans*2+1);
    }
return 0;
}
