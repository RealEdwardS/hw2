#ifndef MOVIE_H
#define MOVIE_H
#include <iomanip>
#include <string>
#include "product.h"
#include "util.h" 

class MovieProduct : public Product{
    public:
        // Ctor
        MovieProduct(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);
        
        // Dtor
        ~MovieProduct();

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
        std::string genre_;
        std::string rating_;    
};
#endif
