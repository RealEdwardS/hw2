
#include "clothing.h"


ClothingProduct::ClothingProduct(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand):
    Product(category, name, price, qty),
    size_(size),
    brand_(brand)
{
}

// Probably need a copy ctor and assignment function
ClothingProduct::~ClothingProduct(){

}

/*
Clothing: the words in the brand should be searchable keywords

Clothing - name, brand
For other keywords (book ISBN and movie genre) no punctuation or size analysis is necessary and it should be used verbatim as a keyword. Here is an example:
The ISBN 978-000000000-1 should be used exactly as is for the keyword entry
*/
// Returns the appropriate keywords that this product should be associated with
std::set<std::string> ClothingProduct::keywords() const{
    std::set<std::string> result = parseStringToWords(this->brand_ + " " + this->name_);

    return result;
    
}

/**
 * Returns a string to display the product info for hits of the search
 * 
    <name>
    Size: <size> Brand: <brand>
    <price> <quantity> left.
 */
std::string ClothingProduct::displayString() const{
    std::string result = this->name_ + "\n" + "Size: " + this->size_ + " Brand: " + this->brand_ + "\n" + std::to_string(this->price_) + " " + std::to_string(this->qty_) + " left.";
    return result; 
} 

/*
os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
Reproduce the database file from the current Products and User values
*/
void ClothingProduct::dump(std::ostream& os) const{
    os << this->category_ << "\n" << this->name_ << "\n" << std::setprecision(2) << this->price_ << "\n" << this->qty_ << "\n" << this->size_ << "\n" << this->brand_ << "\n";
}

