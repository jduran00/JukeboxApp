//  JUKEBOX APP
//
//  Author: Jasmine Duran
//  CU ID: jadu7619

#include "Playlist.h"

// constructor, initialize class variables and pointers here if need.
Playlist::Playlist() {
top_ptr_ = nullptr;
}

// deconstructor,
Playlist::~Playlist() {}



//Initalizes node 
node* Playlist::init_node(int genre, float time, string title) {
  node* ret(new node);
  ret->genre = genre;
  ret->next = NULL;
  ret->previous = NULL;
  ret->time = time;
  ret->played = FALSE;
  ret->title = title;
}

//returns song list 
string Playlist::report() {
  string ret;
  node* cursor = top_ptr_;
  if (cursor == nullptr){
    return ret;
  }
  while (cursor != nullptr){
    auto nexttitle = cursor->title;
    auto length = to_string(time);
    ret = ret + nexttitle + "(" + length + ")" + ", ";
    cursor = cursor -> next;
  }
  return ret;
}

//adds data into new node, then adds new node 
void Playlist::append_data(int genre, float time) {
 auto new_node = init_node(genre, time);
  append(new_node);
  
}

//adds next song in playlist, linking the previous node
void Playlist::append(node* new_node) {
  node* cursor = top_ptr_;
  node* previous = nullptr;
  if( cursor == nullptr){
    top_ptr_ = new_node;
    return;
  }
  while (cursor->next != nullptr){
    previous = cursor
    cursor = cursor -> next;
  }
   cursor ->next->previous = previous;
   cursor -> next = new_node;
    
}

void Playlist::insert_data(int offset, int data) {
  int offset1 = offset;
  node* new_node = init_node(data);
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
    cursor->next = new_node;
    return;
  }

}

void Playlist::remove(int offset) {
  node* cursor = top_ptr_;
   if(top_ptr_ == nullptr || offset <0){
    return;}
   if (size() ==0){
    return;}
  if (offset == 0){
    top_ptr_ = top_ptr_->next;
    return;
  }
   while( offset != 1 && cursor->next != nullptr){
    cursor = cursor->next;
    offset = offset - 1;
   }
   if (offset ==1){
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

bool Playlist::contains(int data) {
  bool ret;
  ret = false;
  node* cursor = top_ptr_;
  while (cursor != nullptr)
  {
    if (cursor->data ==data){
      ret =true;
    }
    cursor = cursor->next;
  }
  
  

  return ret;
}

// This function is implemented for you
// It returns the top pointer
node* Playlist::get_top() { return top_ptr_; }

// This function is implemented for you
// It sets a given pointer as the top pointer
void Playlist::set_top(node* top_ptr) { top_ptr_ = top_ptr; }
