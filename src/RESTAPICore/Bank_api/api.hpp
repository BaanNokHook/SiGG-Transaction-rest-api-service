/**
 * @file api.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string>  
class Credit {
      std::string owner;  
      int credit_limit;  
      int amount_due; 

      public:  

          // constuctor  
          Credit();  

          // destructor  
          ~Credit();   

          // setters 
          void set_credentials(std::string owner_name, int credit_limit);  
          int set_credit_limit(int credit_limit);   
          int add_amount_due(int amount);  
          int pay_debt(int amount_paid);  

          // getters 
          int get_remaining();  
          int get_due();  
          int get_limit();  
};  

class Investing {
      std::string owner;  
      int cash_amount;  

    public: 
        Investing();
        ~Investing();

        // setters
        int deposit_cash(int amount);
        int withdraw_cash(int amount);
        // getters
        int get_cash_amount();
};



class Account {
    std::string owner;
    int total;
    Credit credit_card;

    public:
        // constructor
        Account(std::string owner_name, int inital_deposit=0);

        //destructor
        ~Account();

        // getters
        std::string get_owner();
        int get_total();

        // setters
        int deposit(int amount);
        int withdraw(int amount);

        // credit methods

        // credit setters
        void activate_credit(int credit_limit);
        int change_credit_limit(int credit_limit);
        int use_credit(int amount_due);
        int pay_credit_debt(int payment);

        // credit getters
        int get_credit_remaining();
        int get_amount_due();
        int get_credit_limit();

};
