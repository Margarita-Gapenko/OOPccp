#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Base.h"
#include "Container.h"

class IncorrectRect : public std::exception {};

class IncorrectValue : public std::exception {};

class Shape : public Named {

public:
	Shape() : Named( "" ) {
		sm_count++;
	}
	Shape( std::string name) : Named( name ) {
		sm_count++;
	}
	~Shape() {
		sm_count--;
	}
	virtual void Print( std::ostream & out ) {
		out << std::endl;
	}
	static int GetCount() {
		return sm_count;
	}
private:
	static int sm_count;
};

int Shape::sm_count;

static std::ostream & operator<< ( std::ostream & out, Shape * obj ) {
	obj -> Print( out );
	return out;
}

class Point : public Shape {
public:
	Point() : Shape( "Point" ) {
		m_x = 0;
		m_y = 0;
	}
	Point( double const & x, double const & y ) : Shape( "Point" ) {
		m_x = x;
		m_y = y;
	}
	Point operator = ( Point const & p ) {
		if (this != & p) {
			m_x = p.m_x;
			m_y = p.m_y;
		}
		return * this;
	}
	Point operator = ( int const & p ) {
		m_x = p;
		m_y = p;
		return * this;
	}
	Point operator + ( Point const & p1 ) {
		Point p2 = Point( 0, 0 );
		p2.m_x = m_x + p1.m_x;
		p2.m_y = m_y + p1.m_y;
		return p2;
	}
	Point operator - ( Point const & p1 ) {
		Point p2 = Point( 0, 0 );
		p2.m_x = m_x - p1.m_x;
		p2.m_y = m_y - p1.m_y;
		return p2;
	}
	bool operator == ( Point const & p ) const {
		return ( ( m_x == p.m_x ) && ( m_y == p.m_y ) );
	}
	bool operator != ( int const & p ) {
		return ( ( m_x != p ) || ( m_y != p ) );
	}
	double GetX() const {
		return m_x;
	}
	double GetY() const {
		return m_y;
	}
	void SetX( double const & x ) {
		m_x = x;
	}
	void SetY( double const & y ) {
		m_y = y;
	}
	void Print( std::ostream & out ) {
		out << m_name << std::endl;
		out << "x = " << m_x << std::endl;
		out << "y = " << m_y << std::endl;
	}
private:
	double m_x;
	double m_y;
};

class Circle : public Shape {
public: 
	Circle( Point const & center, double const & radius ) : Shape( "Circle" ) {
		if ( radius <= 0 )
			throw IncorrectValue();
		m_center = center;
		m_radius = radius;
	}
	double Length() {
		return 2 * m_radius * M_PI;
	}
	void SetCenter (Point const & center) {
		m_center = center;
	}
	void SetRadius( double const & radius ) {
		m_radius = radius;
	}
	Point GetCenter() const {
		return m_center;
	}
	double GetRadius() const {
		return m_radius;
	}
	double Area() {
		return M_PI * pow( m_radius, 2 );
	}
	void Print( std::ostream & out ) {
		out << m_name << std::endl;
		out << "Center: " << "x = " << m_center.GetX() << ", y = " << m_center.GetY() << std::endl;
		out << "Radius = " << m_radius << std::endl;
		out << "Length = " << Length() << std::endl;
		out << "Area = " << Area() << std::endl;
	}
private:
	Point m_center = Point( 0, 0 );
	double m_radius;
};

class Rect : public Shape {
public:
	Rect ( Point const & ld, Point const & ru) : Shape( "Rect" ) {
		if ( ( ld.GetX() > ru.GetX() ) || ( ld.GetY() > ru.GetY() ) )
			throw IncorrectRect();
		m_vert_side = ru.GetY() - ld.GetY();
		m_hor_side = ru.GetX() - ld.GetX();
	}
	void SetVertSide( double const & vs ) {
		m_vert_side = vs;
	}
	void SetHorSide( double const & hs ) {
		m_hor_side = hs;
	}
	double GetVertSide() const {
		return m_vert_side;
	}
	double GetHorSide() const {
		return m_hor_side;
	}
	double Perimetår() {
		return 2 * m_vert_side + 2 * m_hor_side;
	}
	double Area() {
		return m_vert_side * m_hor_side;
	}
	void Print( std::ostream & out ) {
		out << m_name << std::endl;
		out << "a = " << m_vert_side << std::endl;
		out << "b = " << m_hor_side << std::endl;
		out << "Perimetr = " << Perimetår() << std::endl;
		out << "Area = " << Area() << std::endl;
	}
protected:
	double m_vert_side;
	double m_hor_side;
};

class Square : public Rect {
public: 
	Square( Point const & ld, double const & side ) : Rect( ld, Point( ld.GetX()+ side,  ld.GetY() +  side ) ) {
		if ( side <= 0 )
			throw IncorrectValue();
		m_name = "Square";
		m_side = side;
	}
	void SetSide( double const & s) {
		m_side = s;
	}
	double GetSide() const {
		return m_side;
	}
	void Print( std::ostream & out ) {
		out << m_name << std::endl;
		out << "a = " << m_side << std::endl;
		out << "Perimetr = " << Perimetår() << std::endl;
		out << "Area = " << Area() << std::endl;
	}
private:
	double m_side;
};

class Polyline : public Shape {
public:
	Polyline( Point const & start_point ) : Shape( "Polyline" ) {
		m_points.PushBack( start_point );
	}
	void AddPoint( Point const & point ) {
		m_points.PushBack( point );
	}
	double Dist( Point const & p1, Point const & p2 ) const {
		return sqrt( pow( p1.GetX() - p2.GetX(), 2.0 ) + pow( p1.GetY() - p2.GetY(), 2.0 ) );
	}
	double Length() {
		double l = 0;
		for( int i = 0; i < m_points.AllSize() - 1; i++ ) {
			l += Dist( m_points[ i ], m_points[i + 1] );
		}
		return l;
	}
	void Print( std::ostream & out ) {
		out << m_name << std::endl;	
		out << m_points.AllSize() << " vertices:" << std::endl;
		for( int i = 0; i < m_points.AllSize(); i++ ) {
			out << "x = " << m_points[ i ].GetX() << ", y = " << m_points[ i ].GetY() << std::endl;
		}
		out << "Length = " << Length() << std::endl;
	}
protected:
	Container<Point> m_points;
};

class Polygone : public Polyline {
public: 
	Polygone( Point const & p1, Point const & p2, Point const & p3 ) : Polyline( p1 ) {
		m_name = "Polygone";
		m_points.PushBack( p2 );
		m_points.PushBack( p3 );
	}
	double Perimeter() {
		return Length() + Dist( m_points.Head(), m_points.Tail() );
	}
	void Print( std::ostream & out ) {
		out << m_name << std::endl;
		out << m_points.AllSize() << " vertices:" << std::endl;
		for( int i = 0; i < m_points.AllSize(); i++ ) {
			out << "x = " << m_points[ i ].GetX() << ", y = " << m_points[ i ].GetY() << std::endl;
		}
		out << "Perimeter = " << Perimeter() << std::endl;
	}
};