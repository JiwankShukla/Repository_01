using namespace std;
#include<iostream>
#include<conio.h>
int timer=0;
class process
{
	public:
		static int count;
		int pn,pid,at,bt,pbt,ct,tat,wt;
		process()
		{
			at=0;
			ct=0;
		}
		
		void input()
		{
			pid=++count;
			cout<<"\n\nFor process ID         : "<<pid<<endl;
			cout<<"Enter priority number  : ";
			cin>>pn;
			cout<<"Enter Arrival Time     : ";
			cin>>at;
			cout<<"Enter Burst time       : ";
			cin>>bt;
			pbt=bt;
		}
		
		void execution(int &t)
		{
			if(bt>0 && bt-t>0)
				bt-=t;
			else
			{
				t=bt;
				bt=0;
			}
		}
		
		void reset(int &timer)
		{
			timer=0;
			bt=pbt;
			ct=0;
		}
		
		void display(int timer=0)
		{
			cout<<"\t   "<<pid<<"\t    |  "<<timer<<"\t\t"<<pn<<"\t\t"<<at<<"\t\t  "<<pbt<<"\t\t\t"<<bt<<"\n";
			cout<<"\t------------|----------------------------------------------------------------------------------------------\n";
		}
		
		void finaldis()
		{
			cout<<"\t   "<<pid<<"\t\t|\t "<<pn<<"\t\t    "<<at<<"\t\t\t  "<<pbt<<"\t\t\t "<<ct<<"\t\t\t  "<<tat<<"\t\t       "<<wt<<"\n";
			cout<<"\t----------------|-----------------------------------------------------------------------------------------------------------------------------\n";
		}	
};

int process::count=0;

void header()
{
	cout<<"\n\n\tProcess ID"<<"  | Timer     "<<"Priority number"<<"\t  Arrival Time"<<"\t   Initial Burst time"<<"\t   Burst time\n";
	cout<<"\t------------|----------------------------------------------------------------------------------------------\n";
}

void finalhead()
{
	cout<<"\n\n\tProcess ID"<<"\t|  priority number"<<"     Arrival Time"<<"\t  Initial Burst time"<<"\t   Completion time"<<"\t   Turn-around time"<<"\t   Waiting time\n";
	cout<<"\t----------------|-----------------------------------------------------------------------------------------------------------------------------\n";
}

void finalcal(process p[],int n)
{
	float avgtat=0,avgwt=0;
	finalhead();
	for(int i=0;i<n;i++)
	{
		p[i].tat=p[i].ct-p[i].at;
		p[i].wt=p[i].tat-p[i].pbt;
		p[i].finaldis();
		avgtat=avgtat+p[i].tat;
		avgwt=avgwt+p[i].wt;
	}
	avgtat=avgtat/n;
	avgwt=avgwt/n;
	cout<<"\n\t\tAverage Turn-Around Time  : "<<avgtat<<"\n\n\t\tAverage Waiting Time      : "<<avgwt;
}

void arrivalsort(process p[],int n)
{
	int i,j,k;
	process z;
	for(i=1;i<n;i++)
		{
			k=p[i].at;
			z=p[i];
			j=i-1;
			while(j>=0 && p[j].at>k)
			{
				p[j+1]=p[j];
				--j;
			}
			p[j+1]=z;	
		}
}

void prioritysort(process p[],int n)
{
	int i,j,k;
	process z;
	for(i=1;i<n;i++)
		{
			k=p[i].pn;
			z=p[i];
			j=i-1;
			while(j>=0 && p[j].pn<k)
			{
				p[j+1]=p[j];
				--j;
			}
			p[j+1]=z;
		}	
}

int maxpn(int k,process p[])
{
	int max=p[0].pn,j=0;
	for(int i=0;i<k;i++)
	{
		if(max<p[i].pn)
		{
			max=p[i].pn;
			j=i;
		}
		
	}
	return j;
}

void algo(process p[],int t,process maxat,int n)
{
	int i,k,temp,l=0,j=0;
	timer=p[0].at;
	header();
	while(true)
	{
		k=0;
		for(i=0;i<n;i++)
		{
			if(p[i].at<=timer)
				{
					++k;
				}	
		}
		j=maxpn(k,p);				
		if (timer>=maxat.at)
		{
			prioritysort(p,n);
			for(i=0;i<n;i++)
			{
				if(p[i].bt!=0)
				{
					temp=p[i].bt;
					p[i].execution(p[i].bt);
					p[i].display(timer);
					timer+=temp;
					if(p[i].ct==0)
						p[i].ct=timer;
				}
			}
			break;
		}				
		else if(p[j].at<=timer && p[j].bt!=0)
		{
			temp=t;
			p[j].execution(t);
			p[j].display(timer);	
			timer=timer+t;
			t=temp;
			if(p[j].bt==0)
				p[j].ct=timer;
		}
		else
		{
			if(p[l].bt!=0)
			timer=p[l].at;
			++l;
		}
				
	}
}

void front()
{
	cout<<"\n\n\t\t\t\t\tWELCOME TO PRIORTY PROCESS SCHEDULER\n\n";
	cout<<"\n\n\t\t1. Create and Add more process\n\n\t\t2. Reset or Display initial input Processes\n\n\t\t3. Delete process\n\n\t\t4. Run Scheduling\n\n\t\t5. Final Result\n\n\t\t6. Exit\n\n\tOption: ";
}

main()
{
	int exit = 1,n=0,n1,opt,i,t,c=0;
	process p[10],maxat;
	while(exit==1)
	{
		system("CLS");
		front();
		cin>>opt;
		switch(opt)
		{
			case 1: system("CLS");
					cout<<"\n\n\n\tEnter number of process\n\n\t( Limit: 10 process )\n\t( PRESS 0 for main menu ): \t";
					cin>>n1;
					system("CLS");
					n1=n1+n;
					for(i=n;i<n1;i++)
					{
						p[i].input();
					}
					n=n1;
					prioritysort(p,n);
					arrivalsort(p,n);
					maxat=p[n-1];
					break;
					
			case 2: system("CLS");
					header();
					for(i=0;i<n;i++)
					{
						p[i].reset(timer);
						p[i].display(timer);
					}
					if(p[0].bt!=0)
					cout<<"\n\n\n\t\tPROCESS RESET TO INITIAL INPUT\n\n\t\tPROCESS IS NOW READY FOR ' RUN SCHEDULER '.\n\n\n";
					cout<<"\n\n\tPress ENTER or any key to go back.";
					getch();
					break;
					
			case 3: system("CLS");
					int d;
					header();
					for(i=0;i<n;i++)
					{
						p[i].display(timer);
					}
					cout<<"\n\tEnter process ID you want deleted \n\n\t(Enter 0 to delete all)\n\t(Enter '111' for main menu) : \t";
					cin>>d;
					if(d==111)
					break;
					for(i=0;i<n;i++)
					{
						if(d==0)
						{
							n=0;
							process::count=0;
						}
						else if(d<=p[i].pid && i+1!=n)
						{
							c++;
							p[i]=p[i+1];
						}
						else if(d==p[i].pid)
							c++;
					}
					if(c!=0)
						--n;
					cout<<"\n\nAfter Delete:\n ";
					header();
					for(i=0;i<n;i++)
					{
						p[i].display(timer);
					}
					cout<<"\n\n\tPress ENTER or any key to go back.";
					getch();
					break;
					
			case 4: system("CLS");
					if(maxat.at==0)
						cout<<"\n\n\tERROR ...... No Process is avalaible\n\n\t\tGo to option 1 (' Create and Add more process ') in MAIN MENU.\n\n";
					else if(timer>=maxat.at)
						cout<<"\n\n\tERROR ...... Reset to intial input first\n\n\t\tGo to option 2 (' Reset or Display initial input Processes ') in MAIN MENU.\n\n";
					else
					{
						cout<<"\n\tEnter Time quantum: ";
						cin>>t;
						cout<<"\n\tIntial value of timer: "<<timer;
						algo(p,t,maxat,n);
						arrivalsort(p,n);
						cout<<"\n\tFinal value of timer: "<<timer;
					}
					cout<<"\n\n\n\tPress ENTER or any key to go back.";
					getch();
					break;
					
			case 5: system("CLS");
					if(timer<=maxat.at)
						cout<<"\n\n\tERROR ...... Scheduler was not initiated, no processing was performed..!\n\n\t\tGo to option 4 (' Run Scheduling ') in MAIN MENU.\n\n";
					else
					{
						finalcal(p,n);
					}
					getch();
					break;
					
			case 6: exit=0;
					break;
		}
	}
}
