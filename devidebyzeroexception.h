#ifndef DEVIDEBYZEROEXCEPTION_H
#define DEVIDEBYZEROEXCEPTION_H

#include <stdexcept>

class DivideByZeroException : public std::runtime_error {
public:
   DivideByZeroException()
      : std::runtime_error{"attempted to divide by zero.\n"} {}
};

#endif // DEVIDEBYZEROEXCEPTION_H
