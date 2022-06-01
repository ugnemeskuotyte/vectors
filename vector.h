#pragma once
//vektorius kurtas pagal cplusplus.com vector class documentation:
// https://www.cplusplus.com/reference/vector/vector/
#include <iostream>
#include <assert.h>
#include <limits.h>

using std::cout;
using std::endl;

template <typename T> 
class vector 
{
public:
	typedef T value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* iterator;
	typedef const value_type* const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;

private:
	iterator Data = nullptr;
	size_type Size = 0;
	size_type Capacity = 0;

public:

	//konstruktoriai
	vector() {}; //empty constructor
	vector(const vector& x) //copy constructor
	{
		this->Size = x.Size;
		this->Capacity = x.Capacity;
		this->Data = new value_type[Size];
		for (size_type i = 0; i < Size; i++)
		{
			Data[i] = x.Data[i];
		}
	}
	vector(vector&& x) //move constructor
	{
		this->Size = x.Size;
		this->Capacity = x.Capacity;
		this->Data = new value_type[Size];
		Data = x.Data;
		x.Data = nullptr;
	}
	vector(std::initializer_list<value_type> il) //initializer list constructor
	{
		ReAlloc(il.size());
		Size = il.size();
		for (size_type i = 0; i < Size; i++)
			::new(&Data[i]) T();
		std::move(il.begin(), il.end(), Data);
	}

	//destruktorius
	~vector()
	{
		//clear();
		::operator delete(Data, Capacity * sizeof(T));
	};

	//operator=
	vector& operator=(const vector& x) //copy assignement
	{
		if (&x == this)
			return *this;
		this->Size = x.Size;
		this->Capacity = x.Capacity;
		this->Data = new value_type[Size];
		std::copy(x.begin(), x.end(), Data);
		return *this;
	}
	vector& operator=(vector&& x) //move assignement
	{
		if (x == this)
			return *this;
		this->Size = x.Size;
		this->Capacity = x.Capacity;
		this->Data = new value_type[Size];
		this->Data = x.Data;
		x.Data = nullptr;
		return *this;
	}
	vector& operator=(std::initializer_list<value_type>il) //initializer list assignment
	{
		ReAlloc(il.size());
		Size = il.size();
		std::move(il.begin(), il.end(), Data);
		return *this;
	}

	//iterators
	iterator begin() { return Data; }
	const_iterator begin() const { return Data; }
	iterator end() { return Data + Size; }	
	const_iterator end() const { return Data + Size; }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return reverse_iterator(begin()); }
	
	//Capacity
	size_type size() const { return Size; }
	size_type max_size() const { return std::numeric_limits<difference_type>::max() / sizeof(value_type); }
	void resize(size_type n)
	{
		if (n < 0)
			throw std::invalid_argument("Invalid size");
		if (n > Size)
		{
			ReAlloc(n);
			for (size_type i = Size; i < n; i++)
				::new(&Data[i]) T();
		}
		else if (n < Size)
		{
			for (size_type i = n + 1; i <= Size; i++)
				Data[i].~T();
		}
		Size = n;
	}
	void resize(size_type n, const value_type& val) 
	{
		if (n < 0)
			throw std::invalid_argument("Invalid size");
		if (n > Size)
		{
			ReAlloc(n);
			for (size_type i = Size; i < n; i++)
				::new(&Data[i]) T(val);
		}
		else if (n < Size)
		{
			for (size_type i = n + 1; i <= Size; i++)
				Data[i].~T();
		}
		Size = n;
	}
	size_type capacity() const { return this->Capacity; }
	bool empty() const { return Size = 0; }
	void reserve(size_type n)
	{
		if (n > this->Capacity)
			this->Capacity = n;
	}
	void shrink_to_fit()
	{
		if (Size < Capacity)
			ReAlloc(Size);
		Capacity = Size;
	}

	// Element access
	reference operator[] (size_type n) { return Data[n]; }
	const_reference operator[] (size_type n) const { return Data[n]; }
	reference at(size_type n)
	{
		if (n >= Size)
			throw std::out_of_range("out of range");
		return Data[n];
	}
	const_reference at(size_type n) const
	{
		if (n >= Size)
			throw std::out_of_range("out of range");
		return Data[n];
	}
	reference front()
	{
		if (Size == 0)
			throw std::invalid_argument("Vector is empty");
		return Data[0];
	}
	const_reference front() const
	{
		if (Size == 0)
			throw std::invalid_argument("Vector is empty");
		return Data[0];
	}
	reference back()
	{
		if (Size == 0)
			throw std::invalid_argument("Vector is empty");
		return Data[Size - 1];
	}
	const_reference back() const
	{
		if (Size == 0)
			throw std::invalid_argument("Vector is empty");
	}
	iterator data() { return Data; }
	const_iterator data() const { return Data; }

	// Modifiers
	void assign(size_type n, const value_type& val) //fill version
	{
		this->Capacity = n;
		this->Size = n;
		this->Data = new value_type[n];
		for (size_type i = 0; i < n; i++)
			Data[i] = val;
	}
	void assign(std::initializer_list<value_type>il) //initializer list
	{
		ReAlloc(il.size());
		Size = il.size();
		for (size_type i = 0; i < Size; i++)
			::new(&Data[i]) T();
		std::move(il.begin(), il.end(), Data);
	}
	void push_back(const_reference val)
	{
		if (Size >= Capacity)
			ReAlloc(Capacity * 2);
		new(&Data[Size + 1]) T(val);
	}
	void push_back(value_type&& val)
	{
		if (Size >= Capacity)
			ReAlloc(Capacity * 2);
		new(&Data[Size + 1]) T(val);
	}
	void pop_back()
	{
		if (Size > 0)
		{
			Data[Size - 1].~T();
			Size = Size - 1;
		}
	}
	iterator insert(iterator position, const const_reference val) //single element
	{
		if (position<begin() || position>end())
			throw std::out_of_range("Out of range");
		if (Size >= Capacity)
			ReAlloc(Capacity * 2);
		Size++;
		iterator naujas=new value_type[Capacity];
		iterator last = std::move(begin(), position, naujas);
		*last = val;
		std::move(position, end(), last + 1);
		Data = naujas;
		return last;
	}
	iterator insert(iterator position, size_type n, const_reference val) //fill
	{
		if (n == 0)
			return position;
		if (position<begin() || position>end())
			throw std::out_of_range("Out of range");
		Size += n;
		if (Size > Capacity)
			ReAlloc(Size);
		iterator naujas = new value_type[Capacity];
		iterator last = std::move(begin(), position, naujas);
		for (size_type i = 0; i < n; i++)
			*(last + i) = val;
		std::move(position, end(), last + n);
		Data = naujas;
		return last;
	}
	iterator insert(iterator position, std::initializer_list<value_type> il) //list
	{
		if (std::distance(il.begin(), il.end()) == 0)
			return position;
		if (position<begin() || position>end())
			throw std::out_of_range("Out of range");
		Size += std::distance(il.begin(), il.end());
		if (Size > Capacity)
			ReAlloc(Size);
		iterator naujas = new value_type[Capacity];
		iterator last = std::move(begin(), position, Data);
		std::move(il.begin(), il.end(), last);
		std::move(position, end(), last + std::distance(il.begin(), il.end()));
		Data = naujas;
		return last;
	}
	iterator erase(iterator position) //single element
	{
		std::move(position + 1, end(), Data + std::distance(Data, position));
		Size--;
		return position;
	}
	iterator erase(iterator first, iterator last) //range
	{
		std::move(last, end(), Data + std::distance(Data, first));
		Size -= std::distance(first, last);
		return first;
	}
	void swap(vector& x)
	{
		iterator temporary;
		temporary = this->Data;
		this->Data = x.Data;
		x.Data = temporary;

		size_type temporarySize = this->Size;
		this->Size = x.Size;
		x.Size = temporarySize;

		temporarySize = this->Capacity;
		this->Capacity = x.Capacity;
		x.Capacity = temporarySize;
	}
	void clear()
	{
		if (Data != nullptr)
		{
			for (size_type i = 0; i < Size; i++)
				Data[i].~T();
		}
		Size = 0;
	}
	template<class... Args>
	iterator emplace(iterator position, Args&&... args)
	{
		if (position< begin() || position>end())
			throw std::out_of_range("Out of range");
		if (Size >= Capacity)
			ReAlloc(Capacity * 2);

		Size++;
		iterator naujas = new value_type[Capacity];
		iterator last = std::move(begin(), position, naujas);
		new(last) T(args...);
		std::move(position, end(), last + 1);
		Data = naujas;
		return last;
	}
	template <class... Args>
	void emplace_back(Args&&... args)
	{
		if (Size >= Capacity)
			ReAlloc(Capacity * 2);
		new(&Data[Size++]) T(args...);
	}

	//bool operators
	bool operator<(const vector& x) const
	{
		for (size_type i = 0; i < std::min(Size, x.size()); i++)
		{
			if (at(i) != x.at(i))
				return (at(i) < x.at(i));
		}
		if (Size < x.size())
			return true;
		return false;
	}
	bool operator>(const vector& x) const
	{
		for (size_type i = 0; i < std::min(Size, x.size()); i++)
		{
			if (at(i) != x.at(i))
				return (at(i) > x.at(i));
		}
		if (Size > x.size())
			return true;
		return false;
	}
	bool operator<=(const vector& x) const
	{
		for (size_type i = 0; i < std::min(Size, x.size()); i++)
		{
			if (at(i) != x.at(i))
				return (at(i) <= x.at(i));
		}
		if (Size <= x.size())
			return true;
		return false;
	}
	bool operator>=(const vector& x) const
	{
		for (size_type i = 0; i < std::min(Size, x.size()); i++)
		{
			if (at(i) != x.at(i))
				return (at(i) >= x.at(i));
		}
		if (Size >= x.size())
			return true;
		return false;
	}
	bool operator==(const vector& x) const
	{
		if (Size != x.size)
			return false;
		for (size_type i = 0; i < Size; i++)
		{
			if (Data[i] != x.max_size.Data[i])
				return false;
		}
		return true;
	}
	bool operator!=(const vector& x) const
	{
		if (Size != x.size)
			return true;
		for (size_type i = 0; i < Size; i++)
		{
			if (Data[i] != x.max_size.Data[i])
				return true;
		}
		return false;
	}
private:
	void ReAlloc(size_type newCapacity)
	{
		if (newCapacity == 0)
			newCapacity = 2;
		T* naujas = (T*) ::operator new(newCapacity * sizeof(T));
		for (size_type i = 0; i < Size; i++)
			new(&naujas[i]) T(Data[i]);
		for (size_type i = 0; i < Size; i++)
			Data[i].~T();
		::operator delete(Data, Capacity * sizeof(T));
		Capacity = newCapacity;
		Data = naujas;
	}
};