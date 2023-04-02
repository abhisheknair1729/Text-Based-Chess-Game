#include<iostream>
#include "chess.h"

Position string_to_position(std::string& s){

	Position pos;
	switch(s[0]){
		case 'a': 
			pos.x = 0;
			break;
		case 'b':
			pos.x = 1;
			break;
		case 'c':
			pos.x = 2;
			break;
		case 'd':
			pos.x = 3;
			break;
		case 'e':
			pos.x = 4;
			break;
		case 'f':
			pos.x = 5;
			break;
		case 'g':
			pos.x = 6;
			break;
		case 'h':
			pos.x = 7;
			break;
	}

	switch(s[1]){
		case '1': 
			pos.y = 0;
			break;
		case '2':
			pos.y = 1;
			break;
		case '3':
			pos.y = 2;
			break;
		case '4':
			pos.y = 3;
			break;
		case '5':
			pos.y = 4;
			break;
		case '6':
			pos.y = 5;
			break;
		case '7':
			pos.y = 6;
			break;
		case '8':
			pos.y = 7;
			break;
	}
	
	return pos;
}

int main(){

	ChessBoard chess;
	std::string start_str, end_str;

	std::cout<<"Welcome to Terminal-based Chess Game\nEnter moves as start-position [space] end-position\n";
	std::cout<<"White to start play\n";
	
	std::string turn = "White";
	int turn_count = 0;
	
	while(true){
		chess.printBoard();	
		std::cout<<turn<<"'s turn\n";
		std::cout<<"Enter Move\t";
		std::cin>>start_str>>end_str;
		
		Position start = string_to_position(start_str);
		Position end   = string_to_position(end_str);

		try{
			bool result = chess.makeMove(turn, start, end);
			if( result ){
				std::cout<< "Game Over! "<<turn<<" wins the game!\n";
				break;
			}
		}catch(IllegalMoveException e) {
			//handle exception
			std::cout<<"\nIllegal Move! Please try again!\n";
			continue;
		}
		
		turn_count++;

		if(turn_count%2 == 0)
			turn = "White";
		else
			turn = "Black";
	}	

}



