#ifndef PLAYLIST_H__
#define PLAYLIST_H__

#include <memory>
#include <string>
#include <iostream>
#include <string>

using namespace std;


const int COUNTRY = 0;
const int POP = 1;
const int ROCK = 2;
const int METAL = 3;
const int BLUES = 4;

//structure of the songs
struct node {
  int genre; // genre as number declared in ****
  node* previous; // points to the previous node, NULL if first node
  node* next; // points to the next node, or NULL if this is the last node.
  bool played; // has the song been played? *** if new listening sesh return all to false
  float length; // ??? may need for pause play
  string title; // name of song
};


//structure of the playlists containing songs and enteracting with one another.  
struct list{
    node* first_song;
    int   genre;
    list* previous_list;
    list* next_list;
    };




class Playlist {
public:
  
  // Constructor
  Playlist();

  // Deconstructor
  ~Playlist();

  // Creates a new node structure from heap memory. Both pointers are NULL, and genre is 0, played is false and time is NULL
  node* init_node(int genre, float length, string title);

  // AppendData adds a song to the end of the list pointed to by top. The
  // resulting list is one element longer, and the newly appended node has the
  // given data value. Creates a song from these elements and appends using append func
  void append_song(int genre, float length,string title);

  //adds new song
  void append(node* new_node);

  ////returns a list of the titles and lengths of songs in playlist
  string report();


  // InsertData inserts a new node that contains the given data value, so the
  // new node occupies the offset indicated. Any nodes that were already in the
  // list at that offset and beyond are shifted down by one. Inserts song at particular spot   // in playlist
  void insert_song(int offset, int genre, float length, string title);


  // This is the same as insert_data, except we're inserting a node, rather than
  // a value. Inserts song at particular spot in playlist. (Like append and append_song)
  void insert(int offset, node* new_node);

  // Removes the song of a particular title, in case user dosent like it
  // If an invalid offset is given (e.g. negative or beyond the end of the
  // list), this function has no effect.
  void remove(string title);

  // Returns the number of songs in playlist an empty list
  // has size 0, a list with one item has size 1, etc.
  int size();
 
 
 //Creates new playlist from heap memory
  list* init_list (node* new_node);

 //find the right playlist for the genre
  list* get_list (int genre); 
    
  // gets top of list
  node* get_top_of_list(int genre);  
    
  ///adds songs to lists
  void append_list (node* node); 

  //marked true if paused
  bool paused();


  // Returns the top pointer.
  node* get_top();

  //  It sets a given pointer as the top pointer.
  void set_top(node* top_ptr);

  // You can declare more public member variables and member functions here if
  // you need them. Implement them in the cpp file.
  list* get_first_list(); //returns first list 

 //returns the first track of previous playlist
  node* get_first_of_previous(node* current);

  //returns the next track in current playlist
  node* get_next_track(node* current);

  //returns the first track of the next playlit
  node*get_first_of_next(node* current);


  //rearrange playlist in the desired order
  void rearrange_playlist ();

private:
  node* top_ptr_;
  list* top_list_;
  
};

#endif // PLAYLIST_H__