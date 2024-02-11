#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <deque>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    stringstream ss;
    ss << rawWords; 
    
    std::set<std::string> result; 

    std::deque<std::string> totalWords;
    std::string currWord; 

    while (ss >> currWord){
        totalWords.push_front(currWord);
    }

    std::vector<std::string> punc = {".", ",", "?", ";", "!", ":", "'", "(", ")", "[", "]", "{", "}", "\"", "*", "@", "/", "-"}; 
    // Didn't add "-", might be problem later

    while (totalWords.size() > 0){

        // If word length is less than 1, continue to next word
        if (totalWords.front().length() < 2){
            totalWords.pop_front();
            continue;
        }

        // Loops through each punc
        for (int x = 0; x < punc.size(); ++x){
            std::string currPunc = punc.at(x);

            int foundIndex = (totalWords.front()).find(currPunc);

            // If found a punc, split and push back of deque
            if (foundIndex != std::string::npos){
                std::string firstHalf = (totalWords.front()).substr(0,foundIndex);
                totalWords.push_back(firstHalf); 

                // If punc wasn't at last index
                if (foundIndex < (totalWords.front()).length()-1){
                    std::string secondHalf = (totalWords.front()).substr(foundIndex, (totalWords.front()).length()-1);
                    totalWords.push_back(secondHalf); 
                }
                
                // Pop the original word
                totalWords.pop_front(); 

                // Skip to the main while loop
                continue;
            }
        }

        // If didn't find punc & size >= 2, then it's a valid word, insert into result (lowercase convert), and continue to next word
        result.insert(convToLower(totalWords.front()));
        totalWords.pop_front();
    }

    return result; 
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
