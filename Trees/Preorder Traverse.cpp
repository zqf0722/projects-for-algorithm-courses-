#include<stdio.h>
#include<math.h>
#define TRUE 1
#define FALSE 0
typedef struct BiTNode{
	int data;
	int lcd,rcd;
	int depth;
	int parentsdata;
	bool isFirst; 
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
typedef struct LNode{
		BiTree data;
		struct LNode* next;
}LNode,*LinkList;
typedef struct{
	LinkList front;
	LinkList rear;
}LinkQueue;
void InitQueue(LinkQueue &q)
{
	q.front=q.rear=new LNode;
	q.front->next=NULL;
}
void DestroyQueue(LinkQueue &q)
{
	while(q.front){
		q.rear=q.front->next;
		delete q.front;
		q.front=q.rear;
	}
}
bool GetHead(LinkQueue q,BiTree &e)
{
	if(q.front==q.rear) return FALSE;
	e=q.front->next->data;
	return TRUE;
}
void EnQueue(LinkQueue &q,BiTree e)
{
	LinkList p;
	p=new LNode;
	p->data=e; p->next=NULL;
	q.rear->next=p;
	q.rear=p;
}
bool DeQueue(LinkQueue &q,BiTree &e)
{
	LinkList p;
	if(q.front==q.rear) return FALSE;
	p=q.front->next;
	q.front->next=p->next;
	e=p->data;
	if(q.rear==p) q.rear=q.front;
	delete p;
	return TRUE;
}
typedef struct SNode{
	BiTree data;
	struct SNode* next;
}SNode,*LinkStack;
void InitStack_L(LinkStack &s)
{
	s=NULL;
}
void DestroyStack_L(LinkStack &s)
{
	LinkStack p;
	while(s)
	{
		p=s;
		s=s->next;
		delete p;
	}
}
bool GetTop_L(LinkStack s,BiTree &e)
{
	if(!s) return FALSE;
	e=s->data;
	return TRUE;
}

void Push_L(LinkStack &s,BiTree e)
{
	LinkStack p;
	p=new SNode;
	p->data=e;
	p->next=s;
	s=p;
}
bool Pop_L(LinkStack &s,BiTree &e)
{
	LinkStack p;
	if(!s) return FALSE;
	p=s;
	s=s->next;
	e=p->data;
	delete p;
	return TRUE;
}
BiTree CreateBiTree2(int a[],int low1,int hig1,int low2,int hig2)
{
	if(low1>hig1) return NULL;
	BiTree p;
	p=new BiTNode;
	p->data=a[low1];
	int m=low2;
	while(a[low1]!=m+1) m++;
	p->lchild=CreateBiTree2(a,low1+1,low1+m-low2,low2,m-1);
	p->rchild=CreateBiTree2(a,low1+m-low2+1,hig1,m+1,hig2);
	return p;
}
void PostOrder(BiTree T)
{
	int depth=0;
	LinkStack s;
	InitStack_L(s);
	T->parentsdata=0;
	BiTree p=T;
	while(p||s!=NULL)
	{
		if(p)
		{
			p->isFirst=FALSE;
			p->depth=depth++;
			Push_L(s,p);
			p=p->lchild;
		}
		else
		{
			if(s!=NULL)
			{
				Pop_L(s,p);
				depth=p->depth;
				if(p->isFirst==TRUE)
				{
					printf("%d ",p->data);
					if(p->lchild!=NULL)
					{
						p->lcd=p->lchild->data;
						p->lchild->parentsdata=p->data;
					}
					else p->lcd=0;
					if(p->rchild!=NULL) 
					{
						p->rcd=p->rchild->data;
						p->rchild->parentsdata=p->data;
					}	
					else p->rcd=0;
					p=NULL;
				}
				else
				{
					p->isFirst=TRUE;
					p->depth=depth++;
					Push_L(s,p);
					p=p->rchild;
				}
			}
		}
	}
	printf("\n");
}
void LayerTraversal(BiTree T)
{
	BiTree p;
	LinkQueue q;
	InitQueue(q);
	if(T) EnQueue(q,T);
	while(q.front!=q.rear)
	{
		DeQueue(q,p);
		printf("%d ",p->data);
		if(p->lchild) EnQueue(q,p->lchild);
		if(p->rchild) EnQueue(q,p->rchild);
	}
	printf("\n");
	return;
}
void GetParentsandchildrenanddepth(BiTree T,int num)
{
	LinkStack s;
	InitStack_L(s);
	while(T||s!=NULL)
	{
		while(T)
		{
			if(T->data==num) 
			{
				printf("%d %d %d %d ",T->parentsdata,T->lcd,T->rcd,T->depth);
				return;
			}
			if(T->data>num)
			{
				T=T->lchild;
				continue;
			}
			if(T->data<num)
			{
				T=T->rchild;
				continue;
			}
		}
	}
}
void GetNode(BiTree T,int num)
{
	int Nodenum=0;
	while(T!=NULL)
	{
		if(T->data==num)
		{
			goto next;
		}
		if(T->data>num)
		{
			T=T->lchild;
			continue;
		}
		if(T->data<num)
		{
			T=T->rchild;
			continue;
		}
	}
	next: LinkStack s1;
	InitStack_L(s1);
	while(T||s1!=NULL)
	{
		while(T)
		{
			Nodenum++;
			Push_L(s1,T);
			T=T->lchild;	
		}
		if(s1!=NULL)
		{
			Pop_L(s1,T);
			T=T->rchild;
		}
	}
	printf("%d\n",Nodenum);
	return;
}
void GetInfo(int num,BiTree T)
{
	GetParentsandchildrenanddepth(T,num);
	GetNode(T,num);
	return;
}
int main()
{
	int n;
	scanf("%d",&n);
	int a[n];
	BiTree T;
	for(int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	T=CreateBiTree2(a,0,n-1,0,n-1);
	int m;
	scanf("%d",&m);
	int b[m];
	for(int i=0;i<m;i++)
	{
		scanf("%d",&b[i]);
	}
	PostOrder(T);
	LayerTraversal(T); 
	for(int i=0;i<m;i++)
	{
		
		GetInfo(b[i],T);
	}

	return 0;
}
