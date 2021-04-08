#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;////2139062143
const int MAX=2000010;
const int mod=1e9+7;

const int CHARCNT=26;
inline int toInt(const char &a){
    return a-'a';
}
struct PAM{
    const int r0=0,r1=1;
    int size,last;//last����ǰ���һ���ڵ�
    char *str;
    struct Node{
        int fail,son[CHARCNT];//failָ���son����,son���Ϊ����ָ��r0,��Ϊr0=0
        int len;//����Ӹ��ߵ���ǰ�ڵ��ַ����������ɵĻ��Ĵ��ĳ���
        int num;//�����Ե�ǰ�ڵ�Ϊ��ͷ�ı���������ַ�λ�ý�β�Ļ��ĺ�׺����������abba��s[3]=��a����num��2

    };
    Node tree[MAX];
    bool init(char *str){//����һ�����Ĵ�
        int i,len=strlen(str);
        for(i=0;i<len/2&&str[i]==str[len-i-1];i++);
        if(i<len/2){//�ж��ǲ��ǻ��Ĵ�
            return false;
        }
        this->str=str;
        insert(str);
        init();
        return true;
    }
    void init(){
        last=0;
        size=2;
        tree[0].fail=1;//fail[0]ָ��������
        tree[1].fail=0;//fail[1]ָ��0
        tree[0].len=0;
        tree[1].len=-1;//�����ڵ��PAM��-1
        tree[0].num=0;
        tree[1].num=0;//��ʼ���numΪ0
    }
    int getFail(int now,int i){//�õ������i���ַ�ʱ��now��fail��λ�ã�i��0��ʼ
        while(i-tree[now].len-1<0||str[i-tree[now].len-1]!=str[i])
            now=tree[now].fail;
        return now;
    }
    void insert(char *s){//����s�ַ����ĵڼ���λ��
        int i,len=strlen(s);
        for(i=0;i<len;i++){
            insert(s[i],i);
        }
    }
    void insert(char a,int i){//�����ַ�
        int pos=getFail(last,i);
        int k=toInt(a);
        str[i]=a;
        Node &posNode=tree[pos];
        if(!posNode.son[k]){//û�о��½�һ��
            Node &newNode= tree[size++];   //��posNode���½��ڵ㣬αָ���������½��ڵ㣬newNodeΪ�½ڵ����ã������newNode���Ը�ֵ
        	newNode.fail=tree[getFail(posNode.fail,i)].son[k];//ʧ��ָ��ָ��
        	posNode.son[k]=size-1;//posNode�Ķ���ָ���½ڵ�ĵ�ַ
        	newNode.len=posNode.len+2;//�½ڵ��lenΪ����+2����Ϊһ���ڵ��������һ���ַ���ǰ�����һ���ַ�
            newNode.num=tree[newNode.fail].num+1;//��ǰ�ַ�Ϊ��β�Ĳ�ͬ�Ļ��Ĵ���������������failָ����ָ�ڵ��num+1
		}//�����ڽ����㣬����ֱ���߹�ȥ
        last=posNode.son[k];
    }

};
PAM pam;

char str[MAX];
int main(int argc,char *argv[]){
	int i,j,k,t,T,n,m,len,ans;
    scanf("%s",str);
    len=strlen(str);
    pam.init();
    pam.str=str;
    k=0;
    for(i=0;i<len;i++){
        if(i)
            str[i]=(str[i]-97+k)%26+97;
        pam.insert(str[i],i);
        k=pam.tree[pam.last].num;
        printf("%d%c",k,i==len-1?'\n':' ');
    }

return 0;
}

