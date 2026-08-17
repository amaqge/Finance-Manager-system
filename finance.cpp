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
    void add_info(int data, string con, int c, string category){
        file.open("finance.txt", ios::app);
        file<<"Data; "<<data<<"| Category; "<<category<<"| Consumption; "<<con<<"| Cost; "<<c<<endl;        
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


class Category:public File{
protected:
// type of category and the cost of each category
    string category;
    int food = 0;
    int transport = 0;
    int entertainment = 0;
    int health = 0;
    int other = 0;
public:
    Category(){}
    // the function to add the cost to the category
    void type_category(string category, int cost){
        this->category = category;
        if(category == "food" || category == "Food"){
            food += cost;
        }
        else if(category == "transport" || category == "Transport"){
            transport += cost;
        }
        else if(category == "entertainment" || category == "Entertainment"){
            entertainment += cost;
        }
        else if(category == "health" || category == "Health"){
            health += cost;
        }
        else{
            other += cost;
        } 
    }
    void display_category(){
        cout<<"Food: "<<food<<endl;
        cout<<"Transport: "<<transport<<endl;
        cout<<"Entertainment: "<<entertainment<<endl;
        cout<<"Health: "<<health<<endl;
        cout<<"Other: "<<other<<endl;
    }
};

class Stats:public File{
protected:
    int sum = 0;
public:
    // the function to calculate the total spending
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
    string category;
public:
    void add_info(int data, int cost, string consumption, Stats& s, File& f1, Category& c, string category){
        // if you spent more than your income it will display an error message
        if(f1.get_income() - cost < 0){
            cout<<"ERROR : you cannot spent more than your income"<<endl;
        }
        // if you spent less than your income it will add the data to the file
        else{
        f1.add_info(data, consumption, cost, category);
        s.total(cost);
        f1.take_cost(cost);
        c.type_category(category, cost);
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
        Category c;
        f1.ho(icome);
    while(true){
        int choice;
        cout<<"======================================================"<<endl;
        cout<<"||         Welcome to Finance Manager System.        ||"<<endl;
        cout<<"||        Please select an option:                   ||"<<endl;
        cout<<"|| 1. Add spending                                   ||"<<endl;
        cout<<"|| 2. Display category information                   ||"<<endl;
        cout<<"|| 3. Display total spending                         ||"<<endl;
        cout<<"|| 4. Display balance                                ||"<<endl;
        cout<<"|| 5. Display all information from the file          ||"<<endl;
        cout<<"|| 6. Exit                                           ||"<<endl;
        cout<<"======================================================"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        
        switch(choice){
           case 1:{
            int data,cost;
            string consumption, category;
            cout<<"Enter the date: ";
            cin>>data;
            cout<<"Enter the category: ";
            cin>>category;
            cout<<"Enter the consumption: ";
            cin>>consumption;
            cout<<"Enter the cost: ";
            cin>>cost;
            a.add_info(data, cost, consumption, s, f1, c, category);
            break;
           }
           case 2:{
            c.display_category();
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
            f1.display();
            break;
           }
           case 6:{
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