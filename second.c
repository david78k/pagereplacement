#include<stdio.h>

#define FRAMESIZE 3

int full=0;//To check whether all frames are filled
int a[21];//To take the input
int ref[FRAMESIZE];//This is for reference bits for each frame
int frame[FRAMESIZE];
int repptr=0;//Initialised to first frame
int count=0;
int repitem = -1;

int display()
{
	int i;
	//printf("\nThe elements in the frame are\n");

	for(i=0;i<full;i++)
		printf("%d ",frame[i]);
	if (repitem != -1)
		printf("(%d replaced)", repitem);
//	printf("\n");
}

int Pagerep(int ele)
{
	int temp;
	 /*When ever a page needs to be replaced the repptr moves from page to page checking whether it's reference bit is 0 or not, if it is 0 it coomes out of the while loop and if it is one, it gives a second chance setting the reference bit to 0*/
	 while(ref[repptr]!=0)
	{ 
		ref[repptr++]=0;
		if(repptr==FRAMESIZE)
			 repptr=0;
	}                     
	 temp=frame[repptr];
	 frame[repptr]=ele;
	 ref[repptr]=1;//The latest page reference, hence it is set to 1
	 return temp;   
}

int Pagefault(int ele)
{
	if(full!=FRAMESIZE)
	{
		ref[full]=1;//All the ref bits are set to 1 as each frame is being filled firstly
               	frame[full++]=ele;
		return -1;
	}
	else {
		Pagerep(ele);
		//printf("Replacing %d => ",Pagerep(ele));
		//printf("The page replaced is %d. ",Pagerep(ele));
		repitem = ele;
		return ele;
	}
}

int Search(int ele)
{
	int i,flag;
	flag=0;
	if(full!=0)
	{
		for(i=0;i<full;i++)
			if(ele==frame[i])
			{   
				flag=1;ref[i]=1;//When ever page reference occurs, it's rference bit is set to 1
				break;
			}
	}
	return flag;   
}

int main()
{
	int n,i;
	FILE *fp;
    	fp=fopen("Input.txt","r");
	printf("The number of elements in the reference string are :");
    	fscanf(fp,"%d",&n);
	printf("%d",n);

    	for(i=0;i<n;i++)
    		fscanf(fp,"%d",&a[i]);

    	printf("\nFrame size = %d\n", FRAMESIZE);
    	printf("The elements present in the string are\n");
    	
	for(i=0;i<n;i++)
		printf("%d  ",a[i]);
    	printf("\n");

    	for(i=0;i<n;i++)
    	{
		printf("%d: ", a[i]);	
        	if(Search(a[i])!=1)
                {	
			Pagefault(a[i]);
                    	display();
                    	count++;
                }
		printf("\n");
        }

        printf("\nThe number of page faults is %d.\n",count);
//      getche();

	return 0;
}

