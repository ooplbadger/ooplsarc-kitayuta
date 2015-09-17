//=========================
// Kitayuta.c++
// oopl_badger
//=========================


//------------------------- Includes
#include "Kitayuta.h"


//------------------------- Globals

// Generic character used when any character will do
static const char GENERIC_CHAR = 'z';

// Wildcard character - match any character
static const char WILDCARD_CHAR = '.';


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
  const char *s2 =    string2.c_str();

  while (*s1 && *s2) {
    if ((*s1 != WILDCARD_CHAR) &&
	(*s2 != WILDCARD_CHAR) &&
	(*s2 != *s1)) {
      break;
    }

    s1++;
    s2++;
  }

  return *(const unsigned char *) s1 - *(const unsigned char *) s2;
}	// kitayuta_strcmp()


//===========================================================================
// kitayuta_eval()
//
string kitayuta_eval(const string& input_str)
{
  return input_str;
}	// kitayuta_eval()
