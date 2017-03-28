/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<StringTriple> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{     vector<StringTriple> result;
     ifstream words(word_list_fname);
     string test;
     if(words.is_open()){
       while(getline(words,test)){
         if(test.size()==5){
           string s1=test.substr(1);
           string s2=test.substr(0,1);
           string s3=test.substr(2,test.length()-2);
           s2.append(s3);
           if(d.homophones(s1,s2)){
             result.push_back(make_tuple(test,s1,s2));
           }
         }
       }
     }





    /* Your code goes here! */
    return result;
}
