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
     * ���鼯�ĳ�ʼ����
     * ����p�е�Ԫ�����ʼideʱ���Ƕ���������Ҳ����ֻ�и��ڵ�
     * ����������p���±�i��ʾ�ڵ㣬��p[i]��ֵ��ʾi�ڵ�ĸ���
     * �ڵ㣻rank[i]=1��ʾһ��ʼ�������ڵ�ĸ߶ȶ�Ϊ1
    **/
    void init(int n){//n�������������[0,n)
        for(int i=0;i<n;i++){
            p[i]=i;
            rank[i]=1;
        }
    }
    /**
     * ����Ԫ�����ڵļ��ϲ�����·��ѹ����
     * ������ҪƵ��ʹ��GetFather����������������ʱ�临�Ӷ������ṹӰ�죻
     * ��Ԫ�ؽ϶��ʱ�򣬼����˻���������GetFather()��ҪO(N)������
     * ��Ҫ��������Ż���ÿ�ε���GetFather������ʱ�򶼽�����Ԫ��ѹ����
     * ��ԭʼ���׽ڵ��ֱ���ӽڵ�
     * */
    int GetFather(int son) {
        if(p[son]!=son)
            p[son]=GetFather(p[son]);
        return p[son];
    }

    void merge(int x, int y){//��ͨ�ϲ�����y���x���������ܽ��Ͳ�ѯЧ�ʣ����ǿ��Կ��Ƹ��ڵ����ĸ�
        p[y]=x;
    }

    /**
     * ����rank��Ȩ��������ʽ���кϲ�
     * */
    void insMerge(int x, int y) {
        int fx=GetFather(x);
        int fy=GetFather(y);

        if(fx==fy) return;
        /**
         * rank[fx]�ϴ�˵����Խ�������ڵ㣬��
         * fy���ӵ���������ѹ��·��
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
     * �ж�����Ԫ���Ƿ�����ͬһ�����ϣ�
     * ����GetFather���������ж�����ԭʼ���׽ڵ��Ƿ���ͬ
     * */
    bool isSameSet(int x, int y) {
        return GetFather(x)==GetFather(y);
    }
};
Union un;
int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    int N,M,i,j,z,a,b;
    char answer;
    cin>>N>>M;//��N���㣬M�β���
    un.init(N+1);
    for(i=0;i<M;i++){//����z,a,b;z==1�����ab����Ԫ�غϲ���һ�����ϣ�z==2��ʾ��a,b�Ƿ���ͬһ����
        scanf("%d%d%d",&z,&a,&b);
        if(z==1){
            un.insMerge(a-1,b-1);
        }else if(z==2){
            printf("%c\n",un.isSameSet(a-1,b-1)?'Y':'N');
        }
    }
return 0;
}
