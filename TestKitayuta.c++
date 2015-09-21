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
  string out_str = kitayuta_eval(string(""));
  ASSERT_EQ(kitayuta_strcmp(out_str, "."), 0);
}

//-------------------------------------------------- Length 1

TEST(KitayutaEval, t1) {
  string out_str = kitayuta_eval(string("a"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "aa"), 0);
}

//-------------------------------------------------- Length 2

TEST(KitayutaEval, t2_0) {
  string out_str = kitayuta_eval(string("aa"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "a.a"), 0);
}

// XXX also "bab"
TEST(KitayutaEval, t2_1) {
  string out_str = kitayuta_eval(string("ab"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "aba"), 0);
}

//-------------------------------------------------- Length 3
TEST(KitayutaEval, t3_0) {
  string out_str = kitayuta_eval(string("aaa"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "aaaa"), 0);
}

TEST(KitayutaEval, t3_1) {
  string out_str = kitayuta_eval(string("aba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abba"), 0);
}

TEST(KitayutaEval, t3_2) {
  string out_str = kitayuta_eval(string("aab"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "baab"), 0);
}

TEST(KitayutaEval, t3_3) {
  string out_str = kitayuta_eval(string("baa"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "baab"), 0);
}

//-------------------------------------------------- Length 4
TEST(KitayutaEval, t4_0) {
  string out_str = kitayuta_eval(string("aaaa"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "aa.aa"), 0);
}

TEST(KitayutaEval, t4_1) {
  string out_str = kitayuta_eval(string("aaab"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "baaab"), 0);
}

// XXX also "ababa"
TEST(KitayutaEval, t4_2) {
  string out_str = kitayuta_eval(string("aaba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "aabaa"), 0);
}

// XXX also "aabaa"
TEST(KitayutaEval, t4_3) {
  string out_str = kitayuta_eval(string("abaa"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "ababa"), 0);
}

TEST(KitayutaEval, t4_4) {
  string out_str = kitayuta_eval(string("baaa"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "baaab"), 0);
}

TEST(KitayutaEval, t4_5) {
  string out_str = kitayuta_eval(string("aabb"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}

TEST(KitayutaEval, t4_6) {
  string out_str = kitayuta_eval(string("abba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "ab.ba"), 0);
}

// XXX also "babab"
TEST(KitayutaEval, t4_7) {
  string out_str = kitayuta_eval(string("abab"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "ababa"), 0);
}

// XXX also "acbca"
TEST(KitayutaEval, t4_8) {
  string out_str = kitayuta_eval(string("abca"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abcba"), 0);
}

TEST(KitayutaEval, t4_9) {
  string out_str = kitayuta_eval(string("abac"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "cabac"), 0);
}

TEST(KitayutaEval, t4_10) {
  string out_str = kitayuta_eval(string("caba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "cabac"), 0);
}

TEST(KitayutaEval, t4_11) {
  string out_str = kitayuta_eval(string("aabc"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}

TEST(KitayutaEval, t4_12) {
  string out_str = kitayuta_eval(string("baac"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}

TEST(KitayutaEval, t4_13) {
  string out_str = kitayuta_eval(string("bcaa"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}


//-------------------------------------------------- Longer tests
TEST(KitayutaEval, tx_0) {
  string out_str = kitayuta_eval(string("abccda"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}

TEST(KitayutaEval, tx_1) {
  string out_str = kitayuta_eval(string("abcba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abccba"), 0);
}

// XXX also "abdcdba"
TEST(KitayutaEval, tx_2) {
  string out_str = kitayuta_eval(string("abcdba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abcdcba"), 0);
}

TEST(KitayutaEval, tx_3) {
  string out_str = kitayuta_eval(string("abcxdba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}

TEST(KitayutaEval, tx_4) {
  string out_str = kitayuta_eval(string("abccba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abc.cba"), 0);
}

TEST(KitayutaEval, tx_5) {
  string out_str = kitayuta_eval(string("abcdcba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abcddcba"), 0);
}

TEST(KitayutaEval, tx_6) {
  string out_str = kitayuta_eval(string("abcxcda"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}

TEST(KitayutaEval, tx_7) {
  string out_str = kitayuta_eval(string("abccdba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abdccdba"), 0);
}

TEST(KitayutaEval, tx_8) {
  string out_str = kitayuta_eval(string("abcxcdba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abdcxcdba"), 0);
}

TEST(KitayutaEval, tx_9) {
  string out_str = kitayuta_eval(string("abccxdba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}

TEST(KitayutaEval, tx_10) {
  string out_str = kitayuta_eval(string("abcdeedcba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abcde.edcba"), 0);
}

// XXX also "abcdfefdcba"
TEST(KitayutaEval, tx_11) {
  string out_str = kitayuta_eval(string("abcdefdcba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abcdefedcba"), 0);
}

TEST(KitayutaEval, tx_12) {
  string out_str = kitayuta_eval(string("abcdefgcba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}

TEST(KitayutaEval, tx_13) {
  string out_str = kitayuta_eval(string("abceffedcba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abcdeffedcba"), 0);
}

TEST(KitayutaEval, tx_14) {
  string out_str = kitayuta_eval(string("abcefgfedcba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abcdefgfedcba"), 0);
}

TEST(KitayutaEval, tx_15) {
  string out_str = kitayuta_eval(string("abcdeffecba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abcdeffedcba"), 0);
}

TEST(KitayutaEval, tx_16) {
  string out_str = kitayuta_eval(string("abcdefgfecba"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "abcdefgfedcba"), 0);
}

//-------------------------------------------------- Real words
TEST(KitayutaEval, tw_0) {
  string out_str = kitayuta_eval(string("noon"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "no.on"), 0);
}

TEST(KitayutaEval, tw_1) {
  string out_str = kitayuta_eval(string("testset"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "testtset"), 0);
}

TEST(KitayutaEval, tw_2) {
  string out_str = kitayuta_eval(string("test"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "teset"), 0);
}

TEST(KitayutaEval, tw_3) {
  string out_str = kitayuta_eval(string("kitayuta"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "NA"), 0);
}

TEST(KitayutaEval, tw_4) {
  string out_str = kitayuta_eval(string("revive"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "reviver"), 0);
}

TEST(KitayutaEval, tw_5) {
  string out_str = kitayuta_eval(string("ee"));
  ASSERT_EQ(kitayuta_strcmp(out_str, "e.e"), 0);
}
