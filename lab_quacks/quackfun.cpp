#include <unistd.h>
#include <iostream>
using namespace std;
/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{ T sum2;
  int size=s.size();
  if(size==0){
    return T();
  }
  else{
    size--;
    T temp=s.top();
    s.pop();
    sum2= temp+sum(s);
    s.push(temp);
  }
  return sum2;
    // Your code here
     // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    int i=1;
    int z=q.size();
    while(z>0){
    if(i>z){
      if(i%2==1){
        for(int k=0; k<z ; k++){
              T temp = q.front();
              q.pop();
              q.push(temp);
}
z=z-i;
i++;
}
if(i%2==0){
for(int j=0; j<z;j++){
  T temp2=q.front();
  q.pop();
  s.push(temp2);
}
for(int p=0; p<z ; p++){
  T temp3=s.top();
  s.pop();
  q.push(temp3);
}
  z=z-i;
  i++;
}
}

        if(i%2==1&&i<z){
          for(int k=0; k<i ; k++){
                T temp = q.front();
                q.pop();
                q.push(temp);
}
  z=z-i;
  i++;
}
if(i%2==0&&i<z){
  for(int j=0; j<i;j++){
    T temp2=q.front();
    q.pop();
    s.push(temp2);
}
  for(int p=0; p<i ; p++){
    T temp3=s.top();
    s.pop();
    q.push(temp3);
  }
    z=z-i;
    i++;
}

}
}




    // optional: queue<T> q2;

    // Your code here


/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
if(s.empty()||q.empty()){
  return true;
}
bool retval=true;
T temp2=s.top();
s.pop();
retval = verifySame(s,q);
T temp3=q.front();
if(temp2!=temp3){
  retval=false;
}
s.push(temp2);
q.pop();
q.push(temp3);

    return retval;
}



}
