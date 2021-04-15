


                                 /*some notes about that project
								   1- to use getline for name
								   2- the problem of password when 001=1 which is accepted and it is wrong password
								   3- to send money from one to one account
								   4- GUI
								   5- use secret password as "$$$$$$"
                                    */



#include<iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
struct date
{
	int day,month,year;
}crt_date;
struct operation        // the last 5 operations
{
	string name;
    string type;
	int money;
	date d_op;
}op_regist,fop_regist;
void withdraw(float  & withdraw,float & balance)
{
  cout<<"enter your amount to withdraw :: $";
  cin>>withdraw;
  if(withdraw>balance)
	  cout<<"you have not enough money"<<endl;
  else if(withdraw <0)
	  cout << "you can't withdraw less than $0" << endl;
  else
  {
	balance-=withdraw;
	cout<<"your current balance is::$"<<balance << endl;
  }
}
void deposit(float & deposit,float & balance)
{
  cout<<"enter your amount to deposit $";
  cin>>deposit;
  if(deposit<0)
	  cout<<"you can't deposite less than 0$"<<endl;
  else
  {
	  balance+=deposit;
	  cout<<"your current balance is::$"<<balance << endl;
  }
}
 struct registration
{
    string name;
    string password;
    float balance;
	//date crt_date;
	vector<operation>op ;
}reg,f;
void regist()
{

	//time_t t=time(0);
	//struct tm*now=localtime(&t);
    ofstream atmfile;
    atmfile.open("ATM.txt",ios::app);
    cout << "Enter user name : ";
    cin >> reg.name ;
    cout << "Enter user password : ";
    cin >> reg.password ;
    //cout << "Enter user balance : ";
    //cin >> reg.balance ;
	reg.balance=100;
	cout << "you have 100$ " << endl;
    atmfile << reg.name << endl;
    atmfile << reg.password << endl;
    atmfile << reg.balance << endl ;
	//atmfile << now->tm_mday << " "<<now->tm_mon+1 <<" " << now->tm_year+1900<< endl;
	atmfile << endl << endl << endl;
    atmfile.close();
}
struct sign_in
{
    string name;
    string password;
    float money;
}ur,emp;
void file_data( vector<registration>&file )// without & the value will not be copied to the variable in function call
{
	
	ifstream atmfile;
	atmfile.open("ATM.txt");
	if(!atmfile.is_open())
		cout << "there is no user registed before " << endl;
	//if(!atmfile.eof())
	    atmfile >> f.name;
	while(!atmfile.eof())
	{
		atmfile >> f.password >> f.balance ;
		if(!atmfile.eof())
		    atmfile >> fop_regist.name;
		while( f.name==fop_regist.name && !atmfile.eof())
		{
			atmfile >> fop_regist.type >> fop_regist.money >>fop_regist.d_op.day >> fop_regist.d_op.month >> fop_regist.d_op.year ;
			f.op.push_back(fop_regist);
		    if(!atmfile.eof())
			{
				atmfile >> fop_regist.name;
			}
			else
				break;

		}

		file.push_back(f);
		while(f.op.size()!=0)
			f.op.pop_back(); 
      
		if(!atmfile.eof())
		{
			f.name=fop_regist.name;
		}
		
	}                                                                                   
	atmfile.close();
}
void emp_data(string emp_arr[], int &x)
{
	ifstream employee;
	employee.open("employee.txt");
	x=0;
	while(!employee.eof())
	{
		employee >> emp_arr[x];
		x++;
	}
	employee.close();
}
int main()
{	
	system("color A");
	bool end=false;
	cout << "                      welcome to our service              " << endl;
	time_t t=time(0);
	char*dt=ctime(&t);
	struct tm*now=localtime(&t);
	cout << "             the current date is : " << dt << endl;
	cout << "                    the current Date is : " << now->tm_mday << '-' << now->tm_mon+1 << '-' << now->tm_year+1900 << endl << endl;
	vector <registration>file;
	
	int job_check;
	cout << "are you : 1-user    " <<endl;
	cout << "          2-employee" <<endl;
	cout << "          3-manager " <<endl;
	cin >> job_check;
	if(job_check==1)
	{
		
		int regist_choice;
		cout << "Do you want to : 1-rgister " << endl;
		cout << "                 2-sign in " << endl;
		cin >> regist_choice;
		if(regist_choice==1)
		{
			regist();
		}
		else if(regist_choice==2)
		{
			int choice;
			file_data(file);
			cout << "Ente your name : " << endl;
			cin >> ur.name;
			for(int x=0;x<file.size();x++)
			{
				if(file[x].name==ur.name)
				{
					cout << "Enter your password :  " ;
					cin >> ur.password;
					if(ur.password==file[x].password)
					{
						
						cout<<"----------|    (( welcome to our ATM service ))    |----------"<<endl;
	                  do
				      {  
			               cout<<"1.withdraw"<<endl;                                                                                                                
	                       cout<<"2.deposit"<<endl;
						   cout <<"3.transfere"<< endl;
	                       cout<<"4.quit"<<endl;
	                       cout<<"enter your choice please"<<endl;
	                       cin>>choice;
	                       switch(choice)
						   {
						       case 1:
								   withdraw(ur.money,file[x].balance);
								   if(file[x].balance>ur.money && ur.money>0)//ÍÊí áæ ßÇäÊ ÇáÞíãÉ Çááí ÏÎáåÇ ÇÕÛÑ ãä  ÕÝÑ Çæ ÇßÈÑ ãä Çá balance 
								   {
								       op_regist.name=file[x].name;
								       op_regist.type="withdraw";
								       op_regist.money=ur.money;
				  				       op_regist.d_op.day=now->tm_mday;
								       op_regist.d_op.month=now->tm_mon+1;
								       op_regist.d_op.year=now->tm_year+1900;
								       file[x].op.push_back(op_regist);
								       
								   }
								   break;

							   case 2:
								   deposit(ur.money,file[x].balance);
								   if(ur.money>0)
								   {
								       op_regist.name=file[x].name;
								       op_regist.type="deposit";
								       op_regist.money=ur.money;
								       op_regist.d_op.day=now->tm_mday;
								       op_regist.d_op.month=now->tm_mon+1;
								       op_regist.d_op.year=now->tm_year+1900;
								       file[x].op.push_back(op_regist);
								   
								   }
								   break;
							   case 3:
								   cout << "Enter name of user you want to transfere to :  ";
								   cin >> f.name;
								   for(int i=0;i<file.size();i++)
								   {
									   if(f.name==file[i].name)
									   {
										   withdraw(ur.money,file[x].balance);
									       if(ur.money>0)
								           {
								               op_regist.name=file[x].name;
								               op_regist.type="send_to";
								               op_regist.money=ur.money;
								               op_regist.d_op.day=now->tm_mday;
								               op_regist.d_op.month=now->tm_mon+1;
								               op_regist.d_op.year=now->tm_year+1900;
								               file[x].op.push_back(op_regist);  
								          
										   file[i].balance+=ur.money;
										       op_regist.name=file[i].name;
								               op_regist.type="Recieve_from";
								               op_regist.money=ur.money;
								               op_regist.d_op.day=now->tm_mday;
								               op_regist.d_op.month=now->tm_mon+1;
								               op_regist.d_op.year=now->tm_year+1900;
								               file[i].op.push_back(op_regist);  
										   }
									   }
								   }
							   case 4:
								   end=true;
								   break;
						   }
					  }while(end!=true);


					  cout << "The last 5 transactions are : " << endl;
					  if(file[x].op.size()>=5)
			          {
					      for(int y=file[x].op.size()-1;y>file[x].op.size()-6;y--)
					      {
						      cout << file[x].op[y].name << "  " << file[x].op[y].type << "  " << file[x].op[y].money << "  " << file[x].op[y].d_op.day << "  " << file[x].op[y].d_op.month << "  " << file[x].op[y].d_op.year << endl;
					      }
					  }
					  else
					  {
						  for(int y=file[x].op.size()-1;y>=0;y--)
						  {
						      cout << file[x].op[y].name << "  " << file[x].op[y].type << "  " << file[x].op[y].money << "  " << file[x].op[y].d_op.day << "  " << file[x].op[y].d_op.month << "  " << file[x].op[y].d_op.year << endl;
						  }
					  }
					}
					else if(ur.password!=file[x].password)
					{
						cout << "Wrong password !! " << endl;
					}
					break;
				}
				else if(file[x].name !=ur.name && x==(file.size())-1)
				{
					cout << "Wrong name !!" << endl;
				}
			}
			if(end==true)
			{
			    ofstream atmfile;
			    atmfile.open("ATM.txt");
			    for(int x=0;x<file.size();x++)
			    {
				    if(file[x].balance==0 && ((now->tm_mday-file[x].op[ file[x].op.size()-1 ].d_op.day)+  (now->tm_mon-file[x].op[ file[x].op.size()-1 ].d_op.month)*30 + (now->tm_year-file[x].op[ file[x].op.size()-1 ].d_op.year)*360 )>60)
					    continue;

				    atmfile << file[x].name << endl;
				    atmfile << file[x].password << endl;
				    atmfile << file[x].balance << endl;
				    for (int y=0; y<file[x].op.size();y++)
				    {
					    atmfile << file[x].op[y].name << "  " << file[x].op[y].type << "  " << file[x].op[y].money<< "  " << file[x].op[y].d_op.day<< "  " << file[x].op[y].d_op.month <<"  " << file[x].op[y].d_op.year << endl;                          
				    }
				    atmfile << endl << endl << endl;
			    }
			    atmfile.close();
			}
		}
	}
	else if(job_check==2)
	{
		file_data(file);
		bool found=false;
		int emp_function;
		vector<sign_in>emp_file;
		ifstream employee;
		employee.open("employee.txt");
		while(!employee.eof())
		{
		    employee >> emp.name >> emp.password;
		    emp_file.push_back(emp);
		}
		cout << "Enter your name : " ;
		cin >> emp.name;
		for(int i=0;i<emp_file.size();i++)
		{
			if(emp_file[i].name==emp.name)
			{
				cout << " Enter your password : ";
		        cin >> emp.password;
				if(emp_file[i].password==emp.password)
				{
		            cout << "Do you want to : 1- Generate report about daily transaction " << endl;
		            cout << "                 2-search for a specific user account " << endl;
		            cin >> emp_function;
		            if(emp_function==1)
		            {
			            cout << "Enter date : " << endl;
			            cin >> crt_date.day >> crt_date.month >> crt_date.year ;
		                for(int x=0;x<file.size();x++)
		                {
			                for(int y=0;y<file[x].op.size();y++)
			                {
					            if(crt_date.day==file[x].op[y].d_op.day &&crt_date.month==file[x].op[y].d_op.month &&crt_date.year==file[x].op[y].d_op.year)
					            {
						            cout << file[x].op[y].name << "  " << file[x].op[y].type << "  " << file[x].op[y].money << "  " << file[x].op[y].d_op.day << "  " << file[x].op[y].d_op.month << "  " << file[x].op[y].d_op.year << endl;
					                found=true;
					            }

			                }
		                }
			            if(found==false)
				            cout << "that date is not found !! " << endl;
		            }
		            else if(emp_function==2)
		            {
			            cout << "Enter name : " ;
			            cin >> ur.name ;
			            for(int x=0;x<file.size();x++)
			            {
				            if(ur.name==file[x].name)
				            {
					            for(int y=0;y<file[x].op.size();y++)
					            {
						            cout << file[x].op[y].name << "  " << file[x].op[y].type << "  " << file[x].op[y].money << "  " << file[x].op[y].d_op.day << "  " << file[x].op[y].d_op.month << "  " << file[x].op[y].d_op.year << endl;
					                found=true;
					            }
				            }
			            }
			            if(found==false)
				            cout << "that user is not found !! " << endl;
		            }
			    }
				else
				{
					cout << " Wrong password " << endl;
					break;
				}
			}
			else if(emp.name!=emp_file[i].name && i==emp_file.size()-1)
			{
				cout << " Wrong name " << endl;
	        }
		}
	}
	else if(job_check==3)
	{
		
		int bonus_check,emp_check;
		float persent;
		cout << "                                      The manager                                  " << endl;
		cout << " enter your name :  " ;
		cin >> ur.name ;
		if(ur.name=="Employer")
		{
			cout << " Enter your password : ";
			cin >> ur.password;
			if(ur.password=="2942019")
			{
				cout << "Do you want to 1-add employees money " << endl;
				cout << "               2-abb new employee    " << endl;
				cin >> emp_check;
				if(emp_check==1)
				{
                    string emp_arr[100];
					int arr_size;
					bool found=false;
				    file_data(file);
				    cout << " Enter monthly money for embloyees :  " << endl;
				    cin >> ur.money;
				    for(int x=0;x<file.size();x++)
				    {
						emp_data(emp_arr,arr_size);
						for(int y=0;y<arr_size;y++)
						{
							if(file[x].name==emp_arr[y])
							{
								file[x].balance+=ur.money;
							}
						}
					}
				    do{
						    cout << "Do you want to 1-give employee bonus " << endl;
						    cout << "               2-deduct from employee" << endl;
						    cout << "               3-quit                " << endl;
						    cin >> bonus_check;
						    switch(bonus_check)
						    {
						        case 1:
                                    cout << "Enter employee name :  ";
						            cin >>emp.name;
						            for(int x=0;x<file.size();x++)
						            {
										
										if(file[x].name==emp.name)
							            {
								            cout << "Enter percent of bonus :  ";
										    cin >> persent ;
										    file[x].balance+=persent*ur.money;
							                found=true;
											break;
									    }
										
						            }
								    break;
							    case 2:
								    cout << "Enter employee name :  ";
						            cin >>emp.name;
						            for(int x=0;x<file.size();x++)
								    {
							            if(file[x].name==emp.name)
							            {
								            cout << "Enter percent to be deducted :  ";
										    cin >> persent ;
										    file[x].balance-=persent*ur.money;
							                found=true;
											break;
									    }
										
								    }
								    break; 
							    case 3:
								    end=true;
						    }
							if(found==false)
								cout << " employee is not found !!" << endl;
						
			        }while(end==false);
				  	       
				    ofstream atmfile;
			        atmfile.open("ATM.txt");
			        for(int x=0;x<file.size();x++)
			        {
				        if(file[x].balance==0 && ((now->tm_mday-file[x].op[ file[x].op.size()-1 ].d_op.day)+  (now->tm_mon-file[x].op[ file[x].op.size()-1 ].d_op.month)*30 + (now->tm_year-file[x].op[ file[x].op.size()-1 ].d_op.year)*360 )>60)
					        continue;

				        atmfile << file[x].name << endl;
				        atmfile << file[x].password << endl;
				        atmfile << file[x].balance << endl;
				        for (int y=0; y<file[x].op.size();y++)
				        {
					        atmfile << file[x].op[y].name << "  " << file[x].op[y].type << "  " << file[x].op[y].money<< "  " << file[x].op[y].d_op.day<< "  " << file[x].op[y].d_op.month <<"  " << file[x].op[y].d_op.year << endl;                          
				        }
				        atmfile << endl << endl << endl;
			        }
			        atmfile.close();
				}
				else if(emp_check==2)
				{
					cout << "Enter employee name :  ";
					cin >> emp.name;
					cout << "Enter employee password : ";
					cin >> emp.password;
					emp.money=0;

				    ofstream atmfile;
			        atmfile.open("ATM.txt",ios::app);
					atmfile << emp.name<<endl;
					atmfile << emp.password << endl;
					atmfile << emp.money << endl;
					atmfile << endl << endl << endl;
					atmfile.close();

					ofstream employee;
					employee.open("employee.txt",ios::app);
					employee << emp.name << endl << endl << endl;
					employee.close();
				}
			}
			else
				cout << "Wrong password !!" << endl;
		}
		else
			cout << "Wrong name !!" << endl;

	}
		system("pause");
}