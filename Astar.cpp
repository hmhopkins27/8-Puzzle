//-------------------------------------------------------------------
//Hannah Hopkins
//Assignment 2
//25 March 2016
//--------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

bool isGoal(vector<int> v);
void init(vector< vector<int> > &T);
void printBoard(vector<int> ss);
int manDistance(vector<int> v);
void genSuc(vector<int> v, vector< vector<int> > &T);
int findLeast(vector< vector<int> > T);
vector<int> removeNode(vector< vector<int> > &T, int location);
bool searchExp(vector<int> v, vector< vector<int> > expanded);
int calHeur(vector<int> v);

int main () {
	
	int locationOfLeast=0;
	
	vector< vector<int> > T;
	vector< vector<int> > expanded;
	
	vector<int> v(9);
	
	init(T);
	
	while(isGoal(v)==false){
		
		if(T.empty()==true){
			cout << "FAIL." << endl;
		}
		else{
			locationOfLeast=findLeast(T);
			v=removeNode(T,locationOfLeast);
			
			if(isGoal(v)==true){
				printBoard(v);
				cout << "Goal found!" << endl;
				break;
			}
			else{
				if(searchExp(v,expanded)==false){
					expanded.push_back(v);
					genSuc(v,T);
					printBoard(v);
				}
			}			
		}				
	}
	
	return 0;
}

int findLeast(vector< vector<int> > T){
	int smallest=100; //will become the smallest number
	int location=0;
	
	for(int i=0; i<T.size(); i++){
		if(calHeur(T[i]) < smallest){
			smallest=calHeur(T[i]);
			location=i;
		}
	}
	
	return location;
}

//calculates the heuristic value (f(n))
//this will determine the value of each state
int calHeur(vector<int> v){
	int h=0, g=0, f=0;
	
	h=manDistance(v);
	g=1;
	f=h+g;
	
	return f;
}

//initializes T to the start state
//reads start state in from a file
void init(vector< vector<int> > &T){
	ifstream StartState;
	vector<int> ss(9);
	
	StartState.open("StartState.txt");
	
	if(StartState.is_open()){
		for(int i=0; i<ss.size(); i++){			
			StartState >> ss[i];		
		}
		
		T.push_back(ss);
				
		StartState.close();
	}
		
	else{
		cout << "Cannot open file." << endl;
	}
	
}

//tests to see if the node that was removed is the goal
//returns true if the goal was found and false if it was not
bool isGoal(vector<int> v){
	bool firstHalf, secondHalf, middle;
	
	for(int i=0; i<4; i++){
		if(v[i]==(i+1)){
			firstHalf=true;
		}
		else{
			firstHalf=false;
		}
	}
	
	if(v[4]==0){
		middle=true;
	}
	else{
		middle=false;
	}
	
	for(int j=5; j<9; j++){
		if(v[j]==j){
			secondHalf=true;
		}
		else{
			secondHalf=false;
		}
	}
	
	if(firstHalf==true && secondHalf==true){
		firstHalf=true; 
	}
	else{
		firstHalf=false;
	}
	
	if(firstHalf==true && middle==true){
		return true;
	}
	
	return false;
}

//prints out the board
void printBoard(vector<int> v){
	cout << "-------------------------" << endl;
	cout << "|   ";
	for(int i=0; i<3; i++){
		cout << v[i] << "   |   ";
	}
	cout << endl;
	cout << "-------------------------" << endl;
	
	cout << "|   ";
	for(int i=3; i<6; i++){
		cout << v[i] << "   |   ";
	}
	cout << endl;
	cout << "-------------------------" << endl;

	cout << "|   ";
	for(int i=6; i<9; i++){
		cout << v[i] << "   |   ";
	}
	cout << endl;
	cout << "-------------------------" << endl;
}

//computes the Manhattan Distance for the node removed
int manDistance(vector<int> v){	
	int manDist=0;
	vector<int> goal(9);
	
	goal[0]=1;
	goal[1]=2;
	goal[2]=3;
	goal[3]=4;
	goal[4]=0;
	goal[5]=5;
	goal[6]=6;
	goal[7]=7;
	goal[8]=8;
	
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			if((v[i] != 0) && (v[i] == goal[j])){
				manDist += abs(i/3 - j/3) + abs(i%3 - j%3);
			}
		}
	}
	
	return manDist;	
}

//generates successors of the node that was removed
void genSuc(vector<int> v, vector< vector<int> > &T){
	int blank=0;
	int temp, temp2, temp3, temp4;
	vector<int> child1(9);
	vector<int> child2(9);
	vector<int> child3(9);
	vector<int> child4(9);
	
	for(int j=0; j<9; j++){
		if(v[j]==0){
			blank=j;
		}
	}
	
	for(int i=0; i<9; i++){ 
		child1[i]=v[i];
		child2[i]=v[i];
		child3[i]=v[i];
		child4[i]=v[i];
	}
	
	switch(blank){
		case 0: 
			temp=child1[1];
			temp2=child2[3];
			
			child1[1]=child1[0];
			child1[0]=temp;
			child2[3]=child2[0];
			child2[0]=temp2;
			
			T.push_back(child1);
			T.push_back(child2);

			break;
		case 1:
			temp=child1[0];
			temp2=child2[4];
			temp3=child3[2];
			
			child1[0]=child1[1];
			child1[1]=temp;
			child2[4]=child2[1];
			child2[1]=temp2;
			child3[2]=child3[1];
			child3[1]=temp3;
			
			T.push_back(child1);
			T.push_back(child2);
			T.push_back(child3);
			
			break;
		case 2:
			temp=child1[1];
			temp2=child2[5];
			
			child1[1]=child1[2];
			child1[2]=temp;
			child2[5]=child2[2];
			child2[2]=temp2;
			
			T.push_back(child1);
			T.push_back(child2);

			break;
		case 3:
			temp=child1[0];
			temp2=child2[4];
			temp3=child3[6];
			
			child1[0]=child1[3];
			child1[3]=temp;
			child2[4]=child2[3];
			child2[3]=temp2;
			child3[6]=child3[3];
			child3[3]=temp3;
			
			T.push_back(child1);
			T.push_back(child2);
			T.push_back(child3);

			break;
		case 4:
			temp=child1[5];
			temp2=child2[3];
			temp3=child3[1];
			temp4=child4[7];
			
			child1[5]=child1[4];
			child1[4]=temp;
			child2[3]=child2[4];
			child2[4]=temp2;
			child3[1]=child3[4];
			child3[4]=temp3;
			child4[7]=child4[4];
			child4[4]=temp4;
			
			T.push_back(child1);
			T.push_back(child2);
			T.push_back(child3);
			T.push_back(child4);
			
			break;
		case 5: 
			temp=child1[2];
			temp2=child2[8];
			temp3=child3[4];
			
			child1[2]=child1[5];
			child1[5]=temp;
			child2[8]=child2[5];
			child2[5]=temp2;
			child3[4]=child3[5];
			child3[5]=temp3;
			
			T.push_back(child1);
			T.push_back(child2);
			T.push_back(child3);
			
			break;
		case 6:
			temp=child1[3];
			temp2=child2[7];
			
			child1[3]=child1[6];
			child1[6]=temp;
			child2[7]=child2[6];
			child2[6]=temp2;
			
			T.push_back(child1);
			T.push_back(child2);

			break;
		case 7:
			temp=child1[4];
			temp2=child2[6];
			temp3=child3[8];
			
			child1[4]=child1[7];
			child1[7]=temp;
			child2[6]=child2[7];
			child2[7]=temp2;
			child3[8]=child3[7];
			child3[7]=temp3;
			
			T.push_back(child1);
			T.push_back(child2);
			T.push_back(child3);
			
			break;
		case 8:
			temp=child1[5];
			temp2=child2[7];
			
			child1[5]=child1[8];
			child1[8]=temp;
			child2[7]=child2[8];
			child2[8]=temp2;
			
			T.push_back(child1);
			T.push_back(child2);

			break;
		default:
			cout << "Error" << endl;
	}	
}

//searches the expanded list for the vector that was removed from T
bool searchExp(vector<int> v, vector< vector<int> > expanded){
	for(int i=0; i< expanded.size(); i++){
		if(v==expanded[i]){
			return true;
		}
	}
	
	return false;
}

vector<int> removeNode(vector< vector<int> > &T, int location){
	vector<int> temp(9);
	temp=T[location];
	T.erase(T.begin()+location); 
	return temp;
}

