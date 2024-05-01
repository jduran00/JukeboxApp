// If you change anything in this file, your changes will be ignored
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include "../code/Playlist.h"
#include <gtest/gtest.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class test_Playlist : public ::testing::Test {
protected:
  // This function runs only once before any TEST_F function
  static void SetUpTestCase() {
    std::ofstream outgrade("./total_grade.txt");
    if (outgrade.is_open()) {
      outgrade.clear();
      outgrade << (int)0;
      outgrade.close();
    }
  }

  // This function runs after all TEST_F functions have been executed
  static void TearDownTestCase() {
    std::ofstream outgrade("./total_grade.txt");
    if (outgrade.is_open()) {
      outgrade.clear();
      outgrade << (int)std::ceil(100 * total_grade / max_grade);
      outgrade.close();
      std::cout << "Total Grade is : "
                << (int)std::ceil(100 * total_grade / max_grade) << std::endl;
    }
  }

  void add_points_to_grade(double points) {
    if (!::testing::Test::HasFailure()) {
      total_grade += points;
    }
  }

  // this function runs before every TEST_F function
  void SetUp() override {}

  // this function runs after every TEST_F function
  void TearDown() override {
    std::ofstream outgrade("./total_grade.txt");
    if (outgrade.is_open()) {
      outgrade.clear();
      outgrade << (int)std::ceil(100 * total_grade / max_grade);
      outgrade.close();
    }
  }

  static double total_grade;
  static double max_grade;
};

double test_Playlist::total_grade = 0;
double test_Playlist::max_grade = 38;

TEST_F(test_Playlist, TestInitialization) {
  Playlist mylist;
  ASSERT_FALSE(mylist.get_top()); // expect top to be NULL
  add_points_to_grade(1);
  node* root = mylist.init_node(COUNTRY, 4.50, "Country Song 1");
  ASSERT_TRUE(root); // expect root itself to have a pointer (not NULL)
  add_points_to_grade(1);
  ASSERT_EQ(COUNTRY, root->genre);
  add_points_to_grade(1);
  ASSERT_FALSE(root->next); // expect next pointer to be null
  add_points_to_grade(1);
}

node* build_three_node_list_helper(int genre1, float length1, string title1, int genre2, float length2, string title2, int genre3, float length3, string title3) {
  node* top(new node);
  top->genre = genre1;
  top->next = new node;
  top->next->genre = genre2;
  top->next->next = new node;
  top->next->next->genre = genre3;
   top->title = title1;
  top->next->title  = title2;
  top->next->next->title  = title3;
  top->length = length1;
  top->next->length = length2;
  top->next->next->length = length3;
  top->next->next->next = (NULL);
  return top;

}

TEST_F(test_Playlist, TestReport) {
  Playlist mylist;

  string exp("");
  ASSERT_EQ("", mylist.report());
  add_points_to_grade(2);

  // create a three node list and test the report result
  node* top = build_three_node_list_helper(0, 4.30, "Country song 1", 0, 4.22, "Country song 2", 0, 3.22, "Country song 3");
  // replace mylist top_ptr_ with this new top
  mylist.set_top(top);
  ASSERT_EQ("Country song 1, Country song 2, Country song 3, ", mylist.report());
  add_points_to_grade(2);
}

TEST_F(test_Playlist, TestAppendsong) {
  Playlist mylist;
  node* top = build_three_node_list_helper(0, 4.30, "Country song 1", 0, 4.22, "Country song 2", 0, 3.22, "Contry song 3");
  mylist.append_list(top);
  
  mylist.append_song(0, 3.56, "Country Song 4");

  // get a cursor for appended data
  node* cursor = mylist.get_top()->next->next->next;
  ASSERT_TRUE(cursor);
  add_points_to_grade(1);

  ASSERT_FALSE(cursor->next); // expect to be NULL
  add_points_to_grade(1);

  ASSERT_EQ("Country Song 4", cursor->title);
  add_points_to_grade(1);

  // try appending one more node
  mylist.append_song(0, 3.46, "Country Song 5");
  // update cursor to point to fifth member
  cursor = mylist.get_top()->next->next->next->next;
  ASSERT_TRUE(cursor); // expect not to be NULL
  add_points_to_grade(1);

  ASSERT_FALSE(cursor->next); // expect to be NULL
  add_points_to_grade(1);

  ASSERT_EQ(0, cursor->genre);
  add_points_to_grade(1);
}

TEST_F(test_Playlist, TestAppendNode) {

  Playlist mylist;

  // test appending to empty list
  node* ap_fave = mylist.init_node(0, 2.30, "Fave country song");
  // add node fave to an empty list
  mylist.append(ap_fave);
  // ensure the list has a non-null top
  ASSERT_TRUE(mylist.get_top()); // expect not to be NULL
  add_points_to_grade(1);
  // ensure first element is the ap_nd node by coparing addresses
  // ASSERT_EQ(ap_five.get(), mylist.GetTop().get());
  ASSERT_EQ(ap_fave, mylist.get_top());
  add_points_to_grade(1);
  // ensure first element's value is 15
  ASSERT_EQ(0, mylist.get_top()->genre);
  add_points_to_grade(1);

  // insert another node and test
  node* ap_ten = mylist.init_node(0, 2.33, "Second fave country song");
  mylist.append(ap_ten);
  ASSERT_EQ(0, mylist.get_top()->next->genre);
  add_points_to_grade(1);
  ASSERT_FALSE(mylist.get_top()->next->next); // expect to be NULL
  add_points_to_grade(1);

  // try appending one more
  node* ap_nn = mylist.init_node(0, 4.12, "Anotha one");
  mylist.append(ap_nn);
  ASSERT_EQ("Anotha one", mylist.get_top()->next->next->title);
  add_points_to_grade(1);
  ASSERT_FALSE(mylist.get_top()->next->next->next); // expect to b NULL
  add_points_to_grade(1);
}
