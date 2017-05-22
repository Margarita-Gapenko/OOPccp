#pragma once

class OutOfRange : public std::exception {};

class EmptyContainer : public std::exception {};


template<typename T>
class Container {
public:
	Container() {
		m_head = NULL;
		m_tail = NULL;
		m_size = 0;
		m_is_empty = true;
	}

	~Container() {
		Clear();
	}

	T & operator [] ( int index ) const {
		Elem * elem = m_head;
		if(( index > 0 ) && ( index < m_size )) {
			for( int i = 1; i <= index; i++ ) {
				elem = elem -> m_next;
			}
			return elem -> m_val;
		}
		else if( 0 == index )
			return m_head -> m_val;
		else {
			throw OutOfRange();
		}
	}

	bool IsEmpty() {
		return m_is_empty;
	}

	void PushFront(T const & val) {
		Elem * new_elem = new Elem;
		new_elem -> m_val = val;
		if( !IsEmpty() ) {
			new_elem -> m_next = m_head;
			m_head -> m_prev = new_elem;
		}
		else {
			new_elem -> m_next = NULL;
			m_tail = new_elem;
			m_is_empty = false;
		}
		m_head = new_elem;
		m_head -> m_prev = NULL;
		m_size++;
	}

	void PushBack(T const & val) {
		Elem * new_elem = new Elem;
		new_elem -> m_val = val;
		if( !IsEmpty() ) {
			m_tail -> m_next = new_elem;
			new_elem -> m_prev = m_tail;
		}
		else {
			new_elem -> m_prev = NULL;
			m_head = new_elem;
			m_is_empty = false;
		}
		m_tail = new_elem;
		m_tail -> m_next = NULL;
		m_size++;
	}

	T PopFront() {
		if( !IsEmpty() ) {
			Elem * new_elem = m_head;
			T val = new_elem -> m_val;
			m_head = new_elem -> m_next;
			if( NULL != m_head)
				m_head -> m_prev = NULL;
			delete new_elem;
			m_size--;
			m_is_empty = ( 0 == m_size ) ? true : false;
			return val;
		}
		else {
			throw EmptyContainer();
		}
	}

	T PopBack() {
		if( !IsEmpty() ) {
			Elem * new_elem = m_ tail;
			T val = new_elem -> m_val;
			m_tail = new_elem -> m_prev;
			if( NULL != m_tail )
				m_tail -> m_next = NULL;
			delete new_elem;
			m_size--;
			m_is_empty = ( 0 == size ) ? true : false;
			return val;
		}
		else {
			throw EmptyContainer();
		}
	}

	void Clear() {
		while( !IsEmpty() ) {
			PopFront();
		}
	}

	int AllSize() const {
		return m_size;
	}

	T & Head() {
		if( !IsEmpty() ) {
			return m_head -> m_val;
		}
		else {
			throw EmptyContainer();
		}
	}

	T & Tail() {
		if( !IsEmpty() ) {
			return m_tail -> m_val;
		}
		else {
			throw EmptyContainer();
		}
	}

	private:
		struct Elem {
			T m_val;
			Elem * m_next;
			Elem * m_prev;
		};
		Elem * m_head;
		Elem * m_tail;
		int m_size;
		bool m_is_empty;
};
