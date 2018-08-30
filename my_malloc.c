#include<stdio.h>
#include<string.h>
#define MAX 16000
char buffer[MAX];
void* endptr=buffer+MAX*sizeof(char);
void* gptr=buffer;
void* lptr;
int freesize=MAX;
struct header
{
	int size;
	char var;
	void * ptr;
}s;
void init()
{
		s.var='f';
		s.size=16000;
		s.ptr=NULL;
		memcpy(gptr,&s,sizeof(s));
		gptr+=sizeof(s);
}
void* my_malloc(int size)//first->best fit implementation
{
	int count=0;
	if(size>freesize)
		return NULL;	//if the size requested is not available then we return null pointer
	else
	{
		lptr=gptr-sizeof(s);
		memcpy(&s,gptr-sizeof(s),sizeof(s));
		printf("%p",lptr);		
		do
		{
				if(s.size<size)
				{	
					lptr+=s.size;
				}
				else
				{	if(s.var=='f')	
					{
					freesize-=size;
					if(s.ptr!=NULL)						
						gptr=s.ptr;
					else
						gptr=lptr+size+2*sizeof(s);
					int temp1=s.size;
					s.size=size;
					s.var='a';
					s.ptr=NULL;
					memcpy(lptr,&s,sizeof(s));
					s.ptr=gptr-sizeof(s);
					s.size=temp1-size;
					s.var='f';
					memcpy(lptr+size+sizeof(s),&s,sizeof(s));	
					return (lptr+sizeof(s));}
					else
						lptr+=s.size; 
				}
				memcpy(&s,lptr,sizeof(s));						
				printf("%p",lptr);				
				printf("count--%d\n",count++);
		}while(lptr!=endptr);
		
	}

	
	
}
int main()
{
		init();
		int *a=(int *)my_malloc(160*sizeof(int));
		for(int i=0;i<160;i++)
			printf("%d\n",a[i]);
		int *b=(int *)my_malloc(10*sizeof(int));
		printf("\n%d\n",a[0]);
		for(int i=0;i<10;i++)		
		{b[i]=i;
		printf("\n%d\n",b[i]);
		}
	return 0;
}
