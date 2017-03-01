//This file is a header file for the puzzle (node) properties

//For the header file
#ifndef EIGHTP
#define EIGHTP
#include <vector>
//#include<string>
//Define class

using namespace std;

class puzzle{
	private:
	//Stores the 9 numbers in the array
	int combi[9];
	
	//store a vector to see what're the previous moves that led to this state (including now)-->Use the size of this see what's the incurred cost
	vector<char> moves_vector;

	int temp;		//store temp value when swapping position
	int inc_cost;   //Calculate the already incurred costs for astar search
	int wrong_tiles; //Heuristic for a* search
	int tot_cost;   //Sum of inc_cost and wrong_tiles
	int valid_move; //If valid move, indicate 1, 0 otherwise
	int factoradic; //Position in Queue obj array. So that if combi is explored, you don't queue that node again
	
	int sum_perm_inverse;
			
	//Instead of pointers to up, down, left and right, use a next pointer instead. Because if not, you can't do a queue structure
	puzzle* next;
	
	public:	
	
	puzzle(int,int,int);
	//Get and set values in arrays
	int* getCombi();  
	void setArr(int*);  //1st for reading array, second for size of array-1
	
	//Get and set values of attributes
	int get_temp();
	int get_inc_cost();
	int get_wrong_tiles();
	int get_tot_cost();
	int get_valid_move();
	int get_factoradic();	
	int get_sum_perm_inverse();
	
	void set_temp(int);
	void set_inc_cost(int);
	void set_wrong_tiles();
	void set_tot_cost();
    void set_valid_move(int);
    void set_factoradic();	
    
    
    vector<char> get_moves_vector();
    void set_move_vector(vector<char>);
    void add_move_vector(char);
 
    puzzle* getNext() const;
    void setNext(puzzle*);
    
	//Printing out the arrays for visual purposes
	void print_arr(int*);

	//Moving the tiles (using the swapping way in the permutation script)	
	void moveleft();
	void movedown();
	void moveup();
	void moveright();	
	
};
#endif





