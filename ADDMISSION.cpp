#include <iostream>
#include<string>
using namespace std;
 
class student
{
	public:
		friend class admission;
		
		string name,branch;
		int pref[3],br[3];
		long regno;
		int pcm,jee,cet;
		
		void accept();
		void display();
};

class admission : public student
{
	student std[60];
	
	public:
		int n;
		
		admission()
		{
			n = 0;
		}
		
		void sort();
		void acceptstudent();
		void displayStudents();
		void allocate();
		void add();
		void rejectStudent(student s);
		void delet();
};

void student::accept()
{
	int flag=-1;
	
	cout<<"\nNAME: ";
	cin>>name;

	cout<<"\nCET SCORE: ";
	cin>>cet;
	if(cet>200 || cet<0)
	{
		while(cet>200 || cet<0)
		{
			cout<<"\nEnter Valid Percentage(<200)!\nRe-Enter CET Score: ";
			cin>>cet;
		}
	}
	
	cout<<"\nJEE SCORE: ";
	cin>>jee;
	if(jee>360)
	{			
		while(jee>360)
		{
			cout<<"\nEnter Valid Marks(<360)!\nRe-Enter JEE Marks: ";
			cin>>jee;
		}
	}
	
	cout<<"\nPCM SCORE(in %): ";
	cin>>pcm;
	if(pcm>100 || pcm<0)
	{
		while(pcm>100 || pcm<0)
		{
			cout<<"\nEnter Valid Percentage(<100)!\nRe-Enter PCM Score: ";
			cin>>pcm;
		}
	}
	
	do
	{
		cout<<"\nFILL BRANCH PREFERENCES (ENTER>> 1-COMP, 2-ENTC, 3-MECH, 4-NO PREFERENCE): ";
		
		for(int i = 0; i < 3; i++)
		{
			cin>>pref[i];
		}
		
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
			{
				if(pref[j]==pref[k] && k!=j)
				{
					flag=1;
					break;
				}
				else
				{
					flag=0;
				}
			}
		}
		
	}while(flag==1);
}



void student::display()
{
	cout<<"\nNAME: "<<name;
	cout<<"\nREGISTRATION NUMBER: "<<regno;
	cout<<"\nSCORE: ";
	cout<<"\n\tPCM: "<<pcm;
	cout<<"\n\tCET: "<<cet;
	cout<<"\n\tJEE: "<<jee;
	cout<<"\nBRANCH PREFERENCES: ";
	
	for(int i = 0; i<3; i++)
	{
		if(pref[i] == 1)
		{
			cout<<"\n\t"<<i+1<<"-COMP";
		}
		else if(pref[i] == 2)
		{
			cout<<"\n\t"<<i+1<<"-ENTC";
		}
		else if(pref[i] == 3)
		{
			cout<<"\n\t"<<i+1<<"-MECH";
		}
	}
	cout<<"\n\n";
}

void admission::acceptstudent()
{
	int flag=0;
	long reno;
	int pos = 0;
	
	cout<<"\nENTER NUMBER OF STUDENTS: ";
	cin>>n;
	
	cout<<"\nDETAILS OF THE APPLICANTS>>>\n";
	
	for(int i = 0; i < n; i++)
	{
		do
		{
			cout<<"\nREGISTRATION NUMBER: ";
			cin>>reno;
			
			std[i].regno = reno;
			
			flag = 0;
			
			for(int k = 0; k < i; k++)
			{
				
				if(std[k].regno == reno)
				{
					flag = 1;
					cout<<"\nRegistration Number Already Used.\nTry Again";
				}
			}
		}while(flag !=0 );
		
		
		std[i].accept();
		cout<<"__________________________________________________________________________________________";
	}
}

void admission::displayStudents()
{
	
	for(int i = 0; i < n; i++)
	{
		if(std[i].pcm < 75)
		{
		   	cout<<"\nForm "<<std[i].name<<" REG. NO. "<< std[i].regno<<" Is Rejected\n";
		   	rejectStudent(std[i]);		   	
		}
		
		if(std[i].regno != 0)
		{
			std[i].display();
		}
		
		cout<<"__________________________________________________________________________________________";
	}
}

void admission::add()
{
	char ch;
	int no;
	int flag = 0;
	int reno;
	
	if(n == 15)
	{
		cout<<"\nAdmission Is Full";
	}
	else
	{
		cout<<"\nNUMBER OF STUDENTS TO BE ADDED: ";
		cin>>no;

		n = n + no;
		
		for(int i = n - no; i < n ; i++)
		{
			do
			{
				cout<<"\nREGISTRATION NUMBER: ";
				cin>>reno;
				
				std[i].regno = reno;
				flag=0;
			
				for(int k=0; k<i ; k++)
				{
					if(std[k].regno == std[i].regno)
					{
						flag=1;
						cout<<"\nRegistration Number Already Used\nTry Again";
					}
				}
			
			}while(flag!=0);
		
			std[i].accept();
		}
	}
}

void admission::rejectStudent(student s)
{
	int count=0;
	
	for(int k=0; k<n; k++)
	{
		for(int i = k; i < n; i++)
		{
		
			std[i] = std[i+1];
			std[i+1].regno=0;
		
		}
		count ++;
	}
    n = n-count-1;
}

void admission::delet()
{
	long reg;
	int count=0,flag=0;
	
	cout<<"\nDROP APPLICATION FORM>>>";
	cout<<"\n\nREGISTRATION NUMBER: ";
	cin>>reg;
	
	for(int k=0; k<n; k++)
	{
		if(reg == std[k].regno)
		{
			for(int i = k; i < n; i++)
			{
			
				std[i] = std[i+1];
				flag=1;
			}
			count ++;
		}
	}
    		n = n-count;
    		
    		if(flag==0)
    		{
    			cout<<"\nRegistration Number Not Found\n";
			}
			if(flag==1)
			{
				cout<<"\nAdmission Cancelled";
			}
}

void admission::sort()
{
	student temp;
	
	for(int i = 0; i < n; i++)
	{
		for(int j = i+1; j < n; j++)
		{
			if(std[i].cet==std[j].cet)
			{
				if(std[i].jee < std[j].jee)
				{
					temp = std[i];
					std[i]= std[j];
					std[j] = temp;
				}
			}
			else
			if(std[i].cet < std[j].cet)
			{
				temp = std[i];
				std[i]= std[j];
				std[j] = temp;
			}
		}
	}
}

void admission::allocate()
{
	sort();	
	int flag=0;	
	int seats[3]={2,2,2};
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=1;k<4;k++)
			{
				if(std[i].pref[j]==k && seats[j]!=0)
				{
					std[i].br[j]=k;
				}	
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(std[i].br[j] == 3 && seats[j]>0)
			{
				std[i].branch = "MECH";
				seats[j]--;
				break;		
			}
			else if(std[i].br[j] == 2 && seats[j]>0)
			{
				std[i].branch = "ENTC";
				seats[j]--;
				break;
			}
			else if(std[i].br[j] == 1 && seats[j]>0)
			{
				std[i].branch = "COMP";
				seats[j]--;
				break;
			}
		}
	}	
	for(int i=0;i<n;i++)
	{
		std[i].display();
		cout<<"\nBRANCH ALLOCATED: "<<std[i].branch;
	}
}


int main(void)
{
	admission a;
	int choice;
	char ch1;
	cout<<"..................WELCOME..................\n";
	do
	{
		cout<<"\n================================================================================";
		cout<<"\n\n\tMAIN MENU";
		cout<<"\n\na-TO FILL APPLICATION FORM\nb-TO CHECK ALLOCATION STATUS \nc-EXIT";
		cout<<"\n================================================================================";
		
		cout<<"\nENTER CHOICE: ";
		cin>>ch1;
		
		switch(ch1)
		{
			
		case 'a':
				do 
				{
					cout<<"\n================================================================================";
					cout<<"\n\n\tMENU";
					cout<<"\n\n1-FILL STUDENT DETAILS \n2-DISPLAY STUDENT DETAILS\n3-ADD MORE STUDENTS\n4-DELETE STUDENT\n0.BACK";
					cout<<"\n================================================================================";
					
					cout<<"\nENTER CHOICE: ";
		     		cin>>choice;
		     		
					switch(choice)
					{
						case 1:
				              	a.acceptstudent();
				              	break;
				              
			        	case 2:
				             	a.displayStudents();
				             	break;
				              
				        case 3:
				             	a.add();
				           	  	break;
				           	  
				     	case 4:
				     			a.delet();
				     			break;
				           	  	
		           }
		           	  
				}while(choice!=0);
				break;
		
		  
	    case 'b': 
				cout<<"\nALLOCATION OF BRANCHES>>>\n";
				
				if(a.n == 0)
				{
					cout<<"\nNo Forms Filled Yet";
				}
				else
				{
					a.allocate();
				}
	    		
				break;
			
		case 'c':
				break;	
				
	       	}
        
    }while(choice != 'c');
    
    cout<<"THANK YOU!";
	
	return 0;
}


/*..................WELCOME..................

================================================================================

        MAIN MENU

a-TO FILL APPLICATION FORM
b-TO CHECK ALLOCATION STATUS
c-EXIT
================================================================================
ENTER CHOICE: a

================================================================================

        MENU

1-FILL STUDENT DETAILS
2-DISPLAY STUDENT DETAILS
3-ADD MORE STUDENTS
4-DELETE STUDENT
0.BACK
================================================================================
ENTER CHOICE: 1

ENTER NUMBER OF STUDENTS: 3

DETAILS OF THE APPLICANTS>>>

REGISTRATION NUMBER: 1

NAME: raksha

CET SCORE: 144

JEE SCORE: 78

PCM SCORE(in %): 89

FILL BRANCH PREFERENCES (ENTER>> 1-COMP, 2-ENTC, 3-MECH, 4-NO PREFERENCE): 1
2
3
__________________________________________________________________________________________
REGISTRATION NUMBER: 2

NAME: sakshi

CET SCORE: 155

JEE SCORE: 232

PCM SCORE(in %): 89

FILL BRANCH PREFERENCES (ENTER>> 1-COMP, 2-ENTC, 3-MECH, 4-NO PREFERENCE): 1
2
3
__________________________________________________________________________________________
REGISTRATION NUMBER: 3

NAME: neha

CET SCORE: 134

JEE SCORE: 233

PCM SCORE(in %): 88

FILL BRANCH PREFERENCES (ENTER>> 1-COMP, 2-ENTC, 3-MECH, 4-NO PREFERENCE): 1
2
3
__________________________________________________________________________________________
================================================================================

        MENU

1-FILL STUDENT DETAILS
2-DISPLAY STUDENT DETAILS
3-ADD MORE STUDENTS
4-DELETE STUDENT
0.BACK
================================================================================
ENTER CHOICE: 2

NAME: raksha
REGISTRATION NUMBER: 1
SCORE:
        PCM: 89
        CET: 144
        JEE: 78
BRANCH PREFERENCES:
        1-COMP
        2-ENTC
        3-MECH

__________________________________________________________________________________________
NAME: sakshi
REGISTRATION NUMBER: 2
SCORE:
        PCM: 89
        CET: 155
        JEE: 232
BRANCH PREFERENCES:
        1-COMP
        2-ENTC
        3-MECH

__________________________________________________________________________________________
NAME: neha
REGISTRATION NUMBER: 3
SCORE:
        PCM: 88
        CET: 134
        JEE: 233
BRANCH PREFERENCES:
        1-COMP
        2-ENTC
        3-MECH

__________________________________________________________________________________________
================================================================================

        MENU

1-FILL STUDENT DETAILS
2-DISPLAY STUDENT DETAILS
3-ADD MORE STUDENTS
4-DELETE STUDENT
0.BACK
================================================================================
ENTER CHOICE: 0

================================================================================

        MAIN MENU

a-TO FILL APPLICATION FORM
b-TO CHECK ALLOCATION STATUS
c-EXIT
================================================================================
ENTER CHOICE: b

ALLOCATION OF BRANCHES>>>

NAME: sakshi
REGISTRATION NUMBER: 2
SCORE:
        PCM: 89
        CET: 155
        JEE: 232
BRANCH PREFERENCES:
        1-COMP
        2-ENTC
        3-MECH


BRANCH ALLOCATED: COMP
NAME: raksha
REGISTRATION NUMBER: 1
SCORE:
        PCM: 89
        CET: 144
        JEE: 78
BRANCH PREFERENCES:
        1-COMP
        2-ENTC
        3-MECH


BRANCH ALLOCATED: COMP
NAME: neha
REGISTRATION NUMBER: 3
SCORE:
        PCM: 88
        CET: 134
        JEE: 233
BRANCH PREFERENCES:
        1-COMP
        2-ENTC
        3-MECH


BRANCH ALLOCATED: ENTC
================================================================================

        MAIN MENU

a-TO FILL APPLICATION FORM
b-TO CHECK ALLOCATION STATUS
c-EXIT
================================================================================
ENTER CHOICE: a

================================================================================

        MENU

1-FILL STUDENT DETAILS
2-DISPLAY STUDENT DETAILS
3-ADD MORE STUDENTS
4-DELETE STUDENT
0.BACK
================================================================================
ENTER CHOICE: 3

NUMBER OF STUDENTS TO BE ADDED: 1

REGISTRATION NUMBER: 4

NAME: margo

CET SCORE: 145

JEE SCORE: 122

PCM SCORE(in %): 82

FILL BRANCH PREFERENCES (ENTER>> 1-COMP, 2-ENTC, 3-MECH, 4-NO PREFERENCE): 1
2
3

================================================================================

        MENU

1-FILL STUDENT DETAILS
2-DISPLAY STUDENT DETAILS
3-ADD MORE STUDENTS
4-DELETE STUDENT
0.BACK
================================================================================
ENTER CHOICE: 2

NAME: sakshi
REGISTRATION NUMBER: 2
SCORE:
        PCM: 89
        CET: 155
        JEE: 232
BRANCH PREFERENCES:
        1-COMP
        2-ENTC
        3-MECH

__________________________________________________________________________________________
NAME: raksha
REGISTRATION NUMBER: 1
SCORE:
        PCM: 89
        CET: 144
        JEE: 78
BRANCH PREFERENCES:
        1-COMP
        2-ENTC
        3-MECH

__________________________________________________________________________________________
NAME: neha
REGISTRATION NUMBER: 3
SCORE:
        PCM: 88
        CET: 134
        JEE: 233
BRANCH PREFERENCES:
        1-COMP
        2-ENTC
        3-MECH

__________________________________________________________________________________________
NAME: margo
REGISTRATION NUMBER: 4
SCORE:
        PCM: 82
        CET: 145
        JEE: 122
BRANCH PREFERENCES:
        1-COMP
        2-ENTC
        3-MECH

__________________________________________________________________________________________
================================================================================

        MENU

1-FILL STUDENT DETAILS
2-DISPLAY STUDENT DETAILS
3-ADD MORE STUDENTS
4-DELETE STUDENT
0.BACK
================================================================================
ENTER CHOICE: 4

DROP APPLICATION FORM>>>

REGISTRATION NUMBER: 4

Admission Cancelled
================================================================================

        MENU

1-FILL STUDENT DETAILS
2-DISPLAY STUDENT DETAILS
3-ADD MORE STUDENTS
4-DELETE STUDENT
0.BACK
================================================================================
ENTER CHOICE: 2

NAME: sakshi
REGISTRATION NUMBER: 2
SCORE:
        PCM: 89
        CET: 155
        JEE: 232
BRANCH PREFERENCES:
        1-COMP
        2-ENTC
        3-MECH

__________________________________________________________________________________________
NAME: raksha
REGISTRATION NUMBER: 1
SCORE:
        PCM: 89
        CET: 144
        JEE: 78
BRANCH PREFERENCES:
        1-COMP
        2-ENTC
        3-MECH

__________________________________________________________________________________________
NAME: neha
REGISTRATION NUMBER: 3
SCORE:
        PCM: 88
        CET: 134
        JEE: 233
BRANCH PREFERENCES:
        1-COMP
        2-ENTC
        3-MECH

__________________________________________________________________________________________
================================================================================

        MENU

1-FILL STUDENT DETAILS
2-DISPLAY STUDENT DETAILS
3-ADD MORE STUDENTS
4-DELETE STUDENT
0.BACK
================================================================================
ENTER CHOICE: 0

================================================================================

        MAIN MENU

a-TO FILL APPLICATION FORM
b-TO CHECK ALLOCATION STATUS
c-EXIT
================================================================================
ENTER CHOICE: b

ALLOCATION OF BRANCHES>>>

NAME: sakshi
REGISTRATION NUMBER: 2
SCORE:
        PCM: 89
        CET: 155
        JEE: 232
BRANCH PREFERENCES:
        1-COMP
        2-ENTC
        3-MECH


BRANCH ALLOCATED: COMP
NAME: raksha
REGISTRATION NUMBER: 1
SCORE:
        PCM: 89
        CET: 144
        JEE: 78
BRANCH PREFERENCES:
        1-COMP
        2-ENTC
        3-MECH


BRANCH ALLOCATED: COMP
NAME: neha
REGISTRATION NUMBER: 3
SCORE:
        PCM: 88
        CET: 134
        JEE: 233
BRANCH PREFERENCES:
        1-COMP
        2-ENTC
        3-MECH


BRANCH ALLOCATED: ENTC
================================================================================

        MAIN MENU

a-TO FILL APPLICATION FORM
b-TO CHECK ALLOCATION STATUS
c-EXIT
================================================================================
*/
