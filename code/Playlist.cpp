//  JUKEBOX APP
//
//  Author: Jasmine Duran
//  CU ID: jadu7619

#include "Playlist.h"
#include <iostream>
#include <string>

// constructor, initialize class variables and pointers here if need.
Playlist::Playlist() {
top_ptr_ = nullptr;
}

// deconstructor,
Playlist::~Playlist() {}



//Initalizes node 
node* Playlist::init_node(int genre, float length, string title) {
  node* ret(new node);
  ret->genre = genre;
  ret->next = NULL;
  ret->previous = NULL;
  ret->length = length;
  ret->played = false;
  ret->title = title;

  return ret;
}

//adds data into new node, then adds new node 
void Playlist::append_song(int genre, float length, string title) {
 auto new_node = init_node(genre, length, title);
  append(new_node);
  
}

//adds next song in playlist, linking the previous node
void Playlist::append(node* new_node) {
  node* cursor = get_top();
  node* previous = nullptr;
  if( cursor == nullptr){
    top_ptr_ = new_node;
    return;
  }
  while (cursor->next != nullptr){
    previous = cursor;

    cursor = cursor -> next;
    //cursor ->next->previous = previous;
  }
   
   //cursor -> next = new_node;
    
}

//returns song list 
string Playlist::report() {
  string ret;
  node* cursor = top_ptr_;
  if (cursor == nullptr){
    return ret;
  }
  while (cursor != nullptr){
    auto next_title = cursor->title;
    //string length = to_string(length); //time? "(" + length + ")" +
    ret = ret + next_title +  ", ";
    cursor = cursor -> next;
  }
  return ret;
}



void Playlist::insert_song(int offset, int genre, float length, string title) {
  int offset1 = offset;
  auto new_node = init_node(genre, length, title);
  insert(offset1, new_node);
  
}

void Playlist::insert(int offset, node* new_node) {
  node* cursor = top_ptr_;
    
  if (offset == 0){
    new_node->next = top_ptr_;
    top_ptr_ = new_node;
    return;
  }
  if (top_ptr_ == nullptr){
    top_ptr_ = new_node;
    return;
  }
  if(top_ptr_ == nullptr || offset <0){
    return;
  }
  if(offset != 1) {
    while(offset != 1 && cursor->next != nullptr) {
      cursor = cursor->next;
      offset = offset - 1;
    }
  }
  if(offset ==1){
    new_node->next = cursor->next;
    new_node->previous = cursor;
    cursor->next = new_node;
    ;
    return;
  }

}

void Playlist::remove(string title) {
  node* cursor = top_ptr_;
  node* previous = nullptr;
  int offset = -1;
  if(top_ptr_ == nullptr){  //empty list, stop func
      return;}
  if(cursor->title == title){ //checks to see if first song is unwanted song
      offset = 0;}
  while( cursor->next != nullptr && cursor->title != title){
      cursor = cursor->next;
      offset = offset +1;}   //find spot of song 
   if(top_ptr_ == nullptr || offset <0){ //checks to see offset was updated
    return;}
   if (size() ==0){ 
    return;}
  if (offset == 0){       //removes top song if unwated
    top_ptr_ = top_ptr_->next;
    return;
  }
   while( offset != 1 && cursor->next != nullptr){ //points to unwanted song
    previous = cursor;
    cursor = cursor->next;
    cursor->previous = previous;
    offset = offset - 1;
   }
   if (offset ==1){                        //removes song
    cursor->next = cursor->next->next;
   }
}

int Playlist::size() {
  int ret = 0;
  node* cursor = top_ptr_;
  if( cursor == nullptr){
    ret = 0;}
  while (cursor != nullptr){
    ret = ret + 1;
    cursor=cursor->next;  }

  return ret;
}

list* Playlist::init_list (node* new_node){
   int genre_temp = new_node->genre;
   list* ret(new list);
   ret-> first_song = new_node;
   ret->genre = genre_temp;
   ret->next_list = NULL;
   ret->previous_list = NULL;

   return ret;
}

list* Playlist::get_list (int genre){
  list* cursor = top_list_;
  if (cursor == NULL){
    return NULL;
  }

  while(cursor->genre != genre && cursor->next_list != NULL){
    cursor = cursor->next_list;
  }
  if(cursor->genre == genre){
    return cursor;
  }
  return NULL;
}

node* Playlist::get_top_of_list(int genre) { 
  list* cursor = top_list_;
  if (cursor == NULL){
    return NULL;
  }
  while(cursor->genre != genre && cursor->next_list != NULL){
    cursor = cursor->next_list;
  }
  if(cursor->genre == genre){
    if(cursor->first_song == NULL){
      return NULL;
    }
    if(cursor->genre == genre){
      return cursor->first_song;
    }
   }
   return NULL;
   }


  void Playlist::append_list (node* node){
  list* cursor = top_list_;
  int genre_temp = node->genre;
  if (cursor == NULL){
    init_list(node);
  }
  while(cursor->genre != genre_temp && cursor->next_list != NULL){
    cursor = cursor->next_list;
  }
  if(cursor->genre == genre_temp){
    if(cursor->first_song == NULL){
      cursor->first_song = node;
    }
    else{
      append_song(genre_temp, node->length, node->title);
    }
  }
}

// It returns the top pointer
node* Playlist::get_top() { return top_ptr_; }

// It returns the first playlist
list* Playlist::get_first_list() { return top_list_; }


// It sets a given pointer as the top pointer
void Playlist::set_top(node* top_ptr) { top_ptr_ = top_ptr; }

node* Playlist::get_next_track(node* current){
  return current->next;
}

node* Playlist::get_first_of_previous(node* current){
  list* current_list = get_list(current->genre);
  if (current_list->previous_list != NULL){
    return current_list->previous_list->first_song;}
  return current_list->first_song; //if current is first playlist
}

node* Playlist::get_first_of_next(node* current){
  list* current_list = get_list(current->genre);
  if (current_list->next_list != NULL){
    return current_list->next_list->first_song;}
  return current_list->first_song; //if current is first playlist
}

void Playlist::rearrange_playlist (){
string Order;
cout << "Enter desired order for playlists as numbers; Country = 0, Pop = 1, Rock = 2, Metal = 3, Blues =4";
cin>> Order;

for ( unsigned i = 0; i < Order.size();i++){
  list* list = get_list(int(Order[i]));
  if (i==0){
    list->previous_list = NULL;
  }
  if(unsigned(Order[i-1]) < 0 ){
    list->previous_list = get_list(int(Order[i-1]));
  }
  if(unsigned(Order[i+1]) > Order.size() ){
    list->next_list = get_list(int(Order[i+1])); 
    }
  else{
    list->next_list = NULL;
    }
}
}

