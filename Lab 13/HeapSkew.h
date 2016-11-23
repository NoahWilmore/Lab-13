/*
	
	Name: Jenny Haggerty && Noah Wilmore
	
	date: 11/22/16
	
	goal: Make a HeapSkew


*/
#if !defined HEAPSKEW_H
#define HEAPSKEW_H

#include "BinaryTree.h"
#include "wx/wx.h"

template < class T >
class HeapSkew : public Drawable
{

   private:
      BinaryTree<T>* bt;
      int sze;
	  
	  //pre: takes two subtrees to be merged
	  //post: takes the two subtrees and recursivly puts the trees together
      BinaryTree<T>* merge(BinaryTree<T>* left, BinaryTree<T>* right);

      int (*compare_items) (T* item_1, T* item_2);

   public:
      HeapSkew(int (*comp_items) (T* item_1, T* item_2));
      ~HeapSkew();

      bool heapIsEmpty();
	  
	  //pre: takes the item to insert
	  //post: inserts the item into the heap using the merge funtion
      void heapInsert(T* item);
	  
	  //pre: none
	  //post: removes the beggest item in the tree from the heap using merge
      T* heapRemove();

      void draw(wxDC& dc, int width, int height);
      void mouseClicked(int x, int y);

};

// this is a MAXHEAP (largest items to top alphabetical order)
template < class T >
HeapSkew<T>::HeapSkew(int (*comp_items) (T* item_1, T* item_2)) : Drawable()
{ 
   bt = new BinaryTree<T>();
   sze = 0;

   compare_items = comp_items;
}

template < class T >
HeapSkew<T>::~HeapSkew() 
{ 
   delete bt;
}  

template < class T >
bool HeapSkew<T>::heapIsEmpty()
{
   return sze == 0;
}

template < class T >
BinaryTree<T>* HeapSkew<T>::merge(BinaryTree<T>* left, BinaryTree<T>* right)
{
  //DO THIS
  //checks to see if the subtress are empty. 
  //if so deletes the empty returns the other
  if(left->isEmpty()){
	  
	  delete left;
	  return right;
	  
  } 
  
  if(right->isEmpty()){
	  
	  delete right;
	  return left;
  
  }
  
  //gets the items at the top and compraires them
  T* leftRoot = left->getRootItem();
  T* rightRoot = right->getRootItem();
  
  if ((*compare_items) (leftRoot, rightRoot) < 0){
	  
	  return merge(right, left);
	  
  }

  //Makes trees to hold subtrees
  BinaryTree<T>* LL = left->detachLeftSubtree();
  BinaryTree<T>* LR = left->detachRightSubtree();
  
  left->attachRightSubtree(LL);
  delete LL;

  if(LR->isEmpty())
  {
	  delete LR;
	  left->attachLeftSubtree(right);
	  delete right;
	  return left;
  }
  else
  {
	  BinaryTree<T>* leftSubtree = merge(LR, right);
	  left->attachLeftSubtree(leftSubtree);
	  delete leftSubtree;
	  return left;
  }

}

template < class T >
void HeapSkew<T>::heapInsert(T* item)
{
   //DO THIS (calls merge, should be short)
   
	BinaryTree<T>* aTree = new BinaryTree<T>(item);
	bt = merge(bt, aTree);
	sze++;
   
}

template < class T >
T* HeapSkew<T>::heapRemove()
{
   //DO THIS (calls merge, should be short)
   
	T* rootItem = bt->getRootItem();  

	BinaryTree<T>* root = bt;
	BinaryTree<T>* left = bt->detachLeftSubtree();
	BinaryTree<T>* right = bt->detachRightSubtree();
	
	
	bt = merge(left, right);
	delete root;
	sze--;

	return rootItem;
   
}

template < class T >
void HeapSkew<T>::draw(wxDC& dc, int width, int height)
{
   bt->draw(dc, width, height);
}

template < class T >
void HeapSkew<T>::mouseClicked(int x, int y) {bt->mouseClicked(x, y);}

#endif
