#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define dd double

struct M{
    int n,m;//m>=n,矩阵有n行m列
    dd **mat;
    void init(int n,int m){//初始化
        this->n=n;
        this->m=m;
        mat=new dd*[n];
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
    void del(){//释放矩阵
        for(int i=0;i<m;i++)
            delete []mat[i];
        delete []mat;
    }
    void print(){//输出
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                printf("%f ",mat[i][j]);
            }printf("\n");
        }
    }
    void getIdmat(){//初始化单位矩阵
        for(int i=0;i<n;i++){
            mat[i][i]=1;
        }
    }

    bool toUpTriMat(){//变成三角矩阵
        int i,j,k,zero;
        dd mul;
        for(i=0;i<n-1;i++){//第几列
            for(j=i+1;j<n;j++){//第几行
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
                    if(zero==n){
                        return false;
                    }
                }
            }
        }
        return true;
    }
    void toSimMat(){//在已经是三角矩阵的情况下，变成最简矩阵,可以用来求逆矩阵
        //toUpTriMat();
        int i,j,k;
        dd mul;

        for(i=n-1;i>0;i--){//第几列
            if(mat[i][m-1]==0)
                continue;
            for(j=i-1;j>=0;j--){//第几行
                mul=-mat[j][i]/mat[i][i];
                for(k=i;k<m;k++){
                    mat[j][k]+=mat[i][k]*mul;
                }
            }
        }
        for(i=0;i<n;i++){
            if(mat[i][i]==0)
                continue;
            for(j=n;j<m;j++){
                mat[i][j]/=mat[i][i];
            }
            mat[i][i]=1;
        }
    }

};
int main(int argc,char *argv[]){
    int m,n,i,j,k;
    scanf("%d%d",&n,&m);
    M a,b;
    a.init(n,m);
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%lf",&a.mat[i][j]);
    b=a;
    a.toUpTriMat();
    a.print();
    printf("\n");
    a.toSimMat();
    a.print();
return 0;
}
/*
4 4
0 -1 0 1
0 1 -1 1
1 0 -1 0
0 1 0 -1
*/
