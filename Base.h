#pragma once
#include <string>

class Printable {
public:
	virtual void Print( std::ostream & out ) = 0;
};

class Named : Printable {
public:
	Named( std::string name ) {
		m_name = name;
	}
protected:
	std::string m_name;
};