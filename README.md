# Enumerators
## Iterators that know when they are done
An `enumerator` is an iterator with member function `explicit operator bool() const` that indicates
when it is valid to dereference the underlying iterator.

They are more general than STL ranges and allow compact expression of algorithms involving
forward iterators. 