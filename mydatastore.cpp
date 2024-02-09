#include "mydatastore.h"

// Dtor
MyDataStore::~MyDataStore(){

}

/**
* Adds a product to the data store
*/ 
void MyDataStore::addProduct(Product* p){
    // std::set<Product*>::iterator it = items.find(p); 
    // if (it != items.end()){
    //     (*it)->qty_;
    // }
    items.insert(p);

}

/**
* Adds a user to the data store
*/
void MyDataStore::addUser(User* u){
    users.insert(u);
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    // AND search
    if (type == 0){
        std::set<Product*> itemsWithBoth; 

        std::vector<std::string>::iterator it1; 
        std::set<Product*>::iterator it2;
        for (it1 = terms.begin(); it1 != terms.end(); ++it1){
            for (it2 = items.begin(); it2 != items.end(); ++it2){
                if ((*it2)->getName() == *(it1)){

                }

                else if ((*it2)->get)
            }
        }

    }

    // OR search
    else if (type == 1){

    }
}

/**
* Reproduce the database file from the current Products and User values
*/
void MyDataStore::dump(std::ostream& ofile){

}