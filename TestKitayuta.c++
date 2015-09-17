//=========================
// TestKitayuta.c++
// oopl_badger
//=========================


//------------------------- Includes
#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string

#include "gtest/gtest.h"

#include "Kitayuta.h"

using namespace std;



// Wildcard character - match any character
static const char WILDCARD_CHAR = '.';


//---------------------------------------------------------------------------
// Test kitayuta_strcmp()
//
TEST(KitayutaStrcmp, t0) {
  ASSERT_EQ(kitayuta_strcmp("", ""), 0);
}

TEST(KitayutaStrcmp, t1_0) {
  ASSERT_EQ(kitayuta_strcmp("a", "a"), 0);
}

TEST(KitayutaStrcmp, t1_1) {
  ASSERT_EQ(kitayuta_strcmp("a", "b"), -1);
}

TEST(KitayutaStrcmp, t1_2) {
  ASSERT_EQ(kitayuta_strcmp("b", "a"), 1);
}

TEST(KitayutaStrcmp, t1_3) {
  ASSERT_EQ(kitayuta_strcmp("a", "e"), -4);
}

TEST(KitayutaStrcmp, t1_4) {
  ASSERT_EQ(kitayuta_strcmp("e", "a"), 4);
}

TEST(KitayutaStrcmp, t1_5) {
  ASSERT_EQ(kitayuta_strcmp("", "a"), -'a');
}

TEST(KitayutaStrcmp, t1_6) {
  ASSERT_EQ(kitayuta_strcmp("a", ""), 'a');
}

TEST(KitayutaStrcmp, t5_0) {
  ASSERT_EQ(kitayuta_strcmp("abc", "abcde"), -'d');
}

TEST(KitayutaStrcmp, t5_1) {
  ASSERT_EQ(kitayuta_strcmp("abcde", "abc"), 'd');
}

TEST(KitayutaStrcmp, t5_2) {
  ASSERT_EQ(kitayuta_strcmp("abcde", "abcde"), 0);
}

TEST(KitayutaStrcmp, t5_3) {
  ASSERT_EQ(kitayuta_strcmp("abcde", "abcfe"), -2);
}

TEST(KitayutaStrcmp, t5_4) {
  ASSERT_EQ(kitayuta_strcmp("abcfe", "abcde"), 2);
}

TEST(KitayutaStrcmp, t5_5) {
  ASSERT_EQ(kitayuta_strcmp("abcde", "abcdg"), -2);
}

TEST(KitayutaStrcmp, t5_6) {
  ASSERT_EQ(kitayuta_strcmp("abcdg", "abcde"), 2);
}

//-------------------------------------------------- Test wildcard

TEST(KitayutaStrcmp, w1_0) {
  ASSERT_EQ(kitayuta_strcmp("a", "."), 0);
}

TEST(KitayutaStrcmp, w1_1) {
  ASSERT_EQ(kitayuta_strcmp(".", "a"), 0);
}

TEST(KitayutaStrcmp, w1_2) {
  ASSERT_EQ(kitayuta_strcmp("", "."), -WILDCARD_CHAR);
}

TEST(KitayutaStrcmp, w1_3) {
  ASSERT_EQ(kitayuta_strcmp(".", ""), WILDCARD_CHAR);
}

TEST(KitayutaStrcmp, w5_0) {
  ASSERT_EQ(kitayuta_strcmp("abcde", "a.c.e"), 0);
}

TEST(KitayutaStrcmp, w5_1) {
  ASSERT_EQ(kitayuta_strcmp("abcde", "a.cfe"), -2);
}

TEST(KitayutaStrcmp, w5_2) {
  ASSERT_EQ(kitayuta_strcmp("abcde", "abc.."), 0);
}

TEST(KitayutaStrcmp, w5_3) {
  ASSERT_EQ(kitayuta_strcmp("abcde", "abc..."), -WILDCARD_CHAR);
}

TEST(KitayutaStrcmp, w5_4) {
  ASSERT_EQ(kitayuta_strcmp("abcde", "abc."), 'e');
}


//---------------------------------------------------------------------------
// Test kitayuta_eval()
//

//-------------------------------------------------- Length 0
// Note:  http://codeforces.com/problemset/problem/505/A/ specifies
// input will always be length one, but we should still work with
// degenerate case.


//------------------------- Test null
TEST(KitayutaEval, t0) {
  string in_str("\n");
  string out_str = kitayuta_eval(in_str);
  ASSERT_EQ(kitayuta_strcmp(out_str, "."), 0);
}

//-------------------------------------------------- Length 1
