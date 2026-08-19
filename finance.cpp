#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;




class File{
protected:
    string data;
    string consumption;
    fstream file;
    int cost;
    int income;
public:
    
// constructor of the income to get it anywhere in the program
    File(){}
    // reading file to save information
    void ho(int income){
        file.open("finance.txt", ios::in);
        string line;
        bool found = false;
        while(getline(file, line)){
            size_t inc= line.find("Income; ");
            if(inc !=  string::npos){
              string income_string = line.substr(8);
              this->income = stoi(income_string);
                found = true;
                break;
            }
        }
        file.close();
        if(!found){
            cout<<"pls enter Income:"<<endl;
            cin>>income;
            this->income = income;

            add();
        }
    }
    int get_income(){
        return income;
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
    void add_info(string data, string con, int c, string category){
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
    void edit_info(){
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
    void load_from_file(){
        file.open("finance.txt", ios::in);
        string line;
        int cost  = 0;
        while(getline(file, line)){
            size_t part  = line.find("| Category; ");
            if(part != string ::npos){
            size_t category_end = line.find("| Consumption; ");
            category = line.substr(
                part + 12,
                category_end - (part + 12)
            );
            }
            
            size_t part2 = line.find("| Cost; ");
            if(part2 != string::npos){
                string cost_string = line.substr(part2 + 8);
                cost = stoi(cost_string);
            }
            if(part != string::npos && part2 != string::npos){
                type_category(category, cost);
            }
        }
        
        file.close();
    }
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
    void load_from_file(){
        file.open("finance.txt", ios::in);
        string line;
        while(getline(file, line)){
            size_t part2 = line.find("| Cost; ");
            if(part2 != string::npos){
                string cost_string = line.substr(part2 + 8);
                cost = stoi(cost_string);
                sum += cost;
            }
        }
        file.close();
    }
    
};

class Add_info:public File{
protected:
    int data;
    string consumption;
    int cost;
    string category;
public:
    void add_info(string data, int cost, string consumption, Stats& s, File& f1, Category& c, string category){
        // if you spent more than your income it will display an error message
        if(f1.get_income() - cost < 0){
            cout<<"ERROR : you cannot spent more than your income"<<endl;
        }
        // if you spent less than your income it will add the data to the file
        else{
        f1.add_info(data, consumption, cost, category);
        s.total(cost);
        c.type_category(category, cost);
        }
    }
    
};

int finance(){
    int income = 0;
        File f1;
        Stats s;
        Add_info a;
        Category c;
        f1.ho(income);
        s.load_from_file();
        c.load_from_file();
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
        cout<<"|| 6. Edit spending                                  ||"<<endl;
        cout<<"|| 7. Delete spending                                ||"<<endl;
        cout<<"|| 8. Exit                                           ||"<<endl;
        cout<<"======================================================"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        
        switch(choice){
           case 1:{
            string consumption, category, data;
            int cost;
            cout<<"Enter the date: ";
            cin>>data;
            cout<<endl;
            cout<<"Enter the category: ";
            cin>>category;
            cout<<endl;
            cout<<"Enter the consumption: ";
            cin>>consumption;
            cout<<endl;
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
                f1.edit_info();
                break; // only for check 
                // soon add more
           }
           case 7:{
                // soon
           }
           case 8:{
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