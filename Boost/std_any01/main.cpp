#include <iostream>
#include <algorithm>
#include <any>

using std::string;
using std::cout;
using std::endl;
using std::for_each;
using std::any;
using std::any_cast;
using std::type_info;
using db_row_t = std::vector<any>;

// This is just an example, no actual work with database. 
db_row_t get_row(const char* /*query*/) { 
    // In real application 'query' parameter shall have a 'const 
    // char*' or 'const std::string&' type? See recipe "Type  
    // 'reference to string'" for an answer. 
    db_row_t row; 
    
    row.push_back(10); 
    row.push_back(10.1f); 
    row.push_back(string("hello again"));
    
    return row; 
}

// This is how a user will use your classes 
struct db_sum { 
private: 
    double& sum_; 
public: 
    explicit db_sum(double& sum)
        : sum_(sum) 
    {} 

    void operator()(const any& value) { 
        const type_info& ti = value.type(); 
        
        if (ti == typeid(int)) { 
            sum_ += any_cast<int>(value); 
        } else if (ti == typeid(float)) { 
            sum_ += any_cast<float>(value); 
        } 
    } 
};

int main(int argc, char *argv[])
{
    db_row_t row = get_row("Query: Give me some row, please."); 
    double res = 0.0; 
    for_each(row.begin(), row.end(), db_sum(res)); 
    cout << "Sum of arithmetic types in database row is: "
         << res << endl;
    
    return EXIT_SUCCESS;
}
