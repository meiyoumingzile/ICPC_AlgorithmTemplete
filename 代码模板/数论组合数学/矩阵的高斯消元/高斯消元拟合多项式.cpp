#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define dd double

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

struct v2{
    dd x,y;
};
v2 A[1010];
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int m,n,i,j,k;
    scanf("%d",&n);//��n����
    for(i=0;i<n;i++){
        scanf("%lf%lf",&A[i].x,&A[i].y);
    }

    M a,b;
    a.init(n,n+1);
    for(i=0;i<n;i++){
        a.mat[i][n]=A[i].y;
    }
    for(i=0;i<n;i++){
        a.mat[i][0]=1.0;
        for(j=1;j<n;j++){
            a.mat[i][j]=a.mat[i][j-1]*A[i].x;
        }
    }

    a.toUpTriMat();
    a.print();
    printf("\n");
    a.toSimMat();
    a.print();
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
