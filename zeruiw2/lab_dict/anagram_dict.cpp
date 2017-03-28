/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
  ifstream words(filename);
  string word;
  if(words.is_open()){
    while(getline(words,word)){
      string test = word;
      std::sort (test.begin(),test.end());
     auto lookup = dict.find(test);
     if(lookup!=dict.end()){
       for(size_t i=0; i<dict.at(test).size();i++){
         if(dict[test][i]==word){
           return ;
         }
       }
       dict[test].push_back(word);
     }
     else{
    dict[test].push_back(word);
     }
    }
  }

  /* Your code goes here! */
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
   for(auto & word: words){
     string test = word;
     std::sort(test.begin(),test.end());
     auto lookup = dict.find(test);
     if(lookup!=dict.end()){
       for(size_t i=0; i<dict.at(test).size();i++){
         if(dict[test][i]==word){
           return ;
         }
       }
       dict[test].push_back(word);
     }
     else{
    dict[test].push_back(word);
     }
   }
    /* Your code goes here! */
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    string ret = word;
    std::sort(ret.begin(), ret.end());
    for(auto & key_val : dict){
      if(key_val.first==ret){
        return key_val.second;
      }
    }
    /* Your code goes here! */
    return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
     vector<vector<string>> ret;
     for(auto& key_val : dict){
       if(key_val.second.size()>=2)
       ret.push_back(key_val.second);
     }
     return ret;
}
