/*
Custom hash map creation 
*/
#include <cstdlib>
#include <string>
#include "hashMap.h"

using namespace std;

template <class t1, class t2>
hashMap<t1, t2>::hashMap(const hashMap<t1, t2>& copy)
{
	copyHashMap(copy);
}

template <class t1, class t2>
const hashMap<t1, t2>& hashMap<t1, t2>::operator=(const hashMap<t1, t2>& rhs)
{
	if (this != &rhs)
	{
		deallocateHashMap();
		copyHashMap(rhs);
	}

	return *this;
}

template <class t1, class t2>	
hashMap<t1, t2>::~hashMap()
{// destructor
	deallocateHashMap();
}

template <class t1, class t2>
t2& hashMap<t1, t2>::operator[](t1 key)
{
	static bool recurseCall = false;
	static size_t index;

	if(!recurseCall)
	{
	if(filledEntries*100/size>= 20)
	{
		resize();
	}// index using the hash
		index = hash(key) % size;
	}
// search for key in linked list at table[index]
	node*curr = table[index];
	int nodeCount = 0;
	while(curr!=nullptr)
	{
		nodeCount++;
		if(curr->key == key)
		{// key is found we return value
			recurseCall = false;
			return curr->value;
		}
		curr = curr->link;
	}
	// if key not found insert node
	if((index%2 == 0 && nodeCount < 2) || (index %2 == 1 && nodeCount <3))
	{// insert our new node
		table[index] = new node(key, t2(), table[index]);
		filledEntries++;
	// return reference of inserted value
		recurseCall = false;
		return table[index]-> value;
	}
	else{// if linked list location is full update index
		recurseCall = true;
		index = (index+1)%size;
		return operator[](key);// recurse for insertion updated index
	}
}

template <class t1, class t2>
void hashMap<t1, t2>::resize()
{//(*this)
	size_t newSize = size*2;// double hash table size
	node** tableNew = new node*[newSize];
	size_t oldFilledEntries = filledEntries;
	// initialize our new table to nullptr
	for(size_t i = 0; i < newSize; i++)
		tableNew[i] = nullptr;
	// rehash the existing elements into our new table
	for(size_t i = 0; i<size; i++)
	{// itterate through old table
		node*curr = table[i];// pointer head of linked list
		while(curr!=nullptr)
		{
			t1 key = curr->key;
			t2 value = curr->value;
			size_t newIndex = hash(key) % newSize;
			// make sure not null before access
			if(tableNew[newIndex]== nullptr)
			{
				tableNew[newIndex] = new node(key,value);
			}else{
				node* newNode = new node(key,value,tableNew[newIndex]);
				tableNew[newIndex] = newNode;
			}
			curr = curr->link;
		}
	}
	// deallocte our old table
	deallocateHashMap();
	table = tableNew;
	size = newSize;
	filledEntries = oldFilledEntries;
}


template <class t1, class t2>
void hashMap<t1, t2>::copyHashMap(const hashMap<t1, t2>& otherMap)
{// deep copy constructor 
	size = otherMap.size;// copys size of other map
	
	filledEntries = otherMap.filledEntries;// copy the number of filled entries

	table = new node*[size]; // allocate for new hash table
	
	for(size_t i = 0; i <size; ++i)
	{
		if(otherMap.table[i] != nullptr)
		{// copy first node// gets object
			table[i] = new node(*otherMap.table[i]);
		// copy rest of list
			node*currOther = otherMap.table[i]->link;
			node* currNew = table[i];

			while(currOther!= nullptr)
			{// deep copy// change to new linked list
				currNew->link = new node(*currOther);
				currNew = currNew->link;
				currOther = currOther->link;
			}
		}
		else{
			table[i]= nullptr;// if bucket in other map is empty we fix ours
		}
	}
}

template <class t1, class t2>
void hashMap<t1, t2>::deallocateHashMap()
{
	// deallocate mem in each node 4 table
	for(size_t i = 0; i < size; i++)
	{// pointer to head index i 
		node* curr = table[i];
		// itterate 
		while(curr!= nullptr)
		{// pointer to next node
			node*next = curr->link;
			delete curr;// delete curr
			curr = next;// move to the next node
		}
		table[i] = nullptr;
	}// DEALLOACATE
	delete[] table;
	table = nullptr;
	size = 0;
	filledEntries = 0;
}
