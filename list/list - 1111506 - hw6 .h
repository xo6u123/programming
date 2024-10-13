// list standard header

#ifndef LIST
#define LIST

template< typename ValueType >
struct ListNode // list node
{
   ListNode *next;  // successor node, or first element if head
   ListNode *prev;  // predecessor node, or last element if head
   ValueType myVal; // the stored value, unused if head
};


// CLASS TEMPLATE ListVal
template< typename Ty >
class ListVal
{
public:
   using node = ListNode< Ty >;
   using nodePtr = node *;

   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   ListVal() // initialize data
      : myHead(),
        mySize( 0 )
   {
   }

   nodePtr myHead; // pointer to head node
   size_type mySize; // number of elements
};


// CLASS TEMPLATE list
template< typename Ty >
class list // bidirectional linked list
{
   using node = ListNode< Ty >;
   using nodePtr = node *;
   using ScaryVal = ListVal< Ty >;

public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = node *;
   using const_iterator = const node *;

   // empty container constructor (default constructor)
   // Constructs an empty container, with no elements.
   list()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;
   }

   // fill constructor
   // Constructs a container with "count" elements.
   // Each element is initialized as 0.
   list( size_type count ) // construct list from count * Ty()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;
      myData.mySize = count;
      nodePtr nodeptr=nullptr;
      if (count > 0) {
          nodeptr = new node;
          myData.myHead->next = nodeptr;
          nodeptr->next= nodeptr->prev = myData.myHead;
          myData.myHead->prev = nodeptr;
          nodeptr->myVal = Ty(0);
          for (int i = 0; i < count - 1; i++) {

              nodeptr->next = new node;
              nodeptr->next->prev = nodeptr;
              nodeptr->next->next = myData.myHead;
              myData.myHead->prev = nodeptr->next;
              nodeptr->next->myVal = Ty(0);
              nodeptr = nodeptr->next;

          }
      }
      

   }

   // copy constructor
   // Constructs a container with a copy of each of the elements in "right",
   // in the same order.
   list( const list &right )
      : myData()
   {

       myData.myHead = new node;
       myData.myHead->myVal = Ty();
       myData.myHead->prev = myData.myHead->next = myData.myHead;
       myData.mySize = right.myData.mySize;
       nodePtr nodeptr = nullptr;
       nodePtr rightnode = right.myData.myHead->next;

       nodeptr = new node;
       myData.myHead->next = nodeptr;
       nodeptr->next = nodeptr->prev = myData.myHead;
       myData.myHead->prev = nodeptr;
       nodeptr->myVal = rightnode->myVal;
       rightnode = rightnode->next;
       for (int i = 1; i < right.myData.mySize ; i++) {

           nodeptr->next = new node;
           nodeptr->next->prev = nodeptr;
           nodeptr->next->next = myData.myHead;
           myData.myHead->prev = nodeptr->next;
           nodeptr->next->myVal = rightnode->myVal;
           nodeptr = nodeptr->next;
           rightnode = rightnode->next;
       }

       
       
       
   }

   // List destructor
   // Destroys the container object.
   // Deallocates all the storage capacity allocated by the list container.
   ~list()
   {
      clear();
      delete myData.myHead;
   }

   // Assigns new contents to the container, replacing its current contents,
   // and modifying its size accordingly.
   // Copies all the elements from "right" into the container
   // (with "right" preserving its contents).
   list& operator=( const list &right )
   {
      if( this != &right )
      {

          nodePtr nodeptr = nullptr;
          nodePtr rightnodeptr = nullptr;
          nodeptr = myData.myHead->next;
          rightnodeptr = right.myData.myHead->next;
          if (myData.mySize == right.myData.mySize) {
              for (int i = 0; i < myData.mySize; i++) {
                  nodeptr->myVal = rightnodeptr->myVal;
                  nodeptr = nodeptr->next;
                  rightnodeptr = rightnodeptr->next;
              }
          }
          else if (myData.mySize < right.myData.mySize) {
              for (int i = 0; i < myData.mySize; i++) {
                  nodeptr->myVal = rightnodeptr->myVal;
                  nodeptr = nodeptr->next;
                  rightnodeptr = rightnodeptr->next;
              }
              nodeptr = myData.myHead->prev;
              for (int j = 0; j < right.myData.mySize - myData.mySize; j++) {
                  nodeptr->next = new node;
                  nodeptr->next->prev = nodeptr;
                  nodeptr->next->next = myData.myHead;
                  myData.myHead->prev = nodeptr->next;
                  nodeptr->next->myVal = rightnodeptr->myVal;
                  nodeptr = nodeptr->next;
                  rightnodeptr = rightnodeptr->next;
              }
          }
          else if (myData.mySize > right.myData.mySize) {
              for (int i = 0; i < right.myData.mySize; i++) {
                  nodeptr->myVal = rightnodeptr->myVal;
                  nodeptr = nodeptr->next;
                  rightnodeptr = rightnodeptr->next;
              }
              nodeptr->prev->next = myData.myHead;
              myData.myHead->prev = nodeptr->prev;
          }
          myData.mySize = right.myData.mySize;
      }

      return *this;
   }

   // Returns an iterator pointing to the first element in the list container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   iterator begin()
   {
      return iterator( myData.myHead->next );
   }

   // Returns an iterator pointing to the first element in the list container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   const_iterator begin() const
   {
      return const_iterator( myData.myHead->next );
   }

   // Returns an iterator referring to the past-the-end element in the list container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list container.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as list::begin.
   iterator end()
   {
      return iterator( myData.myHead );
   }

   // Returns an iterator referring to the past-the-end element in the list container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list container.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as list::begin.
   const_iterator end() const
   {
      return const_iterator( myData.myHead );
   }

   // Returns the number of elements in the list container.
   size_type size() const
   {
      return myData.mySize;
   }

   // Returns whether the list container is empty (i.e. whether its size is 0).
   bool empty() const
   {
      return myData.mySize == 0;
   }

   // Returns a reference to the first element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   reference front()
   {
      return myData.myHead->next->myVal;
   }

   // Returns a reference to the first element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   const_reference front() const
   {
      return myData.myHead->next->myVal;
   }

   // Returns a reference to the last element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   reference back()
   {
      return myData.myHead->prev->myVal;
   }

   // Returns a reference to the last element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   const_reference back() const
   {
      return myData.myHead->prev->myVal;
   }

   // The container is extended by inserting a new element
   // before the element at the specified position.
   // This effectively increases the list size by the amount of elements inserted.
   // Returns an iterator that points to the newly inserted element.
   iterator insert( const_iterator where, const Ty &val ) // insert val at where
   {
       nodePtr temp = myData.myHead->next;
       while (temp != where) {
           temp = temp->next;
       }
       
       nodePtr newnode = nullptr;
       newnode = new node;
       newnode->next = temp;
       newnode->prev = temp->prev;
       temp->prev->next = newnode;
       temp->prev = newnode;
       newnode->myVal = val;
       myData.mySize++;
       
       return newnode;

   }

   // Removes from the list container the element at the specified position.
   // This effectively reduces the container size one, which is destroyed.
   // Returns an iterator pointing to the element that followed the element erased.
   // This is the container end if the operation erased the last element in the sequence.
   iterator erase( const_iterator where )
   {
       nodePtr temp = myData.myHead->next;
       while (temp != where) {
           temp = temp->next;
       }
       temp->next->prev = temp->prev;
       temp->prev->next = temp->next;
       myData.mySize--;
       return temp;

   }

   // Removes all elements from the list container (which are destroyed),
   // and leaving the container with a size of 0.
   void clear() // erase all
   {
      if( myData.mySize != 0 ) // the list is not empty
      {
          nodePtr temp = myData.myHead->next;
          myData.myHead->prev = myData.myHead->next = myData.myHead;
          myData.mySize = 0;
          delete temp;
      }
   }

private:
   ScaryVal myData;
};

// determine if two lists are equal and return true, otherwise return false
template< typename Ty >
bool operator==( const list< Ty > &left, const list< Ty > &right )
{
    
    if (left.size() != right.size())
        return false;
    for (int i = 0; i < left.size(); i++) {
        if (left.front() != right.front())
            return false;
        left.begin() = left.begin()->next;
        right.begin() = right.begin()->next;
    }
    return true;
}

template< typename Ty >
bool operator!=( const list< Ty > &left, const list< Ty > &right )
{
   return !( left == right );
}

#endif // LIST