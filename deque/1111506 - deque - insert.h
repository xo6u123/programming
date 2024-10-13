#ifndef DEQUE_H
#define DEQUE_H

// CLASS TEMPLATE DequeConstIterator
template< typename MyDeque >
class DequeConstIterator // iterator for nonmutable deque
{
private:
   using size_type = typename MyDeque::size_type;

public:
   using value_type = typename MyDeque::value_type;
   using difference_type = typename MyDeque::difference_type;
   using pointer = typename MyDeque::const_pointer;
   using reference = const value_type &;

   // construct with null pointer
   DequeConstIterator()
      : myOff( 0 ),
        myCont( nullptr )
   {
   }

   // construct with offset off in *pDeque
   DequeConstIterator( size_type off, const MyDeque *pDeque )
      : myOff( off ),
        myCont( pDeque )
   {
   }

   DequeConstIterator( const DequeConstIterator &right ) // copy constructor
      : myOff( right.myOff ),
        myCont( right.myCont )
   {
   }

   ~DequeConstIterator() // destructor
   {
   }

   // const return avoids: ( a1 = a2 ) = a3
   const DequeConstIterator& operator=( const DequeConstIterator &right )
   {
      if( &right != this ) // avoid self-assignment
      {
         myCont = right.myCont;
         myOff = right.myOff;
      }
      return *this; // enables x = y = z, for example
   }

   reference operator*() const
   {
      // elements per block (a power of 2)
      size_type dequeSize = sizeof( value_type ) <= 1 ? 16 :
                            sizeof( value_type ) <= 2 ?  8 :
                            sizeof( value_type ) <= 4 ?  4 :
                            sizeof( value_type ) <= 8 ?  2 : 1;

//      size_type block = myOff % ( dequeSize * myCont->mapSize ) / dequeSize;
      size_type block = myCont->getBlock( myOff );
      size_type off = myOff % dequeSize;
      return myCont->map[ block ][ off ];
   }

   pointer operator->() const
   {
      // elements per block (a power of 2)
      size_type dequeSize = sizeof( value_type ) <= 1 ? 16 :
                            sizeof( value_type ) <= 2 ?  8 :
                            sizeof( value_type ) <= 4 ?  4 :
                            sizeof( value_type ) <= 8 ?  2 : 1;

      size_type block = myCont->getBlock( myOff );
      size_type off = myOff % dequeSize;
      return &myCont->map[ block ][ off ];
   }
/*
   pointer operator->() const
   {
      return &( operator*() );
   }
*/
   DequeConstIterator& operator++() // preincrement
   {
      ++myOff;
      return *this;
   }

   DequeConstIterator operator++( int ) // postincrement
   {
      DequeConstIterator tmp = *this;
      ++*this;
      return tmp;
   }

   DequeConstIterator& operator--() // predecrement
   {
      --myOff;
      return *this;
   }

   DequeConstIterator operator--( int ) // postdecrement
   {
      DequeConstIterator tmp = *this;
      --*this;
      return tmp;
   }

   // increment by integer
   DequeConstIterator& operator+=( const difference_type off )
   {
      myOff += off;
      return *this;
   }

   // return this + integer
   DequeConstIterator operator+( const difference_type off ) const
   {
      DequeConstIterator tmp = *this;
      return tmp += off;
   }

   // decrement by integer
   DequeConstIterator& operator-=( const difference_type off )
   {
      return *this += -off;
   }

   // return this - integer
   DequeConstIterator operator-( const difference_type off ) const
   {
      DequeConstIterator tmp = *this;
      return tmp -= off;
   }

   // return difference of iterators
   difference_type operator-( const DequeConstIterator &right ) const
   {
      return ( static_cast< difference_type >( this->myOff - right.myOff ) );
   }

   reference operator[]( const difference_type off ) const // subscript
   {
      return *( *this + off );
   }

   // test for iterator equality
   bool operator==( const DequeConstIterator &right ) const
   {
      return this->myCont == right.myCont && this->myOff == right.myOff;
   }

   // test for iterator inequality
   bool operator!=( const DequeConstIterator &right ) const
   {
      return !( *this == right );
   }

   // test if this < right
   bool operator<( const DequeConstIterator &right ) const
   {
      return this->myOff < right.myOff;
   }

   // test if this > right
   bool operator>( const DequeConstIterator &right ) const
   {
      return right < *this;
   }

   // test if this <= right
   bool operator<=( const DequeConstIterator &right ) const
   {
      return !( right < *this );
   }

   // test if this >= right
   bool operator>=( const DequeConstIterator &right ) const
   {
      return !( *this < right );
   }

   const MyDeque *myCont; // keep a pointer to deque
   size_type myOff;       // offset of element in deque
};


// CLASS TEMPLATE DequeIterator
template< typename MyDeque >
class DequeIterator : public DequeConstIterator< MyDeque >
{ // iterator for mutable deque
private:
   using size_type = typename MyDeque::size_type;
   using MyBase = DequeConstIterator< MyDeque >;

public:
   using value_type = typename MyDeque::value_type;
   using difference_type = typename MyDeque::difference_type;
   using pointer = typename MyDeque::pointer;
   using reference = value_type &;

   using MyBase::MyBase;

   DequeIterator() // construct with null deque pointer
   {
   }

   DequeIterator( size_type off, const MyDeque *pDeque )
      : MyBase( off, pDeque ) // construct with offset off in *pDeque
   {
   }

   reference operator*() const // return designated object
   {
      return const_cast< reference >( MyBase::operator*() );
   }

   pointer operator->() const // return pointer to class object
   {
      return const_cast< pointer >( MyBase::operator->() );
//      return &( operator*() );
   }

   DequeIterator& operator++() // preincrement
   {
      MyBase::operator++();
      return *this;
   }

   DequeIterator operator++( int ) // postincrement
   {
      DequeIterator tmp = *this;
      MyBase::operator++();
      return tmp;
   }

   DequeIterator& operator--() // predecrement
   {
      MyBase::operator--();
      return *this;
   }

   DequeIterator operator--( int ) // postdecrement
   {
      DequeIterator tmp = *this;
      MyBase::operator--();
      return tmp;
   }

   // increment by integer
   DequeIterator& operator+=( const difference_type off )
   {
      MyBase::operator+=( off );
      return *this;
   }

   // return this + integer
   DequeIterator operator+( const difference_type off ) const
   {
      DequeIterator tmp = *this;
      return tmp += off;
   }

   // decrement by integer
   DequeIterator& operator-=( const difference_type off )
   {
      MyBase::operator-=( off );
      return *this;
   }

   using MyBase::operator-; // return difference of iterators

   // return this - integer
   DequeIterator operator-( const difference_type off ) const
   {
      DequeIterator tmp = *this;
      return tmp -= off;
   }

   reference operator[]( const difference_type off ) const // subscript
   {
      return const_cast< reference >( MyBase::operator[]( off ) );
   }
};

// CLASS TEMPLATE DequeVal
template< typename Ty >
class DequeVal // base class for deque to hold data
{
public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;
   using MapPtr = Ty **;

   DequeVal() // initialize values
      : map(),
        mapSize( 0 ),
        myOff( 0 ),
        mySize( 0 )
   {
   }

   // determine block from offset
   size_type getBlock( size_type off ) const
   {
      // elements per block (a power of 2)
      size_type dequeSize = sizeof( value_type ) <= 1 ? 16 :
                            sizeof( value_type ) <= 2 ?  8 :
                            sizeof( value_type ) <= 4 ?  4 :
                            sizeof( value_type ) <= 8 ?  2 : 1;

      return off % ( dequeSize * mapSize ) / dequeSize;
//      return ( off / dequeSize ) & ( mapSize - 1 );
   }

   MapPtr map;        // pointer to array of pointers to blocks
   size_type mapSize; // size of map array, zero or 2^N
   size_type myOff;   // offset of initial element
   size_type mySize;  // current length of sequence
};


// CLASS TEMPLATE deque
template< typename Ty >
class deque // circular queue of pointers to blocks
{
private:
   using MapPtr = Ty **;
   using ScaryVal = DequeVal< Ty >;

public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = DequeIterator< ScaryVal >;
   using const_iterator = DequeConstIterator< ScaryVal >;

   // construct empty deque
   deque()
      : myData()
   {
   }

   // destroy the deque
   ~deque()
   {
      clear();
   }

   // return iterator for beginning of mutable sequence
   iterator begin()
   {
      return iterator( myData.myOff, &myData );
   }

   // return iterator for beginning of nonmutable sequence
   const_iterator begin() const
   {
      return const_iterator( myData.myOff, &myData );
   }

   // return iterator for end of mutable sequence
   iterator end()
   {
      return iterator( myData.myOff + myData.mySize, &myData );
   }

   // return iterator for end of nonmutable sequence
   const_iterator end() const
   {
      return const_iterator( myData.myOff + myData.mySize, &myData );
   }

   iterator makeIter( const_iterator where ) const
   {
      return iterator( where.myOff, &myData );
   }

   // return length of sequence
   size_type size() const
   {
      return myData.mySize;
   }

   // test if sequence is empty
   bool empty() const
   {
      return myData.mySize == 0;
   }

   // insert val at where
   iterator insert( const_iterator where, const value_type &val )
   {
      size_type dequeSize = compDequeSize(); // elements per block (a power of 2)
      size_type off = static_cast< size_type >( where - begin() );
      if( myData.mySize == 0 )
      {
         if( myData.mapSize == 0 )
         {
            myData.map = new value_type * [ 8 ]();
            myData.mapSize = 8;
         }
         int i = 0;
         int j = 0;
         i = off / dequeSize;
         j = off % dequeSize;
         j--;
         
         
         if (j < 0) {
             i--;
             j = dequeSize - 1;
         }
         if (i < 0) {
             i = myData.mapSize - 1;
             j = dequeSize - 1;
         }
         if (j == dequeSize) {
             j = 0;
             i++;

         }
         if (i >= myData.mapSize)
             i = 0;
         myData.map[i] = new value_type[dequeSize];
         myData.map[i][j] = val;
         if (myData.myOff == 0)
             myData.myOff = (dequeSize * myData.mapSize - 1);
      }
      else
      {
         // all elements before where move forward
         if( off <= myData.mySize / 2 )
         {
            if( myData.myOff % dequeSize == 0 &&
               myData.mapSize <= ( myData.mySize + dequeSize ) / dequeSize )
               doubleMapSize();
            int i = 0;
            int j = 0;
            int n = off;
            if (myData.myOff >= dequeSize)
                i = myData.myOff / dequeSize;

            if (myData.myOff % dequeSize != 0) {
                j = (myData.myOff % dequeSize);
            }
            int i2 = i;
            int j2 = j - 1;
            while (n > 0) {

                if (j2 < 0) {
                    i2--;
                    j2 = dequeSize - 1;
                }
                if (i2 < 0) {
                    i2 = myData.mapSize - 1;
                    j2 = dequeSize - 1;
                }
                if (j < 0) {
                    i--;
                    j = dequeSize - 1;
                }
                if (i < 0) {
                    i = myData.mapSize - 1;
                    j = dequeSize - 1;
                }
                if (j2 == dequeSize) {
                    j2 = 0;
                    i2++;

                }
                if (i2 >= myData.mapSize)
                    i2 = 0;
                if (j == dequeSize) {
                    j = 0;
                    i++;

                }
                if (i >= myData.mapSize)
                    i = 0;
                if (myData.map[i] == 0)
                    myData.map[i] = new value_type[dequeSize];
                if (myData.map[i2] == 0)
                    myData.map[i2] = new value_type[dequeSize];

                myData.map[i2][j2] = myData.map[i][j];
                j++;
                j2++;
                //cout << "1:: i:" << i << endl;//<< " tmpi:" << tmpi << " j:" << j << " tmpj:" << tmpj << " n:"<<n << " off:" << right.myData.myOff <<" rightmapsize:"<<right.myData.mapSize << endl;
                n--;
            }
            if (j2 < 0) {
                i2--;
                j2 = dequeSize - 1;
            }
            if (i2 < 0) {
                i2 = myData.mapSize - 1;
                j2 = dequeSize - 1;
            }

            if (j2 == dequeSize) {
                j2 = 0;
                i2++;

            }
            if (i2 >= myData.mapSize)
                i2 = 0;

            if (myData.map[i2] == 0)
                myData.map[i2] = new value_type[dequeSize];
            //cout << "be" << endl;
            myData.map[i2][j2] = val;
            if (myData.myOff == 0)
                myData.myOff = (dequeSize * myData.mapSize - 1);
            else
                myData.myOff--;
           
         }
         else  // all elements after (and at) where move backward
         {
             if ((myData.myOff + myData.mySize) % dequeSize == 0 &&
                 myData.mapSize <= (myData.mySize + dequeSize) / dequeSize)
                 doubleMapSize();
            int i = 0;
            int j = 0;
            int n = myData.mySize-off;


            i = (myData.myOff + myData.mySize) / dequeSize;
 
            j = (myData.myOff + myData.mySize) % dequeSize;
                           
            int i2 = i;
            int j2 = j - 1;
            while (n > 0) {

                if (j2 < 0) {
                    i2--;
                    j2 = dequeSize - 1;
                }
                if (i2 < 0) {
                    i2 = myData.mapSize - 1;
                    j2 = dequeSize - 1;
                }
                if (j < 0) {
                    i--;
                    j = dequeSize - 1;
                }
                if (i < 0) {
                    i = myData.mapSize - 1;
                    j = dequeSize - 1;
                }
                if (j2 == dequeSize) {
                    j2 = 0;
                    i2++;

                }
                while (i2 >= myData.mapSize)
                    i2 -= myData.mapSize;
                if (j == dequeSize) {
                    j = 0;
                    i++;

                }
                while (i >= myData.mapSize) {
                    i -= myData.mapSize;
                }
                if (myData.map[i] == 0)
                    myData.map[i] = new value_type[dequeSize];
                if (myData.map[i2] == 0)
                    myData.map[i2] = new value_type[dequeSize];

                myData.map[i][j] = myData.map[i2][j2];
                j--;
                j2--;
                //cout << "2:: i:" << i << endl;//" tmpi:" << tmpi << " j:" << j << " tmpj:" << tmpj << " n:" << n << " off:" << myData.myOff << " rightmapsize:" << myData.mapSize << endl;
                n--;
            }
            if (j < 0) {
                i--;
                j = dequeSize - 1;
            }
            if (i < 0) {
                i = myData.mapSize - 1;
                j = dequeSize - 1;
            }

            if (j == dequeSize) {
                j = 0;
                i++;

            }
            while (i >= myData.mapSize) {
                i -= myData.mapSize;
            }
            if (myData.map[i] == 0)
                myData.map[i] = new value_type[dequeSize];
            //myData.map[i][j] = val;
            myData.map[i][j] = val;
            
         }
      }

      ++myData.mySize;
      if (myData.myOff >= dequeSize * myData.mapSize) {
           
          myData.myOff -= dequeSize * myData.mapSize;
          
      }
      return begin() + static_cast< difference_type >( off );
   }

   // erase all
   void clear()
   {
      if( myData.mapSize > 0 )
      {
         for( size_type i = 0; i < myData.mapSize; i++ )
            if( myData.map[ i ] != nullptr )
               delete[] myData.map[ i ];
         delete[] myData.map;

         myData.mapSize = 0;
         myData.mySize = 0;
         myData.myOff = 0;
         myData.map = nullptr;
      }
   }

private:

   // determine block from offset
   size_type getBlock( size_type off ) const
   {
      return myData.getBlock( off );
//      return ( ( myData.off / compDequeSize() ) & ( myData.mapSize - 1 ) );
   }

   void doubleMapSize()
   {
      if( myData.mapSize > 0 )
      {
         size_type dequeSize = compDequeSize();
         size_type oldMapSize = myData.mapSize;
         myData.mapSize *= 2;
         value_type **newMap = new value_type * [ myData.mapSize ]();
         size_type n = myData.mySize;
         size_type tmpi = 0;
         size_type tmpj = 0;
         size_type i = 0;
         size_type j = 0;
         if (myData.myOff >= dequeSize)
             tmpi = myData.myOff / dequeSize;

         if (myData.myOff % dequeSize != 0) {
             tmpj = myData.myOff % dequeSize;
         }
         if (myData.myOff >= dequeSize)
             i = myData.myOff / dequeSize;

         if (myData.myOff % dequeSize != 0) {
             j = (myData.myOff % dequeSize);
         }

         while (n > 0) {
             if (tmpj == dequeSize) {
                 tmpj = 0;
                 tmpi++;

             }
             if (tmpi >= oldMapSize)
                 tmpi = 0;
             if (j == dequeSize) {
                 j = 0;
                 i++;

             }
             if (i >= myData.mapSize)
                 i = 0;
             if (newMap[i] == 0)
                 newMap[i] = new value_type[dequeSize];
             newMap[i][j] = myData.map[tmpi][tmpj];
             tmpj++;
             j++;
             //cout << "i:" << i << " tmpi:" << tmpi << " j:" << j << " tmpj:" << tmpj << " n:"<<n << " off:" << right.myData.myOff <<" rightmapsize:"<<right.myData.mapSize << endl;
             n--;
         }
         delete[] myData.map;

         myData.map = newMap;
      }
   }

   size_type compDequeSize()
   {
      return sizeof( value_type ) <= 1 ? 16 : sizeof( value_type ) <= 2 ? 8 :
             sizeof( value_type ) <= 4 ?  4 : sizeof( value_type ) <= 8 ? 2 : 1;
   }

   ScaryVal myData;
};

#endif