#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;



// Dream programer;
// Only I and god know how this code work , 
//after few updates only god will know how it work
// You can change all you want , but pls make explain 
class Stats;
class Category;


class File{
protected:
    string data;
    string consumption;
    fstream file;
    double cost;
    double income;
public:
    
// constructor of the income to get it anywhere in the program
    File(){}
    // reading file to save information
    void ho(double income){
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
    double get_income(){
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
    void add_info(string data, string con, double c, string category){
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
    void edit_info(Stats& s, Category& c){
        vector<string> lines;
        string line;
        file.open("finance.txt", ios::in);
        while(getline(file, line)){
            lines.push_back(line);
        }
        file.close();
        int number = 1;

        for(int i = 0; i < lines.size(); i++){
            if(lines[i].find("Data") != string::npos){
                cout<<number<<". "<<lines[i]<<endl;
                number++;
            }
        }
        int choise;
        cout<<"Enter spending number to edit: ";
        cin>>choise;
        int spending_number = 1;
        int line_index = -1;
        for(int i = 0; i < lines.size(); i++){
            if(lines[i].find("Data; ") != string::npos){
                if(spending_number == choise){
                    line_index = i;
                    break;
                }
                spending_number++;
            }
        }
        if(line_index == -1){
            cout<<"Invalid spending number"<<endl;
            return;
        }
        cout<<"Selected spending: "<<endl;
        cout<<lines[line_index]<<endl;

        size_t old_category_statr = lines[line_index].find("| Category; ");
        size_t old_category_end = lines[line_index].find("| Consumption; ");

        string old_category = lines[line_index].substr(
            old_category_statr + 12,
            old_category_end - (old_category_statr + 12)
        );
        size_t old_cost_start = lines[line_index].find("| Cost; ");
            double old_cost = stod(lines[line_index].substr(old_cost_start + 8));
        string new_data, new_category, new_consumption;
        double new_cost;
        cout<<"Enter new data: ";
        cin>>new_data;
        cout<<endl;
        cout<<"Enter new category";
        cin>>new_category;
        cout<<endl;
        cout<<"Enetr new consumption";
        cin>>new_consumption;
        cout<<endl;
        cout<<"Enter new cost";
        cin>>new_cost;
        cout<<endl;
        s.remove_total(old_cost);
        s.add_total(new_cost);

        c.remove_category(old_category, old_cost);
        c.add_category(new_category, new_cost);
        lines[line_index] = to_string(choise) + ". Data; " + new_data + "| Category; " + new_category + "| Consumption; " + new_consumption + "| Cost; " + to_string(new_cost);
        file.open("finance.txt", ios::out | ios::trunc);
            for(string line : lines){
                file<<line<<endl;
            }
            file.close();
    }
    

};


class Category:public File{
protected:
// type of category and the cost of each category
    string category;
    double food = 0;
    double transport = 0;
    double entertainment = 0;
    double health = 0;
    double other = 0;
public:
    Category(){}
    void load_from_file(){
        file.open("finance.txt", ios::in);
        string line;
        double cost  = 0;
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
                cost = stod(cost_string);
            }
            if(part != string::npos && part2 != string::npos){
                type_category(category, cost);
            }
        }
        
        file.close();
    }
    // the function to add the cost to the category
    void type_category(string category, double cost){
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
    void remove_category(string category, double cost){
        this->category = category;
        if(category == "food" || category == "Food"){
            food -= cost;
        }
        else if(category == "transport" || category == "Transport"){
            transport -= cost;
        }
        else if(category == "entertainment" || category == "Entertainment"){
            entertainment -= cost;
        }
        else if(category == "health" || category == "Health"){
            health -= cost;
        }
        else{
            other -= cost;
        }

    }
    void add_category(string category, double cost){
        type_category(category, cost);
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
    double sum = 0;
public:
    // the function to calculate the total spending
    void total(double cost){
    sum += cost;
}
    // the function to display the total spending
    void display_spending(){
        cout<<"Total spending: "<<sum<<endl;
    }
    // the function to calculate the balance
    void calculate_balance(double income){
        double balance=income-sum;
        cout<<"Balance: "<<balance<<endl;
    }
    void load_from_file(){
        file.open("finance.txt", ios::in);
        string line;
        while(getline(file, line)){
            size_t part2 = line.find("| Cost; ");
            if(part2 != string::npos){
                string cost_string = line.substr(part2 + 8);
                cost = stod(cost_string);
                sum += cost;
            }
        }
        file.close();
    }
    void remove_total(double cost){
        sum -= cost;
    }
    void add_total(double cost){
        sum +=cost;
    }
    
};

class Add_info:public File{
protected:
    int data;
    string consumption;
    double cost;
    string category;
public:
    void add_info(string data, double cost, string consumption, Stats& s, File& f1, Category& c, string category){
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
            double cost;
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
                f1.edit_info(s, c);
                break;
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