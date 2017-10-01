#pragma once

#ifndef NULL
#include <cstddef>
#endif // !NULL


/*
Node class with the modification that values are pointers
This makes sure that no local variables are accidentally deleted during the lifetime of the list
*/

template <typename T>
class node
{
public:
	T * value;			// Object held by the node
	node<T> * next;		// Next node in the list

	node(T * nodeValue, node<T> * nextNode = NULL)
	{
		value = nodeValue;
		next = nextNode;
	}

	~node()
	{
		delete value; // Free the object being held by the node
	}
};