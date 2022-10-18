#include "just_stack.h"

#include <iostream>
using namespace std;

void just_stack::push(const val_type& val)
{
	if (is_full())
		throw "push() when stack is full";

	buffer[length] = val;
	++length;
}

val_type just_stack::pop()
{
	if (is_empty())
		throw "pop() when stack is empty";

	--length;
	return buffer[length];
}

val_type just_stack::top() const
{
	if (is_empty())
		throw "top() when stack is empty";
	return buffer[length-1];
}

bool just_stack::is_empty() const
{
	return length == 0;
}

bool just_stack::is_full() const
{
	return length == size;
}

void just_stack::clear()
{
	length = 0;
}
