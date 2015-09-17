//=========================
// Kitayuta.h
// oopl_badger
//=========================

#ifndef Kitayuta_h
#define Kitayuta_h


//------------------------- Includes

#include <iostream> // istream, ostream
#include <string>   // string

using namespace std;


//===========================================================================
// kitayuta_strcmp
//

/**
 * @param result_str result of kitayuta evaluation
 * @param ref_str correct response
 * @return whether result_str matched ref_str
 *
 * result_str is a string of lowercase English letters, output by kitayuta_eval().
 * ref_str is a string of lowercase English letters with possible wildcards mixed in
 * return result is 0 if the strings match; non-zero if they don't match
 */
int kitayuta_strcmp(const string& result_str, const string& ref_str);


//===========================================================================
// kitayuta_eval
//

/**
 * @param input_str input string
 * @return output string
 *
 * Input string consists of 1-10 characters.  Each character is a lowercase
 * English letter.
 *
 * If it is possible to turn s into a palindrome by inserting one lowercase
 * English letter, print the resulting string in a single line.
 * Otherwise, print "NA" (without quotes, case-sensitive). 
 */
string kitayuta_eval(const string& input_str);


#endif // Kitayuta_h
