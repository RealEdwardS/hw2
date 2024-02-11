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
    std::set<std::string>::iterator it; 
    // For each keyword of product p, it creates a pair in map with keyword and p as second val
    for (it = p->keywords().begin(); it != p->keywords().end(); ++it){
        mapOfKeywords[(*it)].insert(p);
    }
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
    // loop through each product and get their keywords
    
    std::deque<std::set<Product*>> dequeOfProducts;

    for (int i = 0; i < terms.size(); ++i){
        std::map<std::string, std::set<Product*>>::iterator it = mapOfKeywords.find(terms.at(i));
        dequeOfProducts.push_back(it->second);

    }
    
    // Intersection
    //if (type == 0){
        // While deque is greater than 1
        while (dequeOfProducts.size() > 1){
            std::set<Product*> result;
            // Assign result to front
            result = dequeOfProducts.front();

            // Remove front; 
            dequeOfProducts.pop_front(); 

            // Result (currently holding the previous front) is assigned to intersection of prev front and curr front
            if (type == 0){
                result = setIntersection(result, dequeOfProducts.front());
            }

            else if (type == 1){
                result = setIntersection(result, dequeOfProducts.front());
            }
            

            // Remove curr front (second item)
            dequeOfProducts.pop_front();

            // Push front result into deque
            dequeOfProducts.push_front(result); 
        }
        // Result should be intersection/union of all products
    //}

    // Translate set into vector
    std::vector<Product*> finalResult;
    std::set<Product*>::iterator it; 
    for (it = dequeOfProducts.front().begin(); it != dequeOfProducts.front().end(); ++it){
        finalResult.push_back(*it);
    }
    
    return finalResult;
}

/**
* Reproduce the database file from the current Products and User values
*/
void MyDataStore::dump(std::ostream& ofile){
    // ofile << 
}