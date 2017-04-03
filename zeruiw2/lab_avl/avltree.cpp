/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <cmath>
template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    if(t==NULL){return;}
    Node * y  = t->right;
    t->right = y->left;
    y->left =   t;
    update(t);
    t=y;
    update(t);

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // Implemented for you:

    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
  if(t==NULL){return;}
    Node * y= t->left;
    t->left = y->right;
    y->right=t;
    update(t);
    t=y;
    update(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here

    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
  if(subtree==NULL){}

     else if((heightOrNeg1(subtree->left)-heightOrNeg1(subtree->right))==2){
    if(subtree->right==NULL){

    }
      Node * tempL = subtree->left;
      if((heightOrNeg1(tempL->left)-heightOrNeg1(tempL->right))==1){
        rotateRight(subtree);
      }
      else {
        rotateLeftRight(subtree);
      }

     }
     else if((heightOrNeg1(subtree->right)-heightOrNeg1(subtree->left))==2){
     if(subtree->left==NULL){
     }
      Node* tempR = subtree->right;
      if((heightOrNeg1(tempR->left)-heightOrNeg1(tempR->right))==-1){
        rotateLeft(subtree);
      }
      else {
        rotateRightLeft(subtree);
      }
     }



    // your code here
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
  if(subtree==NULL){
    subtree = new Node(key, value);
    subtree->height=0;
  }
  else if(subtree->key==key){}
  else if(subtree->key>key){
    insert(subtree->left, key,value);
  }
  else {
    insert(subtree->right,key,value);

  }
  rebalance (subtree);
  update(subtree);


        // your code here
}
template <class K, class V>
void AVLTree<K,V>::update(Node*& subtree){
if(subtree==NULL){return;}
 else if(subtree->left==NULL&&subtree->right==NULL){
  subtree->height=0;
}
else if(subtree->left==NULL&&subtree->right!=NULL){

  subtree->height = 1+subtree->right->height;
}
else if(subtree->right==NULL&&subtree->left!=NULL){

  subtree->height = 1+subtree->left->height;
}
else {

  subtree->height = 1+ max(subtree->left->height, subtree->right->height);
}




}
template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);    // your code here
    } else if (key > subtree->key) {
        remove(subtree->right, key);
        // your code here
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
          delete subtree;
          subtree = NULL;
            /* no-child remove */
            // your code here
        } else if (subtree->left != NULL && subtree->right != NULL) {
            Node*& replace = rightmost(subtree->left);
            swap(subtree,replace);
            remove(replace,key);

            /* two-child remove */
            // your code here
        } else {
          Node* replace = subtree;
          if(subtree->left!=NULL){
            subtree=subtree->left;
          }else{
            subtree=subtree->right;
          }
          delete replace;
          replace = NULL;
            /* one-child remove */
            // your code here
        }
          update(subtree);
        rebalance(subtree);


        // your code here
    }
}
template<class K, class V>
typename AVLTree<K,V>::Node*& AVLTree<K,V> ::rightmost(Node*& subtree){

  if(subtree->right==NULL){
    return subtree;
  }
  else {
    return rightmost(subtree->right);
  }

}
