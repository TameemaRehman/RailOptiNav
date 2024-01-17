#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <time.h>
#include <string>
#include <conio.h>
#include <cstring>
#include <chrono>
#include <thread>
#include "HashTable.h"
#include "Graphs.h"
#include "Account.h"
#include "PQ.h"
using namespace std;

//System class represent the basic flow of sign-up and login
//It shows the effective use of concept of Hashing
class System {
public:
	// Creation of HashMapTable(that uses chaining) with key considered as username 
	HashMapTable<string, Account, 20> htable;
	const int num_of_trains = 5;
	Train train[5] = { Train("Celestial Express"), Train("Quantum Voyager"), Train("Nebula Navigator"),
					  Train("Stellar Odyssey"), Train("Galaxy Explorer") };
	int seats;

	void login_signup() {

		cout << "[1] Log In to an Existing Account\n[2] Sign Up for a New Account\n\nSelect: ";
		int choice;
		cin >> choice;

		while (choice < 1 || choice > 2) {
			cout << "Invalid Choice! Enter Again" << endl;
			cin >> choice;
		}

		if (choice == 2) {
			string username, password, email;
			long long int contact;
			system("cls");
			cout << "Please Provide the Details for Account Generation:\n" << endl;
			cout << "Username: ";
			cin >> username;
			while (htable.Searchkey(username)) {
				cout << "\nUsername already exists! Kindly Re-enter: ";
				cin >> username;
			}
			cout << "\nE-Mail: ";
			cin >> email;
			cout << "\nContact: ";
			cin >> contact;
			cout << "\nPassword: ";
			mask(password);     //masking provides extra security 

			Account user(email, username, contact, password);  // Creation of User Record
			htable.Insert(username, user);   // Insertion of user record in HashMapTable

			system("cls");
			cout << "\nDisplaying Your Details" << endl;
			cout << "Username: " << user.getUsername() << endl;
			cout << "E-mail: " << user.getEmail() << endl;
			cout << "Contact: " << user.getContact() << endl;
			cout << "\n\n********************SIGN UP SUCCESSFUL********************\n\n";
			system("cls");
		}
		else {
			system("cls");
			string username;
			string password;
			cout << "Please Provide the Details for Logging In into your Account:" << endl;
			cout << "\nUsername: ";
			cin >> username;
			cout << "\nPassword: ";
			mask(password);
			//verifying user
			int ctr = 0;
			while (!VerifyLogin(username, password) && ctr < 4) {
				cout << endl;
				cout << "Invalid ID or Password\n" << endl;
				cout << "\nUsername: ";
				cin >> username;
				cout << "\nPassword: ";
				mask(password);
				ctr++;
			}
			if (ctr < 5)
				cout << "\n\n********************LOGIN SUCCESSFUL********************\n\n";
			else
				cout << "\n\n********************LOGIN FAILED********************\n\n";
		}
	}

	//For Masking Password
	void mask(string& pass) {
		char ch;
		ch = _getch();
		while (ch != 13) {
			if (ch != 8 && ch != 9) {
				pass.push_back(ch);
				cout << "*";
			}
			ch = _getch();
		}
	}
	//Verify Password
	bool VerifyLogin(string usern, string password) {
		if (!htable.Searchkey(usern)) {
			return false;
		}
		Account user_check = htable.Access(usern);
		return (user_check.getPassword() == password);
	}


	//Booking Tickets
	void book_tickets() {
		string cityD, cityA;
		cout << "Search by Departure/Arrival\n\n";
		for (int i = 0; i < train[0].graph.vertices; i++) {
			cout << i + 1 << ") " << train[0].graph.cities[i] << endl;
		}
		cout << endl;
		cout << "----Select Departure----\n";
		cout << "\nEnter city name: ";
		cin >> cityD;
		cout << "\n\n----Select Arrival----\n";
		cout << "\nEnter city name: ";
		cin >> cityA;

		int x = train[0].graph.vertices;
		Trio* trio = new Trio[x];
		system("cls");
		cout << "These are the trains available to depart from " << cityD << " to " << cityA << endl << endl;
		srand(time(0));

		for (int i = 0; i < num_of_trains; i++) {
			trio[i] = train[i].Dijkstra(cityD, cityA);
			cout << i + 1 << ") " << train[i].name << "--> Journey time: " << trio[i].time << " hours" << endl;
		}

		int ans;
		cout << "\n\nSelect: ";
		cin >> ans;

		// print the shortest distance
		cout << endl;
		cout << "Best Optimal Path for Train " << train[ans - 1].name << " from " << cityD << " to " << cityA << " have a distance : " << trio[ans - 1].distance << " kilometers" << endl;

		// Print the path

		train[ans - 1].print_path(cityD, cityA, trio[ans - 1].predecessor);

		//fare per kilometer is 20 
		int fare = trio[ans - 1].distance * 20;
		int opt;
		double TotalFare = 0;
		int numSeats = 0, bookingN = 0;
		string dateT;
		cout << endl;
		cout << "Enter Date for Travelling: ";
		cin >> dateT;
		cout << endl;
		cout << "Enter how many Total Seat Bookings do you want to make: " << endl;
		cin >> numSeats;
		cout << endl;
		cout << "--------------------------------------MENU FOR SEAT CLASS TYPE--------------------------------------" << endl;
		for (int i = 0; i < numSeats; i++) {
			cout << "Enter:\n1-VIP(AC)\n2-First Class(AC)\n3-Economy(Without AC)" << endl;
			cin >> opt;
			seats += numSeats;
			if (seats > train[ans - 1].totalSeats) {
				cout << "Booking can not be done since Seats of the Train are already fully booked!!" << endl;
				break;
			}
			if (opt == 1) {
				TotalFare += fare * 1.35;
			}
			else if (opt == 2) {
				TotalFare += fare * 1.20;
			}
			else {
				TotalFare += fare * 1.10;
			}

			bookingN++;
			train->totalSeats -= bookingN;
			cout << endl;
		}
		cout << endl;
		if (bookingN == numSeats) {
			cout << "Using Train " << train[ans].name << " All " << numSeats << " Bookings Successful for the Date : " << dateT << endl;
			cout << "Deaprture From: " << cityD << endl;
			cout << "Arrival To: " << cityA << endl;
			cout << endl;
			cout << "Payment Amount: " << TotalFare << endl;
		}
		else {
			cout << "Using Train " << train[ans].name << bookingN << "  Bookings Successful for the Date: " << dateT << "..." << endl;
			cout << "Deaprture From: " << cityD << endl;
			cout << "Arrival To: " << cityA << endl;
			cout << endl;
			cout << "Payment Amount: " << TotalFare << endl;
		}
	}
};

int main() {
	system("color B0");
	char choice;
	cout << "\n\n\n-----------------------WELCOME TO RAILWAY TICKET RESERVATION PORTAL-----------------------\n\n\n";
	Sleep(2000);
	cout << "****************Account Generation/Log In****************" << endl << endl;
	System s;
	s.login_signup();
	s.book_tickets();
	this_thread::sleep_for(chrono::milliseconds(2000));
	system("cls");
	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	cout << "Enter F If You Want To Make Ticket Reservations Further OR Else Enter E to Exit " << endl;
	cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl << endl;
	cin >> choice;
	while (choice != 'F' || choice != 'f' || choice != 'E' || choice != 'e') {
		cout << "Invalid Choice Entered! Enter a Valid Option: " << endl;
		cin >> choice;
	}

	while (choice == 'F' || choice == 'f') {
		this_thread::sleep_for(chrono::milliseconds(2000));
		system("cls");
		cout << "****************Account Generation/Log In****************" << endl << endl;
		s.login_signup();
		s.book_tickets();
		Sleep(2000);

		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
		cout << "Enter F If You Want To Make Ticket Reservations Further OR Else Enter E to Exit " << endl;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl << endl;
		cin >> choice;
	}
	if (choice == 'E' || choice == 'e') {
		cout << endl << endl << endl << endl;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
		cout << "Thanks For Booking Your Tickets, We Hope You Will have a Great Journey Ahead!!!" << endl;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
		exit(1);
	}
	_getch();
}