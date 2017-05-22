#pragma once
#include <string>
#include <cstdlib>
#include <ctime>
#include "Shapes.h"

class IncorrectKey : public std::exception {};

class Factory {
public:
	Factory() {}
	Shape * Make(int key) {
		if( key == 0 ) {
			return new Point( RandPoint() );
		}
		else if( key == 1 ) {
			return new Circle( RandPoint(), RandPosInt() );
		}
		else if( key == 2 ) {
			Point tmp = RandPoint();
			return new Rect( tmp, Point( tmp.GetX() + RandPosInt(), tmp.GetY() + RandPosInt() ) );
		}
		else if( key == 3 ) {
			return new Square( RandPoint(), RandPosInt() );
		}
		else if( key == 4 ) {
			int n = (int)( std::rand() % 20 + 1 );
			Polyline * pl = new Polyline( RandPoint() );
			for( int i = 0; i < n; i++ ) {
				pl -> AddPoint( RandPoint() );
			}
			return pl;
		}
		else if( key == 5 ) {
			int n = (int)( std::rand() % 20 + 3 );
			Polygone * pg = new Polygone( RandPoint(), RandPoint(), RandPoint() );
			for( int i = 0; i < n; i++ ) {
				pg -> AddPoint( RandPoint() );
			}
			return pg;
		}
		else {
			throw IncorrectKey();
		}
		
	}
	Point RandPoint() {
		return Point( RandInt(), RandInt() );
	}

	int RandInt() {
		return (int)( std::rand() % 21 - 10 );
	}

	int RandPosInt() {
		return (int)( std::rand() % 10 + 1 );
	}
};



