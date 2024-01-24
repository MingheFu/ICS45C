#include "coins.hpp"

#include <iostream>

using namespace std;

Coins::Coins(int q, int d, int n, int p): quarters(q), dimes(d), nickels(n), pennies(p) {}

void Coins::deposit_coins(Coins& coins){
	quarters += coins.quarters;
	dimes += coins.dimes;
	nickels += coins.nickels;
	pennies += coins.pennies;
	coins.quarters = 0;
	coins.dimes = 0;
	coins.nickels = 0;
	coins.pennies = 0;
}

bool Coins::has_exact_change_for_coins(const Coins& coins) const {
	return (quarters >= coins.quarters) && (dimes >= coins.dimes) && (nickels >= coins.nickels) && (pennies >= coins.pennies);
}

Coins Coins::extract_exact_change(const Coins& coins){
	if (has_exact_change_for_coins(coins)) {
		quarters -= coins.quarters;
		dimes -= coins.dimes;
		nickels -= coins.nickels;
		pennies -= coins.pennies;
		return coins;
	} else {
		return Coins(0, 0, 0, 0);
	}
}

int Coins::total_value_in_cents() const{
	return quarters * CENTS_PER_QUARTER + dimes * CENTS_PER_DIME + nickels * CENTS_PER_NICKEL + pennies;
}	

void Coins::print(std::ostream& out) const {
	out << quarters << " quarters, " << dimes << " dimes, " << nickels << " nickels, " << pennies << " pennies";
}

std::ostream& operator<<(std::ostream& out,const Coins& coins) {
	coins.print(out);
	return out;
}

Coins coins_required_for_cents(int amount_in_cents) {
	int quarters = amount_in_cents/25;
	int dimes = (amount_in_cents % 25) /10;
	int nickels = ((amount_in_cents % 25) % 10) / 5;
	int pennies = ((amount_in_cents % 25) % 10) % 5;
	return Coins(quarters, dimes, nickels, pennies);

}

void print_cents(int cents, std::ostream& out) {
	out << '$' << cents / 100 << '.' << (cents % 100 < 10 ? "0" : "") << cents % 100;
}

Coins ask_for_coins(std::istream& in, std::ostream& out){
	int quarters, dimes, nickels, pennies;
	out << "Quarters? ";
	in >> quarters;
	out << "Dimes? ";
	in >> dimes;
	out << "Nickels? ";
	in >> nickels;
	out <<  "Pennies? ";
	in >> pennies;
	return Coins(quarters, dimes, nickels, pennies);
}

void coins_menu(std::istream& in, std::ostream& out) {
	Coins myCoins(0, 0, 0, 0);
	out << "Coins Menu\n";
	out << "\n";
	while (true) {
		out <<"1. Deposit Change\n";
		out << "2. Extract Change\n";
		out << "3. Print Balance\n";
		out << "4. Exit\n" ;
		out << "\n";
		out << "User Input: ";
		int user_input;
		in >> user_input;

		switch (user_input) {
			case 1: {
				out << "\n";
				Coins deposit_coins = ask_for_coins(in, out);
				myCoins.deposit_coins(deposit_coins);
				out << "\n";
				out << "Thank you!\n";
				out << "\n";
				break;
			}
			case 2: {
				out << "\n";
				Coins extract_coins = ask_for_coins(in, out);
				Coins coins_extracted = myCoins.extract_exact_change(extract_coins);
				out << "\n";
				out << "Thank you!\n";
				if (coins_extracted.total_value_in_cents() <= 0) {
					out << "\n";
					out << "Error: Insufficient Funds\n";
					out << "\n";
				} else {
					out << "\n";
				}
				break;
			}
			case 3: {
				out << "\n";
				int total_value = myCoins.total_value_in_cents();
				print_cents(total_value, out);
				out << "\n";
				out << "Thank you!\n";
				out << "\n";
				break;
			}
			case 4: {
				out << endl;
				return;
			}
			default: {
				out << "\n";
				out << "Error: Invalud Command\n";
				out << "\n";
				break;
			}
		}
	}
}

