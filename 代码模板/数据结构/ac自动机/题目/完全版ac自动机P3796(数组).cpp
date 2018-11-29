#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;
char str[MAX],word[MAX];//strҪ���ҵ�����  word���뵥�� ģʽ��
const int kind=26;
struct ACautomaton{
    struct Node{
        int id,fail,son[kind];//id��������ڵ�Ϊ��β���ַ�����ţ���0��ʼ��-1����û��
        void init(){//�������ӽڵ����,һ����kind��
            id=-1;
            fail=0;
            memset(son,0,sizeof son);
        }
    };
    Node node[MAX];
    int size,slen;//���ڵ�
    string s[1000];//����
    int ind[1000];//ind[i]������id��i���ַ����ּ���
    void init(){//////////////////////����init����ʵ�ֲ�ͬ�ַ���ά��
        slen=size=0;
        node[0].init();//��ʼ�����ڵ�
        memset(ind,0,sizeof ind);
    }
    void insert(char *word){
        int c,now=0,len=strlen(word);
        for(int i=0;i<len;i++ ){
            c=word[i]-'a';//�ж��ǵڼ�����ĸ
            if(node[now].son[c]==0){//������ַ��ڵ㲻���ڣ���������
                node[now].son[c]=++size;
                node[size].init();
            }
            now=node[now].son[c];//ָ���ƶ�����һ��
        }
        node[now].id=slen;
        s[slen++]=word;
    }

    void buildFail(){//bfs�����ֵ�����fali·����һ��ԭ�򣺴������ڵ㿪ʼ��fali��·������ߵ��ĸ��ڵ���ӽڵ�͵�ǰ�ڵ���ĸ��ȣ�����������
        queue<int>que;
        for(int i=0;i<kind;i++){//�������ڵ�����
            int rs=node[0].son[i];
            if(rs){
                node[rs].fail=0;
                que.push(rs);
            }
        }
        while(!que.empty()){
            int now=que.front();//��ȡ���ף��ٳ�����
            que.pop();
            for(int i=0;i<kind;i++){//������ղŵĳ��Խڵ���ӽڵ��Ƿ����
                int &rs=node[now].son[i];
                if(rs){//��������ĸ����
                    node[rs].fail=node[node[now].fail].son[i];
                    que.push(rs);//���ѣ��������
                }else{
                    rs=node[node[now].fail].son[i];
                }
            }
        }
    }

    int query(char *str){
        int i,t,cnt=0,now=0,len=strlen(str);//��ȡ��������
        int maxCnt=-1;
        for(i=0;i<len;i++){
            now=node[now].son[str[i]-'a'];
            for(t=now;t;t=node[t].fail){
                if(node[t].id!=-1){
                    cnt++;
                    ind[node[t].id]++;
                    maxCnt=max(maxCnt,ind[node[t].id]);
                }
            }
        }
        printf("%d\n",maxCnt);
        for(i=0;i<slen;i++){
            if(maxCnt==ind[i]){
                printf("%s\n",s[i].c_str());
            }
        }
        return cnt;
    }
};
ACautomaton ac;

int main(int argc,char *argv[]){
	int n,i;
	while(~scanf("%d",&n),n>0){
        ac.init();
		for(i=0;i<n;i++){
			scanf("%s",word);
			ac.insert(word);
		}
		ac.buildFail();
		scanf("%s",str);
		ac.query(str);
	}
return 0;
}

