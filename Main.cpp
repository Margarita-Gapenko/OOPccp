#include <iostream>
#include "Container.h"
#include "Shapes.h"
#include "Factory.h"

int main() {
	Container< Shape * > container;
	std::srand( unsigned( std::time( 0 ) ) );
	for( int i = 0; i < 20; i++ ) {
		int shape_type = (int)( std::rand() % 6 );
			/* 
			0 - point
			1 - circle
			2 - rect
			3 - square
			4 - polyline
			5 - polygone		
			*/
		Factory f;
		try {
			Shape * s = f.Make( shape_type );
			container.PushBack( s );
		}
		catch ( IncorrectKey ) {
			std::cout << "Incorrect type of shape" << std::endl;
			return -3;
		}
		catch ( IncorrectRect ) {
			std::cout << "Incorrect points for creating a rect" << std::endl;
			return -4;
		}
		catch ( IncorrectValue ) {
			std::cout << "Incorrect value for creating a shape" << std::endl;
			return -5;
		}
	}
	std::cout << "Number of shapes: " << Shape::GetCount() << std::endl;
	std::cout << std::endl;
	
	int count = container.AllSize();

	try {
		for( int i = 0; i < count; i++ ) {
			Shape * s = container.PopFront();
			std::cout << s << std::endl;
			delete s;
		}
	}
	catch ( OutOfRange ) {
		std::cout << "Out of range" << std::endl;
		return -1;
	} 
	catch ( EmptyContainer ) {
		std::cout << "Container is empty" << std::endl;
		return -2;
	}

	container.Clear();
	std::cout << "Number of shapes: " << Shape::GetCount() << std::endl;

	int waiting;
	std::cin >> waiting;
	return 0;
}