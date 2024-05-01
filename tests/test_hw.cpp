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
double test_Playlist::max_grade = 8;

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
