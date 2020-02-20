//Next step need to check for check and check-mate
#include <iostream>
#include <string>
#include <unordered_map>
#include <cmath>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
class gamestate
{
   	//int board [8][8];
	//board will hold int that says what piece is on the spot
	//0 empty, 1-6 = white, 11-16 = black
	//1 Wpawn, 2 Wknight, 3 Wbishop, 4 Wrook, 5 Wqueen, 6 Wking -----------WHITE PIECES
	//11 Bpawn, 12 Bknight, 13 Bbishop, 14 Brook, 15 Bqueen, 16 Bking -----BLACK PIECES
	
	private:
	//bool whiteTurn = true;
	unordered_map<int, vector<pair<int,int>>> pieces; //piece number mapped to-
				//a vector of pairs of coordinates of all of those pieces

	public:
	bool whiteTurn = true;
	int board [8][8];

	gamestate(){//board[x][y] 
		board[0][7] = 14; //a8 black pieces below
		board[1][7] = 12; //b8
		board[2][7] = 13; //c8
		board[3][7] = 15; //d8 
		board[4][7] = 16; //e8
		board[5][7] = 13; //f8
		board[6][7] = 12; //g8
		board[7][7] = 14; //h8

		board[0][0] = 4; //a1 white pieces below
		board[1][0] = 2; //b1
		board[2][0] = 3; //c1
		board[3][0] = 5; //d1
		board[4][0] = 6; //e1
		board[5][0] = 3; //f1
		board[6][0] = 2; //g1
		board[7][0] = 4; //h1

		pieces[4] = {make_pair(0,0), make_pair(0,7)}; //white rooks
		pieces[14] = {make_pair(7,0), make_pair(7,7)}; //black rooks

		pieces[2] = {make_pair(1,0), make_pair(6,0)}; //white knights
		pieces[12] = {make_pair(1,7), make_pair(6,7)}; //black knights

		pieces[3] = {make_pair(2,0), make_pair(5,0)}; //white bishops
		pieces[13] = {make_pair(2,7), make_pair(5,7)}; //black bishops

		pieces[5] = {make_pair(3,0)}; //white queen
		pieces[15] = {make_pair(3,7)}; //black queen

		pieces[6] = {make_pair(4,0)}; //white king
		pieces[16] = {make_pair(4,7)}; //black king
				
		for(int i = 0; i<8; ++i){
			board[i][6] = 11; //all squares on 7 row are black pawn = 11
			board[i][1] = 1; //all swares on 2 row are white pawn = 1

			pieces[1].push_back(make_pair(i,1)); //white pawn on line y = 1
			pieces[11].push_back(make_pair(i,6)); //black pawn on line y = 6
		}
    
		for(int row = 2; row<6; ++row){
			for(int col = 0; col<8; ++col){
				board[col][row] = 0;
			}
		}
	}

	void play(){
		print();
		string start;
		string end;
		while(true){
			cout << "Enter move (start) (end): ";
			cin >> start;
			cin >> end;
			makeMove(start,end);
		}
	}

	bool kingBlocked(){ //useless right now used later in testCheckmate
		pair<int, int> kingPos;
		if(whiteTurn){
			kingPos = pieces[16][0];
		}
		else{
			kingPos = pieces[6][0];
		}
		//8 moves (+1, +1), (+1, -1), (+1, +0) etc
		vector<pair<int,int>> moves = {make_pair(1,1), make_pair(1,0), 
			make_pair(1,-1), make_pair(0,1), make_pair(0,-1), 
			make_pair(-1,1), make_pair(-1,0), make_pair(-1,-1)};
		pair<int,int> tempPos;
		for(int i = 0; i<moves.size(); ++i){
			tempPos.first = kingPos.first + moves[i].first;
			tempPos.second = kingPos.second + moves[i].second;
			if(tempPos.first <= 7 && tempPos.first >= 0 && 
				tempPos.second <= 7 && tempPos.second >= 0 &&
				board[tempPos.first][tempPos.second] < 11){
				return false;
			}  
		}
		return true;
	}
  
	bool isCheck(int startx, int starty, int endx, int endy){
		pair<int,int> currKing;
		if(whiteTurn){
			currKing = pieces[16][0];
		}
		else{
			currKing = pieces[6][0]; 
		}
		//printf("In isCheck: start: (%d,%d), end: (%d,%d), currKing: (%d,%d).\n",
	//		startx,starty,endx,endy,currKing.first,currKing.second);
		switch(board[startx][starty])
		{
			case 1: //white pawn
				return (currKing.first == endx +1 || currKing.first == endx -1) && currKing.second == endy + 1; //pawn able to capture

			case 11: //black pawn
				return (currKing.first == endx +1 || currKing.first == endx -1) && currKing.second == endy - 1; //pawn able to capture

			case 2: //white knight has same ruleset as black knight, so overflows into case 12

			case 12: //black knight
				return abs(currKing.first - endx) == 2 && abs(currKing.second - endy) == 1 
					|| abs(currKing.first - endx) == 1 && abs(currKing.second - endy) == 2;

			case 3: //white bishop

			case 13: //black bishop
				return isValidDiagonal(endx, endy, currKing.first, currKing.second);

			case 4: //white rook

			case 14: //black rook
				return isValidStraight(endx, endy, currKing.first, currKing.second);
			case 5: //white queen

			case 15: //black queen
				return isValidDiagonal(endx, endy, currKing.first, currKing.second) || isValidStraight(endx, endy, currKing.first, currKing.second);

			case 6: //white king

			case 16: //black king

			default:
				return false;
		}
	}

	bool testCheckmate(int startx, int starty, int endx, int endy){
		/*pair<int,int> currKing;
		if(whiteTurn){
			currKing = pieces[16];
		}
		else{
			currKing = pieces[6]; 
		}
		switch(board[startx][starty]){
			case 1: //white pawn
				if(board)

			case 11: //black pawn
		}*/
	}

	bool makeMove(string start, string end){
		if(isMove(start, end)){
			int startx = start[0]-'a'; 
			int starty = start[1]-'1';
			int endx = end[0] -'a';
			int endy = end[1] -'1';

			if(!whiteTurn && board[startx][starty] <= 6){
				cout<<"Invalid Move.\n";
				return false;
			}
			else if(whiteTurn && board[startx][starty] >= 11){
				cout<<"Invalid Move.\n";
				return false;
			}

			if(isCheck(startx, starty, endx, endy)){
				cout<<"Check\n";
			}
			whiteTurn = !whiteTurn;
			board[endx][endy] = board[startx][starty]; //update new postion
			board[startx][starty] = 0; //empty start position
			print();
			return true;
		}
		else{
			cout<<"Invalid Move.\n";
			return false;
		}
	}
	bool isOppositeOrEmpty(int startx, int starty, int endx, int endy){
		if(board[startx][starty] == 0){
			cerr << "Error: Checking if isOppositeOrEmpty on an empty start position.\n";
		}
		bool startWhite = 0 < board[startx][starty] && board[startx][starty] < 7;
		bool endWhite = 0 < board[endx][endy] && board[endx][endy] < 7;
		bool endEmpty = board[endx][endy] == 0;
		return startWhite != endWhite || endEmpty;		
	}

	bool isValidDiagonal(int startx, int starty, int endx, int endy){
		if(abs(endx-startx) != abs(endy-starty)){
			return false;
		}
		bool validDiagonal = true;
		if(endx-startx > 0 && endy-starty > 0){ //going up and right
			for(int i = 1; i < endx - startx; ++i){
				validDiagonal = validDiagonal && board[startx+i][starty+i] == 0;
			}
		}
		else if(endx-startx < 0 && endy-starty > 0){ //going up and left
			for(int i = 1; i < endy - starty; ++i){
				validDiagonal = validDiagonal && board[startx-i][starty+i] == 0;
			}
		}
		else if(endx-startx > 0 && endy-starty < 0){ //going down and right
			for(int i = 1; i < endx - startx; ++i){
				validDiagonal = validDiagonal && board[startx+i][starty-i] == 0;
			}
		}
		else if(endx-startx < 0 && endy-starty < 0){ //going down and left
			for(int i = 1; i < startx - endx; ++i){
				validDiagonal = validDiagonal && board[startx-i][starty-i] == 0;
			}
		}
		return validDiagonal;
	}

	bool isValidStraight(int startx, int starty, int endx, int endy){
		if((startx != endx) && (starty != endy)){
			return false;
		}
		bool validStraight = true;
		if(startx == endx && starty < endy){ //going up
			for(int i = 1; i < endy - starty; ++i){
				validStraight = validStraight && board[startx][starty+i] == 0;
			}
		}
		else if(startx == endx && starty > endy) { //going down
			for(int i = 1; i < starty - endy; ++i){
				validStraight = validStraight && board[startx][starty-i] == 0;
			}
		}
		else if(starty == endy && startx < endx) { //going right
			for(int i = 1; i< endx - startx; ++i){
				validStraight = validStraight && board[startx+i][starty] == 0;
			}
		}
		else if(starty == endy && startx > endx) { //going left
			for(int i = 1; i< startx - endx; ++i){
				validStraight = validStraight && board[startx-i][starty] == 0;
			}
		}
		return validStraight;
	}

	bool isMove(string start, string end){
		//return if move is possible
		if(start[0] < 'a' || start[0] > 'h' || start[1] < '1' || start[1] > '8' ||
			end[0] <'a' || end[0] > 'h' || end[1] < '1' || end[1] > '8'){
			return false; //invalid input
		}
		int startx = start[0]-'a'; 
		int starty = start[1]-'1';
		int endx = end[0] -'a';
		int endy = end[1] -'1'; 

		switch(board[startx][starty])
		{
			case 0: //empty
				return false;

			case 1: //white pawn
				if(starty == 1 && startx == endx && endy == 3 && 
					board[endx][endy] == 0 && board[endx][endy-1] == 0) //at start position
						return true;
				else if(startx == endx && board[endx][endy] == 0 && endy == starty +1) //empty spot one ahead
					return true; 
				else if((endx == startx +1 || endx == startx -1) && endy == starty +1 
					&& 10 < board[endx][endy] && board[endx][endy] < 17) //pawn able to capture
					return true; 
				//todo: en passant
				else
					return false; 

			case 11: //black pawn
				if(starty == 6 && startx == endx && endy == 4 &&
					board[endx][endy] == 0 && board[endx][endy+1] == 0) //at start position and not blocked
					return true;
				else if(startx == endx && board[endx][endy] == 0 && endy == starty -1) //empty one spot ahead
					return true; 
				else if((endx == startx + 1 || endx == startx -1) && endy == starty -1 
					&& 0 < board[endx][endy] && board[endx][endy] < 7) //pawn able to capture
					return true; 
				else
					return false;

			case 2: //white knight has same ruleset as black knight, so overflows into case 12

			case 12: //black knight
				return isOppositeOrEmpty(startx, starty, endx, endy) &&
					(abs(endx - startx) == 2 && abs(endy - starty) == 1 
					|| abs(endx - startx) == 1 && abs(endy - starty) == 2);

			case 3: //white bishop

			case 13: //black bishop
				//check the diagonal that it is trying to reach isOppositeOrEmpty, also make sure it's a diagonal
				if(abs(endx-startx) != abs(endy-starty) || !isOppositeOrEmpty(startx, starty, endx, endy)) { //make sure move is on a diagonal
					return false;
				}
				else{
					return isValidDiagonal(startx, starty, endx, endy);
				}

			case 4: //white rook

			case 14: //black rook
				//make sure it's on a straight line and end is opposite or empty
				if(!((startx == endx) != (starty == endy)) || !isOppositeOrEmpty(startx, starty, endx, endy)){
					return false;
				}
				else {
					return isValidStraight(startx, starty, endx, endy);
				}

			case 5: //white queen

			case 15: //black queen
				if((abs(endx-startx) == abs(endy-starty) || ((startx == endx) != (starty == endy))) &&
					isOppositeOrEmpty(startx, starty, endx, endy)) {
					bool validStraight = isValidStraight(startx, starty, endx, endy);
					bool validDiagonal = isValidDiagonal(startx, starty, endx, endy);
					return validStraight || validDiagonal;
				}
				else{
					return false;
				}

			case 6: //white king

			case 16: //black king
				//just check if the end position is 1 spot away and opposite or empty
				return isOppositeOrEmpty(startx,starty,endx,endy) && 
					abs(endx - startx) < 2 && abs(endy - starty) < 2;	
			default:
				return false;

		}
		return true;
	}
	
	void print(){
		//King = K, Queen = Q, Knight = N, Bishop = B, Rook = R, Pawn = P, Black = B, White = W
		string piece= "WP";
		cout<<endl;
		for(int row = 7; row >=0; --row){
			for(int col = 0; col < 8; ++col){
				//val = board[row][col];
				switch(board[col][row])
				{
					case 0:
						piece = "*";
						break;
					case 1:
						piece = "wP";
						break;
					case 2:
						piece = "wN";
						break;
					case 3:
						piece = "wB";
						break;
					case 4:
						piece = "wR";
						break;
					case 5:
						piece = "wQ";
						break;
					case 6: 
						piece = "wK";
						break;
					case 11:
						piece = "bP";
						break;
					case 12:
						piece = "bN";
						break;
					case 13:
						piece = "bB";
						break;
					case 14:
						piece = "bR";
						break;
					case 15:
						piece = "bQ";
						break;
					case 16:
						piece = "bK";
						break;
				}
				if(piece[0] == 'w'){
				//	printf("\033[;33m%s\033[m",piece); 
					cout << "\033[1;37m"<<piece[1]<<"  \033[0m";
				}
				else if(piece[0] == 'b'){
					cout << "\033[1;30m"<<piece[1]<<"  \033[0m";
				}	
				else{
					//cout<<piece<<"  ";
					cout << "\033[1;32m"<<piece<<"  \033[0m";
				}
			}
			cout<<"\033[1;36m"<<row+1<<"\033[0m"<<endl; //swap this line when done, used for testing
			//cout<<row<<endl;
		}
		for(char a = 'a'; a<='h'; ++a){
			cout << "\033[1;35m"<<a<<"  \033[0m";
		}
		string turnStr;
		if(whiteTurn){
			turnStr = "WHITE";
		}
		else{
			turnStr = "BLACK";
		}
		cout<<endl<<"Turn: "<<turnStr<<endl;
	}

	~gamestate(){}

};
/*
int main(){
	gamestate g;
	g.board[5][6] = 0;
	g.board[0][2] = 3;
	g.print();
	//cout<< g.isMove(0,2,4,7) << " : valid diagonal"<< endl;
	cout<< g.isMove("a3", "e8")<< " : is move\n";
	cout << g.isCheck(2,0,0,2) << endl;
	cout << g.isCheck(1,1,1,2) << endl;

}
*/






//Not used in current model, may be expanded and used in the future for the AI or GUI
class piece
{
	bool white; //black if false, white if true
	pair <int,int> pos; //pos on board from 0,0 - 7,7
	
	public:
	piece(bool newWhite, int posx, int posy)
		:white(newWhite),pos(posx,posy){}

	pair <int,int> getPos(){
		return pos;
	}
	bool isWhite(){
		return white;
	}
	virtual const char * type(){
		return "This should never print since it's a virtual function\n";
	}
};
class pawn : public piece
{
	public:
	pawn (bool newWhite,int posx,int posy)
		:piece(newWhite,posx,posy){}
	void printWhite(){
		if(isWhite()){
			cout<<"It's white\n";
		}
		else
			cout<<"It's black\n";
	}
};
