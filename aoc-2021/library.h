#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>

namespace library {
  using namespace std;

  // returns digits of n in base 10. r[0] is the LSB.
  vector<int> Digits(long n);
  // returns digits of n in specified base. r[0] is the LSB.
  vector<int> DigitsInBase(long n, int base);

  // returns if a positive integer is a palindrome in base 10 (e.g. 9009)
  bool IsPalindrome(long n);
  // returns if a positive integer is a palindrome in the given base (e.g. 585 = 0b1001001001 is palindrome in base 2)
  bool IsPalindromeInBase(long n, int base);

  // Returns true is number is a prime.
  bool IsPrime(long n);
  // returns a vector of size n+1 where a[i] is true iff i is prime
  std::vector<bool> Primes(int n);

  // returns the greatest common divisor of 2 numbers
  long Gcd(long n1, long n2);
  // returns the least common multiple of 2 numbers
  long Lcm(long n1, long n2);
  // returs proper divisors of n. 
  // e.g n=6 returns 1,2,3
  std::vector<int> properDivisors(int n);
  
  // split a string by a character
  vector<string> Split(string &str, char delim);

  // adds numbers given as a string
  std::string AddNumbers(std::vector<std::string> nums);
  // multiplies 2 numbers
  std::string MultiplyNumbers(std::string a, std::string b);
  // returns a^b
  // the odd signature is because the base is allowed to be a pretty big string
  std::string Pow(std::string a, int b);


}

#endif
