//=========================
// Kitayuta.c++
// oopl_badger
//=========================


//------------------------- Includes
#include <algorithm> // reverse
#include <sstream>   // stringstream

#include "Kitayuta.h"


//------------------------- Globals

// Generic character used when any character will do
static const char GENERIC_CHAR = 'z';

// Wildcard character - match any character
static const char WILDCARD_CHAR = '.';

// Needs to be large enough hold output string (including terminating null)
static const int STR_BUF_SIZE = 20;


//===========================================================================
// kitayuta_strcmp()
// - note:  due to wildcard, the while condition must be:
//     (*s1 && *s2)
//   and NOT
//     (*s1)
//
int kitayuta_strcmp(const string& string1, const string& string2)
{
  const char *s1 = string1.c_str();
  const char *s2 = string2.c_str();

  while (*s1 && *s2) {
    if ((*s1 != WILDCARD_CHAR) &&
	(*s2 != WILDCARD_CHAR) &&
	(*s2 != *s1)) {
      break;
    }

    s1++;
    s2++;
  }

  int return_val = *(const unsigned char *) s1 - *(const unsigned char *) s2;

  if (return_val != 0) {
    cout << "\"" << string1 << "\" vs \"" << string2 << "\"" << endl;
  }

  return return_val;
}	// kitayuta_strcmp()


//===========================================================================
// kitayuta_walk()
//

/**
 * @param
 * @return
 */
bool kitayuta_walk(const char *s, int left_idx, int right_idx, int &num_steps)
{
  num_steps = 0;
  while (left_idx < right_idx) {
    if (s[left_idx] != s[right_idx]) {
      return false;
    }
    ++num_steps;
    ++left_idx;
    --right_idx;
  }
  return true;
}	// kitayuta_walk()


//===========================================================================
// kitayuta_eval()
//
string kitayuta_eval(const string& input_string)
{
  const char *s = input_string.c_str();

  int left_idx  = 0;
  int right_idx = input_string.length() - 1;

  stringstream output_ss;


  //-------------------------------------------------- Walk string
  int num_steps;
  if (kitayuta_walk(s, left_idx, right_idx, num_steps)) {
    //-------------------------
    // Everything matches:  input is a palindrome
    //
    string left_half;

    if (left_idx + num_steps == right_idx - num_steps) {
      // Odd number of characters
      left_half = input_string.substr(0, num_steps + 1);
      output_ss << left_half;
    } else {
      // Even number of characters
      left_half = input_string.substr(0, num_steps);
      output_ss << left_half << GENERIC_CHAR;
    }

    string right_half = left_half;
    reverse(right_half.begin(), right_half.end());

    output_ss << right_half;
  } else {
    //-------------------------
    // Match failure, so try inserting a character and trying again
    //

    int num_steps2;
    if (kitayuta_walk(s, left_idx + num_steps + 1, right_idx - num_steps, num_steps2)) {
      //-------------------------
      // Found a match by inserting a character on the right
      //
      string left_half = input_string.substr(0, num_steps + num_steps2 + 1);
      string right_half = left_half;
      reverse(right_half.begin(), right_half.end());

      output_ss << left_half;

      if (left_idx + num_steps + num_steps2 < right_idx - num_steps - num_steps2) {
	// Odd number of characters, so insert middle character
	output_ss << input_string.substr(num_steps + num_steps2 + 1, 1);
      }

      output_ss << right_half;

    } else if (kitayuta_walk(s, left_idx + num_steps, right_idx - num_steps - 1, num_steps2)) {
      //-------------------------
      // Found a match by inserting a character on the left
      //
      string right_half = input_string.substr(right_idx - num_steps - num_steps2,
					      num_steps + num_steps2 + 1);
      string left_half = right_half;
      reverse(left_half.begin(), left_half.end());

      output_ss << left_half;

      if (left_idx + num_steps + num_steps2 < right_idx - num_steps - num_steps2) {
	// Odd number of characters, so insert middle character
	output_ss << input_string.substr(num_steps + num_steps2, 1);
      }

      output_ss << right_half;
    } else {
      // Couldn't find a match by inserting a character on the left or the right:  fail
      output_ss << "NA";
    }
  }

  return output_ss.str();
}	// kitayuta_eval()
