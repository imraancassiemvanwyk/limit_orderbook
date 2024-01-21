#include "limitbook.h"


    std::vector<std::pair<int, std::list<int>>> buyTree;
    std::vector<std::pair<int, std::list<int>>> sellTree;
    int lowestSell;
    int highestBuy;
    int upper_limit;
    int lower_limit;
    double tick_rate;
    std::unordered_map<int, Order> buymap;
    std::unordered_map<int, Order> sellmap;

    void Book::initailise()
    {
        int buckets = (upper_limit - lower_limit) / tick_rate;
        buyTree.resize(buckets);
        sellTree.resize(buckets);
    }

    void Book::Add_order(Order ord)
    {
        if (ord.buyOrSell)
        {
            buymap.insert({ ord.idNumber, ord });
            buyTree[(ord.limit / tick_rate) - 1].second.push_back(ord.idNumber);
            buyTree[(ord.limit / tick_rate) - 1].first += ord.shares;
            if (ord.limit < lowestSell)lowestSell = ord.limit;
        }
        else
        {
            sellTree[(ord.limit / tick_rate) - 1].second.push_back(ord.idNumber);
            sellTree[(ord.limit / tick_rate) - 1].first += ord.shares;
            sellmap.insert({ ord.idNumber, ord });
            if (ord.limit > highestBuy)highestBuy = ord.limit;
        }
    }

    void Book::Cancel_Order(Order ord)
    {
        if (ord.buyOrSell)
        {
            buyTree[(ord.limit / tick_rate) - 1].first -= ord.shares;
            buymap[ord.idNumber].cancelled = true;
        }
        else
        {
            sellTree[(ord.limit / tick_rate) - 1].first -= ord.shares;
            sellmap[ord.idNumber].cancelled = true;
        }
    }

    bool Book::Exexute_order(Order ord, int shares)
    {
        if (shares > ord.shares) std::cout << "invalid share amount";
        if (ord.cancelled)
        {
            if (ord.buyOrSell)
            {
                buyTree[(ord.limit / tick_rate) - 1].second.pop_front();
                buymap.erase(ord.idNumber);
            }
            else
            {
                sellTree[(ord.limit / tick_rate) - 1].second.pop_front();
                sellmap.erase(ord.idNumber);
            }
            return false;
        }
        else
        {
            if (ord.buyOrSell)
            {
                buyTree[(ord.limit / tick_rate) - 1].first -= shares;
                if (buymap[ord.idNumber].shares == shares)
                {
                    buyTree[(ord.limit / tick_rate) - 1].second.pop_front();
                    buymap.erase(ord.idNumber);
                }
                else
                {
                    buymap[ord.idNumber].shares -= shares;
                }
            }
            else
            {
                sellTree[(ord.limit / tick_rate) - 1].first -= shares;
                if (sellmap[ord.idNumber].shares == shares)
                {
                    sellTree[(ord.limit / tick_rate) - 1].second.pop_front();
                    sellmap.erase(ord.idNumber);
                }
                else
                {
                    sellmap[ord.idNumber].shares -= shares;
                }
            }
            return true;
        }
    }
     

