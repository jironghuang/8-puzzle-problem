#include "EightP.h"
#include "Queue.h"
#include <vector>
#include <cstddef>
#include <iostream>
//#include <string>

using namespace std;

//Set first and last node in the queue
queue::queue(){
	
    first = NULL;
    last = NULL;
    
    limit = 100; //default limit for the number of moves
    
}

/*
//Destructor
queue::~queue(){
    while(first!= NULL){
    delete first;
    first = first->getNext();
    }

    delete last;
}
*/
//Get nodes
puzzle* queue::getfront() {
return first;
}


//Check if it's empty. Use for root and also the entire queing process (near the end)
bool queue::isempty(){
//alt do this return first == NULL;
    if(first == NULL){
    return true;
    }else{
    return false;
    }
}

int* queue::front_combi(){
 if(isempty()){
   return NULL;
 }else{
   return first->getCombi();
 }
}

int queue::front_wrong_tile(){
 if(isempty()){
   return -1;    //-1 means empty
 }else{
   return first->get_wrong_tiles();
 }
}


//In main programme, add left, down, up, right before removing the first node. With the nodes already configured with the number of wrong tiles, costs,....
//removing (pop) the first node from the queue. 
//returns the number of wrong tiles
void queue::remove(){
//puzzle* temp = new puzzle();
	if (isempty()){
	    //return -1;	
	    cout<<"No more nodes in the queue."<<endl;
	}else{
	    int v = first->get_wrong_tiles();  //If this is 0, can actually exit while loop because you get correct configuration
	    first = first ->getNext();  //second in top of queue becomes the priority	
	    if(first == NULL){
	        last = NULL;
	    }else{
			//return v;	//Maybe don't need to return since the qn doesn't require. Can even change this to a void function
			//cout<<"Move on to next node."<<endl;
	    }
	}
}

void queue::add(int* a,int t,int ic,int wt,int tc,int vm, char m,vector<char> moves){
puzzle* p = new puzzle(0,0,0);

p->setArr(a);
p->set_temp(t);
p->set_inc_cost(ic);
p->set_wrong_tiles();
p->set_tot_cost();
p->set_valid_move(vm);
p->set_factoradic();
p->set_move_vector(moves);

//Moving the empty tile when creating a new node
if(m == 'D'){//set moving down
    //cout<<m<<endl;
	p->movedown();			
	//p->print_arr(p->getCombi());
	//cout<<""<<endl;
}else if (m == 'L'){//set move left
    //cout<<m<<endl;
	p->moveleft();	
	//p->print_arr(p->getCombi());
	//cout<<""<<endl;
}else if (m == 'U'){//set move up
    //cout<<m<<endl;
	p->moveup();
	//p->print_arr(p->getCombi());
	//cout<<""<<endl;
}else if (m == 'R'){//set move right
    //cout<<m<<endl;
	p->moveright();	
	//p->print_arr(p->getCombi());
	//cout<<""<<endl;
}else{	
    cout<<m<<endl;
	//p->print_arr(p->getCombi());
	//cout<<""<<endl;
}

//Do a pushback of the vector of moves here and update the incurred cost and total cost
p->add_move_vector(m);
p->set_inc_cost(p->get_moves_vector().size());
p->set_tot_cost();

///////////////
	if(isempty()){   
	    first = p;
	}else{
	    last->setNext(p);
	}
    last = p;       
}

//remove the node if it doesn't fulifill the condition: 1.)Already added before or 2.)You can't move in that direction -->can tap on private variable to see if it's valid or invalid
//Mirrors the stack function-->remove the first one that is added
int queue::valid_addition(int* a,int t,int ic,int wt,int tc,int vm, char m){
	puzzle* v = new puzzle(0,0,0);
	
	v->setArr(a);
	v->set_temp(t);
	v->set_inc_cost(ic);
	v->set_wrong_tiles();
	v->set_tot_cost();
	v->set_valid_move(vm);
	v->set_factoradic();
	
//Moving the empty tile when creating a new node
if(m == 'D'){//set moving down
    //cout<<m<<endl;
	v->movedown();			
	//v->print_arr(v->getCombi());
	//cout<<""<<endl;
}else if (m == 'L'){//set move left
    //cout<<m<<endl;
	v->moveleft();	
	//v->print_arr(v->getCombi());
	//cout<<""<<endl;
}else if (m == 'U'){//set move up
    //cout<<m<<endl;
	v->moveup();
	//v->print_arr(v->getCombi());
	//cout<<""<<endl;
}else if (m == 'R'){//set move right
    //cout<<m<<endl;
	v->moveright();	
	//v->print_arr(v->getCombi());
	//cout<<""<<endl;
}else{	
    //cout<<m<<endl;
	//v->print_arr(v->getCombi());
	//cout<<""<<endl;
}	

v->set_factoradic();
if((v->get_valid_move() == 1) && (all_combi[v->get_factoradic()] != 1)){
	return 1;
}else{
	return 0; 	
}
	//delete v;
}


//Add indicator of 1 to array all_combi if you are able to add to the queue
//Use the permuataion formula
void queue::add_indicator(int* a,int t,int ic,int wt,int tc,int vm, char m){
//Or should use the move l,r,u,d, then take the combination from there
	puzzle* i = new puzzle(0,0,0);	
	i->setArr(a);
	i->set_temp(t);
	i->set_inc_cost(ic);
	i->set_wrong_tiles();
	i->set_tot_cost();
	i->set_valid_move(vm);
	i->set_factoradic();

//Moving the empty tile when creating a new node
if(m == 'D'){//set moving down
	i->movedown();			
	//cout<<""<<endl;
}else if (m == 'L'){//set move left
	i->moveleft();	
	//cout<<""<<endl;
}else if (m == 'U'){//set move up
	i->moveup();
}else if (m == 'R'){//set move right
	i->moveright();	
	//cout<<""<<endl;
}else{	
}
//Convert to factoradic
//put a 1 to the position in array
all_combi[i->get_factoradic()] = 1; 
}

//void queue::get_a_star_moves(int* a,int t,int ic,int wt,int tc,int vm){
vector<char> queue::get_a_star_moves(int* a,int t,int ic,int wt,int tc,int vm, vector<char> moves){
	puzzle* left = new puzzle(0,0,0);	
	left->setArr(a);
	left->set_temp(t);
	left->set_valid_move(vm);
	left->set_factoradic();	
	left->set_move_vector(moves);
	left->set_inc_cost(left->get_moves_vector().size());
	left->set_wrong_tiles();
	left->set_tot_cost();
	left->moveleft(); //Total cost updated automatically-->the cost used to decide which move to take in A*
	int l = left->get_tot_cost();
	//if((left->get_valid_move() == 0)||((left->get_moves_vector())[left->get_inc_cost()]== 'R')) //Assign high cost if invalid move and previous move is R
	if(left->get_valid_move() == 0)
		l = 1000000;
//	(left->get_moves_vector())	

	vector<char> le = left->get_moves_vector();
	if(le[le.size()-1]== 'R')
		l = 100000;
	
	
	//cout<<l<<endl;
	
	puzzle* down = new puzzle(0,0,0);	
	down->setArr(a);
	down->set_temp(t);
	down->set_valid_move(vm);
	down->set_factoradic();	
	down->set_move_vector(moves);
	down->set_inc_cost(down->get_moves_vector().size());
	down->set_wrong_tiles();
	down->set_tot_cost();
	down->movedown(); //Total cost updated automatically-->the cost used to decide which move to take in A*
	int d = down->get_tot_cost();
	//cout<<d<<endl;
	//if((down->get_valid_move() == 0)||((down->get_moves_vector())[down->get_inc_cost()]== 'U'))//Assign high cost if invalid move and previous move is U
	if(down->get_valid_move() == 0)
		d = 1000000;
		
	vector<char> dow = down->get_moves_vector();
	if(dow[dow.size()-1]== 'U')
		d = 100000;
	
	puzzle* up = new puzzle(0,0,0);	
	up->setArr(a);
	up->set_temp(t);
	up->set_valid_move(vm);
	up->set_factoradic();	
	up->set_move_vector(moves);
	up->set_inc_cost(up->get_moves_vector().size());
	up->set_wrong_tiles();
	up->set_tot_cost();
	up->moveup(); //Total cost updated automatically-->the cost used to decide which move to take in A*
	int u = up->get_tot_cost();
	//cout<<u<<endl;
	//if((up->get_valid_move() == 0)||((up->get_moves_vector())[up->get_inc_cost()]== 'D')) //Assign high cost if invalid move and previous move is D
	if(up->get_valid_move() == 0)
		u = 1000000;
		
	vector<char> uv = up->get_moves_vector();
	if(uv[uv.size()-1]== 'D')
		u = 100000;
	
	puzzle* right = new puzzle(0,0,0);	
	right->setArr(a);
	right->set_temp(t);
	right->set_valid_move(vm);
	right->set_factoradic();	
	right->set_move_vector(moves);
	right->set_inc_cost(right->get_moves_vector().size());
	right->set_wrong_tiles();
	right->set_tot_cost();
	right->moveright(); //Total cost updated automatically-->the cost used to decide which move to take in A*
	int r = right->get_tot_cost();
	//cout<<r<<endl;
	//if((right->get_valid_move() == 0)||((right->get_moves_vector())[right->get_inc_cost()]== 'R'))//Assign high cost if invalid move and previous move is L
	if(right->get_valid_move() == 0)
		r = 1000000;
	vector<char> ri = right->get_moves_vector();
	if(ri[ri.size()-1]== 'L')
		r = 100000;
	
	//Initialise a vector to be returned
	vector<char> move;
	
	//Determine what nodes should be expanded
	if((l<d) && (l<u) && (l<r)){
		move.push_back('L');		
	}else if((d<l) && (d<u) && (d<r)){
		move.push_back('D');
	}else if((u<l) && (u<d) && (u<r)){
		move.push_back('U');
	}else if((r<l) && (r<d) && (r<u)){
		move.push_back('R');
    }else if((l==d) && (l<u) && (l<r)){
    	move.push_back('L');
		move.push_back('D');
	}else if((l==u) && (l<d) && (l<r)){
		move.push_back('L');
		move.push_back('U');		
    }else if((l==r) && (l<d) && (l<u)){
    	move.push_back('L');
		move.push_back('R');	    	
    }else if((d==u) && (d<l) && (d<r)){   
    	move.push_back('D');
		move.push_back('U');	    
    }else if((d==r) && (d<l) && (d<u)){   
    	move.push_back('D');
		move.push_back('R');	    
    }else if((u==r) && (u<l) && (u<d)){      
    	move.push_back('U');
		move.push_back('R');    	
    }else if((l==d==u) && (l<r)){
    	move.push_back('L');
		move.push_back('D');  
    	move.push_back('U');  	
	}else if((l==u==r) && (l<d)){
    	move.push_back('L');
		move.push_back('U');  
    	move.push_back('R');		
	}else if((d==l==r) && (d<u)){
    	move.push_back('L');
		move.push_back('D');  
    	move.push_back('R');			
	}else if((d==u==r) && (d<l)){	
    	move.push_back('D');
		move.push_back('U');  
    	move.push_back('R');		
	}else if(l== d == u == r){		
    	move.push_back('L');
    	move.push_back('D');
		move.push_back('U');  
    	move.push_back('R');
    }
		
	return move;
	//cout<<move<<endl;
}

//set a limit for the number of moves-->then in the while loop, can use as condition to stop the loopings
//int puzzle::get_temp()
int queue::get_limit(){
	return limit;
}

//void queue::add_indicator(int* a,int t,int ic,int wt,int tc,int vm, char m)
void queue::set_limit(int l){
	/*
	puzzle* p = new puzzle(0,0,0);
	p->add_move_vector(m);
	p->set_inc_cost(p->get_moves_vector().size());
	p->set_tot_cost();
	*/
	limit = l;
}




//Displaying number of wrong tiles along the queue
void queue::display()
{
    puzzle* cur = first;
    while (cur != NULL ) {         // as long as it has not reached the end
        cout<<cur->get_wrong_tiles()<<" -> ";
        cur = cur -> getNext();        //move to the next node for processing
    }
    cout<<"NULL"<<endl;
    delete cur;
}




