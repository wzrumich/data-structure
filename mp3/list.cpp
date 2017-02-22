#include <iostream>
#include <cmath>
using namespace std;
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */





template <class T>
List<T>::~List()
{
  clear();

    /// @todo Graded in MP3.1

}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
if(head==NULL){
return;
}
ListNode* run = head;
while(run!=NULL){
ListNode* temp=run->next;
delete run;
run=NULL;
run=temp;
}
length=0;
head=NULL;
tail=NULL;


    /// @todo Graded in MP3.1

}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{
length++;
ListNode* insertF=new ListNode(ndata);
if(head==NULL){
  insertF->next=tail;
  head=insertF;
  tail=insertF;
  return;
}
else {
insertF->next=head;
head->prev=insertF;
head=insertF;
}

    /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
  length++;
ListNode* insertB= new ListNode(ndata);
if(head==NULL){
  insertB->prev=NULL;
  head=insertB;
  tail=insertB;
}
else {
tail->next=insertB;
insertB->prev=tail;
tail=insertB;
}
    /// @todo Graded in MP3.1
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
  if(startPoint==NULL||endPoint==NULL||startPoint==endPoint){
    return;
  }
  ListNode* st2=startPoint;
  ListNode* temp=NULL;
  ListNode* st=startPoint;
  ListNode* end=endPoint;
  ListNode* stprev=startPoint->prev;
  ListNode* endnext=endPoint->next;
  while(st!=endnext){
    temp=st->prev;
    st->prev=st->next;
    st->next=temp;
    st=st->prev;
  }
startPoint->next=endnext;
if(endnext!=NULL){
  endnext->prev=startPoint;
}

endPoint->prev=stprev;
if(stprev!=NULL){
  stprev->next=endPoint;
}
if(temp!=NULL){
temp=startPoint;
startPoint=endPoint;
endPoint=temp;
}


}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)
{
  if(head==NULL||tail==NULL||n<=0){
    return;
  }
ListNode* st=head;
ListNode* end=head;
    if(n>=length){
      reverse();
      return;
    }
  	for(int i=0; i<n-1 ;i++){
      if(end->next!=NULL){
        end=end->next;
      }
    }
      reverse(head,end);

  	while(end->next!=NULL){
      st=end->next;
      for(int i=0;i<n;i++){
        if(end->next!=NULL){
          end=end->next;
        }
      }
      reverse(st,end);
    }



  }




     /// @todo Graded in MP3.1


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
if(head==NULL||head==tail||tail==NULL){
  return;
}
ListNode * curr=head;
ListNode * currNex=head->next;

while(curr->next!=tail){
  curr->next=currNex->next;
  currNex->next->prev=curr;
  tail->next=currNex;
  currNex->prev=tail;
  tail=currNex;
  tail->next=NULL;
  curr=curr->next;
  currNex=curr->next;

}
    /// @todo Graded in MP3.1
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
        tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
  for(int i=0; i<splitPoint;i++){
    if(start!=NULL){
      start=start->next;
    }
  }
  if(start->prev!=NULL){
start->prev->next=NULL;
start->prev=NULL;}
  ListNode* result = start;
  ListNode* temp=result;
 while(start->next!=NULL){
   result->next=start->next;
   result->next->prev=result;
   start=start->next;
   result=result->next;
 }
result=temp;
return result;
    /// @todo Graded in MP3.2
   // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
  ListNode* result= NULL;
  ListNode* temp=NULL;

  if(first==NULL){
    return second;
  }
  if(second==NULL){
    return first;
  }
  else{
  if(second->data<first->data){
    result=second;
    second=second->next;
  }
  else{
    result=first;
    first=first->next;
  }
  }
    temp=result;
  while(first!=NULL&&second!=NULL){
    if(second->data<first->data){
      result->next=second;
      second->prev=result;
      result=result->next;
      second=second->next;
    }
    else{
      result->next=first;
      first->prev=result;
      result=result->next;
      first=first->next;
    }
  }
  if(first==NULL){
    result->next=second;
    second->prev=result;
  }
  if(second==NULL){
    result->next=first;
    first->prev=result;
  }


     result=temp;
    /// @todo Graded in MP3.2
    return result; // change me!
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
if(start==NULL){
  return NULL;
}
if(chainLength<=1){
  return start;
}
int mid= chainLength/2;
int fmid=chainLength-mid;
ListNode* lag = split(start, mid);
start=mergesort(start,mid);
lag=mergesort(lag,fmid);
return merge(start,lag);




      /// @todo Graded in MP3.2
   // change me!
}
