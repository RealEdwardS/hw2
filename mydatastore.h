#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <set>
#include <vector>
#include <map>
#include <deque>
#include <utility>
#include "datastore.h"
#include "util.h"
#include "product.h"
#include "user.h"
#include "book.h"


class MyDataStore : public DataStore{
    public:

        // Ctor
        // MyDataStore();

        // Dtor
        ~MyDataStore();

        /**
        * Adds a product to the data store
        */ 
        void addProduct(Product* p); 

        /**
        * Adds a user to the data store
        */
        void addUser(User* u);

        /**
         * Performs a search of products whose keywords match the given "terms"
         *  type 0 = AND search (intersection of results for each term) while
         *  type 1 = OR search (union of results for each term)
         */
        std::vector<Product*> search(std::vector<std::string>& terms, int type);

        /**
         * Reproduce the database file from the current Products and User values
         */
        void dump(std::ostream& ofile);
        
        std::deque<Product*> getUserCart(std::string username);
        User* getUser(std::string username);  
    
    private:
        std::set<Product*> items;
        std::set<User*> users; 

        // keyword <-> set of products
        std::map<std::string, std::set<Product*>> mapOfKeywords;
        
        // map of User <-> set of their product/cart
        std::map<User*, std::deque<Product*>> carts; 
};
#endif