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
TEST(KitayutaStrcmp, s0) {
  ASSERT_EQ(kitayuta_strcmp("", ""), 0);
}

TEST(KitayutaStrcmp, s1_0) {
  ASSERT_EQ(kitayuta_strcmp("a", "a"), 0);
}

TEST(KitayutaStrcmp, s1_1) {
  ASSERT_EQ(kitayuta_strcmp("a", "b"), -1);
}

TEST(KitayutaStrcmp, s1_2) {
  ASSERT_EQ(kitayuta_strcmp("b", "a"), 1);
}

TEST(KitayutaStrcmp, s1_3) {
  ASSERT_EQ(kitayuta_strcmp("a", "e"), -4);
}

TEST(KitayutaStrcmp, s1_4) {
  ASSERT_EQ(kitayuta_strcmp("e", "a"), 4);
}

TEST(KitayutaStrcmp, s1_5) {
  ASSERT_EQ(kitayuta_strcmp("", "a"), -'a');
}

TEST(KitayutaStrcmp, s1_6) {
  ASSERT_EQ(kitayuta_strcmp("a", ""), 'a');
}

TEST(KitayutaStrcmp, s5_0) {
  ASSERT_EQ(kitayuta_strcmp("abc", "abcde"), -'d');
}

TEST(KitayutaStrcmp, s5_1) {
  ASSERT_EQ(kitayuta_strcmp("abcde", "abc"), 'd');
}

TEST(KitayutaStrcmp, s5_2) {
  ASSERT_EQ(kitayuta_strcmp("abcde", "abcde"), 0);
}

TEST(KitayutaStrcmp, s5_3) {
  ASSERT_EQ(kitayuta_strcmp("abcde", "abcfe"), -2);
}

TEST(KitayutaStrcmp, s5_4) {
  ASSERT_EQ(kitayuta_strcmp("abcfe", "abcde"), 2);
}

TEST(KitayutaStrcmp, s5_5) {
  ASSERT_EQ(kitayuta_strcmp("abcde", "abcdg"), -2);
}

TEST(KitayutaStrcmp, s5_6) {
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
TEST(KitayutaEval, e0) {
  string out_str = kitayuta_eval(string(""));
  ASSERT_EQ(kitayuta_strcmp(out_str, "."), 0);
}

//-------------------------------------------------- Length 1

TEST(KitayutaEval, e1) {
  string out_str = kitayuta_eval(string("a"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "aa"), 0);
}

//-------------------------------------------------- Length 2

TEST(KitayutaEval, e2_0) {
  string out_str = kitayuta_eval(string("aa"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "a.a"), 0);
}

// XXX also "bab"
TEST(KitayutaEval, e2_1) {
  string out_str = kitayuta_eval(string("ab"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "aba"), 0);
}

//-------------------------------------------------- Length 3
TEST(KitayutaEval, e3_0) {
  string out_str = kitayuta_eval(string("aaa"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "aaaa"), 0);
}

TEST(KitayutaEval, e3_1) {
  string out_str = kitayuta_eval(string("aba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abba"), 0);
}

TEST(KitayutaEval, e3_2) {
  string out_str = kitayuta_eval(string("aab"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "baab"), 0);
}

TEST(KitayutaEval, e3_3) {
  string out_str = kitayuta_eval(string("baa"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "baab"), 0);
}

//-------------------------------------------------- Length 4
TEST(KitayutaEval, e4_0) {
  string out_str = kitayuta_eval(string("aaaa"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "aa.aa"), 0);
}

TEST(KitayutaEval, e4_1) {
  string out_str = kitayuta_eval(string("aaab"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "baaab"), 0);
}

// XXX also "ababa"
TEST(KitayutaEval, e4_2) {
  string out_str = kitayuta_eval(string("aaba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "aabaa"), 0);
}

// XXX also "aabaa"
TEST(KitayutaEval, e4_3) {
  string out_str = kitayuta_eval(string("abaa"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "ababa"), 0);
}

TEST(KitayutaEval, e4_4) {
  string out_str = kitayuta_eval(string("baaa"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "baaab"), 0);
}

TEST(KitayutaEval, e4_5) {
  string out_str = kitayuta_eval(string("aabb"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}

TEST(KitayutaEval, e4_6) {
  string out_str = kitayuta_eval(string("abba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "ab.ba"), 0);
}

// XXX also "babab"
TEST(KitayutaEval, e4_7) {
  string out_str = kitayuta_eval(string("abab"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "ababa"), 0);
}

// XXX also "acbca"
TEST(KitayutaEval, e4_8) {
  string out_str = kitayuta_eval(string("abca"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abcba"), 0);
}

TEST(KitayutaEval, e4_9) {
  string out_str = kitayuta_eval(string("abac"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "cabac"), 0);
}

TEST(KitayutaEval, e4_10) {
  string out_str = kitayuta_eval(string("caba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "cabac"), 0);
}

TEST(KitayutaEval, e4_11) {
  string out_str = kitayuta_eval(string("aabc"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}

TEST(KitayutaEval, e4_12) {
  string out_str = kitayuta_eval(string("baac"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}

TEST(KitayutaEval, e4_13) {
  string out_str = kitayuta_eval(string("bcaa"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}


//-------------------------------------------------- Longer tests
TEST(KitayutaEval, ex_0) {
  string out_str = kitayuta_eval(string("abccda"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}

TEST(KitayutaEval, ex_1) {
  string out_str = kitayuta_eval(string("abcba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abccba"), 0);
}

// XXX also "abdcdba"
TEST(KitayutaEval, ex_2) {
  string out_str = kitayuta_eval(string("abcdba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abcdcba"), 0);
}

TEST(KitayutaEval, ex_3) {
  string out_str = kitayuta_eval(string("abcxdba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}

TEST(KitayutaEval, ex_4) {
  string out_str = kitayuta_eval(string("abccba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abc.cba"), 0);
}

TEST(KitayutaEval, ex_5) {
  string out_str = kitayuta_eval(string("abcdcba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abcddcba"), 0);
}

TEST(KitayutaEval, ex_6) {
  string out_str = kitayuta_eval(string("abcxcda"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}

TEST(KitayutaEval, ex_7) {
  string out_str = kitayuta_eval(string("abccdba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abdccdba"), 0);
}

TEST(KitayutaEval, ex_8) {
  string out_str = kitayuta_eval(string("abcxcdba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abdcxcdba"), 0);
}

TEST(KitayutaEval, ex_9) {
  string out_str = kitayuta_eval(string("abccxdba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}

TEST(KitayutaEval, ex_10) {
  string out_str = kitayuta_eval(string("abcdeedcba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abcde.edcba"), 0);
}

// XXX also "abcdfefdcba"
TEST(KitayutaEval, ex_11) {
  string out_str = kitayuta_eval(string("abcdefdcba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abcdefedcba"), 0);
}

TEST(KitayutaEval, ex_12) {
  string out_str = kitayuta_eval(string("abcdefgcba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}

TEST(KitayutaEval, ex_13) {
  string out_str = kitayuta_eval(string("abceffedcba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abcdeffedcba"), 0);
}

TEST(KitayutaEval, ex_14) {
  string out_str = kitayuta_eval(string("abcefgfedcba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abcdefgfedcba"), 0);
}

TEST(KitayutaEval, ex_15) {
  string out_str = kitayuta_eval(string("abcdeffecba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abcdeffedcba"), 0);
}

TEST(KitayutaEval, ex_16) {
  string out_str = kitayuta_eval(string("abcdefgfecba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abcdefgfedcba"), 0);
}

//-------------------------------------------------- Real words
TEST(KitayutaEval, ew_0) {
  string out_str = kitayuta_eval(string("noon"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "no.on"), 0);
}

TEST(KitayutaEval, ew_1) {
  string out_str = kitayuta_eval(string("testset"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "testtset"), 0);
}

TEST(KitayutaEval, ew_2) {
  string out_str = kitayuta_eval(string("test"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "teset"), 0);
}

TEST(KitayutaEval, ew_3) {
  string out_str = kitayuta_eval(string("kitayuta"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}

TEST(KitayutaEval, ew_4) {
  string out_str = kitayuta_eval(string("revive"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "reviver"), 0);
}

TEST(KitayutaEval, ew_5) {
  string out_str = kitayuta_eval(string("ee"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "e.e"), 0);
}
