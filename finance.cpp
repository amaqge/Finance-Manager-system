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
       income -= cost;
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
            file.open("finance.txt", ios::in);
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
    int icome;
        cout<<"Enter your income: ";
        cin>>icome;
        File f1;
        Stats s;
        Add_info a;
        f1.ho(icome);
    while(true){
        int choice;
        cout<<"======================================================"<<endl;
        cout<<"||         Welcome to Finance Manager System.        ||"<<endl;
        cout<<"||        Please select an option:                   ||"<<endl;
        cout<<"|| 1. Add spending                                   ||"<<endl;
        cout<<"|| 2. Display finance information                    ||"<<endl;
        cout<<"|| 3. Display total spending                         ||"<<endl;
        cout<<"|| 4. Display balance                                ||"<<endl;
        cout<<"|| 5. Exit                                           ||"<<endl;
        cout<<"======================================================"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        
        switch(choice){
           case 1:{
            int data,cost;
            string consumption;
            cout<<"Enter the date: ";
            cin>>data;
            cout<<"Enter the consumption: ";
            cin>>consumption;
            cout<<"Enter the cost: ";
            cin>>cost;
            a.add_info(data, cost, consumption, s, f1);
            break;
           }
           case 2:{
            f1.display();
            break;
           }
           case 3:{
            s.display_spending();
            break;
           }
           case 4:{
            s.calculate_balance(f1.get_income());
            break;
           }
           case 5:{
            cout<<"Exiting the program..."<<endl;
            return 0;
           }
              default:{
                cout<<"Invalid choice. Please try again."<<endl;
                break;
              }
        }
    }
}
int main(){
    return finance();
}