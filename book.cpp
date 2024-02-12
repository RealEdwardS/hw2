#include "book.h"


BookProduct::BookProduct(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author):
    Product(category, name, price/1.00, qty),
    isbn_(isbn),
    author_(author) 
{
}

// Probably need a copy ctor and assignment function
BookProduct::~BookProduct(){

}
/*
Books: the words in the author’s name should be searchable keywords as well as the book’s ISBN number
For other keywords (book ISBN and movie genre) no punctuation or size analysis is necessary and it should be used verbatim as a keyword. Here is an example:
The ISBN 978-000000000-1 should be used exactly as is for the keyword entry

Books - Product name & author
        and ISBN 
*/
std::set<std::string> BookProduct::keywords() const{
    std::set<std::string> result = parseStringToWords(this->author_ + " " + this->name_);
    result.insert(this->isbn_); 
    return result;
}


/**
 * Returns a string to display the product info for hits of the search
 
<name>
Author: <author> ISBN: <isbn>
<price> <quantity> left.

 */
std::string BookProduct::displayString() const{
    std::stringstream ss;
    std::string price;
    ss << std::fixed << std::setprecision(2) << this->price_; 
    ss >> price;
    std::string result;
    result = this->name_ + "         \n" + "Author: " + this->author_ + " ISBN: " + this->isbn_ + "\n" + price + " " + std::to_string(this->qty_) + " left."; 
    return result;
} 

/*
outputs the database format of the product info
Reproduce the database file from the current Products and User values


os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
Reproduce the database file from the current Products and User values

*/
void BookProduct::dump(std::ostream& os) const{
   os << this->category_ << "\n"  << this->name_ << "\n" << std::fixed << std::setprecision(2)<< this->price_ << "\n" << this->qty_ <<  "\n" << this->isbn_ << "\n" << this->author_ << "\n";
}

