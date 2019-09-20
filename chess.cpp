#include <iostream>
#include <string>
#include <cmath>
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
	
	//in future make board a private variable but for testing keep it public
	private:
	//int board [8][8];
	public:
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
		for(int i = 0; i<8; ++i){
			board[i][6] = 11; //all squares on 7 row are black pawn = 11
			board[i][1] = 1; //all swares on 2 row are white pawn = 1
		}
		for(int row = 2; row<6; ++row){
			for(int col = 0; col<8; ++col){
				board[col][row] = 0;
			}
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

		cout<<startx<<','<<starty<<" --> "<<endx<<','<<endy<<": ";
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
				
			default:
				return false;

		}
		return true;
	}
	
	void print(){
		//King = K, Queen = Q, Knight = N, Bishop = B, Rook = R, Pawn = P, Black = B, White = W
		string piece= "WP";
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
			//cout<<row+1<<endl; swap this line when done, used for testing
			cout<<row<<endl;
		}
		//for(char a = 'a'; a<='h'; ++a){ for testing
		for(int a = 0; a<8; ++a){
			//cout << "\033[1;35m"<<a<<"  \033[0m";
			cout<<a<<"  ";
		}
		cout<<endl<<endl;
	}

};

int main(){
	gamestate g;
	g.board[4][4] = 11;
	g.board[4][6] = 0;
	g.board[5][3] = 1;
	g.board[5][1] = 0;
	g.board[4][6] = 4;
	g.print();
	cout<<g.isMove("g8","e7")<<endl;
	//cout<<g.isMove("e5","f4")<<endl;
	//cout<<g.isMove("f4","e5")<<endl;
	//g.isOppositeOrEmpty(0,2,2,4);
}







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
