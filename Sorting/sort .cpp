#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<Windows.h>
#include <mmsystem.h>

#define MAX 9999999
void swap(int &a,int &b)
{
	int m=a;
	a=b;
	b=m;
}

int* generate(int n)
{
	static int*a=(int*)malloc((n+1)*sizeof(int));
	srand((unsigned)time(NULL));
	for (int i=1;i<=n;i++)
	{
		a[i]=rand()%9999999;
	}
	return a;
}

int* copy(int* a,int n)
{
	static int*b=(int*)malloc((n+1)*sizeof(int));
	for (int t=1;t<=n;t++)
	{
		b[t]=a[t];
	}
	return b;
}

int partition(int*a,int p,int r)
{
	int x=a[r];
	int i=p-1;
	for(int j=p;j<=r-1;j++)
	{
		if (a[j]<=x)
		{
			i=i+1;
			swap(a[i],a[j]);
		}
		
	}
	swap(a[i+1],a[r]);
	return i+1;
}

void quick_sort(int* a,int p,int r)
{
	if(p<r)
	{
		int q=partition(a,p,r);
		quick_sort(a,p,q-1);
		quick_sort(a,q+1,r);
	}
}

void insert_sort(int *a,int n)
{
	for(int j=2;j<=n;j++)
	{
		int key=a[j];
		int i=j-1;
		while(i>=1&&a[i]>key)
		{
			a[i+1]=a[i];
			i=i-1;
		}
		a[i+1]=key;
	}
}

int parent(int i)
{
	return floor(i/2);
}

int left(int i)
{
	return(2*i);
}

int right(int i)
{
	return(2*i+1);
}

void max_heapify(int *a,int i,int a_heapsize)
{
	int l=left(i);
	int r=right(i);
	int max;
	if(l<=a_heapsize&&a[l]>a[i])
	{
		 max=l;
	}
	else max=i;
	if(r<=a_heapsize&&a[r]>a[max])
	{
		max=r;
	}
	if (max!=i)
	{
		swap(a[i],a[max]);
		max_heapify(a,max,a_heapsize);
	}
}

void build_maxheap(int *a,int n)
{
	int a_length=n;
	int a_heapsize=a_length;
	for (int i =floor(a_length/2);i>=1;i--)
	{
		max_heapify(a,i,a_heapsize);
	}
}

void heap_sort(int *a,int n)
{
	int a_heapsize=n;
	build_maxheap(a,n);
	for (int i=n;i>=2;i--)
	{
		swap(a[1],a[i-1]);
		a_heapsize--;
		max_heapify(a,1,a_heapsize);
	}
}

void merge(int *a,int p,int q,int r)
{
	int n1=q-p+1;
	int n2=r-q;
	int* L1=new int[n1+2];
	int* L2=new int[n2+2];
	for (int i=1;i<=n1;i++)
	{
		L1[i]=a[p+i-1];
	}
	for(int i=1;i<=n2;i++)
	{
		L2[i]=a[q+i];
	}
	L1[n1+1]=MAX;
	L2[n2+1]=MAX;
	int i=1;
	int j=1;
	for (int k=p;k<=r;k++)
	{
		if(L1[i]<=L2[j])
		{
			a[k]=L1[i];
			i++;
		}
		else
		{
			a[k]=L2[j];
			j++;
		}
	}
}


void merge_sort(int *a,int p,int r)
{
	int q;
	if (p<r)
	{
		q=floor((p+r)/2);
		merge_sort(a,p,q);
		merge_sort(a,q+1,r);
		merge(a,p,q,r);
	}
}

int main()
{

	int n;
	printf("input the size of the array:\n");
	scanf("%d",&n);
	LARGE_INTEGER t1q,t2q,t1h,t2h,t1i,t2i,t1m,t2m,tc;
	int *a;
	a=generate(n);

    QueryPerformanceFrequency(&tc);
	int *Quick=copy(a,n);
	QueryPerformanceCounter(&t1q);
	quick_sort(Quick,1,n);
    QueryPerformanceCounter(&t2q);
    QueryPerformanceFrequency(&tc);    
	printf("快速排序花费时间:%.4lfms\n",(t2q.QuadPart - t1q.QuadPart)*1.0*1000/tc.QuadPart);
	int *Merge=copy(a,n);
    QueryPerformanceCounter(&t1m);
	merge_sort(Merge,1,n);

    QueryPerformanceCounter(&t2m);
	printf("归并排序花费时间:%.4lfms\n",(t2m.QuadPart - t1m.QuadPart)*1.0*1000/tc.QuadPart);	
	int *Heap=copy(a,n);
	QueryPerformanceCounter(&t1h);
	heap_sort(Heap,n);
    QueryPerformanceCounter(&t2h);
    QueryPerformanceFrequency(&tc);    
	printf("堆排序花费时间:%.4lfms\n",(t2h.QuadPart - t1h.QuadPart)*1.0*1000/tc.QuadPart);
	int *Insert=copy(a,n);
	QueryPerformanceCounter(&t1i);
	insert_sort(Insert,n);
    QueryPerformanceCounter(&t2i);
    QueryPerformanceFrequency(&tc);    
	printf("插入排序花费时间:%.4lfms\n",(t2i.QuadPart - t1i.QuadPart)*1.0*1000/tc.QuadPart);
	

	return 0;
    
    
}

