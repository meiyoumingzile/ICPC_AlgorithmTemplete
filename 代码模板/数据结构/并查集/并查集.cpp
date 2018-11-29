#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;

struct Union{
    int p[MAX];
    int rank[MAX];
    /**
     * 并查集的初始化：
     * 数组p中的元素在最开始ide时候都是独立的树，也就是只有根节点
     * 的树，数组p的下标i表示节点，而p[i]的值表示i节点的父亲
     * 节点；rank[i]=1表示一开始所有树节点的高度都为1
    **/
    void init(int n){//n代表人数；编号[0,n)
        for(int i=0;i<n;i++){
            p[i]=i;
            rank[i]=1;
        }
    }
    /**
     * 查找元素所在的集合并进行路劲压缩：
     * 由于需要频繁使用GetFather（）函数，并且其时间复杂度受树结构影响；
     * 当元素较多的时候，集合退化成链表，则GetFather()需要O(N)，所以
     * 需要对其进行优化，每次调用GetFather（）的时候都将输入元素压缩成
     * 最原始父亲节点的直接子节点
     * */
    int GetFather(int son) {
        if(p[son]!=son)
            p[son]=GetFather(p[son]);
        return p[son];
    }

    void merge(int x, int y){//普通合并，把y变成x的子树可能降低查询效率，但是可以控制根节点是哪个
        p[y]=x;
    }

    /**
     * 利用rank加权数组启发式进行合并
     * */
    void insMerge(int x, int y) {
        int fx=GetFather(x);
        int fy=GetFather(y);

        if(fx==fy) return;
        /**
         * rank[fx]较大，说明其越靠近根节点，则将
         * fy连接到其后面可以压缩路径
         * */

        if(rank[fx]>rank[fy]){
            p[fy]=fx;
            rank[fx]+=rank[fy];
        }else{
            p[fx] = fy;
            rank[fy]+=rank[fx];
        }
    }

    /**
     * 判断两个元素是否属于同一个集合：
     * 利用GetFather（）函数判断其最原始父亲节点是否相同
     * */
    bool isSameSet(int x, int y) {
        return GetFather(x)==GetFather(y);
    }
};
Union un;
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //输入重定向，输入数据将从in.txt文件中读取
    //freopen("out.txt","w",stdout); //输出重定向，输出数据将保存在out.txt文件中
    //srand(time(NULL));//有的OJ不能加这句话
    int N,M,i,j,z,a,b;
    char answer;
    cin>>N>>M;//有N个点，M次操作
    un.init(N+1);
    for(i=0;i<M;i++){//输入z,a,b;z==1代表把ab两个元素合并在一个集合，z==2表示问a,b是否在同一集合
        scanf("%d%d%d",&z,&a,&b);
        if(z==1){
            un.insMerge(a-1,b-1);
        }else if(z==2){
            printf("%c\n",un.isSameSet(a-1,b-1)?'Y':'N');
        }
    }
return 0;
}
