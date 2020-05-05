#include<iostream>
#include<string>
#include<fstream>
#include<conio.h>//控制台头文件
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



typedef struct stack//定义栈
{
	char *top;
	char *base;
	int max;
}stack;


void stackInit(stack &s)//栈的初始化
{
	s.base=new char;
	s.top=s.base;
	s.max=100;
}


void push(stack &s,char name)//入栈函数
{
	if(s.top-s.base==s.max)
	{
		cout<<"栈已满"<<endl;
		return ;
	}
	*s.top=name;
	s.top++;
}


void stackPrint(stack s)//输出栈的函数
{
	char *a;
	a=s.base;
	while(a!=s.top)
	{
		cout<<*a;
		a++;
	}
}



void pop(stack &s)//出栈函数
{
	if(s.top==s.base)
	{
		cout<<"栈空，不能出栈";
		return ;
	}
	else s.top--;
}


////////////////////////////////////////////////词法分析////////////////////////////////////////////////////////




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
	while(ch!=EOF)//判断是否到文件结束
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
			}                                    //属于第一类  保留字
			else
			{
				cout<<"2    ";
				cout<<a<<endl;
				f1<<"g";
				f2<<" "<<a<<" ";
			}                                    //属于第二类      标识符
			e=0;
			k=0;
		}

		else if(ch>='0' && ch<='9')
		{
			while((ch>='0' && ch<='9') || (ch=='.'))
			{
				if(ch=='.') x=1;//增加判断是不是浮点数的变量
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
			}                                  //属于第三类    浮点数
			else
			{
				cout<<"4    "<<b<<endl;
				f1<<"d";
				f2<<" "<<b<<" ";
			}                                  //属于第四类         整数
			x=0;
			f=0;
		}


		else if(ch=='(' || ch==')'|| ch==';'|| ch=='"'|| ch=='#'|| ch=='<'|| ch=='>'|| ch=='{'|| ch=='}' || ch==',')
		{
			cout<<"5    "<<ch<<endl;//属于第五类              界符
			f1<<ch;
			f2<<" "<<ch<<" ";
			ch=file.get();
		}
		else if(ch=='='|| ch=='/'|| ch=='%'|| ch=='*'|| ch=='+'|| ch=='-' || ch=='!' || ch=='&')
		{
			cout<<"6    "<<ch<<endl;//属于第六类              运算符
			f1<<ch;
			f2<<" "<<ch<<" ";
			ch=file.get();
		}
		else
		{
			cout<<"0    "<<ch<<endl;//属于第零类               其他
			f1<<ch;
			f2<<" "<<ch<<" ";
			ch=file.get();
		}
	}
	f1<<"#";
	f2<<" "<<"#";
}


////////////////////////////////////////////////////语法分析/////////////////////////////////////////////////////




void linklistInsert(linklist &l,linklist a)//对链表的插入操作
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



void rl(linklist &wf)    //将文法分成right域和left域，并存在链表中，以便以后的使用
{
	linklist a;
	char ch;
	fstream file;
	file.open("wenfa2.txt",ios::in);//打开保存文法的文件
	ch=file.get();
	while(ch!=EOF)
	{
		while((ch==' ') || (ch=='\n')) ch=file.get();//滤空
		if(((ch>='A') && (ch<='Z')) && (file.get()=='-') &&(file.get()=='>'))//取出left域
		{
			a=new node;
			a->left=ch;
		}

		ch=file.get();
		while((ch!=10) && (ch!=EOF))//取出right域
		{
			a->right=a->right+ch;
			ch=file.get();

		}
		linklistInsert(wf,a);//将当前的文法的right域和left域插入到wf链表中
	}

}


void rlPrint(linklist wf)//输出文法的right域和left域的函数
{
	linklist p;
	p=wf;
	while(p->next!=NULL)
	{
		cout<<p->next->left<<"          "<<p->next->right<<endl;
		p=p->next;
	}
}


void linklistInit(linklist &l)//对链表的初始化
{
	l=new node;
	l->next=NULL;
}


int panduan(linklist wf)//判断给定的文法是否是LL（1）
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
				if (ch1==ch2)              //此文法有左递归
				{
					cout<<"此文法不是LL（1）文法"<<endl;
					return 0;
					goto e;
				}
			}
			q=q->next;
		}
		p=p->next;
	}
	cout<<"此文法是LL（1）文法"<<endl;//此文发没有左递归
	return 1;
e:;}


void fzjfCreat(linklist wf,linklist &fzjf)//创建非终极符链表
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
		if(q->next!=NULL) ;//当前的非终极符已经在非终极符链表中
		else               //当前非终极符不在非终极符链表中，插入到链表中
		{
			r=new node;
			r->name=ch;
			r->next=NULL;
			q->next=r;
		}
		p=p->next;
	}
}


void fzjfPrint(linklist fzjf)//打印非终极符链表的函数
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



////////////////////////////////////////////////first集的求解函数///////////////////////////////////////////////////////////////


int First(linklist wf,char x,string &s)//求出非终极符x的first集
{
	linklist p;
	p=wf;
	int i;
	int kong=1;
	while(p->next!=NULL)
	{
		if(p->next->left==x)
		{
			if (p->next->right[0]=='o') kong=0;           //如果first集中有空，则返回0
			else if(!(p->next->right[0]>='A' && p->next->right[0]<='Z'))//如果第一个是终极符，直接加入到first集合中
			{
				for(i=0;s[i]!='\0';i++)        //过滤first集中的重复终级符
				{
					if(s[i]==p->next->right[0]) break;
				}
				if(s[i]=='\0')   s=s+p->next->right[0];
			}
			else First(wf,p->next->right[0],s);   //如果第一个不是非终极符，利用递归函数求出每个非终极符的first集
		}
		p=p->next;
	}
	return kong;
}


void getFirst(linklist wf,linklist fzjf)//求出全部的非终极符first集的函数
{
	linklist p,q;
	int kong;
	p=wf;
	q=fzjf;
	while(q->next!=NULL)
	{
		kong=First(p,q->next->name,q->next->first);//有多少个非终极符，就调用多少次取first集函数
		if(kong==0) q->next->first=q->next->first+'o';
		q=q->next;
	}
}



void firstPrint(linklist fzjf)  //输出first集的函数
{
	linklist p;
	p=fzjf;
	while(p->next!=NULL)
	{
		cout<<"FIRST("<<p->next->name<<")={";
		for(int i=0;p->next->first[i]!='\0';i++)
		{
			cout<<p->next->first[i];
			if(p->next->first[i+1]!='\0') cout<<",";//在每个first终级符后加“，”，直到最后一个
		}
		cout<<"}"<<endl;
		p=p->next;
	}
}


//////////////////////////////////////////////////follow集的求解函数/////////////////////////////////////////////////////////////////



void Follow(linklist wf,char x,string &s,char a)//求出非终极符x的follow集,在此处加一个a标志位Y->gD  D->,Y  进行递归时还要判断左边的是否和刚开始要求的是一样的
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
		weizhi=p->next->right.find(x);//返回要找的非终极符所在的位置
		if(weizhi<100)
		{
			ch=p->next->right[weizhi+1];
			if(ch=='\0' && p->next->left!=x && p->next->left!=a)   Follow(wf,p->next->left,s,x);//如果要求的非终极符后为空，对left求follow
			else if(ch>='A' && ch<='Z')   //如果要求的非终极符后为非终极符
			{
				pd=First(wf,ch,s);//求非终极符的first集并判断是否有空出现
				if(pd==0)  Follow(wf,ch,s,-1);//如果有空出现，就对这个非终极符求follow
			}
			else if(ch!='\0')                             //如果是终级符
			{
				for(i=0;s[i]!='\0';i++)//滤重并插入follow集中
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


void getFollow(linklist wf,linklist fzjf)//求出全部的非终极符follow集的函数
{
	linklist p,q;
	p=wf;
	q=fzjf;
	while(q->next!=NULL)
	{
		Follow(p,q->next->name,q->next->follow,-1);//有多少个非终极符，就调用多少次取follow集函数
		q=q->next;
	}
}



void followPrint(linklist fzjf)  //输出first集的函数
{
	linklist p;
	p=fzjf;
	while(p->next!=NULL)
	{
		cout<<"FOLLOW("<<p->next->name<<")={";
		for(int i=0;p->next->follow[i]!='\0';i++)
		{
			cout<<p->next->follow[i];
			if(p->next->follow[i+1]!='\0') cout<<",";//在每个follow终级符后加“，”，直到最后一个
		}
		cout<<"}"<<endl;
		p=p->next;
	}
}



////////////////////////////////////////////////////求select集函数///////////////////////////////////////////////////////


void getSelect(linklist wf,linklist fzjf)//求select集的函数
{
	linklist p,q;
	p=wf;
	q=fzjf;
	int i=0;
	while(p->next!=NULL)
	{
d:		if(p->next->right[i]>='A' && p->next->right[i]<='Z') //如果第一个是非终极符
		{
			q=fzjf;
			while(q->next!=NULL)
			{
				if(q->next->name==p->next->right[i]) //在非终极符中找到这个非终极符，就对这个非终极符的first集加入到follow集中
				{
					p->next->select=p->next->select+q->next->first;
					for(int j=0;q->next->first[j]!='\0';j++)
					{
						if(q->next->first[j]=='o')		//如果产生式右部第一个的first集中有空
						{
							if(q->next->first[j+1]>='a' && q->next->first[j+1]<='z')//如果下一个是终极符，直接加入select集
							{
								p->next->select=p->next->select+q->next->first[j+1];
							}
							else				//如果下一个不是终极符
							{
								i++;			//对下一个非终极符求first集并加入selec集中
								goto d;
							}
						}
					}
					break;
				}
				else q=q->next;
			}
		}
		else if(p->next->right[i]=='o')//如果第一个字符是空，就是它的left域的follow集
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
		else p->next->select=p->next->right[i];//如果是终极符，直接将终极符加入select集中
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



///////////////////////////////////////////生成预测分析表的函数//////////////////////////////////////////////////

void zjfCreat(linklist wf,string &zjf)//求出所有的终极符
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
				for(j=0;zjf[j]!='\0';j++)//过滤重复的终极符
				{
					if(zjf[j]==p->next->right[i]) break;
				}
				if(zjf[j]=='\0') zjf=zjf+p->next->right[i];
			}
		}
	}
	zjf=zjf+"#";
}

void zjfPrint(string zjf)//显示所有的终极符的函数
{
	int i=0;
	while(zjf[i]!='\0')
	{
		cout<<zjf[i]<<"  ";
		i++;
	}
	cout<<endl;
}


int getFzjfNumber(linklist a,char name)//取出非终极符的序号
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

int getZjfNumber(string s,char name)//取出终极符的序号
{
	int i=0;
	while(s[i]!='\0')
	{
		if(s[i]==name) break;
		i++;
	}
	return i;
}


string ** predictTable(linklist wf,linklist fzjf,string zjf)//创建预测分析表
{
	int fzjfNo,zjfNo,line,row;
	linklist p;
	int i,j;
	char ch1,ch2;
	line=getFzjfNumber(fzjf,' ');//数组的第一个参数是非终极符的数量
	line--;
	row=getZjfNumber(zjf,' ');//数组的第二个参数是终极符你的数量
	row--;
	string **table;
	table=new string *[line+1];//动态申请二维数组
	for(i=0;i<=line;i++)
	{
		table[i]=new string [row+1];
	}
	for(i=0;i<=line;i++)//对预测分析报表进行初始化
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
		fzjfNo=getFzjfNumber(fzjf,ch1);//取出产生式中每个非终极符在非终极符的序号
		for(int selectNumber=0;p->next->select[selectNumber]!='\0';selectNumber++)//取出该产生式的select集
		{
			ch2=p->next->select[selectNumber];
			zjfNo=getZjfNumber(zjf,ch2);
			table[fzjfNo][zjfNo]=p->next->right;
			cout<<ch1<<"("<<ch2<<")"<<"="<<table[fzjfNo][zjfNo]<<endl;//根据该select集对预测分析表进行赋值
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
	cout<<"序号\t栈\t\t\t\t\t文法\t\t\t剩余输入串"<<endl;
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
				cout<<endl<<"此文法可能并不适用于当前句子"<<endl;;
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
				cout<<"\t\t\t\t\t\t消去"<<ss[i-1];
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
	if(*s.base=='#' && ss[i]=='#')  cout<<"分析成功"<<endl;

}






/////////////////////////////////////////////////主函数/////////////////////////////////////////////////////////


void yufa()
{
	int pd;
	string zjf,**table;
	linklist wf;//定义一个文法的链表
	linklist fzjf;//定义一个非终极符链表
	linklistInit(fzjf);
	linklistInit(wf);
	cifa();//对源程序进行词法分析
	rl(wf);//对给定的文法进行right域和left域的分割
	cout<<"按任意键进行文法分析……"<<endl;
	getch();
 	system("cls");
	cout<<"对文法的分析为："<<endl<<"left     right"<<endl;
	rlPrint(wf);//将分割后的结果显示出来
	pd=panduan(wf);
	if(pd==1)//如果当前文法是LL（1）文法
	{
		getch();
		system("cls");
		fzjfCreat(wf,fzjf);
		fzjfPrint(fzjf);
		cout<<"first集为："<<endl;
		getFirst(wf,fzjf);//取出所有非终极符的first集
		firstPrint(fzjf);//显示所有first集
		cout<<"按任意键求follow集……"<<endl;
		getch();
		system("cls");
		fzjfPrint(fzjf);
		cout<<"follow集为："<<endl;
		getFollow(wf,fzjf);//取出所有非终极符的follow集
		followPrint(fzjf);//显示所有follow集
		cout<<"按任意键求select集……"<<endl;
		getch();
		system("cls");
		cout<<"select集为："<<endl;
		getSelect(wf,fzjf);
		selectPrint(wf);
		zjfCreat(wf,zjf);//求出所有的终极符
		//zjfPrint(zjf);//输出所有的终极符
		cout<<"按任意键继续求预测分析表……"<<endl;
		getch();
		system("cls");
		table=predictTable(wf,fzjf,zjf);
		cout<<"按任意键继续分析过程……"<<endl;
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
				f1<<"ja "<<"l"<<flag<<endl;//如果大于跳转到flag
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
				f1<<"ja "<<"l"<<flag+1<<endl;//如果大于跳转到flag
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


		else//;或者}
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
	cout<<"按任意键继续生成四元式"<<endl;
	getch();
	system("cls");
	siyuan();
	system("pause");
	system("cls");
	huibian();
	return 0;
}
