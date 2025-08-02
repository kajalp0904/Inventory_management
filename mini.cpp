#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include<iomanip>
using namespace std;
int check_user(char user[20],char pass[20],char fname[20])
{
    char u[20],p[20];
    fstream obj;
    obj.open(fname,ios::in);
    obj>>u;
    obj>>p;
    obj.close();
    if(strcmp(u,user)==0 && strcmp(p,pass)==0)
    {
        return 1;
    }
    return 0;
}


class Inventory
{
    private:
        int pid;
        char pname[20];
        float pcost;
        int pqty;
        float ptotal;

    public:
        void get();
        void put();
        void add();
        void display();
        void search(int id);
        void Delete(int id);
        void update(int id);
        void getupdate();

};

void Inventory::get()
{
    cout<<"\n\tEnter the product ID:";
    cin>>pid;
    cout<<"\n\tEnter the product name:";
    cin>>pname;
    cout<<"\n\tEnter the product cost(In Rs.)";
    cin>>pcost;
    cout<<"\n\tEnter the product quantity";
    cin>>pqty;

    ptotal=(pqty)*(pcost);
    cout<<"\n\tTotal cost of product:"<<ptotal;
}

void Inventory::put()
{
    cout<<"\n\t"<<setiosflags(ios::left)<<setw(5)<<pid<<setw(15)<<pname<<setw(10)<<pcost<<setw(5)<<pqty<<setw(10)<<ptotal;

}

void Inventory::add()
{
    Inventory obji;
    fstream objf;
    objf.open("data.txt",ios::app | ios::binary);
    if(objf.good())
    {
        obji.get();
        objf.write((char*)&obji,sizeof(obji));
        if(objf.good())
        {
            cout<<"\n\tRecord added successfully";
        }
        objf.close();
    }
    else
    {
        cout<<"\n\tdata.txt file open error in add module";
    }
}

void Inventory::display()
{
     
    Inventory obji;
    fstream objf;
    objf.open("data.txt",ios::in | ios::binary);
    if(objf.good())
    {
        
       while(objf.read((char*)&obji,sizeof(obji)))
        {
            obji.put();
        }
        objf.close();
    }
    else
    {
        cout<<"\n\tdata.txt file open error in display module";
    }
}

void Inventory::search(int id)
{
    int x=0;
    Inventory obji;
    fstream objf;
    objf.open("data.txt",ios::in | ios::binary);
    if(objf.good())
    {
        
       while(objf.read((char*)&obji,sizeof(obji)))
        {
            if(obji.pid==id)
            {
            obji.put();
            x++;
            }
        }
        objf.close();

        if(x==0)
        {
            cout<<"\n\tRecord not found";
        }
        else
        {
            cout<<"\n\tRecord found"<<x<<"times";
        }
    }
    else
    {
        cout<<"\n\tdata.txt file open error in display module";
    }
}

void Inventory::Delete(int id)
{
    int x=0;
    Inventory obji;
    fstream objf,objt;
    objf.open("data.txt",ios::in | ios::binary);

    if(objf.good())
    {
        objt.open("temp.txt",ios::out | ios::binary);
       while(objf.read((char*)&obji,sizeof(obji)))
        {
            if(obji.pid==id)
            {
                
            x++;
            }
            else
            {
                objt.write((char*)&obji,sizeof(obji));
            }
        }
        objf.close();
        objt.close();
        remove("data.txt");
        rename("temp.txt","data.txt");
       
        if(x==0)
        {
            cout<<"\n\tRecord not found";
        }
        else
        {
            cout<<"\n\tRecord deleted"<<x<<"times";
        }
    }
    else
    {
        cout<<"\n\tdata.txt file open error in deleted module";
    }
}

void Inventory::update(int id)
{
    int x=0;
    Inventory obji;
    fstream objf,objt;
    objf.open("data.txt",ios::in | ios::binary);

    if(objf.good())
    {
        objt.open("temp.txt",ios::out | ios::binary);
       while(objf.read((char*)&obji,sizeof(obji)))
        {
            if(obji.pid==id)
            {
            obji.getupdate();
            objt.write((char*)&obji,sizeof(obji));
            x++;
            }
            else
            {
                objt.write((char*)&obji,sizeof(obji));
            }
        }
        objf.close();
        objt.close();
        remove("data.txt");
        rename("temp.txt","data.txt");
       
        if(x==0)
        {
            cout<<"\n\tRecord not found";
        }
        else
        {
            cout<<"\n\tRecord updated"<<x<<"times";
        }
    }
    else
    {
        cout<<"\n\tdata.txt file open error in updated module";
    }
}


void Inventory::getupdate()
{
    cout<<"\n\tEnter the product name:";
    cin>>pname;
    cout<<"\n\tEnter the product cost(In Rs.)";
    cin>>pcost;
    cout<<"\n\tEnter the product quantity";
    cin>>pqty;

    ptotal=(pqty)*(pcost);
    cout<<"\n\tTotal cost of product:"<<ptotal;
}
int main()
{
    int choice,x,id;
    char ch,user[20],pass[20];
    Inventory obj;
    do
    {
            system("cls");
            cout<<"\n\t----------------------------------------";
            cout<<"\n\n\tWelocme to Inventory Management System";
            cout<<"\n\t-----------------------------------------";
            cout<<"\n\t---------------";
            cout<<"\n\tLogin Section";
            cout<<"\n\t---------------";
            cout<<"\n\t1.Admin Login";
            cout<<"\n\t2.Customer Login";
            cout<<"\n\t3.Exit/Quit";
            cout<<"\n\t---------------";
            cout<<"\n\tEnter your choice(1-3)";
            cin>>choice;
            cout<<"\n\t---------------";
            switch(choice)
            {
                case 1:
                    cout<<"\n\tEnter Username:";
                    cin>>user;
                    cout<<"\n\tEnter Password:";
                    cin>>pass;
                    x=check_user(user,pass,"admin.txt");
                    if(x==1)
                    {
                        do
                        {
                            system("cls");

                            cout<<"\n\t---------------";
                            cout<<"\n\tAdmin MENU";
                            cout<<"\n\t---------------";
                            cout<<"\n\t1.Add Record";
                            cout<<"\n\t2.Display Record";
                            cout<<"\n\t3.Search Record";
                            cout<<"\n\t4.Update Record";
                            cout<<"\n\t5.Delete Record";
                            cout<<"\n\t6.Logout";
                            cout<<"\n\t---------------";
                            cout<<"\n\tEnter your choice(1-6)";
                            cin>>choice;
                            cout<<"\n\t---------------";
                            switch(choice)
                            {
                                case 1:
                                    obj.add();
                                    break;
                                
                                case 2:
                                cout<<"\n\t----------------------------------------";
                                cout<<"\n\n\tInventory Management System";
                                cout<<"\n\t-----------------------------------------";


                                cout<<"\n\t"<<setiosflags(ios::left)<<setw(5)<<"pid"<<setw(15)<<"pname"<<setw(10)<<"pcost"<<setw(5)<<"pqty"<<setw(10)<<"ptotal";
                                cout<<"\n\t------------------------------------------";

                                obj.display();
                                cout<<"\n\t------------------------------------------";

                                    break;
                                
                                case 3:
                                    cout<<"\n\tEnter the id to search record";
                                    cin>>id;
                                    obj.search(id);
                                    
                                    break;

                                case 4:
                                    cout<<"\n\tEnter the id to update record";
                                    cin>>id;
                                    obj.update(id);
                                    
                                    break;
                                
                                case 5:
                                    cout<<"\n\tEnter the id to delete record";
                                    cin>>id;
                                    obj.Delete(id);
                                    break;

                                case 6:
                                    exit(0);
                                    break;

                                default:
                                    cout<<"\n\tINVALID";
                                    break;
                            }
                        cout<<"\n\tDo you want to continue in Admin Section(Y/N)??";
                        cin>>ch;
                        }while(ch=='y'|| ch=='Y');



                    }
                    else
                    {
                        cout<<"\n\tInvalid Admin User Credentials";
                    }
                    break;
                
                case 2:
                    cout<<"\n\tEnter Username:";
                    cin>>user;
                    cout<<"\n\tEnter Password:";
                    cin>>pass;
                    x=check_user(user,pass,"user.txt");
                    if(x==1)
                    {
                        do
                        {
                            

                            cout<<"\n\t---------------";
                            cout<<"\n\tCustomer MENU";
                            cout<<"\n\t---------------";
                            cout<<"\n\t1.Display Record";
                            cout<<"\n\t2.Search Record";
                            cout<<"\n\t3.Logout";
                            cout<<"\n\t---------------";
                            cout<<"\n\tEnter your choice(1-3)";
                            cin>>choice;
                            cout<<"\n\t---------------";
                            switch(choice)
                            {
                                case 1:
                                cout<<"\n\t---------------------------------------";
                                cout<<"\n\n\tInventory Management System";
                                cout<<"\n\t---------------------------------------";


                                cout<<"\n\t"<<setiosflags(ios::left)<<setw(5)<<"pid"<<setw(15)<<"pname"<<setw(10)<<"pcost"<<setw(5)<<"pqty"<<setw(10)<<"ptotal";
                                cout<<"\n\t----------------------------------------";

                                obj.display();
                                cout<<"\n\t-----------------------------------------";
                                break;
                                
                                case 2:
                                    cout<<"\n\tEnter the id to search record";
                                    cin>>id;
                                    obj.search(id);
                                    break;
                                
                                case 3:
                                    exit(0);
                                    break;

                              

                                default:
                                    cout<<"\n\tINVALID";
                                    break;
                            }
                        cout<<"\n\tDo you want to continue in Customer Section(Y/N)??";
                        cin>>ch;
                        }while(ch=='y'|| ch=='Y');



                    }
                    else
                    {
                        cout<<"\n\tInvalid Customer User Credentials";
                    }
                    break;
                
                case 3:
                    exit(0);
                    break;

                default:
                    cout<<"\n\tINVALID";
                    break;
            }


    cout<<"\n\tDo you want to continue in Login Section(Y/N)??";
    cin>>ch;
    }while(ch=='y'|| ch=='Y');


    
    return 0;
}