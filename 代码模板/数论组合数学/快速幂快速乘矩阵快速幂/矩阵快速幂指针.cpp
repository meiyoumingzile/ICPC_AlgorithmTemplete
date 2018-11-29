#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
#define ll long long
const int mod=10e+7;

const int MATSIZE=10;
struct M{
    int m,n;
    ll mat[MATSIZE][MATSIZE];
    M(){}
    M(int n,int m){
        init(n,m);
    }
    void init(int n,int m){
        this->n=n;
        this->m=m;
        //memset(mat,0,sizeof(mat));
    }
    M *clone(){
        M *c=new M(n,m);
        int i,j;
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
                c->mat[i][j]=mat[i][j];
        return c;
    }
    void print(){
        int i,j;
        for(i=0;i<n;i++){
            printf("%lld",mat[i][0]);
            for(j=1;j<m;j++){
                printf(" %lld",mat[i][j]);
            }printf("\n");
        }
    }
    void getIdmat(){
        for(int i=0;i<n;i++){
            mat[i][i]=1;
        }
    }
    M *matMul(M *a, M *b,ll mod){
        M *c=new M(a->n,b->m);
        if(a->m!=b->n){//��һ�����������m,Ҫ���ڵڶ������������ſ���
            printf("�����С���Ϸ���\n");
            return c;
        }
        int i,j,k,r;
        r=a->m;
        for(i=0;i<c->n;i++){
            for(j=0;j<c->m;j++){
                c->mat[i][j]=0;
                for(k=0;k<r;k++){//�������
                    c->mat[i][j]+=a->mat[i][k]*b->mat[k][j];
                    c->mat[i][j]%=mod;
                }
            }
         }
         return c;
    }
    M *matMul(M *a,ll b,ll mod){
        M *c=new M(a->n,a->m);
        int i,j,k,r;
        for(i=0;i<c->n;i++){
            for(j=0;j<c->m;j++){
                c->mat[i][j]=a->mat[i][j]*b%mod;
            }
        }
        return c;
    }

    M *matPow(M *a,ll k,ll mod){
        M *e=new M(a->n,a->m),*c,*t;
        if(a->n!=a->m){
            printf("�����С���Ϸ���\n");
            return e;
        }
        e->getIdmat();
        if(k==0){
            return e;
        }
        c=a->clone();
        while(k){
            if(k%2==1){
                t=e;
                e=matMul(e,c,mod);
                delete t;
            }
            t=c;
            c=matMul(c,c,mod);
            delete t;
            k>>=1;
        }
        return e;
    }
};


int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int n,m,i,j;
    ll k;
    M *a=new M();

    while(~scanf("%d%d%lld",&n,&m,&k)){
        a->init(n,m);
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                scanf("%lld",&a->mat[i][j]);
            }
        }

        M *e=a->matPow(a,k,mod);
        e->print();
    }
return 0;
}
