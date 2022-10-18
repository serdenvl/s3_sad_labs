#pragma once

using val_type = unsigned int;

class just_stack
{
protected:
	val_type* buffer;
	size_t size;

	size_t length;

public:
	just_stack(size_t size) : size(size), length(0)
	{
		buffer = new val_type[size];
		*buffer = {};
	}

	~just_stack()
	{
		delete[] buffer;
	}

	void push(const val_type& val);
	val_type pop();

	val_type top() const;
	bool is_empty() const;
	bool is_full() const;

	void clear();
};
