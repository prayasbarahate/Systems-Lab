#include<stdio.h>
#include<iostream>
#include <string>
#include <bits/stdc++.h> 
#include<fstream>
#include<sstream>
#include <sys/stat.h>
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<readline/readline.h>
#include<readline/history.h>
using namespace std;
#define color_green  "\033[1m\033[32m"  

void ls();
void ls_a();
void sort(string);
void sort_r(string);
void cp(string,string);
void cp_u(string,string);
void cat(string);
void cat_n(string);

int main()
{
	//cout<<"HII"<<endl;
	string str;
	string s("exit");
	string s1("ls");
	string s2("ls -a");
	string s3("sort");
	string s4("-r");
	string s5("cp");
	string s6("-u");
	string s7("cat");
	string s8("-n");
	system("clear");
	while(1){
	string rt="(prayas) ";
	char addr[2500];
	char imp[2500];
	chdir("/path/to/change/directory/to");
	getcwd(addr, sizeof(addr));
	string ty=":$ ";

	char * buffer;
	buffer=readline((rt+color_green+addr+"\033[0m"+ty).c_str());
	if (strlen(buffer) != 0)
	{
		add_history(buffer);
		strcpy(imp,buffer);
	} 
	string str(imp);
	if(str==s)
		exit(0);
	//FOR LS & LS-A
	if(str==s1)
		ls();
	if(str==s2)
		ls_a();

	//FOR CP & CP-U
	int count=1;
	istringstream obj(str);
	while(obj)
	{
		string red;
		obj>>red;
		if(count==1)
		{
			if(red!=s5)
			break;
		}
		if(count==2)
		{
			if(red==s6)
			{
				string red2;
				obj>>red;
				obj>>red2;
				cp_u(red,red2);
			}
			else
			{
				string red2;
				obj>>red2;
				cp(red,red2);
			}
		}
		count++;
	}

	//FOR SORT & SORT-R
	count=1;
	istringstream obj2(str);
	while(obj2)
	{
		string red;
		obj2>>red;
		if(count==1)
		{
			if(red!=s3)
			break;
		}
		if(count==2)
		{
			if(red==s4)
			{
				obj2>>red;
				sort_r(red);
			}
			else
			{
				//obj2>>red;
				sort(red);
			}
		}
		count++;
	}

	//FOR CAT & CAT-N
	count=1;
	istringstream obj3(str);
	while(obj3)
	{
		string red;
		obj3>>red;
		if(count==1)
		{
			if(red!=s7)
			break;
		}
		if(count==2)
		{
			if(red==s8)
			{
				cat_n(str);
			}
			else
			{
				
				cat(str);
			}
		}
		count++;
	}
	}
	return 0;
}

void ls()
{
	cout<<"IN LS"<<endl;
}

void ls_a()
{
	cout<<"IN LS_A"<<endl;
}

void sort(string s)
{
	cout<<"IN SORT"<<endl;
	cout<<"string is "<<s<<endl;

}

void sort_r(string s)
{
	cout<<"IN SORT_R"<<endl;
	cout<<"string is "<<s<<endl;

}

void cp(string a,string b)
{
	ifstream obj1;
	obj1.open(a);
	if(!obj1.is_open())
	{
		cout<<"cp: cannot stat '"<<a<<"': No such file or directory"<<endl;
		return ;
	}

	ofstream obj2;
	obj2.open(b);
	
	string s;
	while(getline(obj1,s))
	{	
		obj2<<s<<endl;
	}
	obj1.close();
	obj2.close();
}

void cp_u(string a,string b)
{
	ifstream obj1;
	obj1.open(a);
	if(!obj1.is_open())
	{
		cout<<"cp: cannot stat '"<<a<<"': No such file or directory"<<endl;
		return ;
	}

	//if file2 not exist create and copy
	ifstream obj2;
	obj2.open(b);
	if(!obj2.is_open())
	{
		ofstream obj3;
		obj3.open(b);

		string s;
		while(getline(obj1,s))
		{	
			obj3<<s<<endl;
		}
		obj1.close();
		obj3.close();
		return;
	}
	obj2.close();

	struct stat p1,p2;
	stat(a.c_str(),&p1);
	stat(b.c_str(),&p2);
	ofstream obj4;
	
	if(p1.st_mtime > p2.st_mtime)
	{
		obj4.open(b);
		string s;
		while(getline(obj1,s))
		{	
			obj4<<s<<endl;
		}
		obj4.close();
	}
	obj1.close();
	return;	
}


void cat(string s)
{
	//cout<<" in cat "<<s<<endl;
	int count=0;
	istringstream obj(s);
	while(obj)
	{
		string red;
		obj>>red;
		count++;	
	}
	//cout<<count<<endl;

	int count2=0;
	istringstream objj2(s);
	while(objj2)
	{
		string fil;
		objj2>>fil;
		if(count2>=1 && count2<=count-2)
		{
			ifstream obj2;
			obj2.open(fil);
			if(!obj2.is_open())
			{
				cout<<"cat: "<<fil<<": No such file or directory"<<endl;
				break;
			}
			string lin;
			while(getline(obj2,lin))
			{
				cout<<lin<<endl;
			}
			obj2.close();
		}
		count2++;
	}
}

void cat_n(string s)
{
	//cout<<" in cat n"<<s<<endl;
	int count=0;
	istringstream obj(s);
	while(obj)
	{
		string red;
		obj>>red;
		count++;	
	}
	//cout<<count<<endl;

	int count2=0;
	istringstream objj2(s);
	int i=1;
	while(objj2)
	{
		string fil;
		objj2>>fil;
		if(count2>=2 && count2<=count-2)
		{
			ifstream obj2;
			obj2.open(fil);
			if(!obj2.is_open())
			{
				cout<<"cat: "<<fil<<": No such file or directory"<<endl;
				break;
			}
			string lin;
			while(getline(obj2,lin))
			{
				cout<<"      "<<i<<"  "<<lin<<endl;
				i++;
			}
			obj2.close();
		}
		count2++;
	}
}