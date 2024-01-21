#pragma once
#include <iostream>
#include <list>
#include <vector> 
#include <unordered_map>
#include <sstream>
 
    struct Order {
        bool cancelled = false;
        int idNumber;
        bool buyOrSell;
        int shares;
        int limit;
        double entryTime;
        double eventTime;
    };

    class Book
    {
    public:
        void initailise();
        void Add_order(Order ord);
        void Cancel_Order(Order ord);
        bool Exexute_order(Order ord, int shares);

    };



