#pragma once

template<class E>
class HashEntry {
private:
	int key;
	E value;
public:
	HashEntry(int key, E value) 
	{
		this->key = key;
		this->value = value;
	}

	int getKey() {
		return key;
	}

	E getValue() {
		return value;
	}
};


