#include "vector.h" // include definition of class vector 

// empty container constructor (default constructor)
// Constructs an empty container, with no elements.
vector::vector()
{
   myFirst = myLast = myEnd = nullptr;
}

// fill constructor
// Constructs a container with "count" elements.
// Each element is initialized as 0.
vector::vector( const size_type count )
{
    
    myFirst = new int[count]();
    myLast = myEnd = myFirst+ count;

}

// copy constructor
// Constructs a container with a copy of each of the elements in "right",
// in the same order.
vector::vector( const vector &right )
{
    size_type rightsize = right.myLast - right.myFirst;
    myFirst = new int[rightsize]();
    myLast = myEnd = myFirst+rightsize;
    for (int i = 0; i < rightsize; i++) {
        myFirst[i] = right.myFirst[i];
    }
}

// Vector destructor
// Destroys the container object.
// Deallocates all the storage capacity allocated by the vector.
vector::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
}

// The vector is extended by inserting a new element before the element
// at the specified position, effectively increasing the container size by one.
// This causes an automatic reallocation of the allocated storage space
// if and only if the new vector size surpasses the current vector capacity.
// Relocates all the elements that were after "where" to their new positions.
vector::iterator vector::insert( const_iterator where, const value_type &val )
{
    
   if( where >= myFirst && where <= myLast )
   {
      size_type originalSize = size();
      size_type originalCapacity = capacity();
 
      if( originalSize == originalCapacity )
      {
          pointer temptr;
          pointer newwhere;
          size_type newCapacity;
          if( originalCapacity <= 1 )
             newCapacity = originalCapacity + 1;
          else
             newCapacity = originalCapacity * 3 / 2;
       
          temptr = myFirst;
          myFirst = new int[newCapacity]();
          for (int i = 0; i < where - temptr; i++) {
              myFirst[i] = temptr[i];
          }
          myFirst[where - temptr] = val;
          for (int i = where - temptr +1; i <= myLast-temptr; i++) {
              myFirst[i] = temptr[i-1];
          }
          myLast = myFirst + originalSize + 1;
          myEnd = myFirst + newCapacity;
          newwhere = (where-temptr)+myFirst;
          delete[] temptr;
          return newwhere;
      }
      else
      {
          /*
          temptr = myFirst;
          myFirst = new int[originalCapacity]();
          
          for (int i = 0; i < where - temptr; i++) {
              myFirst[i] = temptr[i];
          }
          myFirst[where - temptr] = val;
          if (where - temptr != originalSize) {
              for (int i = where - temptr + 1; i <= myLast - temptr; i++) {
                  myFirst[i] = temptr[i - 1];
              }
          }
          myLast = myFirst + originalSize + 1;
          myEnd = myFirst+originalCapacity;
          delete[] temptr;*/
          for (int i = myLast - myFirst; i > where - myFirst; i--)
              myFirst[i] = myFirst[i - 1];
          myFirst[where - myFirst] = val;
          myLast++;
          return iterator(where);
      }      
      
   }
   else
      return nullptr;
   
}

// Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
// Copies all the elements from "right" into the container
// (with "right" preserving its contents).
vector& vector::assign( const vector &right )
{
   if( this != &right ) // avoid self-assignment
   {
      size_type rightSize = right.myLast - right.myFirst;
      if( rightSize > capacity() )
      {
         
         size_type newCapacity = capacity() * 3 / 2;
         if (newCapacity < rightSize) {
             newCapacity = rightSize;
             delete[]myFirst;
             myFirst = new int[rightSize];
             myLast = myEnd = myFirst + rightSize;
             for (int i = 0; i < rightSize; i++) {
                 myFirst[i] = right.myFirst[i];
             }
         }
         else {
             delete[] myFirst;
             myFirst = new int[rightSize];
             myLast = myFirst + rightSize;
             myEnd = myFirst + newCapacity;
             for (int i = 0; i < rightSize; i++) {
                 myFirst[i] = right.myFirst[i];
             }
         }
         

      }
      else {
          myLast = myFirst + rightSize;
          for (int i = 0; i < rightSize; i++) {
              myFirst[i] = right.myFirst[i];
          }
      }
   }

   return *this; // enables x = y = z, for example
}

// Removes from the vector a single element (where).
// This effectively reduces the container size by one, which is destroyed.
// Relocates all the elements after the element erased to their new positions.
vector::iterator vector::erase( const_iterator where )
{
   if( where >= myFirst && where < myLast )
   {
       myLast--;
       for (int i = where - begin(); i < myLast - myFirst; i++) {
           myFirst[i] = myFirst[i + 1];
       }
   }
   else
      return nullptr;
}

// Removes all elements from the vector (which are destroyed),
// leaving the container with a size of 0.
// A reallocation is not guaranteed to happen,
// and the vector capacity is not guaranteed to change due to calling this function.
void vector::clear()
{
   myLast = myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::iterator vector::begin()
{
   return myFirst;
}

// Returns an iterator referring to the past-the-end element in the vector container.
// The past-the-end element is the theoretical element
// that would follow the last element in the vector.
// It does not point to any element, and thus shall not be dereferenced.
// If the container is empty, this function returns the same as vector::begin.
vector::iterator vector::end()
{
   return myLast;
}

// Returns whether the vector is empty (i.e. whether its size is 0).
bool vector::empty()
{
   return myFirst == myLast;
}

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
vector::size_type vector::size()
{
   return static_cast< size_type >( myLast - myFirst );
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
// This capacity is not necessarily equal to the vector size.
// It can be equal or greater, with the extra space allowing to accommodate
// for growth without the need to reallocate on each insertion.
vector::size_type vector::capacity()
{
   return static_cast< size_type >( myEnd - myFirst );
}