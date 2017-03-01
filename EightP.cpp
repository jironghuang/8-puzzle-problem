//Notes: Use a switch structure for the different type of search algorithms: namely BFS and A* search
//This script is the main script for the excecution of all the files
#include "EightP.h"
#include "Queue.h"
#include <vector>
//#include <string>
#include <iostream>
#include <string>
#include<fstream>

using namespace std;

int main(){

//Search type for switch structure in the main code
char search;
cout<<"Key in the search type (bfs: Key in b or astar: Key in a)"<<endl;
cin>>search;

//int maxnodes;
//cout<<"Key in the max nodes (integer)"<<endl;
//cin>>maxnodes;

//queue the root
//read in the values from the txt file here
string name_file;
cout<<"Enter the name of the file"<<endl;
cin>>name_file;

int dat[9];

string file = name_file;            
ifstream openFile;
openFile.open(file.c_str());
int input;
for(int i=0; i<9; i++){
     openFile>>input;
     dat[i] = input;
}

//load the values into the root
puzzle*rt = new puzzle(0,0,0);

rt->setArr(dat);
rt->set_wrong_tiles();
rt->setNext(NULL);

puzzle*cur = rt;	//first node memory address

if (search == 'b'){
///////////////////////////////
//Start of the switch structure for search algorithm
///////////////////////////////
queue* bfs = new queue();
bfs->add(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),'N',cur->get_moves_vector());
bfs->add_indicator(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),'N');	//So that in future, you won't add the same node

//Add in a counter to see the number of nodes added to the queue
int nodes_added = 1;
int nodes_dequeued = 1;
while((bfs->front_wrong_tile() != 0) && (bfs->isempty() == false)){
nodes_dequeued++ ;

//Attach move down node if fulfill condition
if(bfs->valid_addition(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),'D') == 1){
	bfs->add(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),'D',cur->get_moves_vector());
	bfs->add_indicator(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),'D');	
	nodes_added++;	
}

//Attach move left node if fulfill condition
if(bfs->valid_addition(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),'L') == 1){
	bfs->add(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),'L',cur->get_moves_vector());
	bfs->add_indicator(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),'L');	
	nodes_added++;
}

//Attach move up node if fulfill condition
if(bfs->valid_addition(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),'U') == 1){
	bfs->add(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),'U',cur->get_moves_vector());
	bfs->add_indicator(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),'U');	
	nodes_added++;
}

//Attach move right node if fulfill condition
if(bfs->valid_addition(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),'R') == 1){
	//cout<<"added R"<<endl;
	bfs->add(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),'R',cur->get_moves_vector());
	bfs->add_indicator(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),'R');	
	nodes_added++;
}

//remove the current node
bfs->remove();

//Assign current with first
cur = bfs->getfront();
//cur->print_arr(cur->getCombi());  //returns the correct combi here. Which means that the cur node is the one with the correct info. Can extract the vector of moves here.

//If cur hit the limit exit while loop and say exceeded
if(cur->get_moves_vector().size() == bfs->get_limit()){
	cout<<"Reached the limit of "<<(bfs->get_limit())<<endl;
	break;	
}

//If cur->getwrongtiles == 0, you copy the info of the vector
if(cur->get_wrong_tiles() == 0){
	vector<char> solution = cur->get_moves_vector();	
	cout<<"number of moves required "<<(solution.size())<<endl;

	cout<<"number of nodes added: "<<nodes_added<<endl;
	cout<<"number of nodes dequeued: "<<nodes_dequeued<<endl;
	
	for(int i = 0;i<solution.size();i++){
	//cout<<"sol move: "<<solution[i]<<endl; 
   }
//With the vector of moves, you print the whole thing on cmd without all the unnecessary expanisions
//Go back to root
//Then use move down, left , up, right functions to display the nodes. Using if construct
puzzle*final_combi = new puzzle(0,0,0);
final_combi = rt;

for(int i = 0;i<solution.size();i++){

	if(solution[i] == 'D'){//set moving down
	    cout<<solution[i]<<endl;
		final_combi->movedown();			
		final_combi->print_arr(final_combi->getCombi());
		cout<<""<<endl;
	}else if (solution[i] == 'L'){//set move left
	    cout<<solution[i]<<endl;
		final_combi->moveleft();	
		final_combi->print_arr(final_combi->getCombi());
		cout<<""<<endl;
	}else if (solution[i] == 'U'){//set move up
	    cout<<solution[i]<<endl;
		final_combi->moveup();
		final_combi->print_arr(final_combi->getCombi());
		cout<<""<<endl;
	}else if (solution[i] == 'R'){//set move right
	    cout<<solution[i]<<endl;
		final_combi->moveright();	
		final_combi->print_arr(final_combi->getCombi());
		cout<<""<<endl;
	}else{	
	    cout<<solution[i]<<endl;
		final_combi->print_arr(final_combi->getCombi());
		cout<<""<<endl;
	}	
}

}

//cout<<"Inc costs: "<<(cur->get_inc_cost())<<endl; //Excluding the roots

}//end of while loop


/////////////////////////////////
//End of the switch option for bfs
/////////////////////////////////
}else if(search == 'a'){
	
/////////////////////////////////
//Start of the switch option for a*
/////////////////////////////////

queue* astar = new queue();
astar->add(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),'N',cur->get_moves_vector());
astar->add_indicator(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),'N');	//So that in future, you won't add the same node

cur = astar->getfront();
int a = cur->get_moves_vector().size();
cout<<a<<" "<<cur->get_moves_vector()[a]<<endl;

//A star search, incurred cost could be the amt++ in each iteration of the while loop. Then assign cur with the incurred cost. A bit tricky in a queue structure. Maybe create incurred cost in the queue structure instead since you can assign it in the while loop
//Doesn't need to use the factordoric property
//Add in a counter to see the number of nodes added to the queue
int nodes_added = 1;
int nodes_dequeued = 1;
vector<char> sel_move;

//sel_move = astar->get_a_star_moves(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),cur->get_moves_vector());
//cout<<"Selected move is: "<<sel_move<<endl;
//astar->add(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),sel_move,cur->get_moves_vector());

//cur = astar->getfront();
//vector<char> solution = cur->get_moves_vector();	
//cout<<"number of moves required "<<(solution.size())<<endl;

//astar->get_a_star_moves(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move());



//Set a while loop -->same as bfs
while((astar->front_wrong_tile() != 0) && (astar->isempty() == false)){
nodes_dequeued++ ;

sel_move = astar->get_a_star_moves(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),cur->get_moves_vector());
//cout<<"Selected move is: "<<sel_move<<endl;

for(int i = 0;i<sel_move.size();i++){
//if(astar->valid_addition(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),sel_move) == 1){
	astar->add(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),sel_move[i],cur->get_moves_vector());
	astar->add_indicator(cur->getCombi(),cur->get_temp(),cur->get_inc_cost(),cur->get_wrong_tiles(),cur->get_tot_cost(),cur->get_valid_move(),sel_move[i]);	
	nodes_added++;		
}

//}
//remove the current node
astar->remove();

//Assign current with first
cur = astar->getfront();
//cur->print_arr(cur->getCombi());  //returns the correct combi here. Which means that the cur node is the one with the correct info. Can extract the vector of moves here.
//a = cur->get_moves_vector().size();


//If cur hit the limit exit while loop and say exceeded
if(cur->get_moves_vector().size() == astar->get_limit()){
	cout<<"Reached the limit of "<<(astar->get_limit())<<endl;
	break;	
}

//If cur->getwrongtiles == 0, you copy the info of the vector
if(cur->get_wrong_tiles() == 0){
	vector<char> solution = cur->get_moves_vector();	
	cout<<"number of moves required "<<(solution.size())<<endl;

	cout<<"number of nodes added: "<<nodes_added<<endl;
	cout<<"number of nodes dequeued: "<<nodes_dequeued<<endl;
	
	for(int i = 0;i<solution.size();i++){
	//cout<<"sol move: "<<solution[i]<<endl; 
   }
   
//With the vector of moves, you print the whole thing on cmd without all the unnecessary expanisions
//Go back to root
//Then use move down, left , up, right functions to display the nodes. Using if construct
puzzle*final_combi = new puzzle(0,0,0);
final_combi = rt;

for(int i = 0;i<solution.size();i++){

	if(solution[i] == 'D'){//set moving down
	    cout<<solution[i]<<endl;
		final_combi->movedown();			
		final_combi->print_arr(final_combi->getCombi());
		cout<<""<<endl;
	}else if (solution[i] == 'L'){//set move left
	    cout<<solution[i]<<endl;
		final_combi->moveleft();	
		final_combi->print_arr(final_combi->getCombi());
		cout<<""<<endl;
	}else if (solution[i] == 'U'){//set move up
	    cout<<solution[i]<<endl;
		final_combi->moveup();
		final_combi->print_arr(final_combi->getCombi());
		cout<<""<<endl;
	}else if (solution[i] == 'R'){//set move right
	    cout<<solution[i]<<endl;
		final_combi->moveright();	
		final_combi->print_arr(final_combi->getCombi());
		cout<<""<<endl;
	}else{	
	    cout<<solution[i]<<endl;
		final_combi->print_arr(final_combi->getCombi());
		cout<<""<<endl;
	}	
}

}

//cout<<"Inc costs: "<<(cur->get_inc_cost())<<endl; //Excluding the root
}//End of while loop


//At end of while loop, take the lower of cost until the queue is empty

/////////////////////////////////
//End of the switch structure
/////////////////////////////////
}else{
	cout<<"Rerun the codes and pls enter either a or b - corresponds to a* and bfs respectively";	
}


//////////////
///Question 2
/////////////
puzzle*qn2 = new puzzle(0,0,0);
qn2->setArr(dat);							//read in at the start of the programme
qn2->set_wrong_tiles();
qn2->set_factoradic();
cout<<"Sum of perm inverse is:"<<qn2->get_sum_perm_inverse();

}









