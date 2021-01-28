#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define dd double
const int INF=2147483647;


ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}
struct Fra{
    ll a,b,g;//b是分母，a是分子
    Fra(){}
    Fra(const ll &a,const ll &b){
        sett(a,b);
    }
    void sett(const ll &a,const ll &b){
        this->a=a;
        this->b=b;
        getg();
        red();
    }
    double toDouble(){
        return a/(double)b;
    }
    void getg(){
        g=gcd(a,b);
    }
    void red(){//约分,且要先计算gcd
        a/=g;
        b/=g;
        g=1;
        if(b<0){
            a=-a;
            b=-b;
        }
    }
    Fra static toFra(int n){
        Fra f;
        f.sett(n,1);
        return f;
    }
    bool is0(){
        return a==0;
    }
    int compare(Fra &t){
        if(t.g>1)
            t.red();
        if(g>1)
            red();
        if(t.b==b){
            if(t.a==a)
                return 0;
            return a>t.a?1:-1;
        }else{
            ll gt=gcd(b,t.b);
            return a/gt*t.b>t.a/gt*b?1:-1;
        }
    }
    int compare(int t){
        Fra f=toFra(t);
        return compare(f);
    }
    void selfadd(const Fra &t){
        sett(a*t.b+b*t.a,b*t.b);
    }
    void selfsub(const Fra &t){
        sett(a*t.b-b*t.a,b*t.b);
    }
    void selfmul(const Fra &t){
        sett(t.a*a,t.b*b);
    }
    void selfdiv(const Fra &t){
        sett(t.b*a,t.a*b);
    }


    Fra add(const Fra &t){
        return Fra(a*t.b+b*t.a,b*t.b);
    }
    void add(const Fra &t,Fra &ans){
        ans.sett(a*t.b+b*t.a,b*t.b);
    }
    Fra sub(const Fra &t){
        return Fra(a*t.b-b*t.a,b*t.b);
    }
    void sub(const Fra &t,Fra &ans){
        ans.sett(a*t.b-b*t.a,b*t.b);
    }
    Fra mul(const Fra &t){
        return Fra(t.a*a,t.b*b);
    }
    void mul(const Fra &t,Fra &ans){
        ans.sett(t.a*a,t.b*b);
    }
    Fra div(const Fra &t){
        return Fra(t.b*a,t.a*b);
    }
    void div(const Fra &t,Fra &ans){
        ans.sett(t.b*a,t.a*b);
    }
    void print(){
        if(a==0){
            printf("0 ");
        }else if(a%b==0){
            printf("%lld ",a/b);
        }else{
            printf("%lld/%lld ",a,b);
        }
    }
};

struct M{
    int n,m;//m>=n,矩阵有n行m列
    Fra **mat;
    int *pos;//左起第一个不为0的数位置
    void init(int n,int m){//初始化
        this->n=n;
        this->m=m;
        pos=new int[n];
        mat=new Fra*[n];
        for(int i=0;i<n;i++){
            mat[i]=new Fra[m];
            memset(mat[i],0,sizeof(Fra)*m);
        }

    }
    void operator = (const M &t){
         init(t.n,t.m);
         for(int i=0;i<n;i++){
            memcpy(mat[i],t.mat[i],sizeof(Fra)*m);
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
                mat[i][j].print();
            }printf("\n");
        }
    }
    void getIdmat(){//初始化单位矩阵
        for(int i=0;i<n;i++){
            mat[i][i].sett(1,1);
        }
    }

    void toUpTriMat(){//变成行阶梯矩阵,得到pos数组
        int i,j,k,h,zero;
        Fra mul;
        for(i=0;i<n-1;i++){//第几列
            for(h=i;h<m;h++){//寻找第一个不为0的列
                for(j=i;j<n&&mat[j][h].is0();j++);
                if(j<n)
                    break;
            }
            pos[i]=h;
            if(h==m){
                while(++i<n)
                    pos[i]=m;
                break;
            }
            for(j=i+1;j<n;j++){//初等行变换来把一列变成0
                if(mat[i][h].is0()){
                    swap(mat[i],mat[j]);
                }else{
                    mul=mat[j][h].div(mat[i][h]);
                    mul.a=-mul.a;
                    for(k=h,zero=0;k<m;k++){
                        mat[j][k].selfadd(mat[i][k].mul(mul));
                        zero+=mat[j][k].is0();
                    }
                    if(zero==m-h){
                        while(++i<n)
                            pos[i]=m;
                        return;
                    }
                }
            }
        }
        for(h=i;h<m&&mat[n-1][h].is0();h++);
        pos[n-1]=h;
    }
    void toSimMat(){//已经是行阶梯，变成最简矩阵
        //toUpTriMat();
        int i,j,k;
        Fra mul;
        /*for(i=0;i<n;i++){
            printf("%d ",pos[i]);
        }printf("\n");*/
        for(i=n-1;i>0;i--){//第几列
            if(pos[i]==m)
                continue;
            for(j=i-1;j>=0;j--){//初等行变换来变成最简矩阵
                mul=mat[j][pos[i]].div(mat[i][pos[i]]);
                mul.a=-mul.a;
                for(k=pos[i];k<m;k++){
                    mat[j][k].selfadd(mat[i][k].mul(mul));
                }
            }
        }
        for(i=0;i<n;i++){
            if(pos[i]==m)
                break;
            for(j=pos[i]+1;j<m;j++){
                mat[i][j].selfdiv(mat[i][pos[i]]);
            }
            mat[i][pos[i]].sett(1,1);
        }
    }

    /*dd calcDet(){//计算方阵行列式
        if(n!=m)
            return 1.0*INF;
        dd  ans=1;
        toUpTriMat();
        for(int i=0;i<n;i++){
            ans*=mat[i][i];
        }
        return ans;
    }*/
};
int main(int argc,char *argv[]){
    int m,n,i,j,k;
    while(1){
        scanf("%d",&n);
        M a,b;
        m=n*2;
        a.init(n,m);
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                scanf("%d",&k);
                a.mat[i][j].sett(k,1);
            }
        }
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                if(i==j){
                    a.mat[i][j+n].sett(1,1);
                }else{
                    a.mat[i][j+n].sett(0,1);
                }
            }
        }
        b=a;
        //printf("%f\n",a.calcDet());
        a.toUpTriMat();
        //a.print();
       // printf("\n");
        a.toSimMat();
        a.print();
    }

return 0;
}
/*
3
1 2 1
-1 1 -2
2 -1 1
*/
