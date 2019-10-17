//chmod 0777 chess.cpp -> give read and write permissions
#include <cmath>
#include <iostream>
#include <vector>
#include <unordered_map>
//#include <pair>
#include <string>
using namespace std;

int main(){

	unordered_map<int, vector<pair<int,int>>> pieces;
	pieces[0] = {make_pair(1,2),make_pair(3,5)};
	cout<<pieces[0][1].second<<endl;
	pieces[2].push_back(make_pair(10,2));
	cout<<pieces[2][0].first<<endl;
	cout<<pieces[0][0].first<<endl;



	/*
	//King Testing
	gamestate k;
	k.board[5][6] = 6;
	k.board[3][1] = 16;
	k.board[5][5] = 6;
	k.board[4][5] = 12;

	//k.print();


	cout<<"King works like a rook for 1 square\n";
	cout<<k.isMove("d2","e2")<<endl;
	cout<<k.isMove("d2","d1")<<endl;
	cout<<k.isMove("d2","c2")<<endl;
	cout<<k.isMove("d2","d3")<<endl;
	cout<<"\nKing works like a bishop for 1 square\n";
	cout<<k.isMove("d2","e3")<<endl;
	cout<<k.isMove("d2","e1")<<endl;
	cout<<k.isMove("d2","c3")<<endl;
	cout<<k.isMove("d2","c1")<<endl;

	k.board[2][3] = 16;

	k.print();

	cout<<"\nKing doesn't work like a rook for 2+ squares\n";
	cout<<k.isMove("c4","a5")<<endl;
	cout<<k.isMove("c4","a4")<<endl;
	cout<<k.isMove("c4","a3")<<endl;
	cout<<k.isMove("c4","a2")<<endl;
	cout<<"\nKing doesn't work like a bishop for 2+ squares\n";
	cout<<k.isMove("c4","d6")<<endl;
	cout<<k.isMove("c4","c6")<<endl;
	cout<<k.isMove("c4","b6")<<endl;
	cout<<k.isMove("c4","a6")<<endl;


	 Queen Testing
	gamestate g;
	g.board[4][3] = 5;
	g.board[3][3] = 15;
	g.board[3][0] = 0;
	g.board[3][7] = 0;
	//g.board[4][4] = 1;
	g.print();
	cout<<"Queen works like a rook:\n";
	cout<<g.isMove("e4","e7")<<endl;
	cout<<g.isMove("e4","e3")<<endl;
	cout<<g.isMove("e4","h4")<<endl;
	cout<<g.isMove("e4","d4")<<endl;

	cout<<"\nQueen works like a bishop:\n";
	cout<<g.isMove("e4","h7")<<endl;
	cout<<g.isMove("e4","f3")<<endl;
	cout<<g.isMove("e4","d3")<<endl;
	cout<<g.isMove("e4","b7")<<endl;

	cout<<"\nQueen fails like a rook:\n";
	cout<<g.isMove("e4","e8")<<endl;
	cout<<g.isMove("e4","e2")<<endl;
	cout<<g.isMove("e4","e4")<<endl;
	cout<<g.isMove("e4","b4")<<endl;

	cout<<"\nQueen fails like a bishop:\n";
	cout<<g.isMove("e4","h8")<<endl;
	cout<<g.isMove("e4","g2")<<endl;
	cout<<g.isMove("e4","c2")<<endl;
	cout<<g.isMove("e4","a8")<<endl;
	*/

}
