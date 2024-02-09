#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <iomanip>
#include "product.h"
#include "util.h"

class BookProduct : public Product{
    public:
        // Ctor
        BookProduct(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author);
        
        // Dtor
        ~BookProduct();

        // Returns the appropriate keywords that this product should be associated with
        std::set<std::string> keywords() const;
        
        /**
         * Returns a string to display the product info for hits of the search
         */
        std::string displayString() const; 

        /**
        * Outputs the product info in the database format
        * Reproduce the database file from the current Products and User values
        */
        void dump(std::ostream& os) const;

    private:
        std::string isbn_;
        std::string author_;    
};
#endif
