#include <cstdlib>
#include <string>

#ifndef HASHMAP_H
#define HASHMAP_H

template <class t1, class t2>
class hashMap
{
private:
	struct node
	{
		t1 key;
		t2 value;
		node * link;

		node() : key(t1()), value(t2()), link(nullptr) {}
		node (t1 k) : key(k), value(t2()), link(nullptr) {}
		node (t1 k, t2 v) : key(k), value(v), link(nullptr) {}
		node (t1 k, t2 v, node * n) : key(k), value(v), link(n) {}
	};

	node ** table;
	std::size_t size;
	std::size_t filledEntries;
	void resize();
	void copyHashMap(const hashMap<t1, t2>&);
	void deallocateHashMap();

	std::size_t hash(const std::string& key) const
	{
		std::size_t hashValue = 5381;

    	for (char character : key)
        	hashValue = ((hashValue << 5) + hashValue) + static_cast<int>(character);

    	return hashValue;	
	}

public:
	hashMap() : size(5), filledEntries(0)
	{
		table = new node*[size];

		for (std::size_t i = 0; i < size; i++)
			table[i] = nullptr;
	}

	hashMap(std::size_t s) : size(s), filledEntries(0)
	{
		table = new node*[size];

		for (std::size_t i = 0; i < size; i++)
			table[i] = nullptr;
	}

	hashMap(const hashMap<t1, t2>&);
	const hashMap<t1, t2>& operator=(const hashMap<t1, t2>&);
	~hashMap();

	t2& operator[](t1);
};
#endif