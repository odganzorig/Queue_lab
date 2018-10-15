// FILE: queue_tests.cpp
// CS 223 Winter 2018, Lab 5
//
// <Name and Date>
//

#include <sstream>
#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>
#include "queue.h"
#include "gtest/gtest.h"  // declares the testing framework

using namespace std;
using namespace main_savitch_8B;

namespace {

    // Lab 5 Unit Testing Plan -- 28 tests, 19 of which are provided

    // 3 tests for BasicConstructor, size, is_empty
    //   - DefaultConstructor
    //   - Capacity_2
    //   - Capacity_20

    // 8 tests for Front, Push, Pop
    //   - pushOneItemCheckFront
    //   - pushTwoItemsCheckFront
    //   - pushTwoPopOneCheckFront
    //   - pushTwoPopTwoCheckEmpty
    //   - pushTwoPopOnePushTwoPopOnePushThree
    //   - pushFivePopFourPushSeven
    //   - pushFivePopFourPushTenPopThree
    //   - pushTwentysixPopTwenty

    // 6 tests for Equivalence & Inequivalence
    //   - nonempty_queue_equivalent_to_itself  <<< NOT PROVIDED
    //   - empty_equivalent_to_empty  <<< NOT PROVIDED
    //   - empty_vs_nonempty  <<< NOT PROVIDED
    //   - both_nonempty_different_lengths  <<< NOT PROVIDED
    //   - both_nonempty_same_lengths_not_equiv
    //   - both_nonempty_same_values_equiv

    // 6 tests for Assignment Operator
    //   - selfAssignmentIsOK  <<< NOT PROVIDED
    //   - copyFromEmptytoNonemptyANDcopyIsIndependent  <<< NOT PROVIDED
    //   - copyFromNonemptyToEmptyANDcopyIsIndependent  <<< NOT PROVIDED
    //   - copyFromQueueWithThreeItemsAtIndexCapMinusOneToEmptyQueue
    //   - copyFromQueueWithFourItemsAndCapacityFourToQueueSize8
    //   - copyFromLongQueueToQueueSize10

    // 5 tests for Copy Constructor
    //   - copyEmptyANDcopyIsIndependent  <<< NOT PROVIDED
    //   - copyOneItemANDcopyIsIndependent  <<< NOT PROVIDED
    //   - copyThreeItemsAtIndexCapMinusOne
    //   - copyFourItemsFromCapacityFour
    //   - copyLongQueue

    TEST(TestBasicConstructorANDaccessorFunctions, DefaultConstructor)
    {
        queue q1;  // empty queue, capacity 8
        EXPECT_TRUE(q1.is_empty());
        EXPECT_EQ(q1.size(), 0);
    }

    TEST(TestBasicConstructorANDaccessorFunctions, Capacity_2)
    {
        queue q1(2);  // empty queue, capacity 2
        EXPECT_TRUE(q1.is_empty());
        EXPECT_EQ(q1.size(), 0);
    }

    TEST(TestBasicConstructorANDaccessorFunctions, Capacity_20)
    {
        queue q1(20);  // empty queue, capacity 20
        EXPECT_TRUE(q1.is_empty());
        EXPECT_EQ(q1.size(), 0);
    }

    // Next we implement and test:
    //  - ensure_capacity (do not test directly)
    //  - front
    //  - push
    //  - pop

    TEST(TestFrontPushPop, pushOneItemCheckFront)
    {
        queue q1;  // empty queue, capacity 8
        q1.push("ziggy");
        EXPECT_EQ(q1.front(), "ziggy");
        EXPECT_EQ(q1.size(), 1);
        EXPECT_FALSE(q1.is_empty());
    }

    TEST(TestFrontPushPop, pushTwoItemsCheckFront)
    {
        queue q1;  // empty queue, capacity 8
        q1.push("ziggy");
        q1.push("cleo");
        EXPECT_EQ(q1.front(), "ziggy");
        EXPECT_EQ(q1.size(), 2);
    }

    TEST(TestFrontPushPop, pushTwoPopOneCheckFront)
    {
        queue q1;  // empty queue, capacity 8
        q1.push("ziggy");
        q1.push("cleo");
        q1.pop();
        EXPECT_EQ(q1.front(), "cleo");
        EXPECT_EQ(q1.size(), 1);
    }

    TEST(TestFrontPushPop, pushTwoPopTwoCheckEmpty)
    {
        queue q1;  // empty queue, capacity 8
        q1.push("ziggy");
        q1.push("cleo");
        q1.pop();
        q1.pop();
        EXPECT_EQ(q1.size(), 0);
    }

    TEST(TestFrontPushPop, pushTwoPopOnePushTwoPopOnePushThree)
    {
        queue q1(3);  // empty queue, capacity 3
        q1.push("ziggy");
        q1.push("cleo");
        q1.pop();
        q1.push("skye");
        q1.push("ruthie");
        q1.pop();
        q1.push("ame");
        q1.push("gray");
        q1.push("xerea");
        EXPECT_EQ(q1.size(), 5);
        EXPECT_EQ(q1.front(), "skye");
        stringstream correct;
        correct << "queue of size 5:\n" << "skye\n" << "ruthie\n"
                << "ame\n" << "gray\n" << "xerea\n";
        stringstream actual;
        actual << q1;
        EXPECT_EQ(correct.str(), actual.str());
    }

    // this test forces next_index to wrap around the end of the array
    TEST(TestFrontPushPop, pushFivePopFourPushSeven)
    {
        queue q1;  // empty queue, capacity 8
        q1.push("a");
        q1.push("b");
        q1.push("c");
        q1.push("d");
        q1.push("e");
        q1.pop();
        q1.pop();
        q1.pop();
        q1.pop();
        q1.push("f");
        q1.push("g");
        q1.push("h");
        q1.push("i");
        q1.push("j");
        q1.push("k");
        q1.push("l");
        EXPECT_EQ(q1.size(), 8);
        EXPECT_EQ(q1.front(), "e");
        stringstream correct;
        correct << "queue of size 8:\ne\nf\ng\nh\ni\nj\nk\nl\n";
        stringstream actual;
        actual << q1;
        EXPECT_EQ(correct.str(), actual.str());
    }

    // forces ensure_capacity to enlarge the array
    TEST(TestFrontPushPop, pushFivePopFourPushTenPopThree)
    {
        queue q1;  // empty queue, capacity 8
        q1.push("a");
        q1.push("b");
        q1.push("c");
        q1.push("d");
        q1.push("e");
        q1.pop();
        q1.pop();
        q1.pop();
        q1.pop();
        q1.push("f");
        q1.push("g");
        q1.push("h");
        q1.push("i");
        q1.push("j");
        q1.push("k");
        q1.push("l");
        q1.push("m");
        q1.push("n");
        q1.push("o");
        q1.pop();
        q1.pop();
        q1.pop();
        EXPECT_EQ(q1.size(), 8);
        EXPECT_EQ(q1.front(), "h");
        stringstream correct;
        correct << "queue of size 8:\nh\ni\nj\nk\nl\nm\nn\no\n";
        stringstream actual;
        actual << q1;
        EXPECT_EQ(correct.str(), actual.str());
    }

    // force a lot of array enlarging and wrapping around the end of the array
    TEST(TestFrontPushPop, pushTwentysixPopTwenty)
    {
        queue q1(2);  // empty queue, capacity 2
        q1.push("a");
        q1.push("b");
        q1.push("c");
        q1.push("d");
        q1.push("e");
        q1.push("f");
        q1.push("g");
        q1.push("h");
        q1.push("i");
        q1.push("j");
        q1.push("k");
        q1.push("l");
        q1.push("m");
        q1.push("n");
        q1.push("o");
        q1.push("p");
        q1.push("q");
        q1.push("r");
        q1.push("s");
        q1.push("t");
        q1.push("u");
        q1.push("v");
        q1.push("w");
        q1.push("x");
        q1.push("y");
        q1.push("z");
        for (int i = 0; i < 20; i++) { q1.pop(); }
        EXPECT_EQ(q1.size(), 6);
        EXPECT_EQ(q1.front(), "u");
        stringstream correct;
        correct << "queue of size 6:\nu\nv\nw\nx\ny\nz\n";
        stringstream actual;
        actual << q1;
        EXPECT_EQ(correct.str(), actual.str());
    }

    // Next we implement and test:
    //  equivalence
    //  inequivalence

    TEST(TestEquivalenceInequivalence, nonempty_queue_equivalent_to_itself)
    {
        queue q1;
        q1.push("July 4");
        q1.push("Labor Day");
        q1.push("Halloween");
        q1.push("Thanksgiving");
        EXPECT_TRUE(q1 == q1);
        EXPECT_FALSE(q1 != q1);
    }

    TEST(TestEquivalenceInequivalence, empty_equivalent_to_empty)
    {
        queue q1;
        queue q2;
        EXPECT_TRUE(q1 == q2);
        EXPECT_FALSE(q1 != q2);
        EXPECT_TRUE(q2 == q1);
        EXPECT_FALSE(q2 != q1);
    }

    TEST(TestEquivalenceInequivalence, empty_vs_nonempty)
    {
        queue q1;
        queue q2;
        q2.push("July 4");
        q2.push("Labor Day");
        q2.push("Halloween");
        q2.push("Veterans' Day");
        EXPECT_TRUE(q1 != q2);
        EXPECT_FALSE(q1 == q2);
        EXPECT_TRUE(q2 != q1);
        EXPECT_FALSE(q2 == q1);
    }

    TEST(TestEquivalenceInequivalence, both_nonempty_different_lengths)
    {
        queue q1;
        q1.push("July 4");
        q1.push("Labor Day");
        queue q2;
        q2.push("July 4");
        q2.push("Labor Day");
        q2.push("Halloween");
        EXPECT_TRUE(q1 != q2);
        EXPECT_FALSE(q1 == q2);
        EXPECT_TRUE(q2 != q1);
        EXPECT_FALSE(q2 == q1);
    }

    TEST(TestEquivalenceInequivalence, both_nonempty_same_lengths_not_equiv)
    {
        queue q1;
        q1.push("July 4");
        q1.push("Labor Day");
        q1.push("Halloween");
        q1.push("Thanksgiving");
        queue q2;
        q2.push("July 4");
        q2.push("Labor Day");
        q2.push("Halloween");
        q2.push("Veterans' Day");
        EXPECT_FALSE(q1 == q2);
        EXPECT_TRUE(q1 != q2);
        EXPECT_FALSE(q2 == q1);
        EXPECT_TRUE(q2 != q1);
    }

    TEST(TestEquivalenceInequivalence, both_nonempty_same_values_equiv)
    {
        queue q1;
        q1.push("July 4");
        q1.push("July 4");
        q1.push("July 4");
        q1.push("July 4");
        q1.push("July 4");
        q1.push("July 4");
        q1.push("July 4");
        q1.pop();
        q1.pop();
        q1.pop();
        q1.pop();
        q1.pop();
        q1.pop();
        q1.push("Labor Day");
        q1.push("Halloween");
        q1.push("Thanksgiving");
        queue q2;
        q2.push("July 4");
        q2.push("Labor Day");
        q2.push("Halloween");
        q2.push("Thanksgiving");
        EXPECT_TRUE(q1 == q2);
        EXPECT_FALSE(q1 != q2);
        EXPECT_TRUE(q2 == q1);
        EXPECT_FALSE(q2 != q1);
    }

    // Finally, we implement and test:
    //  assignment
    //  copy constructor
    //  destructor (test indirectly, with Valgrind)
    TEST(TestAssignmentOperator, selfAssignmentIsOK)
    {
        queue q1;     
        q1.push("hey");
        q1.push("they");
        q1 = q1;
        EXPECT_EQ(q1.size(), 2);
        EXPECT_EQ(q1.front(), "hey");
        q1.pop();
        EXPECT_EQ(q1.front(), "they");
        q1.pop();
        EXPECT_EQ(q1.size(), 0);
    }

    TEST(TestAssignmentOperator, copyFromEmptytoNonemptyANDcopyIsIndependent)
    {
        queue q1;
        queue q2;
        q2.push("hey");
        q2.push("they");
        q2 = q1;
        EXPECT_EQ(q2.size(), 0);
        q1.push("hey");
        EXPECT_EQ(q2.size(), 0);
    }

    TEST(TestAssignmentOperator, copyFromNonemptyToEmptyANDcopyIsIndependent)
    {
        queue q1;     
        q1.push("hey");
        q1.push("they");
        queue q2;
        q2 = q1;
        EXPECT_EQ(q2.size(), 2);
        EXPECT_EQ(q2.front(), "hey");
        q1.pop();
        EXPECT_EQ(q2.front(), "hey");
        q2.pop();
        EXPECT_EQ(q2.front(), "they");
        q1.push("heey");
        EXPECT_EQ(q2.size(), 1);

    }

    TEST(TestAssignmentOperator, copyFromQueueWithThreeItemsAtIndexCapMinusOneToEmptyQueue)
    {
        queue q1(4);     // empty queue size 4
        q1.push("hey");
        q1.push("hey");
        q1.push("hey");
        q1.push("hey");
        q1.pop();
        q1.pop();
        q1.pop();
        q1.push("they");
        q1.push("say");
        queue q2;
        q2 = q1;
        EXPECT_EQ(q2.size(), 3);
        EXPECT_EQ(q2.front(), "hey");
        q2.pop();
        EXPECT_EQ(q2.front(), "they");
        q2.pop();
        EXPECT_EQ(q2.front(), "say");
    }

    TEST(TestAssignmentOperator, copyFromQueueWithFourItemsAndCapacityFourToQueueSize8)
    {
        queue q1(4);     // empty queue size 4
        q1.push("hey");
        q1.push("hey");
        q1.push("hey");
        q1.push("hey");
        q1.pop();
        q1.pop();
        q1.pop();
        q1.push("they");
        q1.push("say");
        q1.push("stay");  // hey, they, say, stay
        queue q2;
        q2.push("hey");
        q2.push("hey");
        q2.push("hey");
        q2.push("hey");
        q2.push("hey");
        q2.push("hey");
        q2.push("hey");
        q2.push("hey");
        q2.push("hey");
        q2.push("hey");
        q2.push("hey");
        q2.push("hey");
        q2 = q1;
        stringstream correct;
        correct << "queue of size 4:\nhey\nthey\nsay\nstay\n";
        stringstream actual;
        actual << q2;
        EXPECT_EQ(correct.str(), actual.str());
    }

    TEST(TestAssignmentOperator, copyFromLongQueueToQueueSize10)
    {
        queue q1(26);        // empty queue, capacity 26
        q1.push("a");
        q1.push("b");
        q1.push("c");
        q1.push("d");
        q1.push("e");
        q1.push("f");
        q1.push("g");
        q1.push("h");
        q1.push("i");
        q1.push("j");
        q1.push("k");
        q1.push("l");
        q1.push("m");
        q1.push("n");
        q1.push("o");
        q1.push("p");
        q1.push("q");
        q1.push("r");
        q1.push("s");
        q1.push("t");
        q1.push("u");
        q1.push("v");
        q1.push("w");
        q1.push("x");
        q1.push("y");
        q1.push("z");
        queue q2;
        for (int i = 0; i < 10; i++)
        {
            q2.push("hey");
        }
        ASSERT_TRUE(q2.size() == 10);
        q2 = q1;
        EXPECT_EQ(q2.size(), 26);
        stringstream correct;
        correct << "queue of size 26:\na\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl\nm\n"
                << "n\no\np\nq\nr\ns\nt\nu\nv\nw\nx\ny\nz\n";
        stringstream actual;
        actual << q2;
        EXPECT_EQ(correct.str(), actual.str());
    }

    TEST(TestCopyConstructor, copyEmptyANDcopyIsIndependent)
    {
        queue q1;
        queue q2(q1);
        q1.push("hey");
        EXPECT_EQ(q2.size(), 0);

    }

    TEST(TestCopyConstructor, copyOneItemANDcopyIsIndependent)
    {
        queue q1;
        q1.push("hey");
        queue q2(q1);
        EXPECT_EQ(q2.size(), 1);
        EXPECT_EQ(q2.front(), "hey");
        q1.pop();
        EXPECT_EQ(q2.size(), 1);
        EXPECT_EQ(q2.front(), "hey");
    }

    TEST(TestCopyConstructor, copyThreeItemsAtIndexCapMinusOne)
    {
        queue q1(4);     // empty queue size 4
        q1.push("hey");
        q1.push("hey");
        q1.push("hey");
        q1.push("hey");
        q1.pop();
        q1.pop();
        q1.pop();
        q1.push("they");
        q1.push("say");
        queue q2(q1);    // hey, they, say
        EXPECT_EQ(q2.size(), 3);
        EXPECT_EQ(q2.front(), "hey");
        q2.pop();
        EXPECT_EQ(q2.front(), "they");
        q2.pop();
        EXPECT_EQ(q2.front(), "say");
    }

    TEST(TestCopyConstructor, copyFourItemsFromCapacityFour)
    {
        queue q1(4);     // empty queue size 4
        q1.push("hey");
        q1.push("hey");
        q1.push("hey");
        q1.push("hey");
        q1.pop();
        q1.pop();
        q1.pop();
        q1.push("they");
        q1.push("say");
        q1.push("stay");  // hey, they, say, stay
        queue q2(q1);
        stringstream correct;
        correct << "queue of size 4:\nhey\nthey\nsay\nstay\n";
        stringstream actual;
        actual << q2;
        EXPECT_EQ(correct.str(), actual.str());
    }

    TEST(TestCopyConstructor, copyLongQueue)
    {
        queue q1(26);        // empty queue, capacity 26
        q1.push("a");
        q1.push("b");
        q1.push("c");
        q1.push("d");
        q1.push("e");
        q1.push("f");
        q1.push("g");
        q1.push("h");
        q1.push("i");
        q1.push("j");
        q1.push("k");
        q1.push("l");
        q1.push("m");
        q1.push("n");
        q1.push("o");
        q1.push("p");
        q1.push("q");
        q1.push("r");
        q1.push("s");
        q1.push("t");
        q1.push("u");
        q1.push("v");
        q1.push("w");
        q1.push("x");
        q1.push("y");
        q1.push("z");
        queue q2(q1);
        EXPECT_EQ(q2.size(), 26);
        stringstream correct;
        correct << "queue of size 26:\na\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl\nm\n"
                << "n\no\np\nq\nr\ns\nt\nu\nv\nw\nx\ny\nz\n";
        stringstream actual;
        actual << q2;
        EXPECT_EQ(correct.str(), actual.str());
    }

} // end namespace

// main() for testing -- boilerplate
int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


