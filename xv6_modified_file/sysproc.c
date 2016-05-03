#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_fifo(void)
{
int i,j,n,a[50],frame[10],no,k,avail,count=0;
            n=20; //no.of pages
	a[1]=3,a[2]=5,a[3]=1,a[4]=3,a[5]=7,a[6]=4,a[7]=9,a[8]=2,a[9]=9,a[10]=8,a[11]=5,a[12]=9,a[13]=7,a[14]=5,a[15]=3,a[16]=7,a[17]=6,a[18]=8,a[19]=3,a[20]=1; //page numbers
            no=4; //no.of frames
for(i=0;i<no;i++)
            frame[i]= -1;
                        j=0;
                        //printf("\tref string\t page frames\n");
for(i=1;i<=n;i++)
                        {
                                    //printf("%d\t\t",a[i]);
                                    avail=0;
                                    for(k=0;k<no;k++)
if(frame[k]==a[i])
                                                avail=1;
                                    if (avail==0)
                                    {
                                                frame[j]=a[i];
                                                j=(j+1)%no;
                                                count++;
                                                //for(k=0;k<no;k++)
                                                //printf("%d\t",frame[k]);
}
                                    //printf("\n");
}
                        //printf("Page Fault is %d\n",count);
			//hr=(n-count)*1.0/n;
			//mr=count*1.0/n;
			//printf("Hit Ratio is %lf\n",hr);
			//printf("Miss Ratio is %lf\n",mr);
			return count;
}

int sys_lru(void)
{
int q[20],p[50],c=0,c1,f,i,j,k=0,n,r,t,b[20],c2[20];
 n=20; //no.of pages
	p[1]=3,p[2]=5,p[3]=1,p[4]=3,p[5]=7,p[6]=4,p[7]=9,p[8]=2,p[9]=9,p[10]=8,p[11]=5,p[12]=9,p[13]=7,p[14]=5,p[15]=3,p[16]=7,p[17]=6,p[18]=8,p[19]=3,p[20]=1; //page numbers
            f=4; //no.of frames
q[k]=p[k];
//printf("\n\t%d\n",q[k]);
c++;
k++;
for(i=1;i<n;i++)
            {
                        c1=0;
                        for(j=0;j<f;j++)
                        {
                                    if(p[i]!=q[j])
                                    c1++;
                        }
                        if(c1==f)
                        {
                                    c++;
                                    if(k<f)
                                    {
                                                q[k]=p[i];
                                                k++;
                                          //      for(j=0;j<k;j++)
                                            //    printf("\t%d",q[j]);
                                              //  printf("\n");
                                    }
                                    else
                                    {
                                                for(r=0;r<f;r++)
                                                {
                                                            c2[r]=0;
                                                            for(j=i-1;j<n;j--)
                                                            {
                                                            if(q[r]!=p[j])
                                                            c2[r]++;
                                                            else
                                                            break;
                                                }
                                    }
                                    for(r=0;r<f;r++)
                                     b[r]=c2[r];
                                    for(r=0;r<f;r++)
                                    {
                                                for(j=r;j<f;j++)
                                                {
                                                            if(b[r]<b[j])
                                                            {
                                                                        t=b[r];
                                                                        b[r]=b[j];
                                                                        b[j]=t;
                                                            }
                                                }
                                    }
                                    for(r=0;r<f;r++)
                                    {
                                                if(c2[r]==b[0])
                                                q[r]=p[i];
                                        //        printf("\t%d",q[r]);
                                    }
                                    //printf("\n");
                        }
            }
}
return c;
}

int sys_optimal(void)
{
int fr[100];
	int p[100],pt[100];
	int n,f,i,cnt=0,pf=0,c,d,swap;
	 n=20; //no.of pages
	p[1]=3,p[2]=5,p[3]=1,p[4]=3,p[5]=7,p[6]=4,p[7]=9,p[8]=2,p[9]=9,p[10]=8,p[11]=5,p[12]=9,p[13]=7,p[14]=5,p[15]=3,p[16]=7,p[17]=6,p[18]=8,p[19]=3,p[20]=1; //page numbers
	for(i=0;i<n;i++)
	{
		pt[i]=p[i];
	}
	f=4;
	for (c = 0 ; c < ( n - 1 ); c++)
  {
    for (d = 0 ; d < n - c - 1; d++)
    {
      if (pt[d] > pt[d+1]) /* For decreasing order use < */
      {
        swap       = pt[d];
        pt[d]   = pt[d+1];
        pt[d+1] = swap;
      }
    }
  }
	for(i=0;i<n-1;i++)
	{
		if(pt[i]!=pt[i+1])
		cnt++;
	}
	if(cnt>=f)
	pf=f;
	else
	pf=cnt;
	 //nt p[12]={2,3,2,1,5,2,4,5,3,2,5,2},i,j,fs[3];
	   int max,j,found=0,lg[f],index,k,flag1=0,flag2=0,frsize=f;
//	    clrscr();
	      for(i=0;i<f;i++)
	       {
		 fr[i]=-1;
	       }
		 for(j=0;j<n;j++)
	{
	   flag1=0;
	      flag2=0;
		for(i=0;i<f;i++)
	     {
		 if(fr[i]==p[j])
		  {
		    flag1=1;
		      flag2=1;
			     break;
		  }
	     }
	       if(flag1==0)
		{
		  for(i=0;i<f;i++)
		       {
			  if(fr[i]==-1)
				  {
				     fr[i]=p[j];
					flag2=1;
					   break;
				  }
			}
	       }
 
		 if(flag2==0)
		    {
		       for(i=0;i<f;i++)
			  lg[i]=0;
			      for(i=0;i<frsize;i++)
				       {
					  for(k=j+1;k<n;k++)
					       {
						  if(fr[i]==p[k])
						       {
							  lg[i]=k-j;
							      break;
						       }
				      }
			}
			  found=0;
			     for(i=0;i<frsize;i++)
				{
				   if(lg[i]==0)
					{
					 index=i;
					    found=1;
						break;
					  }
				  }
				    if(found==0)
					{
					  max=lg[0];
					     index=0;
						for(i=1;i<frsize;i++)
						   {
						     if(max<lg[i])
							{
							max=lg[i];
							 index=i;
					   }
			      }
		 }
	       fr[index]=p[j];
	       pf++;
	}
}	

	return pf;
}

