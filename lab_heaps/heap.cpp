/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    return 1;/// @todo Update to return the index you are choosing to be your root.

}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the left child.
    if(currentIdx*2 <=size){
      return currentIdx*2;
    }
    else return -1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the right child.
    if(currentIdx*2+1<=size)
      return currentIdx*2+1;

    else return -1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    if(currentIdx!=1)/// @todo Update to return the index of the parent.
    return currentIdx/2;
    else return -1;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    if(2*currentIdx<=size){
      return true;
    }/// @todo Update to return whether the given node has a child
    else return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if(currentIdx*2==size){
      return currentIdx*2;
    }
    else {
      if(higherPriority(_elems[currentIdx*2], _elems[currentIdx*2+1] ))
      return currentIdx*2;
      else return currentIdx*2+1;
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    if(hasAChild(currentIdx)){
      size_t maxpri = maxPriorityChild(currentIdx);
      if(higherPriority(_elems[maxpri], _elems[currentIdx])){
        std::swap(_elems[maxpri], _elems[currentIdx]);
        heapifyDown(maxpri);
      }
    }/// @todo Implement th heapifyDown algorithm.
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
       size=0;
      _elems.push_back(T());/// @todo Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
  _elems.push_back(T());
  size = elems.size();

for(size_t i=0; i<size ; i++ ){
  _elems.push_back(elems[i]);
}
for(size_t i=parent(size); i>0 ; i--){
  heapifyDown(i);
}
  /* code */


    /// @todo Construct a heap using the buildHeap algorithm
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    /// @todo Remove, and return, the element with highest priority
    T min = _elems[1];
    _elems[1] = _elems[size];
    size--;
    heapifyDown(1);
    return min;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    /// @todo Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{

    _elems.push_back(elem);
    size++;
    heapifyUp(size);/// @todo Add elem to the heap
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
    return _elems.size()==1;
}
