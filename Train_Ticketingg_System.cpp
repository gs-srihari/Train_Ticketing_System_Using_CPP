#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<conio.h>
#include<process.h>
class train
{
  int k1;
  char dp[25];
  char dest[25];
  int top;
  char timing[25];
  struct trainmem
  {
   int age;
   char n[25];//name
   char gender;
   char phone[15];
   char usnm[25];
   int tickno;
  }a[40];
  public:
    void readdetails()
    {
     cout<<"Departure:";
     cin>>dp;
     cout<<"Destination:";
     cin>>dest;
     cout<<"Timing:";
     cin>>timing;
     top=-1;
     k1=0;
    }
    void readtrainmem(char us[])
    {
     if(top==39)
     cout<<"No more tickets available .Sorry\n";
     else
     {
     top++;
     cout<<"Age:";
     cin>>a[top].age;
     cout<<"Name:";
     cin>>a[top].n;
     cout<<"Gender:";
     cin>>a[top].gender;
     cout<<"Phone:";
     cin>>a[top].phone;
     a[top].tickno=++k1;
     strcpy(a[top].usnm,us);
     cout<<"Your ticket\n";
     cout<<"\n\n";
     cout<<"Name:"<<a[top].n<<" "<<"Age"<<a[top].age<<" "<<"Gender"<<a[top].gender<<" "<<"Phone:"<<a[top].phone<<" Ticket number"<<a[top].tickno<<endl;
     }
  }
  void view(int i)
  {
   cout<<"Age:"<<a[i].age<<endl<<"Name"<<a[i].n<<endl<<"Gender"<<a[i].gender<<endl<<"Phone:"<<a[i].phone<<endl;
  }
  void deleteticket(int ns,char sname[])
  {
   int i;
   for(i=0;i<=top;i++)
   {
   if((a[i].tickno==ns)&&(strcmp(a[i].usnm,sname)==0))
   {
    int j;
    for(j=i;j<top;j++)
    {
     strcpy(a[j].n,a[j+1].n);
     a[j].age=a[j+1].age;
     a[j].gender=a[j+1].gender;
     strcpy(a[j].phone,a[j+1].phone);
     strcpy(a[j].usnm,a[j+1].usnm);
     a[j].tickno=a[j+1].tickno;
    }
    top--;
    break;
   }
  }
}
int returntop()
{
 return top;
}
void deltickpop()
{
 top--;
}
char* rettime()
{
 return timing;
}
char* retdep()
{
 return dp;
}char* retdes()
{
 return dest;
}
void display(char us[])
{
 for(int j=0;j<=top;j++)
 if(strcmp(a[j].usnm,us)==0)
 {cout<<"Train"<<retdep()<<" - "<<retdes();
 cout<<" Name:"<<a[j].n<<" "<<"Age"<<a[j].age<<" "<<"Gender"<<a[j].gender<<" "<<"Phone:"<<a[j].phone<<" Ticket number"<<a[j].tickno<<endl;
 }
}
void display1()
{
  for(int k=0;k<=top;k++)
 cout<<"Name:"<<a[k].n<<" Age"<<a[k].age<<" Gender"<<a[k].gender<<" Phone:"<<a[k].phone<<" Ticket Number:"<<a[k].tickno<<endl;
}

};
struct user
{
int age;
 char name[25];
 long int aadhar_no;
 char city[25];
 char state[25];
 char username[25];
 char password[25];
 };
void addtrain()
{
train a;
fstream f;
f.open("t234.dat",ios::binary|ios::app);
a.readdetails();
f.write((char*)&a,sizeof(a));
f.close();
cout<<"Train is added\n";
}
int book(int k)
{
 int fl=0;
 cout<<"Enter the source and destination\n";
 char s1[25],d[25];
 cin>>s1>>d;
 train s;
 fstream f;
 f.open("t234.dat",ios::in);
 while(f.read((char*)&s,sizeof(s)))
 {
  if((strcmp(s.retdep(),s1)==0)&&(strcmp(s.retdes(),d)==0))
  {
   int l=s.returntop();
   if(l+k>39){
   cout<<"tickets not available";
   fl=1;
   }
  }
 }
 return fl;
}
void bookticket(char a[])
{
fstream f,f1;
train s;
char s1[25],d[25];
cout<<"Enter the source and destination\n";
cin>>s1>>d;
f.open("t234.dat",ios::binary|ios::in);
f1.open("tem.dat",ios::binary|ios::out);
while(f.read((char*)&s,sizeof(s)))
{
 if((strcmp(s1,s.retdep())==0)&&(strcmp(s.retdes(),d)==0))
  {
   s.readtrainmem(a);
   f1.write((char*)&s,sizeof(s));
   cout<<"ticket  booked\n";
  }
 else
 f1.write((char*)&s,sizeof(s));
}
f.close();
f1.close();
f.open("t234.dat",ios::binary|ios::out);
f1.open("tem.dat",ios::binary|ios::in);
while(f1.read((char*)&s,sizeof(s)))
{
 f.write((char*)&s,sizeof(s));
}
f1.close();
f.close();
}
void cancelticket(char a[])
{
fstream f,f1;
train s;
char s1[25],d[25];
cout<<"Enter the source and destination\n";
cin>>s1>>d;
f.open("t234.dat",ios::binary|ios::in);
f1.open("tem.dat",ios::binary|ios::out);
while(f.read((char*)&s,sizeof(s)))
{
 if((strcmp(s1,s.retdep())==0)&&(strcmp(s.retdes(),d)==0))
  {
   int k;     cout<<"Enter ticket number\n";
   cin>>k;
   s.deleteticket(k,a);
   cout<<"Ticket is cancelled"<<endl;
   f1.write((char*)&s,sizeof(s));
  }
 else
 f1.write((char*)&s,sizeof(s));
}
f.close();
f1.close();
f.open("t234.dat",ios::binary|ios::out);
f1.open("tem.dat",ios::binary|ios::in);
while(f1.read((char*)&s,sizeof(s)))
{
 f.write((char*)&s,sizeof(s));
}
f1.close();
f.close();
}
void remtrain()
{
 fstream f,f1;
 f.open("t234.dat",ios::binary|ios::in);
 f1.open("tem.dat",ios::binary|ios::out);
 train s;
 char s1[25],d[25];
 cout<<"Source:";
 cin>>s1;
 cout<<"Destination:";
 cin>>d;
 while(f.read((char*)&s,sizeof(s)))
 if((strcmp(s1,s.retdep())!=0)||(strcmp(d,s.retdes())!=0))
 f1.write((char*)&s,sizeof(s));
 f.close();
 f1.close();
 f1.open("tem.dat",ios::binary|ios::in);
 f.open("t234.dat",ios::binary|ios::out);
 while(f1.read((char*)&s,sizeof(s)))
 f.write((char*)&s,sizeof(s));
 f.close();
 f1.close();
 cout<<"Train is removed\n";
}
void clearlist()
{
 fstream f,f1;
 f.open("t234.dat",ios::binary|ios::in);
 f1.open("tem.dat",ios::binary|ios::out);
 train s;
 char s1[25],d[25];
 cout<<"Enter the source and destination";
 cin>>s1>>d;
 while(f.read((char*)&s,sizeof(s)))
 {
  if((strcmp(s1,s.retdep())==0)&&(strcmp(d,s.retdes())==0))
  {
    while(s.returntop()!=-1)
    {
      s.deltickpop();
    }
    f1.write((char*)&s,sizeof(s));
  }
  else
  {
   f1.write((char*)&s,sizeof(s));
  }
 }
 f.close();
 f1.close();
  f1.open("tem.dat",ios::binary|ios::in);
 f.open("t234.dat",ios::binary|ios::out);
 while(f1.read((char*)&s,sizeof(s)))
 f.write((char*)&s,sizeof(s));
 f.close();
 f1.close();
 cout<<"The required train was cleared of its passennger details";
}
void vt()
{
 fstream f;
 train s;
 f.open("t234.dat",ios::binary|ios::in);
 while(f.read((char*)&s,sizeof(s)))
 {  cout<<endl<<s.retdep()<<s.retdes()<<endl;
 s.display1();
 }
 f.close();
}
void view_tickets1(char a[])
{
 train s;
 fstream f;
 f.open("t234.dat",ios::binary|ios::in);
 while(f.read((char*)&s,sizeof(s)))
  s.display(a);
 f.close();
}
void viewtickets()
{
 char s1[25],d[25];
 train s;
 cout<<"Enter the source and destination\n";
 cin>>s1>>d;
 fstream f;
 f.open("t234.dat",ios::binary|ios::in);
 while(f.read((char*)&s,sizeof(s)))
 {
  if((strcmp(s.retdep(),s1)==0)&&(strcmp(s.retdes(),d)==0))
  {
   s.display1();
  }
 }
f.close();
}
void users()
{
 int ch;

 cout<<"Menu\n1.Register\n2.Login\nEnter 0  to exit";
 cout<<"Enter your choice\n";
 cin>>ch;
 if(ch==1)
 {
  user k;
  cout<<"Name";
  cin>>k.name;
  cout<<"Age:";
  cin>>k.age;
  cout<<"Aadhar number:";
  cin>>k.aadhar_no;
  cout<<"City:";
  cin>>k.city;
  cout<<"State:";
  cin>>k.state;
  cout<<"Enter username:";
  cin>>k.username;
  cout<<"Enter password:";
  cin>>k.password;
  cout<<"Registered\n:";
  fstream f;
  f.open("log1.dat",ios::binary|ios::app);
  f.write((char*)&k,sizeof(k));
  f.close();
 }
 else if(ch==2)
 {
  fstream f;
  f.open("log1.dat",ios::binary|ios::in);
  char u[25],p[25];
  cout<<"Username:\n";
  cin>>u;
  cout<<"Password:\n";
  cin>>p;
  user k;
  int ctrk=0;
  while(f.read((char*)&k,sizeof(k)))
  {
   if((strcmp(k.username,u)==0)&&(strcmp(k.password,p)==0))
   {
	    ctrk=1;
   }
  }
  if(ctrk==0)
  {
  cout<<"Login unsuccesful\n";
  }
  else
  {
 x: cout<<"Menu\n1.Book\n2.Cancel\n3.View\n";
  int k;
  cout<<"Enter choice\n";
  cin>>k;
  if(k==1)
  {
   bookticket(u);
  }
  else if(k==2)
  {
   cancelticket(u);
  }
  else if(k==3)
  {
   view_tickets1(u);
  }
  cout<<"Enter 1 if u want to continue\n";
  int k1;cin>>k1 ;
  if(k1==1)
  goto x;
  }
}
}
void admin(char u[],char p[])
{
 char a[25],b[25];
 cout<<"Enter username:";
 cin>>a;
 cout<<"Enter password:";
 cin>>b;
 if((strcmp(a,u)==0)&&(strcmp(b,p)==0))
 {
 while(1){
  cout<<"Menu\n1.View details of train\n2.Clear details of a train\n3.Remove train\n4.Add train\nEnter 0 to break ang go 2 main menu\n";
  int k1;
  cin>>k1;
  if(k1==1)viewtickets();
  else if(k1==2)clearlist();
  else if(k1==3)remtrain();
  else if(k1==4)addtrain();
  else if (k1==0)break;}
 }
 else
 {
 cout<<"Invalid id";
 }
}
void main()
{
clrscr();
int l;
while(1)
{
cout<<"Menu\n1.User\n2.Admin\n3.Exit\nEnter your choice\n";
cin>>l;
switch(l)
{
 case 1:{
	 users();
	 break;
	}
 case 2:{
	  admin("train","admin123");
	  break;
	}
case 3:{
	exit(0);
}
default:{
	 cout<<"Invalid choice\n";
	}
}
}
getch();
}
