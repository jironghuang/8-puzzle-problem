#include "EightP.h"
#include <iostream>
#include <vector>
//#include<string>
using namespace std;

puzzle::puzzle(int c,int w,int t){
  temp = 0;
  inc_cost = c;
  wrong_tiles = w;
  tot_cost = t;
  valid_move = 1;    //default is valid
  factoradic = 0;
  sum_perm_inverse = 0;
  
  //Assign null to node in next
  next = NULL;   
}


//Get array of values
int* puzzle::getCombi(){
	return combi; 	
}

//Setting values in arrays 
void puzzle::setArr(int* a) {
//For the puzzles it's sz = 8 for 9 values
for(int i = 0; i<9 ; i++){
combi[i] = a[i];	
}
}


//Get attributes
int puzzle::get_temp(){
	return temp;
}

int puzzle::get_inc_cost(){
	return inc_cost;
}

int puzzle::get_wrong_tiles(){
	return wrong_tiles;	
}
int puzzle::get_tot_cost(){
	return tot_cost;
}
int puzzle::get_valid_move(){
	return valid_move;
}

int puzzle::get_factoradic(){
	return factoradic;
}

int puzzle::get_sum_perm_inverse(){
	return sum_perm_inverse;
}

	
//Set attributes
void puzzle::set_temp(int t){
	temp = t;	
}

void puzzle::set_inc_cost(int c){
	inc_cost = c;	
}

void puzzle::set_wrong_tiles(){
	wrong_tiles = 0;
	for(int i = 0; i<9 ; i++){	   
		if(((i+1)-combi[i])!=0){
		 wrong_tiles = wrong_tiles + 1;	
		}
	}
}
void puzzle::set_tot_cost(){
	tot_cost = inc_cost + wrong_tiles;
} 
void puzzle::set_valid_move(int m){
	valid_move = m;	
}

void puzzle::set_factoradic(){
//Calculate the factordoric number in the puzzle object instead
//Use the math formula here
//create a vector here to store the numbers -->from left to right for caclulating the permutation inverse
vector<int>perm_inv;
perm_inv.push_back(combi[1]-1);
int more = 0;   //to calculate if the number in the position is larger than what has already been inspected

for(int j = 1; j<9; j++){	
    more = 0;
	//Loop through the vector, perm_inv and see 
	for(int k = 0;k<perm_inv.size();k++){
		if(combi[j]>combi[k])
			more++;
	}	
	//calculate the number to be included in the permutation inverse -->combi[i] - 1 - more 
	perm_inv.push_back(combi[j]-1-more);		
}

int sum_p = 0;
for(int i = 1;i<perm_inv.size();i++){
	sum_p = sum_p + perm_inv[i];
}

sum_perm_inverse = sum_p;				//This is more for qn 2

//Convert to factoradic
//Brute force the factorial calculation
//Check if this is in the correct order -->perm_inv[8]
int eightfac = perm_inv[0] *8*7*6*5*4*3*2*1 ;
int sevfac =   perm_inv[1] *7*6*5*4*3*2*1 ;
int sixfac =   perm_inv[2] *6*5*4*3*2*1 ;
int fivefac =  perm_inv[3] *5*4*3*2*1 ;
int fourfac =  perm_inv[4] *4*3*2*1 ;
int threefac = perm_inv[5] *3*2*1 ;
int twofac =   perm_inv[6] *2*1 ;
int onefac =   perm_inv[7] *1 ;
int zerofac =  perm_inv[8] *1 ;

factoradic = eightfac + sevfac + sixfac + fivefac + fourfac + threefac + twofac + onefac + zerofac ;
//put a 1 to the position in array-->This is done in the Queue.cpp, not here
} 

//Vector of moves
vector<char> puzzle:: get_moves_vector(){
	return moves_vector;
}

//Copy the entire vector of moves
void puzzle:: set_move_vector(vector<char> m){
	moves_vector = m;
}

//Add just 1 more move
void puzzle:: add_move_vector(char m){
	moves_vector.push_back(m);
}

//Get nodes
puzzle* puzzle::getNext()const {
return next;
}

//Set nodes
void puzzle::setNext(puzzle* n) {
next = n;
}

//Printing out the arrays
void puzzle::print_arr(int* a){
	cout<<a[0]<<" "<<a[1]<<" "<<a[2]<<endl;
	cout<<a[3]<<" "<<a[4]<<" "<<a[5]<<endl;
	cout<<a[6]<<" "<<a[7]<<" "<<a[8]<<endl;	
	/*
	for(int i = 0; i<9; i++){
		cout<<a[i]<<"->";
	}	
	*/
}



//Moving the empty tile - in this case, number 9
void puzzle::moveleft(){	
	////Moving from position 0 (not possible)
	if (combi[0] == 9){                
		//cout<<"Invalid move, cant move left"<<endl;
		valid_move = 0;	
	//Moving from position 1 to 0	
	}else if(combi[1] == 9) {
		puzzle::set_temp(combi[1]);   ///Think if should set temp as private variable or create the variable here 
	    combi[1] = combi[0];
	    combi[0] = get_temp();
	    valid_move = 1;	
	    puzzle::set_wrong_tiles();
		puzzle::set_factoradic();
		puzzle::set_tot_cost();
	//Moving from position 2 to 1 	
	}else if(combi[2] == 9) {
		puzzle::set_temp(combi[2]);   
	    combi[2] = combi[1];
	    combi[1] = get_temp();
	    valid_move = 1;	
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//Moving from position 3 (not possible)
	}else if(combi[3] == 9) {
		//cout<<"Invalid move, cant move left"<<endl;
		valid_move = 0;
	    puzzle::set_wrong_tiles();	
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//Moving from position 4 to 3 
	}else if(combi[4] == 9) {
		puzzle::set_temp(combi[4]);   
	    combi[4] = combi[3];
	    combi[3] = get_temp();
	    valid_move = 1;
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//Moving from position 5 to 4 
	}else if(combi[5] == 9) {
		puzzle::set_temp(combi[5]);   
	    combi[5] = combi[4];
	    combi[4] = get_temp();
	    valid_move = 1;		
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	}else if(combi[6] == 9) {
		//cout<<"Invalid move, cant move left"<<endl;
		valid_move = 0;	
	    puzzle::set_wrong_tiles();	
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	}else if(combi[7] == 9) {
		puzzle::set_temp(combi[7]);   
	    combi[7] = combi[6];
	    combi[6] = get_temp();
	    valid_move = 1;
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();	
	}else if(combi[8] == 9) {
		puzzle::set_temp(combi[8]);   
	    combi[8] = combi[7];
	    combi[7] = get_temp();
	    valid_move = 1;			
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
    }
}

void puzzle::movedown(){	
	//moving from 0 to 3
	if (combi[0] == 9){
		puzzle::set_temp(combi[0]);   
	    combi[0] = combi[3];
	    combi[3] = get_temp();
	    valid_move = 1;
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 1 to 4
	}else if(combi[1] == 9) {
		puzzle::set_temp(combi[1]);   
	    combi[1] = combi[4];
	    combi[4] = get_temp();	
		valid_move = 1;	
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 2 to 5
	}else if(combi[2] == 9) {
		puzzle::set_temp(combi[2]);   
	    combi[2] = combi[5];
	    combi[5] = get_temp();	
	    valid_move = 1;
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 3 to 6
	}else if(combi[3] == 9) {
		puzzle::set_temp(combi[3]);   
	    combi[3] = combi[6];
	    combi[6] = get_temp();	
	    valid_move = 1;
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 4 to 7
	}else if(combi[4] == 9) {
		puzzle::set_temp(combi[4]);   
	    combi[4] = combi[7];
	    combi[7] = get_temp();	
	    valid_move = 1;
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 5 to 8
	}else if(combi[5] == 9) {
		puzzle::set_temp(combi[5]);   
	    combi[5] = combi[8];
	    combi[8] = get_temp();	
		valid_move = 1;		
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 6 (not possible)
	}else if(combi[6] == 9) {
		//cout<<"Invalid move, cant move down"<<endl;
		valid_move = 0;	
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 7 (not possible)	
	}else if(combi[7] == 9) {
		//cout<<"Invalid move, cant move down"<<endl;
		valid_move = 0;		
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 8 (not possible)
	}else if(combi[8] == 9) {
		//cout<<"Invalid move, cant move down"<<endl;	
		valid_move = 0;		
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	}
}

void puzzle::moveup(){
	//moving from 0 (not possible) 
	if (combi[0] == 9){
		//cout<<"Invalid move, cant move up"<<endl;
		valid_move = 0;	
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 1 (not possible)	
	}else if(combi[1] == 9) {
		//cout<<"Invalid move, cant move up"<<endl;
		valid_move = 0;	
	    puzzle::set_wrong_tiles();	
		puzzle::set_tot_cost();	
	    puzzle::set_factoradic();
	//moving from 2 (not possible)
	}else if(combi[2] == 9) {
		//cout<<"Invalid move, cant move up"<<endl;
		valid_move = 0;		
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 3 to 0 
	}else if(combi[3] == 9) {
		puzzle::set_temp(combi[3]);   
	    combi[3] = combi[0];
	    combi[0] = get_temp();	
	    valid_move = 1;
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
    //moving from 4 to 1
	}else if(combi[4] == 9) {
		puzzle::set_temp(combi[4]);   
	    combi[4] = combi[1];
	    combi[1] = get_temp();	
	    valid_move = 1;
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 5 to 2
	}else if(combi[5] == 9) {
		puzzle::set_temp(combi[5]);   
	    combi[5] = combi[2];
	    combi[2] = get_temp();	
		valid_move = 1;	
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();	
	    puzzle::set_factoradic();
	//moving from 6 to 3
	}else if(combi[6] == 9) {
		puzzle::set_temp(combi[6]);   
	    combi[6] = combi[3];
	    combi[3] = get_temp();
		valid_move = 1;	
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();		
	    puzzle::set_factoradic();
    //moving from 7 to 4
	}else if(combi[7] == 9) {
		puzzle::set_temp(combi[7]);   
	    combi[7] = combi[4];
	    combi[4] = get_temp();
		valid_move = 1;			
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 8 to 5
	}else if(combi[8] == 9) {
		puzzle::set_temp(combi[8]);   
	    combi[8] = combi[5];
	    combi[5] = get_temp();	
		valid_move = 1;		
	    puzzle::set_wrong_tiles();	
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
    }	
}

void puzzle::moveright(){
	//moving from 0 to 1
	if (combi[0] == 9){
		puzzle::set_temp(combi[0]);   
	    combi[0] = combi[1];
	    combi[1] = get_temp();	
		valid_move = 1;	
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 1 to 2		
	}else if(combi[1] == 9) {
		puzzle::set_temp(combi[1]);   
	    combi[1] = combi[2];
	    combi[2] = get_temp();	
		valid_move = 1;	
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 2 (not possible) 
	}else if(combi[2] == 9) {
		//cout<<"Invalid move, cant move right"<<endl;	
		valid_move = 0;	
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 3 to 4
	}else if(combi[3] == 9) {
		puzzle::set_temp(combi[3]);   
	    combi[3] = combi[4];
	    combi[4] = get_temp();	
		valid_move = 1;
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 4 to 5
	}else if(combi[4] == 9) {
		puzzle::set_temp(combi[4]);   
	    combi[4] = combi[5];
	    combi[5] = get_temp();	
		valid_move = 1;		
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 5 (not possible) 
	}else if(combi[5] == 9) {
		//cout<<"Invalid move, cant move right"<<endl;
		valid_move = 0;		
	    puzzle::set_wrong_tiles();	
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 6 to 7		
	}else if(combi[6] == 9) {
		puzzle::set_temp(combi[6]);   
	    combi[6] = combi[7];
	    combi[7] = get_temp();	
		valid_move = 1;		
	    puzzle::set_wrong_tiles();	
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 7 to 8
	}else if(combi[7] == 9) {
		puzzle::set_temp(combi[7]);   
	    combi[7] = combi[8];
	    combi[8] = get_temp();	
		valid_move = 1;	
	    puzzle::set_wrong_tiles();
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
	//moving from 8 (not possible) 
	}else if(combi[8] == 9) {
		//cout<<"Invalid move, cant move right"<<endl;		
		valid_move = 0;	
	    puzzle::set_wrong_tiles();	
		puzzle::set_tot_cost();
	    puzzle::set_factoradic();
    }	
}





