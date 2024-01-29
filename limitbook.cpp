#include "limitbook.h"


    std::vector<std::pair<int, std::list<Order>>> buyTree;
    std::vector<std::pair<int, std::list<Order>>> sellTree;
    int lowestSell;
    int highestBuy;
    int upper_limit;
    int lower_limit;
    double tick_rate;

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
            buyTree[((ord.limit-lower_limit) / tick_rate) - 1].second.push_back(ord);
            buyTree[((ord.limit - lower_limit) / tick_rate) - 1].first += ord.shares;
            if (ord.limit < lowestSell)lowestSell = ord.limit;
        }
        else
        {
            sellTree[((ord.limit - lower_limit) / tick_rate) - 1].second.push_back(ord);
            sellTree[((ord.limit - lower_limit) / tick_rate) - 1].first += ord.shares;
            if (ord.limit > highestBuy)highestBuy = ord.limit;
        }
    }

    void Book::Cancel_Order(Order ord)
    {
        if (ord.buyOrSell)
        {
            Order temp = ord;
            temp.cancelled = true;
            buyTree[((ord.limit - lower_limit) / tick_rate) - 1].first -= ord.shares;
            auto itr = std::find(
                buyTree[((ord.limit - lower_limit) / tick_rate) - 1].second.begin(), 
                buyTree[((ord.limit - lower_limit) / tick_rate) - 1].second.end(), ord);
            *itr = temp;
        }
        else
        {
            Order temp = ord;
            temp.cancelled = true;
            sellTree[((ord.limit - lower_limit) / tick_rate) - 1].first -= ord.shares;
            auto itr = std::find(
                sellTree[((ord.limit - lower_limit) / tick_rate) - 1].second.begin(),
                sellTree[((ord.limit - lower_limit) / tick_rate) - 1].second.end(), ord);
            *itr = temp;
        }
    }

    bool Book::Exexute_order(Order ord, int shares)
    {
        if (shares > ord.shares) std::cout << "invalid share amount";
        if (ord.cancelled)
        {
            if (ord.buyOrSell)
            {
                buyTree[((ord.limit - lower_limit) / tick_rate) - 1].second.pop_front();
            }
            else
            {
                sellTree[((ord.limit - lower_limit) / tick_rate) - 1].second.pop_front();
            }
            return false;
        }
        else
        {
            if (ord.buyOrSell)
            {
                buyTree[((ord.limit - lower_limit) / tick_rate) - 1].first -= shares;
                if (buyTree[((ord.limit - lower_limit) / tick_rate) - 1].second.front().shares == shares)
                {
                    buyTree[((ord.limit - lower_limit) / tick_rate) - 1].second.pop_front();
                }
                else
                {
                    buyTree[((ord.limit - lower_limit) / tick_rate) - 1].second.front().shares -= shares;
                }
            }
            else
            {
                sellTree[((ord.limit - lower_limit) / tick_rate) - 1].first -= shares;
                if (sellTree[((ord.limit - lower_limit) / tick_rate) - 1].second.front().shares == shares)
                {
                    sellTree[((ord.limit - lower_limit) / tick_rate) - 1].second.pop_front();
                }
                else
                {
                    sellTree[((ord.limit - lower_limit) / tick_rate) - 1].second.front().shares -= shares;
                }
            }
            return true;
        }
    }
     

