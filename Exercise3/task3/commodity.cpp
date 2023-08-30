#include "commodity.hpp"
#include <string>
using namespace std;
const double tax = 1.25;
Commodity::Commodity(const string &name_, const int id_, double price_) : name(name_), id(id_), price(price_) {}

void Commodity::set_price(double _price) {
  price = _price;
}

double Commodity::get_price(double amount) {
  return price * amount;
}

double Commodity::get_price_with_sales_tax(double amount) {
  return price * amount * tax;
}
