#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;




class File{
protected:
    int data;
    string consumption;
    fstream file;
    int cost;
    int income;
public:
    
// constructor of the income to get it anywhere in the program
    File(){}
    void ho(int income){
        this->income = income;
    }
    int get_income(){
        return income;
    }
    void take_cost(int cost){
        this->cost = cost;
    }
// the constructor to write the data to the file
    void add(){
        file.open("finance.txt", ios::app);
        file<<"======================="<<endl;
        file<<"||     FINANCE         ||"<<endl;
        file<<"======================="<<endl;
        
        file<<"Income; "<<income<<endl;
        file.close();
    }
// the constructor of the class
    void add_info(int data, string con, int c){
        file.open("finance.txt", ios::app);
        file<<"Data; "<<data<<"| Consumption; "<<con<<"| Cost; "<<c<<endl;        
        file.close();
    }
// the function to display the data from the file
    void display(){
        string line;
            file.open("finance.txt", ios::app);
            while(getline(file, line)){
                cout<<line<<endl;     
            } 
            file.close();  
    }
};

class Stats:public File{
protected:
    int sum = 0;
public:
    // the constructor to calculate the total spending
    void total(int cost){
        sum += cost;
    }
    // the function to display the total spending
    void display_spending(){
        cout<<"Total spending: "<<sum<<endl;
    }
    // the function to calculate the balance
    void calculate_balance(int income){
        int balance=income-sum;
        cout<<"Balance: "<<balance<<endl;
    }
};

class Add_info:public File{
protected:
    int data;
    string consumption;
    int cost;
public:
    void add_info(int data, int cost, string consumption, Stats& s, File& f1){
        // if you spent more than your income it will display an error message
        if(f1.get_income() - cost < 0){
            cout<<"ERROR : you cannot spent more than your income"<<endl;
        }
        // if you spent less than your income it will add the data to the file
        else{
        f1.add_info(data, consumption, cost);
        s.total(cost);
        f1.take_cost(cost);
        }
    }
    
};

 




int finance(){
    Stats s;
    File f1;
    int income;
    cout<<"pls enter your income: ";
    cin>>income;
    f1.ho(income);
    f1.add();
    Add_info a;
    string consumption;
    int data, cost;
    cin>>data>>cost>>consumption;
    a.add_info(data, cost, consumption, s, f1);
    data = 0; cost = 0; consumption = "";
    f1.display();
    s.display_spending();
    s.calculate_balance(income);
    
    

}