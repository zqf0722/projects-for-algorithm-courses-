#include<stdio.h>
#include<math.h>
#define TRUE 1
#define FALSE 0
#define BLACK 1
#define RED 0 
#define MAX 9999
typedef struct BiTNode{
	char classid[20];
	int color;
	int depth;
	int low,high;
	int id;
	int max;
	struct BiTNode *root,*lchild,*rchild,*parent;
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

void makenil(BiTree &T)
{
	BiTree p;
	p = new BiTNode;
	p->max=MAX;
	p->color=BLACK;
	T=p;
}

int MAXI(int a,int b,int c)
{
	if(a>b)
	{
		if(a>c) return a;
		else return c;
	}
	else
	{
		if(b>c) return b;
		else return c;
	}
}



int ifnil(BiTree T)
{
	if(T->max==MAX)
	{
		return 1;
	}
	else return 0;
}

int max_tree(BiTree &T)
{
	if(!ifnil(T))
	{
		int l=max_tree(T->lchild);
		int r=max_tree(T->rchild);
		int max=MAXI(T->high,l,r);
		T->max=max;
		return max;
	}
	else return 0;
}

void left_rotate(BiTree &T,BiTree x)
{
	//printf("fuck\n");
	BiTree y; 
	y=x->rchild;
	x->rchild=y->lchild;
	//printf("fuck\n");
	if(!ifnil(y->lchild))
	{
		y->lchild->parent=x;
	}

	y->parent=x->parent;
	
	if (ifnil(x->parent))
	{
		T=y;
	}

	else if(x==x->parent->lchild)
	{
		x->parent->lchild=y;
	}
	else
	{
		x->parent->rchild=y;
	}
	y->lchild=x;
	x->parent=y;
}

void right_rotate(BiTree &T,BiTree y)
{
	BiTree x=y->lchild;
	y->lchild=x->rchild;
	if(!ifnil(x->rchild))
	{
		x->rchild->parent=y;
	}	
	x->parent=y->parent;
	if(ifnil(y->parent))
	{
		T=x;
	}
	else if(y==y->parent->lchild)
	{
		y->parent->lchild=x;
	}
	else y->parent->rchild=x;

	x->rchild=y;
	y->parent=x;
	
}

void rb_insert_fixup(BiTree &T,BiTree z)
{
	while(z->parent->color==RED)
	{
		if(z->parent==z->parent->parent->lchild)
		{
			BiTree y=z->parent->parent->rchild;
			if(y->color==RED)
			{
				z->parent->color=BLACK;
				y->color=BLACK;
				z->parent->parent->color=RED;
				z=z->parent->parent;
				continue;
			}
			if(z==z->parent->rchild)
			{
				z=z->parent;
				left_rotate(T,z);

			}
			z->parent->color=BLACK;
			z->parent->parent->color=RED;
			right_rotate(T,z->parent->parent);
		}
		else
		{
			BiTree y=z->parent->parent->lchild;
			if(y->color==RED)
			{
				z->parent->color=BLACK;
				y->color=BLACK;
				z->parent->parent->color=RED;
				z=z->parent->parent;
				continue;
			}
			if(z==z->parent->lchild)
			{
				z=z->parent;				
				right_rotate(T,z);
				//printf("fuck\n");

			}
			printf("%d ",z->low);
			z->parent->color=BLACK;
			//printf("fuck\n");
			z->parent->parent->color=RED;
			printf("%d",z->parent->parent->low);
			left_rotate(T,z->parent->parent);		
			printf("%d ",z->low);	
		}
	}
	T->color=BLACK;
}

void rb_insert(BiTree &T,BiTree z)
{
	BiTree y;
	BiTree x=T;
	makenil(y);
	while(!ifnil(x))
	{
		y=x;
		if(z->low<x->low)
		x=x->lchild;
		else x=x->rchild;
	}
	z->parent=y;
	if(ifnil(y))
	{
		T=z;
		z->color=BLACK;
		makenil(z->parent);
		makenil(z->lchild);
		makenil(z->rchild);
		return;
	}
	else if(z->low<y->low)
	{
		y->lchild=z;
	}
	else y->rchild=z;
	makenil(z->lchild);
	makenil(z->rchild);
	z->color=RED;
	rb_insert_fixup(T,z);
	
}

void rb_tran(BiTree &T,BiTree u,BiTree v)
{
	if(ifnil(u->parent))
	{
		T=v;
		makenil(v->parent);
	}
	else if(u==u->parent->lchild)
	u->parent->lchild=v;
	else
	u->parent->rchild=v;
	v->parent=u->parent;
}

void rb_delete_fixup(BiTree &T,BiTree x)
{
	while(!ifnil(x->parent)&&x->color==BLACK)
	{
		if(x==x->parent->lchild)
		{
			BiTree w=x->parent->lchild;
			if(w->color==RED)
			{
				w->color=BLACK;
				x->parent->color=RED;
				left_rotate(T,x->parent);
				w=x->parent->rchild;
			}
			if(w->lchild->color==BLACK&&w->rchild->color==BLACK)
			{
				w->color=RED;
				x=x->parent;
			}
			else
			{
				if(w->rchild->color==BLACK)
				{
					w->lchild->color=BLACK;
					w->color=RED;
					right_rotate(T,w);
					w=x->parent->rchild;
				}
				w->color=x->parent->color;
				x->parent->color=BLACK;
				w->rchild->color=BLACK;
				left_rotate(T,x->parent);
				T=x;
				makenil(x->parent);
			}
		}
		else
		{
			BiTree w=x->parent->lchild;
			if(w->color==RED)
			{
				w->color=BLACK;
				x->parent->color=RED;
				right_rotate(T,x->parent);
				w=x->parent->lchild;
			}
			if(w->rchild->color==BLACK&&w->lchild->color==BLACK)
			{
				w->color=RED;
				x=x->parent;
			}
			else
			{
				if(w->lchild->color==BLACK)
				{
					w->rchild->color=BLACK;
					w->color=RED;
					left_rotate(T,w);
					w=x->parent->lchild;
				}
				w->color=x->parent->color;
				x->parent->color=BLACK;
				w->rchild->color=BLACK;
				right_rotate(T,x->parent);
				T=x;
				makenil(x->parent);
			}
		}
	}
	x->color=BLACK;
}

BiTree tree_min(BiTree T)
{
	BiTree a;
	a=T;
	while(!ifnil(a->lchild))
	{
		a=a->lchild;
	}
	return a;
}

void rb_delete(BiTree &T,BiTree z)
{
	BiTree y=z;
	int y_original_color=y->color;
	BiTree x;
	if(ifnil(z->lchild))
	{
		
		x=z->rchild;
		rb_tran(T,z,z->rchild);
	}
	else if(ifnil(z->rchild))
	{		
		x=z->lchild;
		rb_tran(T,z,z->lchild);
	}
	else
	{
		y=tree_min(z->rchild);
		y_original_color=y->color;
		x=y->rchild;
		if(y->parent==z)
		{
			x->parent=y;
		}
		else
		{
			rb_tran(T,y,y->rchild);
			y->rchild=z->rchild;
			y->rchild->parent=y;
		}
		rb_tran(T,z,y);
		y->lchild=z->lchild;
		y->lchild->parent=y;
		y->color=z->color;
	} 
	//printf("%d",x->parent->max);
	if(y_original_color==BLACK)
	{
		rb_delete_fixup(T,x);
	}
}



void mid(BiTree T)
{
	if(ifnil(T)) return ;
	mid(T->lchild);
	printf("课程编号: ");
	printf("%d ",T->id);	
	printf("课程名称: ");
	printf("%s ",T->classid); 
	printf("课程区间: "); 
	printf("%d %d \n",T->low,T->high);	
	mid(T->rchild);
}

void LayerTraversal(BiTree T)
{
	max_tree(T);
	BiTree p;
	LinkQueue q;
	InitQueue(q);
	if(!ifnil(T)) EnQueue(q,T);
	while(q.front!=q.rear)
	{
		DeQueue(q,p);
		printf("课程编号: ");
		printf("%d ",p->id);	
		printf("课程名称: ");
		printf("%s ",p->classid); 
		printf("课程区间: "); 
		printf("%d %d ",p->low,p->high);	
		printf("max=%d\n",p->max);
		if(!ifnil(p->parent))
		{
			printf("%s ",p->parent->classid);
			printf("%d %d\n",p->parent->low,p->parent->high);
		} 
		if(!ifnil(p->lchild)) EnQueue(q,p->lchild);
		if(!ifnil(p->rchild)) EnQueue(q,p->rchild);
	}
	printf("\n");
	return;
}

int ifoverlap(BiTree T,int low,int high)
{
	if(T->low>=high||T->high<low)
	return 0;
	else return 1;
}

void interval_search(BiTree T,int low,int high)
{
	max_tree(T);
	BiTree x=T;
	BiTree y;

		if(ifoverlap(x,low,high))
		{
			printf("课程编号: ");
			printf("%d ",x->id);	
			printf("课程名称: ");
			printf("%s ",x->classid); 
			printf("课程区间: "); 
			printf("%d %d \n",x->low,x->high);
		}
		if(!ifnil(x->lchild)&&x->lchild->max>=low)
		{
			interval_search(x->lchild,low,high); 
		}
		if(!ifnil(x->rchild))
		{
			interval_search(x->rchild,low,high);
		}
		return;
}

BiTree interval_delete_search(BiTree T,int low,int high)
{
	BiTree x=T;
	while(!ifnil(x))
	{
		if(low==x->low&&high==x->high)
		{
			return x;
		}
		if(x->low<low)
		{
			x=x->rchild;
		}
		else x=x->lchild;
		
	}
	printf("没有这样的课程\n");
	return x;
}


int main()
{

	BiTree T;
	T = new BiTNode;
	makenil(T);
	int flag; 
	
menu:
	printf("\n");
	printf("--------课表管理系统-------\n");	
	printf("1.插入课程\n2.删除课程\n3.查询课程\n4.中序显示当前课程\n5.层序显示当前课程\n");
	printf("其余键退出系统\n");	
	scanf("%d",&flag);
	switch(flag)
	{
		case 1:
			BiTree p;
			p = new BiTNode;			
			printf("课程名称\n"); 
			getchar();
			gets(p->classid);
			printf("课程编号\n"); 
			scanf("%d",&p->id);
			printf("课程区间\n");
			scanf("%d %d",&p->low,&p->high); 
			rb_insert(T,p); 
			goto menu;
		case 2:
			int low,high;
			BiTree x;
			printf("要删除的区间:\n");
			scanf("%d %d",&low,&high);
			x=interval_delete_search(T,low,high);
			if(ifnil(x)) goto menu;
			else
			{
				rb_delete(T,x);
				printf("删除已成功\n"); 
			} 
			goto menu;
		case 3:
			printf("输入区间:\n");
			scanf("%d %d",&low,&high);
			interval_search(T,low,high);
			goto menu;
		case 4:
			 mid(T);
			 goto menu;
		case 5:
			 LayerTraversal(T);
			 goto menu;
		default:
			return 0;
	}
}
