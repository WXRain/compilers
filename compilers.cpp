#include<iostream>
#include<string>
#include<fstream>
#include<conio.h>//����̨ͷ�ļ�
#include<stdlib.h>
#include<string.h>
using namespace std;

typedef struct node
{
	char left;
	char name;
	string right;
	node *next;
	string first;
	string follow;
	string select;
	int data;
}node,*linklist;



typedef struct stack//����ջ
{
	char *top;
	char *base;
	int max;
}stack;


void stackInit(stack &s)//ջ�ĳ�ʼ��
{
	s.base=new char;
	s.top=s.base;
	s.max=100;
}


void push(stack &s,char name)//��ջ����
{
	if(s.top-s.base==s.max)
	{
		cout<<"ջ����"<<endl;
		return ;
	}
	*s.top=name;
	s.top++;
}


void stackPrint(stack s)//���ջ�ĺ���
{
	char *a;
	a=s.base;
	while(a!=s.top)
	{
		cout<<*a;
		a++;
	}
}



void pop(stack &s)//��ջ����
{
	if(s.top==s.base)
	{
		cout<<"ջ�գ����ܳ�ջ";
		return ;
	}
	else s.top--;
}


////////////////////////////////////////////////�ʷ�����////////////////////////////////////////////////////////




void cifa()
{
	int k=0,f=0,num=0,x=0,i=0,e=0;
	char a[12],b[12];
	char c[50][50]={"include","string","iostream.h","if","while","void","int","main","cout","cin","for","else"};
	fstream file,f1,f2;
	file.open("yuan2.txt",ios::in);
	f1.open("t.txt",ios::out);
	f2.open("t2.txt",ios::out);
	char ch;
	ch=file.get();
	//while(ch==' ' || ch==10) ch=file.get();
	while(ch!=EOF)//�ж��Ƿ��ļ�����
	{
		while(ch==' ' || ch==10) ch=file.get();
		if((ch>='a' && ch<='z') || (ch>='A' && ch<='Z'))
		{
			while((ch>='a' && ch<='z') || (ch>='A' && ch<='Z') || ch=='.' || (ch>='0' && ch<='9'))
			{
				if(k<10)
				{
					a[k]=ch;
					k++;
					ch=file.get();
				}
				else ch=file.get();
				a[k]='\0';
			}
			for(i=0;i<50;i++)
			{
				if(!strcmp(a,c[i])) {e=1;break;}
			}
			if(e==1)
			{
				cout<<"1    ";
				cout<<a<<endl;
				if(!strcmp(a,"void"))
				f1<<"v";
				else if(!strcmp(a,"main"))
				f1<<"m";
				else if(!strcmp(a,"while"))
				{f1<<"w";
				f2<<" "<<"while"<<" ";}
				else if(!strcmp(a,"if"))
				{f1<<"i";
				f2<<" "<<"if"<<" ";}
				else if(!strcmp(a,"else"))
				{f1<<"e";
				f2<<" "<<"else"<<" ";}
				else if(!strcmp(a,"int"))
				{f1<<"t";
				f2<<" "<<"int"<<" ";}
			}                                    //���ڵ�һ��  ������
			else
			{
				cout<<"2    ";
				cout<<a<<endl;
				f1<<"g";
				f2<<" "<<a<<" ";
			}                                    //���ڵڶ���      ��ʶ��
			e=0;
			k=0;
		}

		else if(ch>='0' && ch<='9')
		{
			while((ch>='0' && ch<='9') || (ch=='.'))
			{
				if(ch=='.') x=1;//�����ж��ǲ��Ǹ������ı���
				b[f]=ch;
				f++;
				ch=file.get();
			}
			b[f]='\0';
			if(x==1)
			{
				cout<<"3    "<<b<<endl;
				f1<<"d";
				f2<<" ";
				f2<<b<<" ";
			}                                  //���ڵ�����    ������
			else
			{
				cout<<"4    "<<b<<endl;
				f1<<"d";
				f2<<" "<<b<<" ";
			}                                  //���ڵ�����         ����
			x=0;
			f=0;
		}


		else if(ch=='(' || ch==')'|| ch==';'|| ch=='"'|| ch=='#'|| ch=='<'|| ch=='>'|| ch=='{'|| ch=='}' || ch==',')
		{
			cout<<"5    "<<ch<<endl;//���ڵ�����              ���
			f1<<ch;
			f2<<" "<<ch<<" ";
			ch=file.get();
		}
		else if(ch=='='|| ch=='/'|| ch=='%'|| ch=='*'|| ch=='+'|| ch=='-' || ch=='!' || ch=='&')
		{
			cout<<"6    "<<ch<<endl;//���ڵ�����              �����
			f1<<ch;
			f2<<" "<<ch<<" ";
			ch=file.get();
		}
		else
		{
			cout<<"0    "<<ch<<endl;//���ڵ�����               ����
			f1<<ch;
			f2<<" "<<ch<<" ";
			ch=file.get();
		}
	}
	f1<<"#";
	f2<<" "<<"#";
}


////////////////////////////////////////////////////�﷨����/////////////////////////////////////////////////////




void linklistInsert(linklist &l,linklist a)//������Ĳ������
{
	linklist p;
	p=l;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=a;
	a->next=NULL;

}



void rl(linklist &wf)    //���ķ��ֳ�right���left�򣬲����������У��Ա��Ժ��ʹ��
{
	linklist a;
	char ch;
	fstream file;
	file.open("wenfa2.txt",ios::in);//�򿪱����ķ����ļ�
	ch=file.get();
	while(ch!=EOF)
	{
		while((ch==' ') || (ch=='\n')) ch=file.get();//�˿�
		if(((ch>='A') && (ch<='Z')) && (file.get()=='-') &&(file.get()=='>'))//ȡ��left��
		{
			a=new node;
			a->left=ch;
		}

		ch=file.get();
		while((ch!=10) && (ch!=EOF))//ȡ��right��
		{
			a->right=a->right+ch;
			ch=file.get();

		}
		linklistInsert(wf,a);//����ǰ���ķ���right���left����뵽wf������
	}

}


void rlPrint(linklist wf)//����ķ���right���left��ĺ���
{
	linklist p;
	p=wf;
	while(p->next!=NULL)
	{
		cout<<p->next->left<<"          "<<p->next->right<<endl;
		p=p->next;
	}
}


void linklistInit(linklist &l)//������ĳ�ʼ��
{
	l=new node;
	l->next=NULL;
}


int panduan(linklist wf)//�жϸ������ķ��Ƿ���LL��1��
{
	linklist p,q;
	char ch1,ch2;
	p=wf;
	while(p->next!=NULL)
	{
		q=p->next;
		ch1=p->next->right[0];
		while(q->next!=NULL)
		{
			if(p->next->left==q->next->left)
			{
				ch2=q->next->right[0];
				if (ch1==ch2)              //���ķ�����ݹ�
				{
					cout<<"���ķ�����LL��1���ķ�"<<endl;
					return 0;
					goto e;
				}
			}
			q=q->next;
		}
		p=p->next;
	}
	cout<<"���ķ���LL��1���ķ�"<<endl;//���ķ�û����ݹ�
	return 1;
e:;}


void fzjfCreat(linklist wf,linklist &fzjf)//�������ռ�������
{
	linklist p,q,r;
	r=new node;
	char ch;
	p=wf;
	q=fzjf;
	r->next=NULL;
	r->name=p->next->left;
	fzjf->next=r;

	while(p->next!=NULL)
	{
		ch=p->next->left;
		q=fzjf;
		while(q->next!=NULL)
		{
			if(q->next->name!=ch)   q=q->next;
			else break;
		}
		if(q->next!=NULL) ;//��ǰ�ķ��ռ����Ѿ��ڷ��ռ���������
		else               //��ǰ���ռ������ڷ��ռ��������У����뵽������
		{
			r=new node;
			r->name=ch;
			r->next=NULL;
			q->next=r;
		}
		p=p->next;
	}
}


void fzjfPrint(linklist fzjf)//��ӡ���ռ�������ĺ���
{
	linklist p;
	p=fzjf;
	while(p->next!=NULL)
	{
		cout<<p->next->name<<"  ";
		p=p->next;
	}
	cout<<endl;
}



////////////////////////////////////////////////first������⺯��///////////////////////////////////////////////////////////////


int First(linklist wf,char x,string &s)//������ռ���x��first��
{
	linklist p;
	p=wf;
	int i;
	int kong=1;
	while(p->next!=NULL)
	{
		if(p->next->left==x)
		{
			if (p->next->right[0]=='o') kong=0;           //���first�����пգ��򷵻�0
			else if(!(p->next->right[0]>='A' && p->next->right[0]<='Z'))//�����һ�����ռ�����ֱ�Ӽ��뵽first������
			{
				for(i=0;s[i]!='\0';i++)        //����first���е��ظ��ռ���
				{
					if(s[i]==p->next->right[0]) break;
				}
				if(s[i]=='\0')   s=s+p->next->right[0];
			}
			else First(wf,p->next->right[0],s);   //�����һ�����Ƿ��ռ��������õݹ麯�����ÿ�����ռ�����first��
		}
		p=p->next;
	}
	return kong;
}


void getFirst(linklist wf,linklist fzjf)//���ȫ���ķ��ռ���first���ĺ���
{
	linklist p,q;
	int kong;
	p=wf;
	q=fzjf;
	while(q->next!=NULL)
	{
		kong=First(p,q->next->name,q->next->first);//�ж��ٸ����ռ������͵��ö��ٴ�ȡfirst������
		if(kong==0) q->next->first=q->next->first+'o';
		q=q->next;
	}
}



void firstPrint(linklist fzjf)  //���first���ĺ���
{
	linklist p;
	p=fzjf;
	while(p->next!=NULL)
	{
		cout<<"FIRST("<<p->next->name<<")={";
		for(int i=0;p->next->first[i]!='\0';i++)
		{
			cout<<p->next->first[i];
			if(p->next->first[i+1]!='\0') cout<<",";//��ÿ��first�ռ�����ӡ�������ֱ�����һ��
		}
		cout<<"}"<<endl;
		p=p->next;
	}
}


//////////////////////////////////////////////////follow������⺯��/////////////////////////////////////////////////////////////////



void Follow(linklist wf,char x,string &s,char a)//������ռ���x��follow��,�ڴ˴���һ��a��־λY->gD  D->,Y  ���еݹ�ʱ��Ҫ�ж���ߵ��Ƿ�͸տ�ʼҪ�����һ����
{
	linklist p;
	char ch;
	p=wf;
	int i;
	int pd;
	size_t weizhi;
	if(x==wf->next->left)
	{
		for(i=0;s[i]!='\0';i++)
		{
			if(s[i]=='#')  break;
		}
		if(s[i]=='\0') s=s+'#';
		else ;
	}
	while(p->next!=NULL)
	{
		weizhi=p->next->right.find(x);//����Ҫ�ҵķ��ռ������ڵ�λ��
		if(weizhi<100)
		{
			ch=p->next->right[weizhi+1];
			if(ch=='\0' && p->next->left!=x && p->next->left!=a)   Follow(wf,p->next->left,s,x);//���Ҫ��ķ��ռ�����Ϊ�գ���left��follow
			else if(ch>='A' && ch<='Z')   //���Ҫ��ķ��ռ�����Ϊ���ռ���
			{
				pd=First(wf,ch,s);//����ռ�����first�����ж��Ƿ��пճ���
				if(pd==0)  Follow(wf,ch,s,-1);//����пճ��֣��Ͷ�������ռ�����follow
			}
			else if(ch!='\0')                             //������ռ���
			{
				for(i=0;s[i]!='\0';i++)//���ز�����follow����
				{
					if(ch==s[i]) break;
				}
				if(s[i]=='\0')
 					s=s+ch;
			}
		}
		p=p->next;
	}
}


void getFollow(linklist wf,linklist fzjf)//���ȫ���ķ��ռ���follow���ĺ���
{
	linklist p,q;
	p=wf;
	q=fzjf;
	while(q->next!=NULL)
	{
		Follow(p,q->next->name,q->next->follow,-1);//�ж��ٸ����ռ������͵��ö��ٴ�ȡfollow������
		q=q->next;
	}
}



void followPrint(linklist fzjf)  //���first���ĺ���
{
	linklist p;
	p=fzjf;
	while(p->next!=NULL)
	{
		cout<<"FOLLOW("<<p->next->name<<")={";
		for(int i=0;p->next->follow[i]!='\0';i++)
		{
			cout<<p->next->follow[i];
			if(p->next->follow[i+1]!='\0') cout<<",";//��ÿ��follow�ռ�����ӡ�������ֱ�����һ��
		}
		cout<<"}"<<endl;
		p=p->next;
	}
}



////////////////////////////////////////////////////��select������///////////////////////////////////////////////////////


void getSelect(linklist wf,linklist fzjf)//��select���ĺ���
{
	linklist p,q;
	p=wf;
	q=fzjf;
	int i=0;
	while(p->next!=NULL)
	{
d:		if(p->next->right[i]>='A' && p->next->right[i]<='Z') //�����һ���Ƿ��ռ���
		{
			q=fzjf;
			while(q->next!=NULL)
			{
				if(q->next->name==p->next->right[i]) //�ڷ��ռ������ҵ�������ռ������Ͷ�������ռ�����first�����뵽follow����
				{
					p->next->select=p->next->select+q->next->first;
					for(int j=0;q->next->first[j]!='\0';j++)
					{
						if(q->next->first[j]=='o')		//�������ʽ�Ҳ���һ����first�����п�
						{
							if(q->next->first[j+1]>='a' && q->next->first[j+1]<='z')//�����һ�����ռ�����ֱ�Ӽ���select��
							{
								p->next->select=p->next->select+q->next->first[j+1];
							}
							else				//�����һ�������ռ���
							{
								i++;			//����һ�����ռ�����first��������selec����
								goto d;
							}
						}
					}
					break;
				}
				else q=q->next;
			}
		}
		else if(p->next->right[i]=='o')//�����һ���ַ��ǿգ���������left���follow��
		{
			q=fzjf;
			while(q->next!=NULL)
			{
				if(q->next->name==p->next->left)
				{
					p->next->select=q->next->follow;
					break;
				}
				else q=q->next;
			}
		}
		else p->next->select=p->next->right[i];//������ռ�����ֱ�ӽ��ռ�������select����
		p=p->next;
	}
}




void selectPrint(linklist wf)
{
	linklist p;
	p=wf;
	while(p->next!=NULL)
	{
		cout<<"SELECT("<<p->next->left<<"->"<<p->next->right<<")={";
		for(int i=0;p->next->select[i]!='\0';i++)
		{
			cout<<p->next->select[i];
			if(p->next->select[i+1]!='\0') cout<<",";
		}
		cout<<"}"<<endl;
		p=p->next;
	}
}



///////////////////////////////////////////����Ԥ�������ĺ���//////////////////////////////////////////////////

void zjfCreat(linklist wf,string &zjf)//������е��ռ���
{
	linklist p;
	for(p=wf;p->next!=NULL;p=p->next)
	{
		int i;
		for(i=0;p->next->right[i]!='\0' && p->next->right[i]!='o';i++)
		{
			if(p->next->right[i]>='A' && p->next->right[i]<='Z');
			else
			{
				int j;
				for(j=0;zjf[j]!='\0';j++)//�����ظ����ռ���
				{
					if(zjf[j]==p->next->right[i]) break;
				}
				if(zjf[j]=='\0') zjf=zjf+p->next->right[i];
			}
		}
	}
	zjf=zjf+"#";
}

void zjfPrint(string zjf)//��ʾ���е��ռ����ĺ���
{
	int i=0;
	while(zjf[i]!='\0')
	{
		cout<<zjf[i]<<"  ";
		i++;
	}
	cout<<endl;
}


int getFzjfNumber(linklist a,char name)//ȡ�����ռ��������
{
	linklist p;
	int i=0;
	p=a;
	while(p->next!=NULL)
	{
		if(p->next->name==name) break;
		i++;
		p=p->next;
	}
	return i;
}

int getZjfNumber(string s,char name)//ȡ���ռ��������
{
	int i=0;
	while(s[i]!='\0')
	{
		if(s[i]==name) break;
		i++;
	}
	return i;
}


string ** predictTable(linklist wf,linklist fzjf,string zjf)//����Ԥ�������
{
	int fzjfNo,zjfNo,line,row;
	linklist p;
	int i,j;
	char ch1,ch2;
	line=getFzjfNumber(fzjf,' ');//����ĵ�һ�������Ƿ��ռ���������
	line--;
	row=getZjfNumber(zjf,' ');//����ĵڶ����������ռ����������
	row--;
	string **table;
	table=new string *[line+1];//��̬�����ά����
	for(i=0;i<=line;i++)
	{
		table[i]=new string [row+1];
	}
	for(i=0;i<=line;i++)//��Ԥ�����������г�ʼ��
	{
		for(j=0;j<=row;j++)
		{
			table[i][j]="-1";
		}
	}
	p=wf;
	while(p->next!=NULL)
	{
		ch1=p->next->left;
		fzjfNo=getFzjfNumber(fzjf,ch1);//ȡ������ʽ��ÿ�����ռ����ڷ��ռ��������
		for(int selectNumber=0;p->next->select[selectNumber]!='\0';selectNumber++)//ȡ���ò���ʽ��select��
		{
			ch2=p->next->select[selectNumber];
			zjfNo=getZjfNumber(zjf,ch2);
			table[fzjfNo][zjfNo]=p->next->right;
			cout<<ch1<<"("<<ch2<<")"<<"="<<table[fzjfNo][zjfNo]<<endl;//���ݸ�select����Ԥ���������и�ֵ
		}
		p=p->next;
	}

/*	for(i=0;i<=line;i++)
	{
		for(j=0;j<=row;j++)
		{
			cout<<table[i][j]<<" ";
		}
	}*/
	return table;
}


void analysis(string **table,linklist wf,linklist fzjf,string zjf)
{
	cout<<"���\tջ\t\t\t\t\t�ķ�\t\t\tʣ�����봮"<<endl;
	int num=1;
	stack s;
	int a,b;
	stackInit(s);
	push(s,'#');
	linklist search;
	push(s,wf->next->left);
	fstream f;
	f.open("t.txt",ios::in);
	string ss;
	f>>ss;
	//cout<<ss<<endl;
	int i=0,u;
	cout<<num<<"\t";
	num++;
	stackPrint(s);
	cout<<endl;
	while(ss[i]!='#')
	{
		if(*(s.top-1)>='A' && *(s.top-1)<='Z')
		{
			a=getFzjfNumber(fzjf,*(s.top-1));
			b=getZjfNumber(zjf,ss[i]);
			if(a>getFzjfNumber(fzjf,' ')-1 || b>getZjfNumber(zjf,' ')-1)
			{
				cout<<endl<<"���ķ����ܲ��������ڵ�ǰ����"<<endl;;
				return;
			}
			if(table[a][b]=="-1")
			{
				cout<<endl<<"ERROR"<<endl;
				return ;
			}
			else
			{
				pop(s);
				int j;
				for(j=0;table[a][b][j]!='\0';j++);
				if(table[a][b]=="o")
				{
					cout<<num<<"\t";
					num++;
					stackPrint(s);
					cout<<"\t\t\t\t\t\t"<<*(s.top)<<"->o";
					cout<<"\t\t";
					for(u=i;ss[u]!='\0';u++)
					{
						cout<<ss[u];
					}
					cout<<endl;
				}
				else
				{
					for(j=j-1;j!=0;j--)
					{
						push(s,table[a][b][j]);
					}
					push(s,table[a][b][j]);
					cout<<num<<"\t";
					num++;
					stackPrint(s);
					cout<<"\t\t\t\t\t\t";
					for(search=wf;search->next!=NULL;search=search->next)
					{
						if(search->next->right==table[a][b])
						break;
					}
					cout<<search->next->left<<"->"<<table[a][b];



					cout<<"\t\t";
					for(u=i;ss[u]!='\0';u++)
					{
						cout<<ss[u];
					}
					cout<<endl;



				}
			}
		}
		else
		{
			if(*(s.top-1)==ss[i])
			{
				//stackPrint(s);
				pop(s);
				i++;
				cout<<num<<"\t";
				num++;
				stackPrint(s);
				cout<<"\t\t\t\t\t\t��ȥ"<<ss[i-1];
				cout<<"\t\t";
				for(u=i;ss[u]!='\0';u++)
				{
					cout<<ss[u];
				}

				cout<<endl;
			}
			else
			{
				cout<<endl<<"ERROR"<<endl;
				return ;
			}
		}
	}
	if(*s.base=='#' && ss[i]=='#')  cout<<"�����ɹ�"<<endl;

}






/////////////////////////////////////////////////������/////////////////////////////////////////////////////////


void yufa()
{
	int pd;
	string zjf,**table;
	linklist wf;//����һ���ķ�������
	linklist fzjf;//����һ�����ռ�������
	linklistInit(fzjf);
	linklistInit(wf);
	cifa();//��Դ������дʷ�����
	rl(wf);//�Ը������ķ�����right���left��ķָ�
	cout<<"������������ķ���������"<<endl;
	getch();
 	system("cls");
	cout<<"���ķ��ķ���Ϊ��"<<endl<<"left     right"<<endl;
	rlPrint(wf);//���ָ��Ľ����ʾ����
	pd=panduan(wf);
	if(pd==1)//�����ǰ�ķ���LL��1���ķ�
	{
		getch();
		system("cls");
		fzjfCreat(wf,fzjf);
		fzjfPrint(fzjf);
		cout<<"first��Ϊ��"<<endl;
		getFirst(wf,fzjf);//ȡ�����з��ռ�����first��
		firstPrint(fzjf);//��ʾ����first��
		cout<<"���������follow������"<<endl;
		getch();
		system("cls");
		fzjfPrint(fzjf);
		cout<<"follow��Ϊ��"<<endl;
		getFollow(wf,fzjf);//ȡ�����з��ռ�����follow��
		followPrint(fzjf);//��ʾ����follow��
		cout<<"���������select������"<<endl;
		getch();
		system("cls");
		cout<<"select��Ϊ��"<<endl;
		getSelect(wf,fzjf);
		selectPrint(wf);
		zjfCreat(wf,zjf);//������е��ռ���
		//zjfPrint(zjf);//������е��ռ���
		cout<<"�������������Ԥ���������"<<endl;
		getch();
		system("cls");
		table=predictTable(wf,fzjf,zjf);
		cout<<"������������������̡���"<<endl;
		getch();
		system("cls");
		analysis(table,wf,fzjf,zjf);
	}

}


void siyuan()
{
	fstream f1;
	f1.open("t1.txt",ios::out);
	stack x;
	stackInit(x);
	fstream f;
	f.open("t2.txt",ios::in);
	string s,mid,op,equ,mid1;
	int flag=0,jumpIf=-1,jumpWh=-1;
	f>>s;
	f>>s;
	f>>s;
	f>>s;
	while(s!="#")
	{
e:		if(s=="int")
		{
			f>>s;
			cout<<"\t"<<"("<<"int,"<<s<<","<<"$,$"<<")"<<endl;
			f>>s;
			if(s==",")
			{
				s="int";
				goto e;
			}
		}

		else if(s=="+" || s=="-" || s=="*" || s=="/")
		{
			op=s;
			f>>s;
			cout<<"\t"<<"("<<op<<","<<mid1<<","<<s<<","<<"AX"<<")"<<endl;
			if(op=="+")
			{
				f1<<"add "<<mid1<<","<<s<<";"<<endl;
			}
			else if(op=="-")
			{
				f1<<"sub "<<mid1<<","<<s<<";"<<endl;
			}
			else if(op=="*")
			{
				f<<"mul "<<mid1<<","<<s<<";"<<endl;
			}
			else if(op=="/")
			{
				f<<"div "<<mid1<<","<<s<<";"<<endl;
			}
			cout<<"\t"<<equ<<endl;
			f1<<"mov "<<mid<<","<<mid1<<";"<<endl;
		}


		else if(s=="=")
		{
			equ="(=,"+mid+",AX,"+"$"+")";
			f>>s;
			mid1=s;
			if(s>="-65535" && s<="65535")
			{
				cout<<"\t(=,"<<mid<<","<<s<<",$)"<<endl;
				f1<<"mov "<<mid<<","<<s<<";"<<endl;
			}
			f>>s;

		}

		else if(s=="if")
		{
			f>>s;
			f>>s;
			mid=s;
			f>>s;
			op=s;
			f>>s;
			push(x,flag+2);
			push(x,flag+1);
			push(x,flag);
			if(op==">")
			{
				cout<<"\t("<<op<<","<<mid<<","<<s<<",T(l"<<flag<<"))"<<endl;
				f1<<"cmp "<<mid<<","<<s<<";"<<endl;
				f1<<"ja "<<"l"<<flag<<endl;//���������ת��flag
				flag++;
				cout<<"\t("<<op<<","<<mid<<","<<s<<",F(l"<<flag<<"))"<<endl;
				f1<<"jbe "<<"l"<<flag<<endl;
			}
			else if(op=="<")
			{
				cout<<"\t("<<op<<","<<mid<<","<<s<<",T(l"<<flag<<"))"<<endl;
				f1<<"cmp "<<mid<<","<<s<<";"<<endl;
				f1<<"jb "<<"l"<<flag<<endl;
				flag++;
				cout<<"\t("<<op<<","<<mid<<","<<s<<",F(l"<<flag<<"))"<<endl;
				f1<<"jae "<<"l"<<flag<<endl;
			}
			flag++;
			while(s!="{") f>>s;
			printf("l%d\n",*(x.top-1));
			f1<<"l"<<(int)(*(x.top-1))<<endl;
			cout<<endl;
			pop(x);
			f>>s;
			flag++;
			jumpIf=1;
		}
		else if(s=="else")
		{
			f>>s;
			f>>s;
			jumpIf=0;
		}

		else if(s=="while")
		{
			f>>s;
			f>>s;
			mid=s;
			f>>s;
			op=s;
			f>>s;
			push(x,flag+2);
			push(x,flag);
			push(x,flag+1);
			printf("l%d\n",*(x.top-2));
			f1<<"l"<<(int)(*(x.top-2))<<endl;
			cout<<endl;
		/*	cout<<"\t("<<op<<","<<mid<<","<<s<<",T(l"<<flag+1<<"))"<<endl;
			flag++;
			cout<<"\t("<<op<<","<<mid<<","<<s<<",F(l"<<flag+1<<"))"<<endl;*/
			if(op==">")
			{
				cout<<"\t("<<op<<","<<mid<<","<<s<<",T(l"<<flag+1<<"))"<<endl;
				f1<<"cmp "<<mid<<","<<s<<";"<<endl;
				f1<<"ja "<<"l"<<flag+1<<endl;//���������ת��flag
				flag++;
				cout<<"\t("<<op<<","<<mid<<","<<s<<",F(l"<<flag+1<<"))"<<endl;
				f1<<"jbe "<<"l"<<flag+1<<endl;
			}
			else if(op=="<")
			{
				cout<<"\t("<<op<<","<<mid<<","<<s<<",T(l"<<flag+1<<"))"<<endl;
				f1<<"cmp "<<mid<<","<<s<<";"<<endl;
				f1<<"jb "<<"l"<<flag+1<<endl;
				flag++;
				cout<<"\t("<<op<<","<<mid<<","<<s<<",F(l"<<flag+1<<"))"<<endl;
				f1<<"jae "<<"l"<<flag+1<<endl;
			}
			flag++;
			jumpWh=flag;
			while(s!="{") f>>s;
			printf("l%d\n",*(x.top-1));
			f1<<"l"<<(int)(*(x.top-1))<<endl;
			cout<<endl;
			pop(x);
			f>>s;
			flag++;
		}


		else//;����}
		{
			if(s=="}" && x.top!=x.base)
			{
				if(jumpIf==1)
				{
					cout<<"\t(jump,";
					printf("l%d",*(x.top-2));
					cout<<",$,$)"<<endl;
					f1<<"jump "<<"l"<<(int)(*(x.top-1))<<";"<<endl;
					printf("l%d\n",*(x.top-1));
					f1<<"l"<<(int)(*(x.top-1))<<endl;
					jumpIf=-1;
				}
				else if(jumpIf==0)
				{
					printf("l%d\n",*(x.top-1));
					f1<<"l"<<(int)(*(x.top-1))<<endl;
					jumpIf=-1;

				}
				if(jumpWh==*(x.top-1))
				{
					cout<<"\t(jump,";
					printf("l%d",*(x.top));
					cout<<",$,$)"<<endl;
					f1<<"jump l"<<(int)(*(x.top))<<";"<<endl;
					printf("l%d\n",*(x.top-1));
					f1<<"l"<<(int)(*(x.top-1))<<endl;
					jumpWh=-1;

				}

				cout<<endl;
				pop(x);
			}
				mid=s;
				f>>s;
		}

	}
}

void huibian()
{
	fstream f;
	f.open("t1.txt",ios::in);
	char ch;
	ch=f.get();
	while(ch!=EOF)
	{
		cout<<ch;
		ch=f.get();
	}
}



int main()
{

	yufa();
	cout<<"�����������������Ԫʽ"<<endl;
	getch();
	system("cls");
	siyuan();
	system("pause");
	system("cls");
	huibian();
	return 0;
}
