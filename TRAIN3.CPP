#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
class train
{
	int tno;
	char tname[50];
	char source[50];
	char dest[50];
	int fare;
	public: void get();
		void put();
		void disp();
		void write_file();
		void read_file();
		void search_train();
		void update_train();
		void del_train();
		void reserve();
		void cancel();
		int  count_train();
		void budget_train(int);
		int rettno()
		{
			return tno;
		}
		int retfare()
		{
			return fare;
		}
		char *retdest()
		{
			return dest;
		}
};
void train::get()
{
	cout<<"\nEnter train number :";
	cin>>tno;
	cout<<"\nEnter train name :";
	gets(tname);
	cout<<"\nEnter source station :";
	gets(source);
	cout<<"\nEnter destination station :";
	gets(dest);
	cout<<"\nEnter fare :";
	cin>>fare;
}
void train::put()
{
	cout<<"\nTrain number          :"<<tno;
	cout<<"\nTrain name            :"<<tname;
	cout<<"\nSource station        :"<<source;
	cout<<"\nDestination station   :"<<dest;
	cout<<"\nFare of train 	       :"<<fare;
}
void train::disp()
{
	cout<<tno<<"\t\t"<<tname<<"\t\t"<<source<<"\t"<<dest<<"\t"<<fare<<endl;
}
void train::write_file()
{
	fstream f;
	train t;
	f.open("train.dat",ios::app|ios::binary);
	t.get();
	f.write((char *)&t,sizeof(t));
	cout<<"\nRecord write sucessfully";
	getch();
	f.close();
}
void train::read_file()
{
	fstream f;
	train t;
	f.open("train.dat",ios::in|ios::binary);
	f.read((char *)&t,sizeof(t));
	cout<<"\n\n\nTrain no	Train name	source	dest	fare"<<endl;
	cout<<"------------------------------------------------------"<<endl;
	while(!f.eof())
	{
		t.disp();
		f.read((char *)&t,sizeof(t));
	}
	getch();
	f.close();
}
void train::search_train()
{
	fstream f;
	train t;
	int ttno;
	cout<<"\nEnter train number to search :";
	cin>>ttno;
	int flag=0;
	f.open("train.dat",ios::in|ios::binary);
	while(!f.eof())
	{
		f.read((char *)&t,sizeof(t));
		if(t.rettno()==ttno)
		{
			t.put();
			getch();
			flag=1;
			break;
		}
	}
	if(flag==0)
		cout<<"\nTrain number not exist ";
	getch();
	f.close();
}
void train::update_train()
{
	fstream f;
	train t;
	char ans,ch;
	int tn;
	long pos;
	int flag=0;
	f.open("train.dat",ios::in|ios::out|ios::binary);
	cout<<"\nEnter train no to edit :";
	cin>>tn;
	while(!f.eof())
	{
		pos=f.tellg();
		f.read((char *)&t,sizeof(t));
		if(t.rettno()==tn)
		{
			flag=1;
			t.put();
			cout<<"\n\nWant to update the detail:";
			cin>>ans;
			if(ans=='y' || ans=='Y')
			{
				t.get();
				cout<<"\nWant to save data (y/n):";
				cin>>ch;
				if(ans=='y' || ans=='Y')
				{
					f.seekp(pos);
					f.write((char *)&t,sizeof(t));
					cout<<"\nRecord modify sucessfully";
					getch();
				}
			}
		}
	}
	if(flag==0)
	{
		cout<<"\nTrain number not found";
		getch();
	}
	f.close();
}
void train::del_train()
{
	fstream f,f1;
	train t;
	char ans,ch;
	int tn;
	int flag=0;
	f.open("train.dat",ios::in|ios::binary);
	f1.open("temp.dat",ios::out|ios::binary);
	cout<<"\nEnter train no to delete :";
	cin>>tn;
	f.read((char *)&t,sizeof(t));
	while(!f.eof())
	{

		if(t.rettno()!=tn)
			f1.write((char *)&t,sizeof(t));
		else
		{
			t.put();
			flag=1;
		}
		f.read((char *)&t,sizeof(t));
	}
	f.close();
	f1.close();

	if(flag==0)
		cout<<"\nTrain no not exist";
	else
	{
		cout<<"\nWant to delete this Record(y/n):";
		cin>>ans;
		if(ans=='y' || ans=='Y')
		{
			cout<<"\nDetail of train no "<<tn<<" deleted sucessfully";
			getch();
			remove("train.dat");
			rename("temp.dat","train.dat");
		}
	}
}
int train::count_train()
{
	fstream f;
	train t;
	char usdes[50];
	int c=0;
	f.open("train.dat",ios::in|ios::binary);
	cout<<"\n enter the destination of your choice :";
	gets(usdes);
	while(f.read((char*)&t,sizeof(t)))
	{
		if(strcmpi(t.retdest(),usdes)==0)
			c++;
	}
	f.close();
	return c;
}
void train::budget_train(int b)
{
	fstream f;
	train t;
	char usdes[50];
	f.open("train.dat",ios::in|ios::binary);
	cout<<"\n enter the destination :";
	gets(usdes);
	while(f.read((char*)&t,sizeof(t)))
	{
		if(t.retfare()<=b && (strcmpi(t.retdest(),usdes)==0))
		t.put();
	}
	f.close();
}
void main()
{
	clrscr();
	char ch;
	int  am;
	train t;
	while(1)
	{
		clrscr();
		cout<<"\n\n\n\n\t\t\t\tTrain Menu";
		cout<<"\n\t\t\t1. Add new train detail";
		cout<<"\n\t\t\t2. Display train detail";
		cout<<"\n\t\t\t3. Search for train by train no";
		cout<<"\n\t\t\t4. Update train detail";
		cout<<"\n\t\t\t5. Delete train detail";
		cout<<"\n\t\t\t6. calculate the no. of trains user given destination";
		cout<<"\n\t\t\t7. display the details of a train which is in budget";
		cout<<"\n\t\t\t0. Exit to menu";
		cout<<"\n\n\t\t\tEnter your choice(0-7):";
		cin>>ch;
		if(ch=='0')
			exit(0);
		switch(ch)
		{
			case '1': t.write_file();
				break;
			case '2': t.read_file();
				break;
			case '3':t.search_train();
				break;
			case '4': t.update_train();
				break;
			case '5': t.del_train();
				break;
			case '6': cout<<"the no. of trains :\n"<<t.count_train();
				break;
			case '7': cout<<"enter the max amount the user can afford\n";
				  cin>>am;
				  t.budget_train(am);
				break;
			default: cout<<"\n\tInvalid choice\n\n";

		}
			 getch();
	}
}

