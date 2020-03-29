using namespace std;
#include<iostream>
#include<conio.h>
int timer=0;
class process				// This Class contains arrival, burst, waiting, completion and Turnaround time of each process.
{	
	public:
		static int count;
		int pn,pid,at,bt,pbt,ct,tat,wt;
		process()			// Constructon to set Arrival time and completion time value to 0 initially.
		{
			at=0;
			ct=0;
		}
		
		void input()
		{
			pid=++count;
			cout<<"\n\nFor process ID         : "<<pid<<endl;	// Process ID value taken as input.
			cout<<"Enter priority number  : ";					
			cin>>pn;											// Priority number taken as input.
			cout<<"Enter Arrival Time     : ";
			cin>>at;											// Arrival Time taken as input.
			cout<<"Enter Burst time       : ";
			cin>>bt;											// Burst Time taken as input.
			pbt=bt;
		}
		
		void execution(int &t)		// This function execute the burst time by taking timer value and return new value of timer.
		{
			if(bt>0 && bt-t>0)
				bt-=t;
			else
			{
				t=bt;
				bt=0;
			}
		}
		
		void reset(int &timer)		// This function reset timer and completion time of each process to 0,
		{							// and reset burst time to initial burst time value.
			timer=0;
			bt=pbt;
			ct=0;
		}
		
		void display(int timer=0)	// This function display all the attributes of each process at the time of scheduling.
		{
			cout<<"\t   "<<pid<<"\t    |  "<<timer<<"\t\t"<<pn<<"\t\t"<<at<<"\t\t  "<<pbt<<"\t\t\t"<<bt<<"\n";
			cout<<"\t------------|----------------------------------------------------------------------------------------------\n";
		}
		
		void finaldis()				// This function display the final value of all the attributes of each process after scheduling .
		{
			cout<<"\t   "<<pid<<"\t\t|\t "<<pn<<"\t\t    "<<at<<"\t\t\t  "<<pbt<<"\t\t\t "<<ct<<"\t\t\t  "<<tat<<"\t\t       "<<wt<<"\n";
			cout<<"\t----------------|-----------------------------------------------------------------------------------------------------------------------------\n";
		}	
};

int process::count=0; 		// Counter is declare and initialize to keep count of each object and to get Process ID.

void header()				// This function is just to give a header as a layout.
{
	cout<<"\n\n\tProcess ID"<<"  | Timer     "<<"Priority number"<<"\t  Arrival Time"<<"\t   Initial Burst time"<<"\t   Burst time\n";
	cout<<"\t------------|----------------------------------------------------------------------------------------------\n";
}

void finalhead()			// This function is just to give a header as a layout.
{
	cout<<"\n\n\tProcess ID"<<"\t|  priority number"<<"     Arrival Time"<<"\t  Initial Burst time"<<"\t   Completion time"<<"\t   Turn-around time"<<"\t   Waiting time\n";
	cout<<"\t----------------|-----------------------------------------------------------------------------------------------------------------------------\n";
}

void finalcal(process p[],int n)		// This function is to calculate the final value of each process.
{
	float avgtat=0,avgwt=0;
	finalhead();						// Header is called here
	for(int i=0;i<n;i++)
	{
		p[i].tat=p[i].ct-p[i].at;
		p[i].wt=p[i].tat-p[i].pbt;
		p[i].finaldis();				// Header is called here.
		avgtat=avgtat+p[i].tat;			// Average Turnaround time is calculated.
		avgwt=avgwt+p[i].wt;			// Averaage waiting time is calculated.
	}
	avgtat=avgtat/n;
	avgwt=avgwt/n;
	cout<<"\n\t\tAverage Turn-Around Time  : "<<avgtat<<"\n\n\t\tAverage Waiting Time      : "<<avgwt;		// Average Turnaround and Waiting time is displayed.
}

void arrivalsort(process p[],int n)			// This function sort process according to Arrival time in Increasing order. (Insertion Sort)
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

void prioritysort(process p[],int n)			// This function sort process according to Priority number in Decreasing order. (Insertion Sort)
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

int maxpn(int k,process p[])			// This function return process of highest priority number.
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

void algo(process p[],int t,process maxat,int n)		// This is the Main Algorithem which run scheduling according to Arrival time and priority number.
{
	int i,k,temp,l=0,j=0;
	timer=p[0].at;					// Here timer is set to first process having least Arrival time.
	header();
	while(true)				// While loop which run until break line is executed.
	{
		k=0;
		for(i=0;i<n;i++)
		{
			if(p[i].at<=timer)
				{
					++k;		// This variable keep count of the process which have arrived within the timer.
				}	
		}
		j=maxpn(k,p);				// Here variable is set to the index value of highest priority number, which have arrived within the timer.
		if (timer>=maxat.at)		// This condition will only be true when all the processes have arrived. 
		{
			prioritysort(p,n);		// Processes are sort in Descending order depending on the priority number.
			for(i=0;i<n;i++)
			{
				if(p[i].bt!=0)		// This condition will run if the burst time of the process is not equal to zero. 
				{
					temp=p[i].bt;
					p[i].execution(p[i].bt);		// Remaining Burst time of the process is executed and timer also updated.
					p[i].display(timer);			// Value of updated timer and resulted burst time is displayed with every other attribute of the process.
					timer+=temp;
					if(p[i].ct==0)				// If the completion time of the process was not already calculated then this condition will run.
						p[i].ct=timer;		// Completion time of the process is set. 
				}
			}
			break;
		}				
		else if(p[j].at<=timer && p[j].bt!=0)		// This conditon will run for highest priority process for which burst time is not zero.
		{
			temp=t;
			p[j].execution(t);			// Burst time is executed and updated depending on time quantum 't'.
			p[j].display(timer);		// Updated Burst time is displayed with other attributes.
			timer=timer+t;				// Timer is incremented.
			t=temp;
			if(p[j].bt==0)			// When Burst timee value of the process become zero this condtion will be true.
				p[j].ct=timer;		//	Completion time is set of the process as soon as burst time become zero.
		}
		else		// This will run when the burst time of any process become zero but all the process have not arrived.
		{
			if(p[l].bt!=0)				// Here burst time of that process is check which still not have arrived but is next in the queue.
				timer=p[l].at;			// timer is updated to Arrival time of process which is next in queue.
			++l;					// If Burst time of the next process is also 0 then this variable is increamented to check further in queue.
		}
				
	}
}

void front()		// This function will show the main menu of the program with different options.
{
	cout<<"\n\n\t\t\t\t\tWELCOME TO PRIORTY PROCESS SCHEDULER\n\n";
	cout<<"\n\n\t\t1. Create and Add more process\n\n\t\t2. Reset or Display initial input Processes\n\n\t\t3. Delete process\n\n\t\t4. Run Scheduling\n\n\t\t5. Final Result\n\n\t\t6. Exit\n\n\tOption: ";
}

main()		// Program starts from here.
{
	int exit = 1,n=0,n1,opt,i,t,c=0;
	process p[20],maxat;				// Here Object of class process is created where each object represent single process.
	while(exit==1)			// A while loop, runs until user chooses to exit.
	{
		system("CLS");
		front();			// Main Menu is displayed.
		cin>>opt;			// Here user will be able to choose different option represented in main menu.
		switch(opt)
		{
			case 1: system("CLS");			// In this case, user be able to add process and its attribute values.
					cout<<"\n\n\n\tEnter number of process\n\n\n\t( PRESS 0 for main menu ): \t";
					cin>>n1;			// Number of process is asked.
					system("CLS");
					n1=n1+n;				// Number of process is added to existing number of the process.
					for(i=n;i<n1;i++)
					{
						p[i].input();		// User is able to input different attribute of a each process like AT,BT,etc.
					}
					n=n1;
					prioritysort(p,n);		// Processes are first sorted in descending order based on Priority number.
					arrivalsort(p,n);		// Then, Processes are sorted on the basis of Arrival time in ascending. 
					maxat=p[n-1];		// 'maxat' will represent the process which arrive at last.
					break;
					
			case 2: system("CLS");			// In this case, user be able to see what all processes are inputed and also reset all process to their initial values.
					header();
					for(i=0;i<n;i++)
					{
						p[i].reset(timer);		// This will reset each process attributes to thier initial value,
						p[i].display(timer);		//And display all attributes of each process.
					}
					if(p[0].bt!=0)			// This condition will be true only if processes are not set to thier initial values.
					cout<<"\n\n\n\t\tPROCESS RESET TO INITIAL INPUT\n\n\t\tPROCESS IS NOW READY FOR ' RUN SCHEDULER '.\n\n\n";
					cout<<"\n\n\tPress ENTER or any key to go back.";
					getch();
					break;
					
			case 3: system("CLS");			// In this case, user be able to delete process depending on process ID.
					int d;
					header();
					for(i=0;i<n;i++)
					{
						p[i].display(timer);		// Display process before delete.
					}
					cout<<"\n\tEnter process ID you want deleted \n\n\t(Enter 0 to delete all)\n\t(Enter '111' for main menu) : \t";
					cin>>d;				// Process ID is inputed of which user want to delete.
					if(d==111)		// If user typed '111', user be able to exit delete menu.
					break;
					for(i=0;i<n;i++)
					{
						if(d==0)		// In this condition, all Processes are deleted.
						{
							n=0;
							process::count=0;
						}
						else if(d<=p[i].pid && i+1!=n)		// If process ID exist then it get deleted.
						{
							c++;
							p[i]=p[i+1];
						}
						else if(d==p[i].pid)	// If process ID is of last process then this condition is true.
							c++;
					}
					if(c!=0)		// If any process is deleted then this condition is true.
						--n;		// Number of process is decremented.
					cout<<"\n\nAfter Delete:\n ";
					header();
					for(i=0;i<n;i++)
					{
						p[i].display(timer);		// Display process after delete.
					}
					cout<<"\n\n\tPress ENTER or any key to go back.";
					getch();
					break;
					
			case 4: system("CLS");			// In this case, User is able to call main algo and scheduling is performed.
					if(maxat.at==0)		// If no process is available, user is asked to create process in optiion 1 of main menu.
						cout<<"\n\n\tERROR ...... No Process is avalaible\n\n\t\tGo to option 1 (' Create and Add more process ') in MAIN MENU.\n\n";
					else if(timer>=maxat.at)		// Once case 4 is executed, user is required to go throught option 2 before running case 4 again.
						cout<<"\n\n\tERROR ...... Reset to intial input first\n\n\t\tGo to option 2 (' Reset or Display initial input Processes ') in MAIN MENU.\n\n";
					else
					{
						cout<<"\n\tEnter Time quantum: ";
						cin>>t;											// User is asked to enter time quantum.
						cout<<"\n\tIntial value of timer: "<<timer;		// Initial timer value is displayed.
						algo(p,t,maxat,n);								// Main algo is called which perform scheduling.
						arrivalsort(p,n);								// Processes are once again sorted on basis on Arrival time after scheduling. 
						cout<<"\n\tFinal value of timer: "<<timer;		// Final timer value timer is displayed.
						cout<<"\n\n\tNow go to option 5 (' Final Result ') ";
					}
					cout<<"\n\n\n\tPress ENTER or any key to go back.";
					getch();
					break;
					
			case 5: system("CLS");			// In this case, Final result is displayed once scheduling is executed.
					if(timer<=maxat.at)			// When scheduling is not run before this case, then user is asked to go option 4 first.
						cout<<"\n\n\tERROR ...... Scheduler was not initiated, no processing was performed..!\n\n\t\tGo to option 4 (' Run Scheduling ') in MAIN MENU.\n\n";
					else
					{
						finalcal(p,n);		// Final value is calculated and displayed once scheduling is executed.
					}
					getch();
					break;
					
			case 6: exit=0;			// In this case, user be able to exit the program by ending while loop.
					break;
		}
	}
}
