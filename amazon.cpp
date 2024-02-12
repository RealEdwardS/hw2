#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "user.h"
#include "db_parser.h"
#include "product.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"

// #include "book.h"
// #include "clothing.h"
// #include "movie.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};

struct ProdNameSorter2 {
    bool operator()(Product* p1, Product* p2) {
        return false;
    }
};

void displayProducts(vector<Product*>& hits);
void displayVIEWProducts(vector<Product*>& hits, bool result);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits; // <-- Product cart
    bool done = false;
    while(!done) {
        cout << "\nEnter command: ";// << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                cout << "\n";
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
              cout << "\n"; 
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                ds.deleteAll();
                // Delete parsers
                // delete userSectionParser;
                // delete productSectionParser; 
                done = true;
            }
	    /* Add support for other commands here */

            else if ( cmd == "ADD"){
              cout << "\n"; 
                string username;
                unsigned int searchHitHumber;
                if (ss >> username){
                  bool isSecond = false;
                    User* currUser = ds.getUser(username, isSecond);

                    // If cannot find user
                    if (currUser == nullptr){
                        cout << "Invalid request" << endl; 
                    }

                    // If found searchNumber
                    else if (ss >> searchHitHumber){
                        // If the search number is invalid
                        if (searchHitHumber <= 0 || searchHitHumber > hits.size()){
                            cout << "Invalid request"; 
                        }

                        else{ 
                            Product* wantedItem = hits.at(searchHitHumber-1);
                            ds.addItem(currUser, wantedItem); 
                        }
                    }

                    // If not found search number
                    else{
                        cout << "Invalid request" << endl; 
                    }
                }

                // If not found username
                else{
                    cout << "Invalid request" << endl;
                }
            }

            else if ( cmd == "VIEWCART"){
                cout << "\n"; 
                string username;
                if (ss >> username){
                    bool isSecond = false; 
                    User* currUser = ds.getUser(username, isSecond); 
                    // If cannot find username
                    if (currUser == nullptr){
                        cout << "Invalid username" << endl; 
                    }

                    
                    else{
                      vector<Product*> result;
                        if (isSecond == false){
                          //cout << "i aem ercalled " << endl;
                          //ds.reverseCart(currUser);
                          deque<Product*> currUserCart = ds.getUserCart(currUser); 
                           
                          for (unsigned int i = 0; i < currUserCart.size()+1; ++i){
                            result.push_back(currUserCart.front());
                            currUserCart.pop_front();
                          }
                        }

                        else{
                          deque<Product*> currUserCart = ds.getUserCart(currUser); 
                          for (unsigned int i = 0; i < currUserCart.size()+1; ++i){
                            result.push_back(currUserCart.front());
                            currUserCart.pop_front();
                          }
                        }



                        displayVIEWProducts(result, isSecond); 
                        // deque<Product*> currUserCart = ds.getUserCart(username); 
                        // // cout << to_string(currUserCart.size()) << endl; 
                        // vector<Product*> result;
                        // // vector<Product*> finalResult;
                        // for (unsigned int i = 0; i < currUserCart.size()+1; ++i){
                        //     result.push_back(currUserCart.front()); 
                        //     currUserCart.pop_front(); 
                        // }

                        // // for (int i = 0; i < result.size(); ++i){
                        // //   finalResult.push_back(result.at(result.size()-1)); 
                        // // }
                        // //std::reverse(result.begin(), result.end());
                        // displayVIEWProducts(result); 
                    }
                }
                
                // If cannot get input
                else{
                  cout << "\n"; 
                    cout << "Invalid username"; 
                }
            }

            else if ( cmd == "BUYCART"){
                string username;
                if (ss >> username){
                  bool isSecond = false;
                    User* currUser = ds.getUser(username, isSecond);
                    // If cannot find username
                    if (currUser == nullptr){
                        cout << "Invalid username" << endl;
                    }
                    
                    else{
                        deque<Product*> currUserCart = ds.getUserCart(currUser);
                        double totalPrice = 0; 

                        // Go through cart
                        for (unsigned int i = 0; i < currUserCart.size()+1; ++i){
                            // If balance is good, remove money from person, subtract product qty, and pop from cart 
                            if (totalPrice + (currUserCart.front())->getPrice() <= currUser->getBalance()){
                                currUser->deductAmount((currUserCart.front())->getPrice());
                                currUserCart.front()->subtractQty(1);
                                currUserCart.pop_front(); 
                            }
                        }
                    }
                }

                else{
                    cout << "Invalid request" << endl; 
                }
            }

            else {
                cout << "Unknown command" << endl;
            }
        }

    }

    // ds.deleteAll();
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}

void displayVIEWProducts(vector<Product*>& hits, bool second)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }

    //if (second == false){
      std::sort(hits.begin(), hits.end(), ProdNameSorter2());
    //}

    // else{
    //   std::sort(hits.begin(), hits.end(), ProdNameSorter());
    // }
    
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Item " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
    // cout << "\n";
}