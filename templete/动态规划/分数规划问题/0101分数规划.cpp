#include<stdio.h>
#include<math.h>
#include<algorithm>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-2
const int inv2=500000004;
const int INF=2147483647;
const int MAX=100010;
const int mod=1e9+7;

struct v2{
    int x,y;
};
v2 ob[MAX];
float d[MAX];

int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int T,i,j,k,n,h;
    float sum,r=-INF,l=0,v;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        r=INF;
        l=0;
        for(i=0;i<n;i++){
            scanf("%d%d",&ob[i].y,&ob[i].x);
            //r=max(r,(float)ob[i].x);
        }
        while(1){//abs(sum)<=inf
            v=(r+l)/2.0;
            for(i=0;i<n;i++){
                d[i]=ob[i].x-ob[i].y*v;
            }
            sort(d,d+n);

            for(i=0,sum=0.0;i<k;i++){
                sum+=d[n-i-1];
            }
            if(sum>inf){
                l=v;
            }else if(sum<-inf){
                r=v;
            }else{
                break;
            }
        }
        printf("%.2f\n",v);
    }
return 0;
}

/*
3 2
2 2
5 3
2 1
*/
