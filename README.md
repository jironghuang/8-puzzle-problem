# 8-puzzle-problem

#Command line codes for running the codes#
You may compile the programme by typing g++ EightP_mtd.cpp Queue.cpp and EightP.cpp into the cmd prompt. 

To activate the programme, you may type a.out into the command line. Then key in these parameters in the following sequence from the cin functions.
•	Enter the searchtype: bfs/ astar 
•	Enter the name of the file (only 1 filename): E.g. Qn1_1_startposition.txt/ Qn1_2_startposition.txt

Note: I set the default on the max number of moves to be 100.
File structures in the zipped files and key functions used
I adopted an object-oriented programming framework which a puzzle is denoted as a node and the search algorithms resemble a queue structure. 

#EightP.h/EightP_mtd.cpp#
-To create the puzzle/combination object

void puzzle::set_tot_cost(), Sum of incurred costs (each expansions results in +1 incurred cost) and the heuristic of number of wrong tiles

void puzzle::set_factoradic()	More for BFS. Once we’re able to find the factodoric index, we could denote 1 in the array of length 362880 if the combi has been explored.

void puzzle::moveleft(), movedown(), moveup(), moveright(). Moving the empty tile around while establishing rules on whether it’s legal for the move to be made.
	
#Queue.h/Queue.cpp#
-To create the queue object for the search algorithm	
void queue::add(int* a,int t,int ic,int wt,int tc,int vm, char m,vector<char> moves)	
Queuing the combinations as puzzles. This is the process: Once I dequeue a node, I will queue the childs after the ‘last’ node before the expansion

valid_addition(int* a,int t,int ic,int wt,int tc,int vm, char m), Test if it’s a valid addition. If valid, then I will add on to the queue. This accounts for whether it’s legal to move l,d,u or r. Also, if a node has already been added to the queue (known by factodoric index in array), I will not add on to the queue. 

add_indicator(int* a,int t,int ic,int wt,int tc,int vm, char m)	Add factodoric index if node was added to the queue earlier

vector<char> queue::get_a_star_moves(int* a,int t,int ic,int wt,int tc,int vm, vector<char> moves), Get the moves accounting for the costs in A* strategy. i.e. costs incurred + number of wrong tiles in exisiting combi

#EightP.cpp#
This is the main file for execution		
1. Switch statements for search, maxmoves and starting position.txt included

#Questions#
Question 1: Is the claim correct? (are they solvable and do they require 31 moves?)
As the time taken for Breadth first search is rather long, I will use my A* results to answer the question.
Yes, the puzzles are solvable. But from my algorithm, both sets of puzzles require 46 moves (192 nodes expanded) to solve instead. It could be due to difference in heuristics used. In my case, I look at the number of wrong tiles while Kevin may have used Manhattan distance to do it instead. 

Question 2: To test whether the board is solvable, add up entries in the inversion vector.
To answer Question 2, I generated 7 test cases from http://mypuzzle.org/sliding
From the table, we can see that it’s possible for sum of permutation inverse to odd and also solvable. That being said, in my test cases below, I’m unable to falsify his claim that ‘even’ number of the sum of permutation inverse is solvable.
Also surprisingly, the performance of the A* search algorithm exceeds the ‘supposedly’ worst case scenario in Question 1. I suspect that this may be because I chose to expand the nodes with the same cost – but that’s advised by the textbook.
You may find the code (execution of sum of permutation inverse) at the bottom of the EightP.cpp script.
Numbers	Solvable? 

(Sum of perm inverse commented out at the last section of EightP.cpp script)	Performance of A* (Number of moves/nodes queued). Some performance may look bad because I expanded the nodes with the same costs
Q2_1_testcase.txt: 2,6,5,4,7,9,1,3,8	Yes (14)	40/14244
Q2_2_testcase.txt: 7,5,4,3,6,9,8,2,1	Yes (17)	46/5293
Q2_3_testcase.txt: 8,1,2,5,7,9,4,6,3	Yes (10)	24/138
Q2_4_testcase.txt: 2,9,3,1,7,6,5,4,8	Yes (14)	34/ 430
Q2_5_testcase.txt: 1,4,3,9,7,8,2,6,5	Yes (15)	60/1025
Q2_6_testcase.txt: 2,8,1,4,5,6,3,9,7	Unknown	Reached the limit of 100 moves
Q2_7_testcase.txt: 1,5,4,7,3,9,6,2,8	Yes (13)	90/14221

Question 3: How efficient is A* search as compared to Breadth First Search
In Question 3, I established some simple test cases (by working backwards) so that I can easily measure the performance of the 2 algorithms.  
Looking at the performance below, A* performed comparatively better – in terms of the number of nodes added which would lead to higher number of nodes dequeued.
Numbers	Solvable? 
(Sum of perm inverse commented out at the last section of EightP.cpp script)	Performance of A* (Number of moves/nodes queued). Some performance may look bad because I expanded the nodes with the same costs	Performance of BFA (Number of moves/nodes queued). 
Q3_1_testcase.txt: 4,1,2,5,8,3,7,9,6	Yes	8/23	7/219
Q3_2_testcase.txt: 1,9,2,4,5,3,7,8,6	Yes
	4/4	3/29
Q3_3_testcase.txt: 9,1,2,4,5,3,7,8,6	Yes	5/5	4/47
Q3_4_testcase.txt: 4,1,2,9,5,3,7,8,6	Yes	6/6	5/77
Q3_5_testcase.txt: 1,9,2,4,5,3,7,8,6	Yes	4/4	3/29


