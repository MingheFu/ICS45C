#ifndef COIN_HPP
#define COIN_HPP

#include <iosfwd>

constexpr int CENTS_PER_QUARTER = 25;
constexpr int CENTS_PER_DIME = 10;
constexpr int CENTS_PER_NICKEL = 5;

class Coins{
public:
	Coins(int q, int d, int n, int p);
	
	void deposit_coins(Coins& coins);

	bool has_exact_change_for_coins(const Coins& coins) const;

	Coins extract_exact_change(const Coins& coins);

	int total_value_in_cents() const;

	void print(std::ostream& out) const;

	bool operator == (const Coins& other) const = default;


private:
	int quarters, dimes, nickels, pennies;
};

std::ostream& operator<<(std::ostream& out, const Coins& coins);

Coins coins_required_for_cents(int aomount_in_cents);

void print_cents(int cnets, std::ostream& out);

Coins ask_for_coins(std::istream& in, std::ostream& out);

void coins_menu(std::istream& in, std::ostream& out);

#endif // End of the include guard.

