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
        int id;//������ڵ�Ϊ��β���ַ�����ţ���0��ʼ��-1����û��
        Node *fail,*son[kind];
        Node(Node *r){//�������ӽڵ����,һ����kind��
            id=-1;
            fail=r;
            for(int i=0;i<kind;i++)
                son[i]=r;
        }
    };
    Node *root;//���ڵ�
    string s[1000];//����
    int ind[1000];//ind[i]������id��i���ַ����ּ���
    int slen;
    ACautomaton(int n){
        init();
    }
    void init(){//////////////////////����init����ʵ�ֲ�ͬ�ַ���ά��
        root=new Node(NULL);
        root->fail=root;
        slen=0;
        memset(ind,0,sizeof ind);
        for(int i=0;i<kind;i++){//Ĭ����Сд��ĸ
            root->son[i]=root;
        }
    }
    void insert(char *word){
        int c;
        int len=strlen(word);
        Node *now=root;
        for(int i=0;i<len;i++ ){
            c=word[i]-'a';//�ж��ǵڼ�����ĸ
            if(now->son[c]==root){//������ַ��ڵ㲻���ڣ���������
                now->son[c]=new Node(root);
            }
            now=now->son[c];//ָ���ƶ�����һ��
        }
        now->id=slen;
        s[slen++]=word;
    }

    void buildFail(){//bfs�����ֵ�����fali·����һ��ԭ�򣺴������ڵ㿪ʼ��fali��·������ߵ��ĸ��ڵ���ӽڵ�͵�ǰ�ڵ���ĸ��ȣ�����������
        queue<Node*>que;
        Node *now,*p,*next;
        for(int i=0;i<kind;i++){//�������ڵ�����
            if(root->son[i]!=root){
                root->son[i]->fail=root;
                que.push(root->son[i]);
            }
        }
        while(!que.empty()){
            now=que.front();//��ȡ���ף��ٳ�����
            que.pop();
            for(int i=0;i<kind;i++){//������ղŵĳ��Խڵ���ӽڵ��Ƿ����
                if(now->son[i]!=root){//��������ĸ����
                    now->son[i]->fail=now->fail->son[i];
                    que.push(now->son[i]);//���ѣ��������
                }else{
                    now->son[i]=now->fail->son[i];
                }
            }
        }
    }

    int query(char *str){
        int i,cnt=0,len=strlen(str);//��ȡ��������
        Node *now=root,*t;
        int maxCnt=-1;
        for(i=0;i<len;i++){
            now=now->son[str[i]-'a'];
            for(t=now;t!=root;t=t->fail){
                if(t->id!=-1){
                    cnt++;
                    ind[t->id]++;
                    maxCnt=max(maxCnt,ind[t->id]);
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


int main(int argc,char *argv[]){
	int n,i;
	while(~scanf("%d",&n),n>0){
        ACautomaton *ac=new ACautomaton(n);
		for(i=0;i<n;i++){
			scanf("%s",word);
			ac->insert(word);
		}
		ac->buildFail();
		scanf("%s",str);
		ac->query(str);
        delete ac;
	}
return 0;
}

