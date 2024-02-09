#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <set>
#include <vector>
#include "datastore.h"
#include "util.h"
#include "product.h"
#include "user.h"


class MyDataStore : public DataStore{
    public:
        // Dtor
        ~MyDataStore();

        /**
        * Adds a user to the data store
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
    
    private:
        std::set<Product*> items;
        std::set<User*> users; 
};
#endif