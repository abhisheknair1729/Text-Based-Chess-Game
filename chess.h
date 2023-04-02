#include<iostream>
#include<vector>

enum class Color {black, white, inactive}; //inactive color refers to dummy pieces

struct IllegalMoveException{};

struct Position {
	int x; 
	int y;
	Position():x{0}, y{0} {}
	Position( int x, int y):x{x}, y{y} {}
	bool operator==(Position p);
};

bool Position::operator==(Position p){
	if(x==p.x && y==p.y){
		return true;
	}
	
	return false;
}

class Piece {
	public:
		Piece():color{Color::inactive}, is_king{false}, is_pawn{false} {}
		Piece(Color color):color{color}, is_king{false}, is_pawn{false} {}
		Piece(Color color, bool is_king, bool is_pawn):color{color}, is_king{is_king}, is_pawn{is_pawn} {}
		Color getColor();
		bool isKing() {return is_king;}
		bool isPawn() {return is_pawn;}
		virtual std::string name(){ return "Piece"; }
		virtual bool isLegalMotion(Position start, Position end);
	protected:
		Color color; // black/white
		bool is_king;
		bool is_pawn;
};

Color Piece::getColor(){
	return color;
}

bool Piece::isLegalMotion(Position start, Position end){
	return false;
}

class Pawn: public Piece {
	public:
	Pawn(Color color):Piece(color, false, true) {}
	std::string name(){ return "P"; }
	bool isLegalMotion(Position start, Position end);
};

bool Pawn::isLegalMotion(Position start, Position end){
	if( color == Color::white ){
		if(start.x == end.x){
			if( end.y == start.y + 1 ){
				return true;
			}
			else if( start.y == 1 && end.y == 3 ){
				return true;
			}
		}else if( (end.x-start.x>-2) && (end.x-start.x<2) ){
			return end.y==start.y+1;
		}

	}
	else{  // color == Color::black
		if(start.x == end.x){
			if( end.y == start.y - 1 ){
				return true;
			}
			else if( start.y == 6 && end.y == 4 ){
				return true;
			}
		}else if( (end.x-start.x>-2) && (end.x-start.x<2) ){
			return end.y==start.y-1;
		}

	}
	
	return false;
}

class Knight: public Piece {
	public:
	Knight(Color color):Piece(color) {}
	std::string name(){ return "H"; }
	bool isLegalMotion(Position start, Position end);
};

bool Knight::isLegalMotion(Position start, Position end){
	
	if( start == end ){  //base case
		return false;
	}

	if( ((end.x == start.x+1) || (end.x == start.x-1) ) && ((end.y == start.y+2) || (end.y == start.y-2))){
		return true;
	}
	if( ((end.x == start.x+2) || (end.x == start.x-2) ) && ((end.y == start.y+1) || (end.y == start.y-1))){
		return true;
	}
	return false;
}

class Bishop: public Piece {
	public:
	Bishop(Color color): Piece(color) {}
	std::string name(){ return "B"; }
	bool isLegalMotion(Position start, Position end);
};

bool Bishop::isLegalMotion(Position start, Position end){
	int diffx = end.x - start.x;
	int diffy = end.y - start.y;
	int absdiffx = diffx>0?diffx:-1*diffx;
	int absdiffy = diffy>0?diffy:-1*diffy;
	if( start == end ){  //base case
		return false;
	}

	if( absdiffy/absdiffx == 1 ){
		return true;
	}

	return false;
}

class Rook: public Piece {
	public:
	Rook(Color color): Piece(color) {}
	std::string name(){ return "R"; }
	bool isLegalMotion(Position start, Position end);
};

bool Rook::isLegalMotion(Position start, Position end){
	if( start == end ){  //base case
		return false;
	}

	if(end.x == start.x || end.y == start.y){
		return true;
	}

	return false;
}

class Queen: public Piece {
	public:
	Queen(Color color): Piece(color) {}
	std::string name(){ return "Q"; }
	bool isLegalMotion(Position start, Position end);
};

bool Queen::isLegalMotion(Position start, Position end){
	
	int diffx = end.x - start.x;
	int diffy = end.y - start.y;
	int absdiffx = diffx>0?diffx:-1*diffx;
	int absdiffy = diffy>0?diffy:-1*diffy;
	
	if( start == end ){  //base case
		return false;
	}
	
	if( absdiffy/absdiffx == 1 ){
		return true;
	}
	if(end.x == start.x || end.y == start.y){
		return true;
	}

	return false;
}

class King: public Piece {
	public:
	
	King(Color color):Piece(color, true, false) {}
	std::string name(){ return "K"; }
	bool isLegalMotion(Position start, Position end);
	//King(Color color):color{color}, is_king{true} {}
};

bool King::isLegalMotion(Position start, Position end){
	int diffx = end.x - start.x;
	int diffy = end.y - start.y;
	int absdiffx = diffx>0?diffx:-1*diffx;
	int absdiffy = diffy>0?diffy:-1*diffy;
	
	if( start == end ){  //base case
		return false;
	}
	
	if( (absdiffx < 2) && (absdiffy < 2) ){
		return true;
	}

	return false;
}

class ChessBoard {
	public:
		ChessBoard();
		bool isPositionOccupied(Position& p);
		bool isMotionObstructed(Piece& p, Position& start, Position& end);
		bool isLegalMove(Piece& p, Position& start, Position& end);
		void printBoard(); //getter
		bool makeMove(std::string turn, Position& start, Position& end); //setter
		//bool isCheck(Color c);
	private:
		std::vector<std::vector<Piece*>> board;
};

ChessBoard::ChessBoard(){
	for(auto i=0; i<8; i++){
		std::vector<Piece*> row;
		for(auto j=0; j<8; j++){
			if( i==0 || i==7 ){
				Color c = i==0?Color::white:Color::black;
				if(j==0 || j==7){
					Rook *r = new Rook(c);
					row.push_back(r);
				}
				else if(j==1 || j==6){
					Knight *h = new Knight(c);
					row.push_back(h);
				}
				else if(j==2 || j==5){
					Bishop *b = new Bishop(c);
					row.push_back(b);
				}
				else if(j==3){
					Queen *q = new Queen(c);
					row.push_back(q);
				}
				else if(j==4){
					King *k = new King(c);
					row.push_back(k);
				}
			}
			else if( i==1 || i==6 ){
				Color c = i==1?Color::white:Color::black;
				Pawn *p = new Pawn(c);
				//std::cout<<(p.getColor()==Color::inactive?"True":"False") << "\n";
				row.push_back(p);
			}
			else{   // Dummy pieces
				Piece *p = new Piece();
				row.push_back(p);
			}
		}
		board.push_back(row);
	}
}

bool ChessBoard::isPositionOccupied(Position& p){
	if(board[p.y][p.x]->getColor() == Color::inactive){
		return false;
	}
	
	return true;
}

bool ChessBoard::isMotionObstructed(Piece &p, Position& start, Position& end){
	
	Color c = p.getColor();

	// cannot place piece on top of piece of same color
	if( board[end.y][end.x]->getColor() != Color::inactive ){
		if( board[end.y][end.x]->getColor() == c ){
			return true;
		}
	}
	
	/* Check if motion is that of knight. Knight is never obstructed
	 * except when destination has same color as knight */

	if( ((end.x == start.x+1) || (end.x == start.x-1) ) && ((end.y == start.y+2) || (end.y == start.y-2))){
		return false;
	}
	if( ((end.x == start.x+2) || (end.x == start.x-2) ) && ((end.y == start.y+1) || (end.y == start.y-1))){
		return false;
	}
	
	// Create path that the piece moves over
	std::vector<Position> path;
	if( start.x == end.x ){
		int s = start.y < end.y ? start.y : end.y;
		int e = start.y < end.y ? end.y : start.y;
		for(int i=s+1; i<e; i++){
			path.push_back(Position(start.x, i));
		}
	}
	else if( start.y == end.y ){
		int s = start.x < end.x ? start.x : end.x;
		int e   = start.x < end.x ? end.x : start.x;
		for(int i=s+1; i<e; i++){
			path.push_back(Position(i, start.y));
		}
	}
	else{   // diagonal piece movement
		int incx   = start.x > end.x ?-1:1;
		int incy   = start.y > end.y ?-1:1;
		int startx = start.x + incx;
		int starty = start.y + incy;
		
		while( !(startx==end.x && starty==end.y) ){
			path.push_back(Position(startx, starty));
			startx+=incx;
			starty+=incy;
		}

		if( p.isPawn() ){
			Color c = board[end.y][end.x]->getColor();
			if( c != p.getColor() && c != Color::inactive ){
				return false;
			}
			return true;
		}
	}
	
	for(auto pos: path){
		if(isPositionOccupied(pos)){
			return true;
		}
	}	

	return false;
};

bool ChessBoard::isLegalMove(Piece& p, Position& start, Position& end){
	
	//std::cout<<"Piece-wise Legal Motion: "<<p.isLegalMotion(start, end);
	//std::cout<<"Is Motion Obstructed: "<<isMotionObstructed(p.getColor(), start, end);

	if(p.isLegalMotion(start, end) && !isMotionObstructed(p, start, end)){
		return true;
	}

	return false;
}

void ChessBoard::printBoard(){
	std::cout<<"\n\n";
	for(int i=7; i>=0; i--){
		std::cout<<"\033[1;37m";
		std::cout<<i+1<<"\t";
		for(int j=0; j<8; j++){
			//display the piece
			if(board[i][j]->getColor() == Color::inactive){
				std::cout<<"\033[1;33m";
				std::cout<<".\t";
			}
			if(board[i][j]->getColor() == Color::black){
				std::cout<<"\033[1;34m";
				std::cout<<board[i][j]->name()<<"\t";
			}
			if(board[i][j]->getColor() == Color::white){
				std::cout<<"\033[1;37m";
				std::cout<<board[i][j]->name()<<"\t";
			}
		}
		std::cout<<"\n\n";
	}
	std::cout<<"\n\ta\tb\tc\td\te\tf\tg\th\n";
	std::cout<<"\n";
}

bool ChessBoard::makeMove(std::string turn, Position& start, Position& end){
	
	Color c = turn=="White"?Color::white:Color::black;
	
	if( board[start.y][start.x]->getColor() != c ){
		throw IllegalMoveException();	
	}else{
		if(isLegalMove(*board[start.y][start.x], start, end)){
			if(board[end.y][end.x]->isKing()){
				return true;
			}
			delete board[end.y][end.x];
			board[end.y][end.x] = board[start.y][start.x];
			Piece *p = new Piece();
			board[start.y][start.x] = p;
		}else{
			throw IllegalMoveException();
		}
	}
	return false;
}
