#include<bits/stdc++.h>
//#include<windows.h>
using namespace std;
#define ll long long
#define inf 1e-5
const int inv2=500000004;
const int INF=2147483647;
const int MAX=1000010;
const int mod=1e9+7;


char word[100];//���뵥�� ģʽ��
char str[1000010];// ��Ҫ���ҵ� ����
struct ACautomaton{
    const int kind=26;
    vector<char>sonChar;////���������Сд��ĸ
    map<char,int>sonInd;//����ĳ���ַ��ڵڼ���
    struct Node{
        string char_end;
        Node *danger=NULL;
        Node **son;//Trieÿ���ڵ��26���ӽڵ㣬NULL��ʾ������
        Node *fail=NULL; //ʧ��ָ��
        Node(int cnt){//�������ӽڵ����,һ����kind��
            son=new Node*[cnt];
            char_end="";
            for(int i=0;i<cnt;i++)
                son[i]=NULL;
        }
    };


    Node *root;//���ڵ�
    ACautomaton(int n){
        s=new string[n];
        this->init();
        root=new Node(kind);
    }


    string *s;
    map<string,int>letter_number;//��¼ĳ�����ʸ���

    int s_i=0;
    //map<string,int>pos;//��¼λ��

    void init(){//////////////////////����init����ʵ�ֲ�ͬ�ַ���ά��
        for(int i=0;i<kind;i++){//Ĭ����Сд��ĸ
            sonChar[i]='a'+i;
            sonInd[sonChar[i]]=i;
        }
    }
    void AC_insert(char *word){
         int index;
         int len=strlen(word);
         Node *tree=root;
         for(int i=0;i<len;i++ ){
             index=word[i]-'a';//�ж��ǵڼ�����ĸ
             if(!tree->son[index]){//������ַ��ڵ㲻���ڣ���������
                Node *newNode=new Node(kind);
                tree->son[index]=newNode;//��������
             }
             tree=tree->son[index];//ָ���ƶ�����һ��
         }
         //pos[word]=s_i;
         tree->char_end=s[s_i++]=word;  //���ʽ�β�ڵ�count+1�����
    }

    void build_ac_automation(){//bfs�����ֵ�����fali·����һ��ԭ�򣺴������ڵ㿪ʼ��fali��·������ߵ��ĸ��ڵ���ӽڵ�͵�ǰ�ڵ���ĸ��ȣ�����������
        queue<Node*>Q;
        Q.push(root);//��ͷ���
        Node *que_temp,*p,*tree;
        while(!Q.empty()){
            que_temp=Q.front();//��ȡ���ף��ٳ�����
            Q.pop();
            for(int i=0;i<kind;i++){//������ղŵĳ��Խڵ���ӽڵ��Ƿ����
                if(que_temp->son[i]!=NULL){//��������ĸ����
                    if(que_temp==root){//����Ǹ����ӵĽڵ��Ǹ���������fali·��ֱ�ӵ����Ϳ���
                        que_temp->son[i]->fail=root;
                    }else{//ע��Ҫ����fali·�ǵ�ǰ�����е��ӽڵ�����ǵ�ǰ���ԵĽڵ�
                        p=que_temp->fail;//ע��Ҫ����fali·�ǵ�ǰ�����е��ӽڵ�����ǵ�ǰ���Եģ����Ը��ݹ���Ӧ�����ŵ�ǰfail��
                        while(p!=NULL){//ֱ��p�ǿսڵ�Ϊֹ�������ڵ��fail���ǿյ�
                           if(p->son[i]!=NULL){//���ĳ���ڵ���ӽڵ��Ҫ�ҵĽڵ���ͬ������������
                               que_temp->son[i]->fail=p->son[i];
                               break;
                           }
                           p=p->fail;//��������fail��
                        }
                        if(p==NULL){//�������������while���˸��ڵ㻹û���ҵ�,��˵��Ӧ��ֱ��ȥ���Ӹ��ڵ�ͺ���
                            que_temp->son[i]->fail=root;
                        }else if(que_temp->son[i]->fail->char_end!=""&&que_temp->son[i]->char_end==""){
                            que_temp->son[i]->danger=que_temp->son[i]->fail;
                        }
                    }
                    Q.push(que_temp->son[i]);//���ѣ��������
                 }
             }
         }
    }

    int query(){
        int i=0,cnt=0,index,j=0,
            len=strlen(str);//��ȡ��������
        Node *p=root;
        for(i=0;i<len;i++){
            index=str[i]-'a';//���ǻ�ȡ�ڼ���
            Node *nowDanger=p;
            while(nowDanger->danger!=NULL){
                letter_number[nowDanger->danger->char_end]++;
                cnt++;
                nowDanger=nowDanger->danger;
            }
            while(p->son[index]==NULL&&p!=root)//���������ǰ��ĸ�ڷǸ�ĳ�ڵ�ķֲ��ﲻ���ڣ���������ֱ�ӻظ���������fail·�߼���ƥ�䣬����kmp����son������
                p=p->fail;
            p=p->son[index];//�ҵ���pָ��ýڵ㣬��������ƥ��һ�����Ƿ�ɹ�����һ�а�
            if(p==NULL)//������˸���û�У�������û�ҵ�Ҳ���������son[index]�ǿյģ�ֻ�ܴӸ���
                p=root;
            Node *temp=p;//ƥ��ýڵ������ʧ��ָ����ݣ��ж������ڵ��Ƿ�ƥ��
            while(temp!=root&&temp->char_end!=""){//�ص����˽���
                letter_number[temp->char_end]++;
                cnt++;
                temp=temp->fail;//����ʧ��ָ�����Ѱ����һ�����������Ľڵ�
            }
        }
        return cnt;
    }
    void print(int n){
        for(int i=0;i<n;i++){
            cout<<s[i];
            printf("  %d\n",letter_number[s[i]]);
        }
    }
};


int main(int argc,char *argv[]){
    //freopen("in.txt","r",stdin); //�����ض����������ݽ���in.txt�ļ��ж�ȡ
    //freopen("out.txt","w",stdout); //����ض���������ݽ�������out.txt�ļ���
    //srand(time(NULL));//�е�OJ���ܼ���仰
    	int n,i;
	while(~scanf("%d",&n),n>0){
        ACautomaton *ac=new ACautomaton(n);
		for(i=0;i<n;i++){
			scanf("%s",word);
			ac-> AC_insert(word);
		}
		ac->build_ac_automation();
		scanf("%s",str);
		ac->query();
        delete ac;
	}
return 0;
}

