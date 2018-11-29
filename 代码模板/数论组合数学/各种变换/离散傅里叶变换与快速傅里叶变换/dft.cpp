#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define cd complex<double>
const int MAX=10000;
const double PI=3.1415926;

struct M{//复数矩阵
    int m,n;
    cd **mat;
    void init(int n,int m){
        this->n=n;
        this->m=m;
        mat=new  cd*[n];//////////建立二维数组；
        for(int i=0;i<n;i++){
            mat[i]=new cd[m];
            memset(mat[i],0,sizeof(cd)*m);
        }
    }
    void del(){
        for(int i=0;i<m;i++){//释放二维数组；
            delete []mat[i];
        }
        delete []mat;
    }

    void print(){
        int i,j;
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                printf("%.10lf %.10lf\n",mat[i][j].real(),mat[i][j].imag());
            }
        }
    }
    void selfMul(int n){
        int i,j;
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
               mat[i][j].real()/=n;
               mat[i][j].imag()/=n;
            }
        }
    }
};

M matMul(M a,M b){
    M c;
    if(a.m!=b.n){//第一个矩阵的列数m,要等于第二个矩阵行数才可以
        printf("矩阵大小不合法！\n");
        return c;
    }
    int i,j,k,r;
    r=a.m;
    c.init(a.n,b.m);
    for(i=0;i<c.n;i++){
        for(j=0;j<c.m;j++){
            c.mat[i][j]=0;
            for(k=0;k<r;k++){//矩阵的行
                c.mat[i][j]+=a.mat[i][k]*b.mat[k][j];
            }
        }
     }
     return c;
}

cd getW(int n){
    double k=2*PI/n;
    cd ans(cos(k),-sin(k));
    return ans;
}
M x;

void DFT(const M &x){//对xft
    int i,j,k;
    cd w=getW(x.n);
    M T;
    T.init(x.n,x.n);
    for(i=0;i<x.n;i++){
        for(j=0;j<x.n;j++){
            T.mat[i][j]=pow(w,i*j);
        }
    }
    M ans=matMul(T,x);
    ans.print();
}

int main(){
    int i,j,k,N;
    double a,b;
    /*cd w2=getW(4)*getW(4);
    cd w3=getW(2)*getW(2);
    printf("%lf \n",log2(2));
    printf("%.10lf %.10lf\n",w2.real(),w2.imag());
    printf("%.10lf %.10lf\n",w3.real(),w3.imag());*/
    while(~scanf("%d",&N)){
        x.init(N,1);//必须是竖着的
        for(i=0;i<N;i++){
            scanf("%lf%lf",&a,&b);
            x.mat[i][0].real()=a;
            x.mat[i][0].imag()=b;
        }
        //x.print();
        DFT(x);
    }
    return 0;
}
/*
8
1 2
3 4
5 6
7 8
9 -1
10 -2
16 -3
20 -4

*/
