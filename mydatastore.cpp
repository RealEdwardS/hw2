#include "mydatastore.h"

// Dtor
MyDataStore::~MyDataStore(){
    // std::map<User*, std::deque<Product*>>::iterator it; 
    // for (it = carts.begin(); it != carts.end(); ++it){
    //     delete (it)->second; 
    // }
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
    std::set<std::string> currKeywords = p->keywords(); 
    for (it = currKeywords.begin(); it != currKeywords.end(); ++it){
        mapOfKeywords[(*it)];
        // std::map<std::string, std::set<Product*>> mapIt; 
        mapOfKeywords[(*it)].insert(p); 
    }
}

/**
* Adds a user to the data store
*/
void MyDataStore::addUser(User* u){
    users.insert(u);
    std::deque<Product*> userCart;
    carts[u] = userCart;
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
        if (it == mapOfKeywords.end()){
            continue;
        }
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
                result = setUnion(result, dequeOfProducts.front());
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
void MyDataStore::reverseCart(User* currUser){
   std::map<User*, std::deque<Product*>>::iterator secondIt = carts.find(currUser);
   
   reverse(secondIt->second.begin(), secondIt->second.end());
}
User* MyDataStore::getUser(std::string username, bool& isSecond){
    std::set<User*>::iterator it;
    User* wantedUser; 

    bool foundName = false;
    for (it = users.begin(); it != users.end(); ++it){
        if ((*it)->getName() == username){
          if (it != users.begin()){
            isSecond = true; 
          }
            wantedUser = *it;
            foundName = true; 
            break;
        }
    }

    if (foundName == false){
        return nullptr; 
    }

    return wantedUser; 
} 
std::deque<Product*> MyDataStore::getUserCart(User* wantedUser){
    // std::set<User*>::iterator it;
    // User* wantedUser; 

    // bool foundName = false;
    // for (it = users.begin(); it != users.end(); ++it){
    //     if ((*it)->getName() == username){
    //         wantedUser = *it;
    //         foundName = true; 
    //         break;
    //     }
    // }

    // if (foundName == false){
    //     throw "Invalid request"; 
    // }

    // User* wantedUser = getUser(username); 

    std::map<User*, std::deque<Product*>>::iterator secondIt = carts.find(wantedUser);
    std::deque<Product*> userCart = secondIt->second; 

    return userCart; 
}

/**
* Reproduce the database file from the current Products and User values
*/
void MyDataStore::dump(std::ostream& ofile){
    ofile << "<products>\n"; 
    std::set<Product*>::iterator itemIterator; 
    for (itemIterator = items.begin(); itemIterator != items.end(); ++itemIterator){
        (*itemIterator)->dump(ofile); 
    }
    ofile << "</products>\n";

    ofile << "<users>\n";
    std::set<User*>::iterator userIterator;
    for (userIterator = users.begin(); userIterator != users.end(); ++userIterator){
        (*userIterator)->dump(ofile); 
    }

    ofile << "</users>\n";
}

void MyDataStore::addItem(User* currUser, Product* currItem){
    std::set<User*>::iterator userIt = users.find(currUser);
    if (userIt == users.end()){
        throw "Cannot find user"; 
    }

    std::deque<Product*>* currCart = &(carts[*userIt]); 
    currCart->push_back(currItem); 
}



void MyDataStore::deleteAll(){
    mapOfKeywords.clear();
    carts.clear();
    std::set<Product*>::iterator itemIterator; 
    for (itemIterator = items.begin(); itemIterator != items.end(); ++itemIterator){
        delete *(itemIterator); 
    }

    std::set<User*>::iterator userIterator;
    for (userIterator = users.begin(); userIterator != users.end(); ++userIterator){
        delete *(userIterator);
    }
}


std::deque<Product*>& MyDataStore::removeFrontItemFromCart(User* user){
    // std::map<User*, std::deque<Product*>>::iterator it = this->carts.find(user);
    // std::cout << "\nCARTS SIZE" << carts[user].size() << std::endl;
    carts[user].pop_front();
    // std::cout << "\nCARTS SIZE AFTER" << carts[user].size() << std::endl;

    return carts[user]; 
}

std::deque<Product*>& MyDataStore::clearCart(User* user){

    carts[user].clear();

    return carts[user]; 
}