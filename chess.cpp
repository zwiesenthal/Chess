#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
class gamestate
{
   	//int board [8][8];
	//board will hold int that says what piece is on the spot
	//0 empty, 1-6 = white, 11-16 = black
	//1 pawn, 2 knight, 3 bishop, 4 rook, 5 queen, 6 king -----------WHITE PIECES
	//11 pawn, 12 knight, 13 bishop, 14 rook, 15 queen, 16 king -----BLACK PIECES
	public:
	int board [8][8];
	gamestate(){//board[y][x] 
		board[0][0] = 14; //a8 black pieces below
		board[0][1] = 12; //b8
		board[0][2] = 13; //c8
		board[0][3] = 15; //d8 
		board[0][4] = 16; //e8
		board[0][5] = 13; //f8
		board[0][6] = 12; //g8
		board[0][7] = 14; //h8

		board[7][0] = 4; //a8 white pieces below
                board[7][1] = 2; //b8
                board[7][2] = 3; //c8
                board[7][3] = 5; //d8
                board[7][4] = 6; //e8
                board[7][5] = 3; //f8
                board[7][6] = 2; //g8
                board[7][7] = 4; //h8
		for(int i = 0; i<8; ++i){
			board[1][i] = 11; //all squares on 7 row are black pawn = 11
			board[6][i] = 1; //all swares on 2 row are white pawn = 1
		}
		for(int row = 2; row<6; ++row){
			for(int col = 0; col<8; ++col){
				board[row][col] = 0;
			}
		}
				
	}
	bool isMove(string start, string end){
		//return if move is possible
		if(start[0] < 'a' || start[0] > 'h' || start[1] < '1' || start[1] > '8' ||
			end[0] <'a' || end[0] > 'h' || end[1] < '1' || end[1] > '8'){
			return false; //invalid input
		}
		int starty = start[0]-'a'; //y,x
		int startx = start[1]-'1'; //start x and start y are position on board of start
		int endy = end[0] -'a';
		int endx = end[1] -'1'; 

		cout<<starty<<','<<startx<<' '<<endy<<','<<endx<<endl;
		switch(board[startx][starty])
		{
			case 0: //empty
				return false;
			case 1: //white pawn
				if(starty == 1){ //at start position
					if(startx == endx && board[endx][endy] == 0 &&  4<= endy <=5){
						return true;//pawn hasn't moved yet and tries to go to empty spot
					}
					else if(startx == endx && board[endx][endy] == 0 && endy == starty -1)
						return true;//not at start spot but try to move one up to empty
					else if((endx == startx +1||endx == startx-1) && endy == starty -1 && 10 < board[endx][endy] < 17)
						return true; //pawn able to capture
					else
						return false; //isn't moving up 1 or 2 if at start or attacking piece, ampesaunt later
				}
			default:
				return false;

		}
		return true;
	}
	
	void print(){
		//King = K, Queen = Q, Knight = N, Bishop = B, Rook = R, Pawn = P, Black = B, White = W
		//Ex. White Bishop = WB, Black Knight = BN
		//int val;
		string piece= "WP";
		for(int row = 0; row < 8; ++row){
			for(int col = 0; col < 8; ++ col){
				//val = board[row][col];
				switch(board[row][col])
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
			cout<<8-row<<endl;
		}
		for(char a = 'a'; a<='h'; ++a){
			//cout << "\033[1;35m"<<a<<"  \033[0m";
			cout<<a<<"  ";
		}
		cout<<endl<<endl;
	}

};

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
		return "This should never print since its virtual function\n";
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

int main(){
	gamestate g;
	g.print();
	g.board[6][4] = 0;
	g.board[4][4] = 1;
	g.print();
	cout<<g.isMove("e4","e5")<<endl;
	cout<<g.isMove("e4","e6")<<endl;
	cout<<g.isMove("e4","f5")<<endl;
	cout<<g.isMove("e4","f3")<<endl;

	//cout<<g.isMove("e2","e4")<<endl;
	//cout<<g.isMove("a3","a4")<<endl;	
	
}
