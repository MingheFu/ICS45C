#include <iostream>

#include "coins.hpp"

using namespace std;

int main() {
	Coins piggyBank(50, 50, 50, 50);
	Coins pocket(8, 3, 6, 8);
	cout << "Initial piggy bank: " << piggyBank << endl;
	cout << "Initial pocket: " << pocket << endl;
	
	cout << "\nBought chips using pocket" << endl;
	Coins chips(5, 2, 0, 4);
	cout << "Chips required the coins: " << chips << endl;
	pocket.extract_exact_change(chips);
	cout << "Pocket after paying for chips: " << pocket << endl;

	cout << "\nTransferring money to pocket" << endl;
	Coins transfer(16, 0, 1, 0);
	cout << "Coins for transfer: " << transfer;
	pocket.deposit_coins(transfer);
	piggyBank.extract_exact_change(transfer);
	cout << "Pocket: " << pocket << endl;
	cout << "Piggy bank: " << piggyBank << endl;

	cout << "\nTransferring sofa change to piggy bank" << endl;
	Coins sofa( 10, 10, 10, 10);
	piggyBank.deposit_coins(sofa);
	cout << "Sofa: " << sofa << endl;
	cout << "Piggy bank: " << piggyBank << endl;
	
	int total_value = piggyBank.total_value_in_cents();
	cout <<"\nPiggy bank total: ";
	print_cents(total_value, cout);
}

