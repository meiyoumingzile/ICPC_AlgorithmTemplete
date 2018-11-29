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
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=1000010;
const int mod=1e9+7;
ll getinv(ll a){
    ll n=mod-2,ans=1;
    a%=mod;
    while(n){
        if(n%2)
            ans=ans*a%mod;
        a=a*a%mod;
        n>>=1;
    }
    return ans;
}
struct M{
    int n,m;//m>=n,������n��m��
    ll **mat;
    void init(int n,int m){//��ʼ��
        this->n=n;
        this->m=m;
        mat=new ll*[n];
        for(int i=0;i<n;i++){
            mat[i]=new ll[m];
            memset(mat[i],0,sizeof(ll)*m);
        }
    }
    void operator = (const M &t){
         init(t.n,t.m);
         for(int i=0;i<n;i++){
            memcpy(mat[i],t.mat[i],sizeof(ll)*m);
         }
    }
    void del(){//�ͷž���
        for(int i=0;i<m;i++)
            delete []mat[i];
        delete []mat;
    }
    void print(){//���
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                printf("%lld ",mat[i][j]);
            }printf("\n");
        }
    }
    void getIdmat(){//��ʼ����λ����
        for(int i=0;i<n;i++){
            mat[i][i]=1;
        }
    }
    bool toUpTriMat(){//������Ǿ���
        rg int i,j,k,zero;
        for(i=0;i<n-1;i++){//�ڼ���
            ll inv=getinv(mat[i][i]);
            for(j=i+1;j<n;j++){//�ڼ���
                if(mat[i][i]==0){
                    swap(mat[i],mat[j]);
                }else{
                    ll mul=(mat[j][i]*inv%mod*(-1)+mod)%mod;
                    for(k=zero=0;k<m;k++){
                        mat[j][k]=(mat[j][k]+mat[i][k]*mul%mod)%mod;
                        if(mat[j][k]==0){
                            zero++;
                        }
                    }
                    if(zero==n)return false;
                }
            }
        }
        return true;
    }
    void toSimMat(){//���Ѿ������Ǿ��������£����������,���������������
        //toUpTriMat();
        rg int i,j,k;
        for(i=n-1;i>0;i--){//�ڼ���
            ll inv=getinv(mat[i][i]);
            for(j=i-1;j>=0;j--){//�ڼ���
                ll mul=(mat[j][i]*inv%mod*(-1)+mod)%mod;
                for(k=i;k<m;k++){
                    mat[j][k]=(mat[j][k]+mat[i][k]*mul%mod)%mod;
                }
            }
        }
        for(i=0;i<n;i++){
            ll inv=getinv(mat[i][i]);
            for(j=n;j<m;j++){
                mat[i][j]=mat[i][j]*inv%mod;
            }
            mat[i][i]=1;
        }
    }
};

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    rg int n,i,j,k;
    scanf("%d",&n);
    M a,b;
    a.init(n,2*n);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%lld",&a.mat[i][j]);
        }
    }
    for(i=0;i<n;i++){
        a.mat[i][i+n]=1;
    }
    if(a.toUpTriMat()){
        a.toSimMat();
        for(i=0;i<n;i++){
            printf("%lld",a.mat[i][n]);
            for(j=1;j<n;j++){
                printf(" %lld",a.mat[i][n+j]);
            }printf("\n");
        }
    }else{
        printf("No Solution\n");
    }
return 0;
}
/*
3 4
2 1 1 1
6 2 1 -1
-2 2 1 7

3 4
1 2 3 0
3 4 7 2
6 5 9 11
*/
