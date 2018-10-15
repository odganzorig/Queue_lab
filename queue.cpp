// queue.cpp for CS 223 Lab 5
//
// <student name>
// <current date>
//
// CLASS IMPLEMENTED: queue (see queue.h for documentation)
//
// INVARIANTS for the queue class:
//
//   1. The current number of items in the queue is maintained in the instance
//      variable `count`.
//
//   2. The instance variable `data` is an array in dynamic (heap) memory of
//      length `capacity`, used to store the items in the queue. The items are
//      stored from data[first] through data[last].
//
//   3. The data array is indexed in a "circular" fashion: if the queue is not
//      full and if the most recently added item is at index capacity-1 (the
//      largest valid index in `data`), then the next added item will be stored
//      at index 0.  That is, `next_index(capacity-1)` is 0.
//
//   4. For an empty queue, `last` is any valid index, and `first` is
//      equal to `next_index(last)`. Note that a "full" queue shares the same
//      property (first == next_index(last)), so we CANNOT use this property
//      to determine if the queue is empty.
//
//   5. Before trying to add an item, we always call `ensure_capacity`, which
//      copies the data over to a new (larger) array if there is currently no
//      available capacity for an additional item.
//
// INSTANCE VARIABLES:
//      queue::size_type capacity
//      queue::value_type data[capacity]
//      queue::size_type first      // Index of item at front of the queue
//      queue::size_type last       // Index of item at rear of the queue
//      queue::size_type count      // Current number of items in the queue

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cassert>
#include "queue.h"

using namespace std;

namespace main_savitch_8B
{

    // CONSTRUCTOR
    // Basic constructor
    // Precondition:  cap >= 2
    // Postcondition: queue has been initialized as an empty queue
    //    with capacity equal to `cap`.
    // Note:  If cap < 2, the queue capacity defaults to 8.
    queue::queue(size_type cap)
    {
        capacity = cap;
        data = new value_type[capacity];
        count = 0;
        last = 0;
        first = next_index(last);
    }


    // Copy constructor
    // Postcondition: queue is initialized as an independent copy of `other`;
    //    subsequent changes to either of the queues will NOT affect the other.
    queue::queue(const queue& other)
    {
        this -> capacity = other.capacity;                    
        this -> count = 0;
        this -> last = 0;
        this -> first = next_index(last);
        data = new value_type[capacity];
        for (size_type i = 0; i < other.count; i++)
        {
            this -> push(other.data[(i + other.first)% capacity]);
        }
        
    }


    // DESTRUCTOR
    queue::~queue()
    {
        delete [] data; 

    }


    // ACCESSOR MEMBER FUNCTIONS

    // size
    // Postcondition: Return value is the current number of items in the queue.
    queue::size_type queue::size() const
    {
        return count;

    }


    // is_empty()
    // Postcondition: Returns true if this is an empty queue; otherwise 
    //    returns false.
    bool queue::is_empty() const
    {
        if (count == 0)
        {
            return true;
        }
        return false;
        
    }


    // front
    // Precondition:  size > 0
    // Postcondition: Return value is the front item of the queue.
    queue::value_type queue::front() const
    {
        assert(size() > 0);
        return data[first];
    }


    // PRIVATE FUNCTIONS

    // next_index
    // private function for helping to move a circular array index forward
    // Precondition: 0 <= i < capacity
    // Postcondition: Returns (i + 1) modulo capacity.
    // Note: complete code is provided
    queue::size_type queue::next_index(size_type i) const
    {
        return (i + 1) % capacity;
    }

    // ensure_capacity
    // private function for increasing the capacity of the queue as needed
    // Postcondition:
    //    - If capacity == count (queue is full) when this function is called,
    //      then after it returns, capacity == count * 2
    //    - The items in the queue, and their ordering, is unchanged.
    // NOTE: If capacity > count when this function is called, then it has no
    //    effect.
    void queue::ensure_capacity()
    {
        if (count < capacity){return;}
        else 
        {
            value_type* temp = data;
            data = new value_type[capacity*2];
            for (size_type i = 0; i < count; i++)
            {
                data[i] = temp[first];
                first = next_index(first);
            }
            capacity *= 2;
            first = 0;
            last = count-1;
            delete[] temp;
        }
    }


    // MODIFICATION MEMBER FUNCTIONS (PUBLIC)

    // push
    // Postcondition: A new item, `entry`, has been inserted at the rear
    //    of the queue.
    // Postcondition: size has increased by 1.
    void queue::push(const value_type& entry)
    {
        ensure_capacity();
        last = next_index(last);
        data[last] = entry;
        ++count;
    }


    // pop
    // Precondition:  size > 0
    // Postcondition: The front item of the queue has been removed.
    // Postcondition: size has decreased by 1.
    void queue::pop()
    {
        assert(size() > 0);
        first = next_index(first);
        --count;
    }


    // assignment operator
    // Postcondition: This queue becomes an identical -- but indepedent --
    //    copy of `other` queue.
    // Postcondition: Returns this queue to allow for "chained assignment".
    queue& queue::operator=(const queue& other)
    {
        if (this == &other)
        {
            return *this;
        } 
        delete [] data; 
        data = NULL;   
        this -> capacity = other.capacity;                    
        this -> count = 0;
        this -> last = 0;
        this -> first = next_index(last);
        data = new value_type[capacity];
        for (size_type i = 0; i < other.count; i++)
        {
            this -> push(other.data[(i + other.first) % capacity]);
        }
        return *this;
    }
    


    // NON-MEMBER FUNCTIONS (FRIENDS)

    // equivalence operator, checks for logical equivalence of q1 and q2
    // Postcondition: Returns true if
    //       a) q1 and q2 are equal in length, and
    //       b) q1 and q2 have equivalent values and the same ordering;
    //    otherwise, returns false.
    //  Example 1. The queues <a, b, c> and <a, b, c> are equivalent.
    //  Example 2. The queues <a, b, c> and <c, a, b> are not equivalent.
    //  Example 3. The queues <a, b> and <a, b, c> are not equivalent
    bool operator==(const queue& q1, const queue& q2)
    {
        if (q1.size() == q2.size())
        {
        queue::size_type i = q1.first;
        queue::size_type j = q2.first;
            for (queue::size_type k = 0; k < q1.size(); k++)
            {
                if(q1.data[i] != q2.data[j])
                {
                    return false;
                }
            i = (i + 1) % q1.capacity;
            j = (j + 1) % q2.capacity;
            }
            return true;
        }
        return false;
    }


    // inequivalence operator
    // Postcondition: Returns false if q1 == q2; otherwise, returns true.
    bool operator!=(const queue& q1, const queue& q2)
    {
        return (!(q1 == q2));

    }


    // output stream operator
    // Printed queue should have this general format:
    //    queue of size <num>:
    //    first_item
    //       .
    //       .
    //       .
    //    last_item
    //
    // For example, if the queue contains 3 strings: "German shepherd",
    //    "French bulldog", and "Boston terrier", pushed into the queue in
    //    that order, then the printed queue will look as follows:
    //       queue of size 3:
    //       German shepherd
    //       French bulldog
    //       Boston terrier
    //
    // Postcondition: Returns the ostream to allow for chaining.
    // Note: complete code is provided
    std::ostream& operator<<(std::ostream& out, const queue& q)
    {
        out << "queue of size " << q.size() << ":\n";

        for (queue::size_type i = 0; i < q.size(); i++)
        {
            out << q.data[(q.first + i) % q.capacity] << "\n";
        }

        return out;
    }

}  // end namespace main_savitch_8B
