#include "Pair.hpp"

template <typename Type1, typename Type2>
Pair<Type1, Type2>::Pair(Type1 first, Type2 second) : first(first), second(second) {}

Pair<Type>::operator+(const Pair &other);
Pair<Type>::operator<(const Pair &other);
Pair<Type>::operator>(const Pair &other);

friend std::ostream &operator<<(std::ostream &os, const Pair &pair);
