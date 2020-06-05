#pragma once
#pragma once
#include <iostream>
#include "HashEntry.h"
using namespace std;
#define DELETED new HashEntry(-99,-99)
const int TABLE_SIZE = 9000;
template<class E>
class HashMap {
private:
	HashEntry<E> **table;
	int numElementos;
	int primo;

public:
	HashMap() 
	{
		table = new HashEntry<E>*[TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; i++)
			table[i] = NULL;
		numElementos = 0;
		primo = HallarMejorPrimo();
	}

	~HashMap() 
	{
		for (int i = 0; i < TABLE_SIZE; i++)
			if (table[i] != NULL)
				delete table[i];
		delete[] table;
	}

	void Hash(int key, E value) 
	{
		int NuevoIndex, i = 1;
		int hash = key % TABLE_SIZE;

		if (table[hash] == NULL) 
		{
			table[hash] = new HashEntry<E>(key, value);
			numElementos++;
		}
		else
		{
			int hash2 = primo - (key % primo);
			while (1)
			{
				NuevoIndex = ((hash + i * hash2) % TABLE_SIZE);

				if (table[NuevoIndex] == NULL)
				{
					table[NuevoIndex] = new HashEntry<E>(key, value);
					break;
				}
				i++;
			}
		}
	}

	int HallarMejorPrimo()
	{
		int mitad = TABLE_SIZE / 2;
		int PrimoMayor;
		int residuo, cont = 0;
		int aux = mitad;
		while (1)
		{
			aux++;
			for (int i = 1; i <= aux; i++)
			{
				residuo = aux % i;
				if (residuo == 0)
					cont++;
			}
			if (cont == 2)
			{
				PrimoMayor = aux;
				aux = mitad;
				cont = 0;
				break;
			}
			else { cont = 0; }
		}
		return PrimoMayor;
		}

	E get(int key) {
		int hash = (key % TABLE_SIZE);
		return table[hash]->getValue();
		
	}

	int get_key(int key)
	{
		int hash = (key % TABLE_SIZE);
		if (table[hash] == NULL) 
		{
			return -1;
		}
		else 
		{
			return hash;
		}
	}

	
};
