#ifndef CLOTHING_H
#define CLOTHING_H
#include <string>
#include <sstream>
#include <iomanip>
#include "product.h"
#include "util.h"



/*
For other keywords (book ISBN and movie genre) no punctuation or size analysis is necessary and it should be used verbatim as a keyword. Here is an example:
The ISBN 978-000000000-1 should be used exactly as is for the keyword entry
*/
class ClothingProduct : public Product{
    public:
        // Ctor
        ClothingProduct(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
        
        // Dtor
        ~ClothingProduct();

        // Returns the appropriate keywords that this product should be associated with
        std::set<std::string> keywords() const;

        /**
         * Returns a string to display the product info for hits of the search
         */
        std::string displayString() const; 

        /**
        * Outputs the product info in the database format
        */
        void dump(std::ostream& os) const;

    private:
        std::string size_;
        std::string brand_;    
};
#endif
