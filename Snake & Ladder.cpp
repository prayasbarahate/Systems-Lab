#include<iostream>
#include<stdlib.h>
#include<sys/wait.h>
#include<stdio.h>
#include<unistd.h>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;

int main(int argc, char *argv[])
{
	if(argc<4)
	{
		cout<<"less arguments"<<endl;
		return 0;
	}
	int n,s,fish=0;
	char *a=argv[1];
	char *b=argv[2];
	string filnam=argv[3];
	s=atoi(a);
	n=atoi(b);
	
	int snake_ladder[s+1];
	for(int i=0;i<=s;i++)
		snake_ladder[i]=0;
	string str;
	ifstream obj1;
	obj1.open(filnam);

	while(getline(obj1, str))
	{
		istringstream obj2(str);
		int count=1;
		int flag;
		string s1("L");
		string s2("l");
		string s3("S");
		string s4("s");
		while(obj2)
		{
			string red;
			obj2>>red;
			if(count==1)
			{
				if(red==s1 || red==s2)
					flag=0;

				if(red==s3 || red==s4)
					flag=1;
			}
			

			if(count==2)
			{
				int g=stoi(red);
				obj2>>red;
				int h=stoi(red);

				if(g<1 || g>s || h<1 || h>s)
				{
					cout<<"g:"<<g<<" h:"<<h<<" s:"<<s<<endl;
					cout<<"snake or ladder out of bound"<<endl;
					return 0;
				}

				if(snake_ladder[g]>0)
				{
					cout<<"Two ladder or snake at same position"<<endl;
					return 0;
				}
				
				if(flag==0)
				{
					if(g>h)
					{
						cout<<"wrong ladder created "<<endl;
						return 0;
					}
				}
				if(flag==1)
				{
					if(g<h)
					{
						cout<<"wrong snake created "<<endl;
						return 0;
					}
				}
				snake_ladder[g]=h;
			}
			count++;
		}
	} 
	
	//print snakes and ladder
	for(int i=1;i<=s;i++)
	{
		if(snake_ladder[i]>0)
			cout<<i<<"  "<<snake_ladder[i]<<endl;
	}
	
	
	//array to store child process id's
	int pid[n];
	//array to store current position of each player 
	int plpos[n];
	for(int i=0;i<n;i++)
		plpos[i]=0;

	//Creating 2n pipes
	int finolex[2*n][2];	
	for(int i=0;i<2*n;i++)
		{
			int status=pipe(finolex[i]);
			if(status!=0)
				cout<<"fail to create pipe"<<endl;
		}

	
	int par_id=getpid();
	
	for(int i=0;i<n;i++) 
    { 
    	int pid1=fork();
    	if(pid1<0)
    	{
    		cout<<"error creating process"<<endl;
    		exit(1);
    	}
        else if(pid1 == 0) 
        { 
        	if(getppid()!=par_id)
        		exit(1);
        	else
        	{
        		while(1)
        		{
	        	
	            	//printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
	            	int cat;           	
	            	close(finolex[2*i][1]);
		    		close(finolex[2*i+1][0]);
		    		read(finolex[2*i][0],&cat,sizeof(cat));
		    		//cout<<"child reads "<<cat<<endl;

		    		if(cat==-5)
		    		{
		    			cout<<"child process " <<getpid()<<" closed"<<endl;
		    			exit(0);
		    		}
		    		if(getpid()==cat)
		    		{
		    			srand(time(0)+i+13);
		    			int dog=rand()%6+1;
		    			write(finolex[2*i+1][1],&dog,sizeof(dog));
		    			//cout<<"child writes "<<dog<<endl;

		    		}
	        	
        		}
        	}
        } 
        else
        { 
        	pid[i]=pid1;
        	//wait(NULL);
        }
    } 

    
    //print process id's
    //if(getpid()==par_id)
    //{
    //	for(int i=0;i<n;i++)
	//		cout<<pid[i]<<" ";
    //}
    
    srand(time(0)+13);
    int chance=rand()%n;
    
		//cout<<"chance : "<<chance<<endl;

	//till game ends
	while(1)
	{
		if(getpid()==par_id)
    	{
			int apple=pid[chance];
			int banana; 
			close(finolex[2*chance][0]);
			close(finolex[2*chance+1][1]);
			write(finolex[2*chance][1], &apple, sizeof(apple));
			//cout<<"parent writes "<<apple<<endl;
			read(finolex[2*chance+1][0],&banana,sizeof(banana));
			//cout<<"parent reads "<<banana<<endl;
			
			plpos[chance]+=banana;

			//condition for loop break
			if(plpos[chance]>=s)
			{
				
				for(int i=0;i<n;i++)
					cout<<"player "<<i<<" at : "<<plpos[i]<<endl;
			    cout<<"game ends with winner as PLAYER "<<chance<<endl;

			    //send -5 to all pipes
			    for(int k=0;k<2*n;k=k+2)
			    {
			    	int elephant=-5;
			    	close(finolex[k][0]);
					close(finolex[k+1][1]);
					write(finolex[k][1], &elephant, sizeof(elephant));
			    }
			    fish=1;
				break;
			}

			while(snake_ladder[plpos[chance]]>0)
			{
				plpos[chance]=snake_ladder[plpos[chance]];
				//cout<<"snake or ladder used"<<endl;
			}

			//display position of all players
			for(int i=0;i<n;i++)
				cout<<"player "<<i<<" at : "<<plpos[i]<<endl;
			cout<<endl;

			//condition for loop break
			if(plpos[chance]>=s)
			{
				cout<<"game ends with winner as PLAYER "<<chance<<endl;
				//send -5 to all pipes
			    for(int k=0;k<2*n;k=k+2)
			    {
			    	int elephant=-5;
			    	close(finolex[k][0]);
					close(finolex[k+1][1]);
					write(finolex[k][1], &elephant, sizeof(elephant));
			    }
			    fish=1;
				break;
			}

			if(banana!=6)
				chance=(chance+1)%n;	
    	}
	}

	wait(NULL);

	for(int i=0;i<2*n;i++)
	{
		for(int j=0;j<=1;j++)
		{
			close(finolex[i][j]);
		}
	}

	cout<<"all pipes closed"<<endl;

	if(fish==1)
	{
		cout<<"parent process closed"<<endl;
		exit(0);
	}	
    
    return 0;
}