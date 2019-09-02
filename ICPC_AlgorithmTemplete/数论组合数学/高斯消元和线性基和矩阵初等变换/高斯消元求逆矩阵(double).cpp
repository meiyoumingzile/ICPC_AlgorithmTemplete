#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define dd double
const int INF=2147483647;
struct M{
    int n,m;//m>=n,������n��m��
    dd **mat;
    int *pos;//�����һ����Ϊ0����λ��
    void init(int n,int m){//��ʼ��
        this->n=n;
        this->m=m;
        pos=new int[n];
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
    void del(){//�ͷž���
        for(int i=0;i<m;i++)
            delete []mat[i];
        delete []mat;
    }
    void print(){//���
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                printf("%f ",mat[i][j]);
            }printf("\n");
        }
    }
    void getIdmat(){//��ʼ����λ����
        for(int i=0;i<n;i++){
            mat[i][i]=1;
        }
    }

    void toUpTriMat(){//����н��ݾ���,�õ�pos����
        int i,j,k,h,zero;
        dd mul;
        for(i=0;i<n-1;i++){//�ڼ���
            for(h=i;h<m;h++){//Ѱ�ҵ�һ����Ϊ0����
                for(j=i;j<n&&mat[j][h]==0;j++);
                if(j<n)
                    break;
            }
            pos[i]=h;
            if(h==m){
                while(++i<n)
                    pos[i]=m;
                break;
            }
            for(j=i+1;j<n;j++){//�����б任����һ�б��0
                if(mat[i][h]==0){
                    swap(mat[i],mat[j]);
                }else{
                    mul=-mat[j][h]/mat[i][h];
                    for(k=h,zero=0;k<m;k++){
                        mat[j][k]+=mat[i][k]*mul;
                        zero+=(mat[j][k]==0);
                    }
                    if(zero==m-h){
                        while(++i<n)
                            pos[i]=m;
                        return;
                    }
                }
            }
        }
        for(h=i;h<m&&mat[n-1][h]==0;h++);
        pos[n-1]=h;
    }
    void toSimMat(){//�Ѿ����н��ݣ����������
        //toUpTriMat();
        int i,j,k;
        dd mul;
        for(i=0;i<n;i++){
            printf("%d ",pos[i]);
        }printf("\n");
        for(i=n-1;i>0;i--){//�ڼ���
            if(pos[i]==m)
                continue;
            for(j=i-1;j>=0;j--){//�����б任�����������
                mul=-mat[j][pos[i]]/mat[i][pos[i]];
                for(k=pos[i];k<m;k++){
                    mat[j][k]+=mat[i][k]*mul;
                }
            }
        }
        for(i=0;i<n;i++){
            if(pos[i]==m)
                break;
            for(j=pos[i]+1;j<m;j++){
                mat[i][j]/=mat[i][pos[i]];
            }
            mat[i][pos[i]]=1;
        }
    }

    dd calcDet(){//���㷽������ʽ
        if(n!=m)
            return 1.0*INF;
        dd  ans=1;
        toUpTriMat();
        for(int i=0;i<n;i++){
            ans*=mat[i][i];
        }
        return ans;
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
    printf("%f\n",a.calcDet());
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

3 6
1 1 1 1 0 0
0 0 2 4 6 8
0 0 3 6 9 12

4 8
9 8 13 12 1 0 0 0
7 7 11 11 0 1 0 0
6 5 8 7 0 0 1 0
8 8 12 12 0 0 0 1

3 6
1 1 1 1 0 0
1 2 1 0 1 0
1 1 3 0 0 1
3 3
2 3 -1
1 2 0
-1 2 -2
*/
