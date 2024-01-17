#pragma once
#include <iostream>
#include <string>
using namespace std;

class Account {
private:
	//attributes
	string email;
	string username;
	long long int contact;
	string password;
public:
	//default constructor
	Account() {
		contact = 0;
	}
	//parameterized constructor
	Account(string e, string un, long long int c, string p) {
		email = e;
		username = un;
		contact = c;
		password = encryptPassword(p, 'K');
	}
	// member functions
	string encryptPassword(string password, char key);
	string decryptPassword(string encryptedPassword, char key);

	//accessors/getters
	string getEmail()const;
	string getUsername()const;
	long long int getContact()const;
	string getPassword();

	// setter/mutator functions
	void setEmail(const string e);
	void setUsername(const string un);
	void setContact(const long long int c);
	void setPass(const string p);


};

string Account::getEmail()const {
	return email;
}

string Account::getUsername()const {
	return username;
}

string Account::getPassword() {
	return decryptPassword(password, 'K');
}
long long int Account::getContact()const {
	return contact;
}

void Account::setEmail(const string e) {
	email = e;
}

void Account::setUsername(const string un) {
	username = un;
}


void Account::setContact(const long long int c) {
	contact = c;
}

void Account::setPass(const string p) {
	password = p;
}

string Account::encryptPassword(string password, char key) {
	string encryptedPassword = password;

	for (char& c : encryptedPassword) {
		c ^= key;
	}

	return encryptedPassword;
}

string Account::decryptPassword(string encryptedPassword, char key) {
	return encryptPassword(encryptedPassword, key); // XOR encryption and decryption are the same operation
}