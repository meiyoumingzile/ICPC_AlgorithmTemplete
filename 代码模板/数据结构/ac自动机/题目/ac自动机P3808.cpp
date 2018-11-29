#include<bits/stdc++.h>
//#include<windows.h>
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
        int cnt;//�������������Ϊ��β
        Node *dan,*fail,*son[kind];
        Node(){//�������ӽڵ����,һ����kind��
            cnt=0;
            fail=dan=NULL;
            for(int i=0;i<kind;i++)
                son[i]=NULL;
        }
    };
    Node *root;//���ڵ�
    char sonChar[kind];////���������Сд��ĸ
    ACautomaton(int n){
        init();
        root=new Node();
    }
    void init(){//////////////////////����init����ʵ�ֲ�ͬ�ַ���ά��
        for(int i=0;i<kind;i++){//Ĭ����Сд��ĸ
            sonChar[i]='a'+i;
        }
    }
    void insert(char *word){
         int c;
         int len=strlen(word);
         Node *now=root;
         for(int i=0;i<len;i++ ){
             c=word[i]-'a';//�ж��ǵڼ�����ĸ
             if(!now->son[c]){//������ַ��ڵ㲻���ڣ���������
                now->son[c]=new Node();//��������
             }
             now=now->son[c];//ָ���ƶ�����һ��
         }
         now->cnt++;
    }

    void buildFail(){//bfs�����ֵ�����fali·����һ��ԭ�򣺴������ڵ㿪ʼ��fali��·������ߵ��ĸ��ڵ���ӽڵ�͵�ǰ�ڵ���ĸ��ȣ�����������
        queue<Node*>que;
        Node *now,*p,*next;
        root->fail=root;
        for(int i=0;i<kind;i++){//�������ڵ�����
            if(root->son[i]){
                root->son[i]->fail=root;
                que.push(root->son[i]);
            }
        }
        while(!que.empty()){
            now=que.front();//��ȡ���ף��ٳ�����
            que.pop();
            for(int i=0;i<kind;i++){//������ղŵĳ��Խڵ���ӽڵ��Ƿ����
                next=now->son[i];
                p=now->fail;
                if(next){//��������ĸ����
                    next->fail=p->son[i];
                    que.push(next);//���ѣ��������
                }else{
                    now->son[i]=p->son[i];
                }
            }
        }
    }

    int query(char *str){
        int i=0,cnt=0,index,j=0,len=strlen(str);//��ȡ��������
        Node *now=root,*t;
        for(i=0;i<len;i++){
            index=str[i]-'a';//���ǻ�ȡ�ڼ���
            now=now->son[index];
            for(t=now;t&&t->cnt!=-1;t=t->fail){
                cnt+=t->cnt;
                t->cnt=-1;
            }
        }
        return cnt;
    }
};


int main(int argc,char *argv[]){
	int n,i;
	while(~scanf("%d",&n)){
		ACautomaton *ac=new ACautomaton(n);
		for(i=0;i<n;i++){
			scanf("%s",word);
			ac->insert(word);
		}
		ac->buildFail();
		scanf("%s",str);
		printf("%d\n",ac->query(str));
		delete ac;
	}
return 0;
}

