//=========================
// Kitayuta.c++
// oopl_badger
//=========================


//------------------------- Includes
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

/**
 * @param      s                 original string
 * @param      left_idx          left-side character currently being compared
 * @param      right_idx         right-side character currently being compared
 * @param      left_ptr          left-side buffer for recording matching characters
 * @param      right_ptr         right-side buffer for recording matching characters
 * @param[out] num_matching_char number of matching characters
 * @return                       whether we matched everything up to the middle
 *
 * Check for palindromic match, recording matching characters in a left-buffer
 * and a right-buffer.
 */
bool kitayuta_walk(const char *s, int left_idx, int right_idx,
		   char *left_ptr, char *right_ptr, int &num_matching_char)
{
  num_matching_char = 0;
  while (left_idx < right_idx) {
    if (s[left_idx] != s[right_idx]) {
      return false;
    }

    // Record the matching character
    *(left_ptr++)  = s[left_idx];
    *(right_ptr--) = s[left_idx];

    ++num_matching_char;
    ++left_idx;
    --right_idx;

  }
  return true;
}	// kitayuta_walk()


//===========================================================================
// kitayuta_output_answer()

/**
 * @param      output_ss           output stringstream (if we match)
 * @param      s                   original string
 * @param      left_idx            left-side starting point for comparison
 * @param      right_idx           right-side starting point for comparison
 * @param      left_buf            left-side buffer (beginning of buffer)
 * @param      left_ptr            left-side pointer for recording matching characters
 * @param      right_ptr           right-side pointer for recording matching characters
 * @param[out] num_matching_char   number of matching characters
 * @param      need_to_insert_char whether a character needs to be inserted
 * @return                         whether we matched everything up to the middle
 *
 * Check for palindromic match.  If it exists, then output results, including any
 * previously-recorded matches as well.  Insert a character in the middle if need be.
 */
bool kitayuta_output_answer(stringstream & output_ss,
			    const char *s,
			    int left_idx, int right_idx,
			    char *left_buf, char *left_ptr, char *right_ptr,
			    int &num_matching_char,
			    bool need_to_insert_char)
{
  if (!kitayuta_walk(s, left_idx, right_idx,
		    left_ptr, right_ptr, num_matching_char)) {
    return false;
  }

  //--------------------------------------------------
  // Left and right halves match
  //


  left_ptr[num_matching_char] = 0;	// terminate left-half string

  output_ss << left_buf;

  if (left_idx + num_matching_char <= right_idx - num_matching_char) {
    //-------------------------  Odd number of characters, so output middle character
    output_ss << s[left_idx + num_matching_char];

    if (need_to_insert_char) {
      // Output middle character again
      output_ss << s[num_matching_char];
    }

  } else {
    //------------------------- Even number of characters
    if (need_to_insert_char) {
      output_ss << GENERIC_CHAR;
    }
  }

  output_ss << (right_ptr - num_matching_char + 1);


  return true;
}	// kitayuta_output_answer()


//===========================================================================
// kitayuta_insert_char()
//

/**
 * @param      output_ss           output stringstream (if we match)
 * @param      s                   original string
 * @param      left_idx            left-side starting point for comparison
 * @param      right_idx           right-side starting point for comparison
 * @param      left_buf            left-side buffer (beginning of buffer)
 * @param      left_ptr            left-side pointer for recording matching characters
 * @param      right_ptr           right-side pointer for recording matching characters
 * @param      inserted_char       character to be inserted
 * @return                         whether we matched everything up to the middle
 *
 * A mismatch was previously found, so insert the mismatching character and try again.
 */
bool kitayuta_insert_char(stringstream & output_ss,
			  const char *s,
			  int left_idx, int right_idx,
			  char *left_buf, char *left_ptr, char *right_ptr,
			  char inserted_char)
{
  // Handle the character we inserted
  left_ptr[-1] = inserted_char;
  right_ptr[1] = inserted_char;


  int num_matching_char;
  return kitayuta_output_answer(output_ss, s,
				left_idx, right_idx,
				left_buf, left_ptr, right_ptr,
				num_matching_char,
				false);
}	// kitayuta_insert_char()


//===========================================================================
// kitayuta_eval()
//
string kitayuta_eval(const string& input_string)
{
  const char *s = input_string.c_str();

  int left_idx  = 0;
  int right_idx = input_string.length() - 1;

  char left_buf [STR_BUF_SIZE];  // left half of palindrome
  char right_buf[STR_BUF_SIZE]; // right half of palindrome

  right_buf[STR_BUF_SIZE - 1] = 0;	// terminate right-half string
  char *right_ptr = right_buf + STR_BUF_SIZE - 2;

  stringstream output_ss;


  //-------------------------------------------------- Walk string
  int num_matching_char;
  if (!kitayuta_output_answer(output_ss, s,
			      left_idx, right_idx,
			      left_buf, left_buf, right_ptr,
			      num_matching_char,
			      true)) {
    //-------------------------
    // Match failure, so try inserting a character and trying again
    //
    char *new_left_ptr  = left_buf + num_matching_char + 1;
    char *new_right_ptr = right_ptr - num_matching_char - 1;

    if (// Try inserting character on the right
	!kitayuta_insert_char(output_ss, s,
			      left_idx + num_matching_char + 1,
			      right_idx - num_matching_char,
			      left_buf, new_left_ptr, new_right_ptr,
			      s[num_matching_char]) &&

	// Try inserting character on the left
	!kitayuta_insert_char(output_ss, s,
			      left_idx + num_matching_char,
			      right_idx - num_matching_char - 1,
			      left_buf, new_left_ptr, new_right_ptr,
			      s[right_idx - num_matching_char])) {

      //--------------------------------------------------
      // Couldn't find a match by inserting a character on the left or the right:  fail
      //
      output_ss << "NA";
    }
  }

  return output_ss.str();
}	// kitayuta_eval()
