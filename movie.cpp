#include "movie.h"



MovieProduct::MovieProduct(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating):
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{
}

// Probably need a copy ctor and assignment function
MovieProduct::~MovieProduct(){

}

/*
Movie: the movie’s genre should be a searchable keyword

Movie - Product name 
        & genre 
For other keywords (book ISBN and movie genre) no punctuation or size analysis is necessary and it should be used verbatim as a keyword. Here is an example:
The ISBN 978-000000000-1 should be used exactly as is for the keyword entry


*/
std::set<std::string> MovieProduct::keywords() const{
    std::set<std::string> result = parseStringToWords(this->name_);
    result.insert(convToLower(this->genre_)); 
    
    return result; 
}


/**
 * Returns a string to display the product info for hits of the search
 * 
    <name>
    Genre: <genre> Rating: <rating>
    <price> <quantity> left.
 */

std::string MovieProduct::displayString() const{
    std::string result = this->name_ + "\n" + "Genre: " + this->genre_ + " Rating: " + this->rating_ + "\n" + std::to_string(this->price_) + " " + std::to_string(this->qty_) + " left.";
    return result;
} 


/*
os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
Reproduce the database file from the current Products and User values
*/
void MovieProduct::dump(std::ostream& os) const{
    os << this->category_ << "\n" << this->name_ << "\n" << std::setprecision(2) << this->price_ << "\n" << this->qty_ << "\n" << this->genre_ << "\n" << this->rating_ << "\n";
}

