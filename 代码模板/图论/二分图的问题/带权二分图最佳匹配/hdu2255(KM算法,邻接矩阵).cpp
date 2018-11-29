#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define getName(xxx) #xxx
#define ll long long
#define inf 1e-5
#define rg register
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1010;
const int mod=1e9+7;

//KM�㷨

struct Graphic{//�ڽӾ��󴢴棬��Ϊ������ʱ�Ȩ�����Ҷ���ͼ���Ȩֵƥ�������һ���С�㷨���Ӷȱ������n^3��
    int V1,V2;
    int adMat[1010][1010];
    void clear(){
        memset(adMat,0,sizeof(adMat));
    }
};
Graphic g;
int lx[MAX],ly[MAX],xtoy[MAX],ytox[MAX],visx[MAX],visy[MAX];//lx,ly�Ƕ����ţ�xtoy���������㷨�еı�ʾx��ÿ����ӳ�䵽y,��ytox��ʾy����ӳ�䵽x,vis[x]��ʾx��ĳ������ľ�б�����
int minVal;
inline bool KM_dfs(int now){//�ҵ�һ�����ƥ��
    visx[now]=1;//���x��
    for(rg int i=1;i<=g.V2;i++){
        const int &next=i;
        if(visy[next]==0){
            const int &t=lx[now]+ly[next]-g.adMat[now][next];
            if(t==0){
                visy[next]=1;//���y��
                if(xtoy[next]==0||KM_dfs(xtoy[next])){
                    xtoy[next]=now;
                    ytox[now]=next;
                    return true;
                }
            }else{////������С��0
                if(t<minVal)minVal=t;//ȡ����С��t,����t��ô���ľ���֪��������ζ��val�������ȥminȷ�ҵ������Ȩֵƥ��
            }
        }
    }
    return false;
}
int KM(){
    int i,j,ans;
    memset(xtoy,0,sizeof(xtoy));
    memset(ytox,0,sizeof(ytox));
    memset(lx,0,sizeof(lx));
    memset(ly,0,sizeof(ly));
    for(i=1;i<=g.V1;i++){//��ʼ��
        for(j=1;j<=g.V2;j++){
            lx[i]=max(lx[i],g.adMat[i][j]);
        }
    }
    for(i=1;i<=g.V1;i++){
        while(1){
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            minVal=INF;
            if(KM_dfs(i))
                break;
            for(j=1;j<=g.V1;j++)//����x�궥,x�ļ�ȥ���ӵ�y��
                if(visx[j])
                    lx[j]-=minVal;
            for(j=1;j<=g.V2;j++)//����y�궥,x�ļ�ȥ���ӵ�y��
                if(visy[j])
                    ly[j]+=minVal;
        }
    }
    for(i=1,ans=0;i<=g.V2;i++)//ͨ������g.V2������Ȩ��,Ҳ���Ա���g.V1,����һ��
        ans+=g.adMat[i][ytox[i]];
    /*for(i=1,ans=0;i<=g.V1;i++)//ͨ������g.V2������Ȩ��,Ҳ���Ա���g.V1,����һ��,���Ǳ������y��x���ϵ�Ȩֵ,�������ⶨ��
        ans+=g.adMat[xtoy[i]][i];
        */
    return ans;
}
int main(){//��ʽǰ����д��
	int i,j,k,T=0,n,cost;
    while(~scanf("%d",&n)){
        g.clear();
        for(i=1;i<=n;i++){
            for(j=1;j<=n;j++){
                scanf("%d",&g.adMat[i][j]);
            }
        }
        g.V1=g.V2=n;
        printf("%d\n",KM());
    }
return 0;
}

