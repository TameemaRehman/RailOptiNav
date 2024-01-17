#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <windows.h>
#include <string>
#include <string.h>
#include <conio.h>
#include <cstring>
using namespace std;

template <typename U, typename T>
class HashNode {
public:
	T value;
	U key;
	HashNode* next;
	HashNode(U key, T value) {
		this->key = key;
		this->value = value;
		this->next = NULL;
	}
};

template <typename U, typename T, int TABLE_SIZE>
class HashMapTable {
private:
	HashNode<U, T>** htable;
public:
	HashMapTable() {
		htable = new HashNode<U, T> *[TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; i++)
			htable[i] = NULL;
	}
	int HashFunc(U k) {
		int sum = 0;
		for (int i = 0; i < k.size(); i++) {
			sum += k[i];
		}
		return sum % TABLE_SIZE;
	}
	void Insert(U key, T value) {
		HashNode <U, T>* newelement = new HashNode<U, T>(key, value);
		int index = HashFunc(key);
		if (htable[index] == NULL) {
			htable[index] = newelement;
		}
		else {
			HashNode<U, T>* temp = htable[index];
			while (temp->next) {
				temp = temp->next;
			}
			temp->next = newelement;
		}
	}
	T Access(U k) {
		int key = HashFunc(k);
		if (htable[key] != NULL) {
			HashNode<U, T>* temp = htable[key];
			bool found = false;
			while (temp) {
				if (temp->key == k) {
					found = true;
					break;
				}
				temp = temp->next;
			}
			if (found) {
				return temp->value;
			}
			else {
				return T();
			}
		}
		return T();
	}
	bool Searchkey(U username) {
		int key = HashFunc(username);
		if (htable[key] != NULL) {
			HashNode<U, T>* temp = htable[key];
			bool found = false;
			while (temp) {
				if (temp->key == username) {
					found = true;
					break;
				}
				temp = temp->next;
			}
			if (found) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}


	void Remove(U k) {
		int key = HashFunc(k);
		if (htable[key] != NULL) {
			HashNode<U, T>* temp = htable[key];
			HashNode<U, T>* prev = NULL;
			while (temp) {
				if (temp->key == k) {
					if (prev == NULL) {
						htable[key] = temp->next;
					}
					else {
						prev->next = temp->next;
					}
					delete temp;
					return;
				}
				prev = temp;
				temp = temp->next;
			}
		}
		cout << "ERROR! This value not in the hashmap\n";
		return;
	}
	void display() {
		for (int i = 0; i < TABLE_SIZE; i++) {
			cout << "Index: " << i << ": ";
			if (htable[i] != NULL) {
				HashNode<U, T>* temp = htable[i];
				while (temp) {
					cout << temp->value << " ";
					temp = temp->next;
				}
				cout << endl;
			}
			else {
				cout << "NULL" << endl;
			}
		}
	}

	~HashMapTable() {
		for (int i = 0; i < TABLE_SIZE; i++) {
			HashNode<U, T>* current = htable[i];
			while (current != NULL) {
				HashNode<U, T>* prev = current;
				current = current->next;
				delete prev;
			}
		}
		delete[] htable;
	}
};