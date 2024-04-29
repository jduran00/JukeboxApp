#ifndef PLAYLIST_H__
#define PLAYLIST_H__

#include <memory>
#include <string>

using namespace std;

struct node {
  int genre; // genre as number declared in ****
  node* previous // points to the previous node, NULL if first node
  node* next; // points to the next node, or NULL if this is the last node.
  bool played // has the song been played? *** if new listening sesh return all to false
  float time // ??? may need for pause play
  string title // name of song
};

// Linked List Invariant: following the 'next' links must eventually lead to a
// NULL reference signifying the end of the list. (E.g. no circular references
// are allowed.)
class Playlist {
public:
  
  // Constructor
  Playlist();

  // Deconstructor
  ~Playlist();

  // Creates a new node structure from heap memory. Both pointers are NULL, and genre is 0, played is false and time is NULL
  node* init_node(int data);

  //returns a list of the titles and lengths of songs in playlist
  string report();

  // AppendData adds a node to the end of the list pointed to by top. The
  // resulting list is one element longer, and the newly appended node has the
  // given data value. Consider using the Append function to help - just create
  // a new node* and let Append do the work.
  void append_data(int data);

  // Append is the same as AppendData, except we're adding a node, rather than a
  // value.
  void append(node* new_node);

  // InsertData inserts a new node that contains the given data value, so the
  // new node occupies the offset indicated. Any nodes that were already in the
  // list at that offset and beyond are shifted down by one. For example if the
  // list contains 23, 74, 93, and we insert 42 at index 1, the resulting list
  // should be 23, 42, 74, 93.
  //
  // If an offset is beyond the end (or beginning) of the list, this function
  // should have no effect.
  //
  // Inserting at the end of the list should have the same effect as appending.
  void insert_data(int offset, int data);

  // This is the same as insert_data, except we're inserting a node, rather than
  // a value. This closely mirrors Append and AppendData.
  void insert(int offset, node* new_node);

  // Removes the node indicated by the given offset and frees its memory. For
  // example if our list contains 23, 74, 93, and we remove offset 1, the
  // resulting list should then contain 23, 93.
  //
  // If an invalid offset is given (e.g. negative or beyond the end of the
  // list), this function has no effect.
  void remove(int offset);

  // Returns the number of nodes in the linked list reachable by head
  // before (but not including) the terminating NULL link. E.g., an empty list
  // has size 0, a list with one item has size 1, etc.
  int size();

  // Returns true if this linked list contains a node with the specified value,
  // false otherwise.
  bool contains(int data);

  // This function is implemented for you. Returns the top pointer.
  node* get_top();

  // This is implemented for you. It sets a given pointer as the top pointer.
  void set_top(node* top_ptr);

  // You can declare more public member variables and member functions here if
  // you need them. Implement them in the cpp file.

private:
  node* top_ptr_;

  // you can add add more private member variables and member functions here if
  // you need
};

#endif // PLAYLIST_H__