// FILE: queue.h
// Header file for Lab 5, CS 223, Winter 2018
//
// Modified version of the queue.h file provided by Main/Savitch, Chap. 8
//
// Barb Wahl and Theresa Wilson, 3-4-2018
//
// ********** DO NOT CHANGE THIS FILE **********
//
// CLASS PROVIDED: queue
//
// TYPEDEFS and MEMBER CONSTANTS for the queue class:
//   typedef ____ value_type
//     queue::value_type is the data type of the items in the queue. It
//     may be any of the C++ built-in types (int, char, etc.), or any class with
//     a default constructor, assignment operator, equivalence operator, and
//     copy constructor.
//
//   typedef ____ size_type
//     queue::size_type is the data type of any variable that keeps track
//     of how many items are in a queue.
//
// VALUE SEMANTICS for the queue class:
//   Assignment and copy constructor may be used with queue objects.
//
// FRIENDS OF THE CLASS
//    friend bool operator==(const queue& q1, const queue& q2);
//    friend bool operator!=(const queue& q1, const queue& q2);
//    friend std::ostream& operator<<(std::ostream& out, const queue& q);

#ifndef MAIN_SAVITCH_QUEUE1_H
#define MAIN_SAVITCH_QUEUE1_H

namespace main_savitch_8B
{
class queue
{
 public:
    // TYPEDEFS and MEMBER CONSTANTS
    typedef std::size_t size_type;
    typedef std::string value_type;

    // CONSTRUCTORS

    // Basic constructor
    // Precondition:  cap >= 2
    // Postcondition: queue has been initialized as an empty queue
    //    with capacity equal to `cap`.
    // Note:  If cap < 2, the queue capacity defaults to 8.
    queue(size_type cap=8);

    // Copy constructor
    // Postcondition: queue is initialized as an independent copy of `other`;
    //    subsequent changes to either of the queues will NOT affect the other.
    queue(const queue& other);

    // DESTRUCTOR
    ~queue();

    // ACCESSOR MEMBER FUNCTIONS

    // size
    // Postcondition: Return value is the current number of items in the queue.
    size_type size() const;

    // is_empty()
    // Postcondition: Returns true if this is an empty queue; otherwise,
    //    returns false.
    bool is_empty() const;

    // front
    // Precondition:  size > 0
    // Postcondition: Return value is the front item of the queue.
    value_type front() const;

    // MODIFICATION MEMBER FUNCTIONS

    // push
    // Postcondition: A new item, `entry`, has been inserted at the rear
    //    of the queue.
    // Postcondition: size has increased by 1.
    void push(const value_type& entry);

    // pop
    // Precondition:  size > 0
    // Postcondition: The front item of the queue has been removed.
    // Postcondition: size has decreased by 1.
    void pop();

    // assignment operator
    // Postcondition: This queue becomes an identical -- but indepedent --
    //    copy of `other` queue.
    // Postcondition: Returns this queue to allow for "chained assignment".
    queue& operator=(const queue& other);

    // FRIENDS
    friend bool operator==(const queue& q1, const queue& q2);
    friend bool operator!=(const queue& q1, const queue& q2);
    friend std::ostream& operator<<(std::ostream& out, const queue& q);

 private:
    size_type capacity;         // Current queue capacity (array length)
    value_type* data;           // Circular array in the heap
    size_type first;            // Index of item at front of the queue
    size_type last;             // Index of item at rear of the queue
    size_type count;            // Number of items currently in the queue

    // next_index
    // private function for helping to move a circular array index forward
    // Precondition: 0 <= i < capacity
    // Postcondition: Returns (i + 1) modulo capacity.
    size_type next_index(size_type i) const;

    // ensure_capacity
    // private function for increasing the capacity of the queue as needed
    // Postcondition:
    //    - If capacity == count (queue is full) when this function is called,
    //      then after it returns, capacity == count * 2
    //    - The items in the queue, and their ordering, is unchanged.
    // NOTE: If capacity > count when this function is called, then it has no
    //    effect.
    void ensure_capacity();

};  // end of class definition

// NON-MEMBER FUNCTIONS (FRIENDS)

// equivalence operator, checks for logical equivalence of q1 and q2
// Postcondition: Returns true if
//       a) q1 and q2 are equal in length, and
//       b) q1 and q2 have equivalent values and the same ordering;
//    otherwise, returns false.
//  Example 1. The queues <a, b, c> and <a, b, c> are equivalent.
//  Example 2. The queues <a, b, c> and <c, a, b> are not equivalent.
//  Example 3. The queues <a, b> and <a, b, c> are not equivalent.
bool operator==(const queue& q1, const queue& q2);

// inequivalence operator
// Postcondition: Returns false if q1 == q2; otherwise, returns true.
bool operator!=(const queue& q1, const queue& q2);

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
std::ostream& operator<<(std::ostream& out, const queue& q);

} // end namespace

#endif
