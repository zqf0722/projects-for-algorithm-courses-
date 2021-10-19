#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
int package=100;
int weight[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
int value[20]={1,3,5,6,7,8,10,12,14,16,17,18,19,20,21,22,23,22,24,25};

typedef struct BiTNode{
	int level;
	int isok;
	int cw,cv;
	int x[20];
	float up;
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

void EnQueue(LinkQueue &q,BiTree e)
{
	LinkList p;
	p=new LNode;
	p->data=e; p->next=NULL;
	q.rear->next=p;
	q.rear=p;
}

void EnQueue_plus(float up,LinkQueue &q,BiTree e)
{
	//printf("%.2f\n",up); 
	
	BiTree T[10000];
	int i;
	int flag=0;
	for(i=0;;i++)
	{
		T[i]=new BiTNode;
		if(q.front==q.rear&&i==0) 
		{
			//printf("i=0 out\n");
			EnQueue(q,e);
			return;
		}
		if(q.front==q.rear)
		{
			//printf("i!=0 out\n");
			break;
		}
		DeQueue(q,T[i]);
		//printf("up=%.2f T.up=%.2f\n",up,T[i]->up);
		if(T[i]->up<up&&flag==0)
		{
			flag=1;
			//printf("fuck\n");
			T[i+1]=T[i];
			T[i]=e;
			i++;
		}
	}
	if(flag==0) 
	{
		T[i]=new BiTNode;
		T[i]=e;
	}
	for(int j=0;j<=i;j++)
	{
		//printf("in!\n");
		EnQueue(q,T[j]);
	}	
}

int min(int a,int b)
{
	if(a<b)
	return a;
	else
	return b;
}

int max(int a,int b)
{
	if(a>b)
	return a;
	else
	return b;
}

int ifoverload(char *a)
{
	int all=0;
	for(int i=0;i<20;i++)
	{
		if(a[i]=='0');
		else
		{
			all=all+weight[i];
			if(all>package)
			return 1;
		}
	}
	return 0;
}

int computeval(char *a)
{
	int val=0;
	for (int i=0;i<20;i++)
	{
		if(a[i]=='0');
		else
		{
			val=val+value[i];
		}
	}
	return val;
}

void add(char* a)
{
	for(int i=19;i>=0;i--)
	{
		if(a[i]=='0')
		{
			a[i]='1';
			return; 
		}
		else
		{
			a[i]='0';
		} 
	}
} 

void qiongju()
{
	char max[21];
	int max_v=0;
	char a[]="00000000000000000000\0";
	for(int i=0;i<pow(2,20);i++)
	{
		if(ifoverload(a)==0)
		{
			int val=computeval(a);
			if(val>max_v)
			{
				max_v=val;
				strcpy(max,a);
			}
		}
		add(a);
	} 
	printf("最高价值为:%d\n",max_v);
	printf("所取货物为:\n");
	puts(max);
	
}

int m[20][101];

void dynamic()
{
	int c=100;
	int jmax=min(100,weight[19]-1);
	int j;
	for(j=0;j<=jmax;j++)
	{
		m[19][j]=0;
	}
	for(j=weight[19];j<=100;j++)
	{
		m[19][j]=value[19];
	}
	for(int i=18;i>=1;i--)
	{
		jmax=min(weight[i]-1,100);
		for(j=0;j<=jmax;j++)
		{
			m[i][j]=m[i+1][j];
		}
		for(j=weight[i];j<=100;j++)
		{
			m[i][j]=max(m[i+1][j],m[i+1][j-weight[i]]+value[i]);
		}
	}
	if (c>=weight[0])
	{
		m[0][c]=max(m[1][c],m[1][c-weight[0]]+value[0]);
	}
	else
	{
		m[0][c]=m[1][c];
	}
	printf("最高价值为:%d\n",m[0][c]);
	printf("所取货物为:\n");
	for(int i=0;i<19;i++)
	{
		if(m[i][c]==m[i+1][c])
		{
			printf("0");
		}
		else
		{
			c-=weight[i];
			printf("1");
		}
	}
	if(m[19][c]>0)
	{
		printf("1");
	}
	else printf("0");
	printf("\n");
}

int bw_m[20][101];

int lookupchain(int i,int j)
{
	int c=100;
	int jmax;
	if(bw_m[i][j]>0) return bw_m[i][j];
	if(i==19)
	{
		jmax=min(100,weight[19]-1);
		if(j>jmax) bw_m[i][j]=value[i];
		else bw_m[i][j]=0;
	}
	if(i>0&&i<19)
	{
		jmax=min(c,weight[i]-1);
		if(j<=jmax)
		{
			bw_m[i][j]=lookupchain(i+1,j);
		}
		else
		{
			bw_m[i][j]=max(lookupchain(i+1,j),lookupchain(i+1,j-weight[i])+value[i]);
		}
	}
	if(i==0)
	{
		if (c>=weight[0])
		{
			bw_m[0][c]=max(lookupchain(1,c),lookupchain(1,c-weight[i])+value[i]);
		}
		else
		{
			bw_m[0][c]=lookupchain(1,c);
		}	
	}
	return bw_m[i][j];
}


void beiwang()
{
	int c=100;
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<101;j++)
		{
			bw_m[i][j]=-1;
		}
	}
	printf("最高价值为:%d\n",lookupchain(0,100));
	printf("所取货物为:\n");
	for(int i=0;i<19;i++)
	{
		if(bw_m[i][c]==bw_m[i+1][c])
		{
			printf("0");
		}
		else
		{
			c=c-weight[i];
			printf("1");
		}
	}
	if(bw_m[19][c]>0)
	{
		printf("1");
	}
	else printf("0");
	printf("\n");
}

int hs_m[20];
int opt_hs[20];
int cw_hs=0;int cv_hs=0;int bestv_hs=0;
void huisu(int t)
{
	if(t>19)
	{
		if(bestv_hs<cv_hs)
		{
			for(int i=0;i<20;i++)
			{
				opt_hs[i]=hs_m[i];
			}
			bestv_hs=cv_hs;
		}
	}
	else
	{
		if(cw_hs+weight[t]<=100)
		{
			hs_m[t]=1;
			cw_hs+=weight[t];
			cv_hs+=value[t];
			huisu(t+1);
			cw_hs-=weight[t];
			cv_hs-=value[t];
		}
		hs_m[t]=0;
		huisu(t+1);
	} 
}

int cw_fz,cv_fz,bestp_fz;
float vper[20];
int v_s[20];
int w_s[20];

float bound(int i)
{
	int cleft=100-cw_fz;
	float b=(float)cv_fz;
	while(i<=19&&w_s[i]<=cleft)
	{
		cleft-=w_s[i];
		b+=v_s[i];
		i++;
	}
	if(i<=19) 
	{
		b+=(float)vper[i]*cleft;
	}
	return b;
}

void swap(float &a,float &b)
{
	float m=a;
	a=b;
	b=m;
}


int partition(float*a,int p,int r)
{
	float x=a[r];
	int i=p-1;
	for(int j=p;j<=r-1;j++)
	{
		if (a[j]>x)
		{
			i=i+1;
			swap(a[i],a[j]);
		}
		
	}
	swap(a[i+1],a[r]);
	return i+1;
}

void quick_sort(float* a,int p,int r)
{
	if(p<r)
	{
		int q=partition(a,p,r);
		quick_sort(a,p,q-1);
		quick_sort(a,q+1,r);
	}
}

void sort()
{

	int value_fz[20],weight_fz[20]; 
	for(int i=0;i<20;i++)
	{
		value_fz[i]=value[i];
		weight_fz[i]=weight[i];
		vper[i]=(float)value[i]/weight[i];
	}
	quick_sort(vper,0,19);
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			if(vper[i]==(float)value_fz[j]/weight_fz[j])
			{
				value_fz[j]=-1;
				weight_fz[j]=1;
				v_s[i]=value[j];
				w_s[i]=weight[j];
				break;
			}
		}
		
	}
} 


void fenzhi()
{

	sort();
	int xuanze[20];
	cw_fz=0; cv_fz=0;
	bestp_fz=0;
	int i=0; 
	float up=bound(0); 
	LinkQueue q;
	InitQueue(q);
	BiTree N;		
	while(i!=20)
	{
		if(cw_fz+w_s[i]<=100)
		{
			if(cv_fz+v_s[i]>bestp_fz) 
			{
				bestp_fz=cv_fz+v_s[i];
			}
			BiTree p;
			p=new BiTNode;
			p->cv=cv_fz+v_s[i];
			p->cw=cw_fz+w_s[i];
			xuanze[i]=1;
			p->isok=1;
			p->up=up;
			for(int k=0;k<20;k++)
			p->x[k]=xuanze[k];
			p->level=i+1;
			//printf("1\n");
			EnQueue_plus(up,q,p);
		}
		up=bound(i+1);
		if(up>=bestp_fz)
		{
			BiTree p2;
			p2=new BiTNode;
			p2->cv=cv_fz;
			p2->cw=cw_fz;
			p2->up=up;
			xuanze[i]=0;
			p2->level=i+1;
			p2->isok=0;
			for(int k=0;k<20;k++)
			p2->x[k]=xuanze[k];
			//printf("0\n");
			EnQueue_plus(up,q,p2);
		}

		DeQueue(q,N);
		i=N->level;
		cw_fz=N->cw;
		cv_fz=N->cv;
		up=N->up;
		for(int k=0;k<20;k++)
		xuanze[k]=N->x[k];
	}	
	printf("最高价值为:%d\n",bestp_fz);
	printf("所取货物为:\n");
	int j;
	for(i=0;i<=19;i++)
	{
		for(j=0;j<20;j++)
		{
			if(weight[i]==w_s[j])
			{
				break;
			}
		}
		printf("%d",xuanze[j]);
	}
	printf("\n");	
}



void ran()
{
	int x[20]={0};
	int max_x[20];
	int count=0;
	int w=0;
	int max_v=0;
	int val=0;
	srand((unsigned)time(NULL));	
	while(count<=500000)
	{
		w=0;
		val=0;

		int i = rand() % 20 ;
		if(x[i]==0) x[i]=1;
		else x[i]=0;
		for(int j=0;j<20;j++)
		{
			if(x[j]==1)
			{
				w+=weight[j];	
				val+=value[j];
			}			
		}
		if(w>100)
		{
			count++;
			continue;
		}
		else
		{
			if(val>max_v)
			{
				max_v=val;
				for(int j=0;j<20;j++)
				{
					max_x[j]=x[j];
				}
			}
		}
		count++;
	}
	printf("最高价值为:%d\n",max_v);
	printf("所取货物为:\n");
	for(int i=0;i<=19;i++)
	{
		printf("%d",max_x[i]);
	}
	printf("\n");		
}

int main()
{
	printf("穷举法:\n");
	qiongju();
	printf("动态规划:\n");
	dynamic();
	printf("自顶向下备忘录:\n");
	beiwang();
	printf("回溯法:\n");
	huisu(0);
	//输出x
	printf("最高价值为:%d\n",bestv_hs);
	printf("所取货物为:\n");
	for(int i=0;i<=19;i++)
	{
		printf("%d",opt_hs[i]);
	}
	printf("\n");	
	printf("分支界定法:\n");
	fenzhi();
	printf("蒙特卡洛方法:\n");
	ran();
	return 1;
} 
