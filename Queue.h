#ifndef QUEUE_H
#define QUEUE_H
#include <vector>
//#include <string>
#include "EightP.h"

using namespace std;

class queue{
   private:
      puzzle* first;
      puzzle* last;
      
      //Store integer array of 9! here. Mainly to see if that combination has been tapped before 
      int all_combi[362880];   //number of positions = 362880, from 0 to 362879
      
      int limit; //set a limit of vector size -->i.e. the number of moves
      
   public:
      queue();     //done
      //~queue();
      
      puzzle* getfront(); //Get the front object
      
      bool isempty(); //done
      int* front_combi();  //done,returns front array without removing
      int front_wrong_tile();  //Get the number of wrong tiles in the front node
      void remove(); //done, another name is enqueue
      void add(int*,int,int,int,int,int,char,vector<char>);  //add a node to the queue

	  //See if valid addition to the queue 1.)Already added before or 2.)You can't move in that direction -->can tap on private variable to see if it's valid or invalid
      int valid_addition(int*,int,int,int,int,int,char);      //1 if valid, 0 if it's not
      
      //Add indicator of 1 to array all_combi if you are able to add to the queue
      void add_indicator(int*,int,int,int,int,int,char);
      
      //Return the move from A star for expansion
      //void get_a_star_moves(int* ,int ,int ,int ,int ,int ); 
       vector<char> get_a_star_moves(int* ,int ,int ,int ,int ,int, vector<char>); 
      
      //set a limit for the number of moves-->then in the while loop, can use as condition to stop the loopings
      int get_limit();
      void set_limit(int);
      
      void display();  //Displaying number of wrong tiles along the queue
};
#endif
