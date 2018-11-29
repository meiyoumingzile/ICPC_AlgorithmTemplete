#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<string>
#include<cstring>
#include<ctime>
#include<map>
#include<set>
//#include<windows.h>
using namespace std;
//std::ios::sync_with_stdio(false);
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define dd double
#define ll long long
#define inf 1e-5
const int INF=1<<30;
const int MAX=1000010;
const int mod=1e9+7;

struct M{
    int n,m;//m>=n,������n��m��
    dd **mat;
    void init(int n,int m){
        this->n=n;
        this->m=m;
        mat=new  dd*[n];//////////������ά���飻
        for(int i=0;i<n;i++){
            mat[i]=new dd[m];
            memset(mat[i],0,sizeof(dd)*m);
        }
    }
    void operator = (const M &t){
         init(t.n,t.m);
         for(int i=0;i<n;i++){
            memcpy(mat[i],t.mat[i],sizeof(dd)*m);
         }
    }
    void del(){
        for(int i=0;i<m;i++){//�ͷŶ�ά���飻
            delete []mat[i];
        }
        delete []mat;
    }

    void print(){
        int i,j;
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                printf("%lf ",mat[i][j]);
            }printf("\n");
        }
    }

    void getIdmat(){//��ʼ����λ����
        for(int i=0;i<n;i++){
            mat[i][i]=1;
        }
    }

   bool toUpTriMat(){//������Ǿ���
        int i,j,k,zero;
        dd mul;
        for(i=0;i<m-1;i++){//�ڼ���
            for(j=i+1;j<n;j++){//�ڼ���
                if(mat[i][i]==0){
                    swap(mat[i],mat[j]);
                }else{
                    mul=-mat[j][i]/mat[i][i];
                    for(k=0,zero=0;k<m;k++){
                        mat[j][k]+=mat[i][k]*mul;
                        if(mat[j][k]==0){
                            zero++;
                        }
                    }
                    if(zero==m){
                        return false;
                    }
                }
            }
        }
        return true;
    }
    void toSimMat(){//���Ѿ������Ǿ��������£����������,���������������
        //toUpTriMat();
        int i,j,k;
        dd mul;
        for(i=n-1;i>0;i--){//�ڼ���
            for(j=i-1;j>=0;j--){//�ڼ���
                mul=-mat[j][i]/mat[i][i];
                for(k=i;k<m;k++){
                    mat[j][k]+=mat[i][k]*mul;
                }
            }
        }
        for(i=0;i<n;i++){
            for(j=n;j<m;j++){
                mat[i][j]/=mat[i][i];
            }
            mat[i][i]=1;
        }
    }

};



int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int i,j,n;
    scanf("%d",&n);
    M a;
    a.init(n,n+1);
    for(i=0;i<n;i++){
        for(j=0;j<n+1;j++){
            scanf("%lf",&a.mat[i][j]);
        }
    }
    if(!a.toUpTriMat()){
        printf("No Solution\n");
    }else{
        a.toSimMat();
        for(i=0;i<n;i++){
            printf("%.2lf\n",a.mat[i][n]);
        }
    }
return 0;
}
