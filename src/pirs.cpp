#include <iostream>
#include <cmath>
#include <gmp.h>
#include <gmpxx.h>
#include <string>
#include <vector>
#include <limits>

// Configuration structure
struct Config {
    mpz_class LLN = 1;                    // Lower limit for perfect number
    mpz_class ULN = 10000;                // Upper limit for perfect number
    int LLD = 1;                          // Min digits for perfect number
    int ULD = std::numeric_limits<int>::max(); // Max digits for perfect number
    mpz_class LMPN = 2;                   // Min Mersenne prime number
    mpz_class UMPN = 20;                  // Max Mersenne prime number
    int LMPD = 1;                         // Min digits for Mersenne primes
    int UMPD = 10;                        // Max digits for Mersenne primes
    mpz_class PNL = -1;                   // Max perfect numbers to find (-1 = infinite)
    bool RUN = true;                      // Return detailed info flag
};

// Function to check if a number is prime
bool isPrime(const mpz_class& num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;

    mpz_class sqrtNum = sqrt(num.get_d());
    for (mpz_class i = 3; i <= sqrtNum; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

// Function to generate Mersenne primes from a given n
mpz_class generateMersennePrime(const mpz_class& n) {
    mpz_class mersennePrime;
    mpz_ui_pow_ui(mersennePrime.get_mpz_t(), 2, n.get_ui());
    mersennePrime -= 1;
    return mersennePrime;
}

// Function to check if the Mersenne prime is valid based on digit length
bool isValidMersennePrime(const mpz_class& mersennePrime, const Config& config) {
    std::string mersennePrimeStr = mersennePrime.get_str();
    return (mersennePrimeStr.length() >= config.LMPD) && (mersennePrimeStr.length() <= config.UMPD);
}

// Function to generate the perfect number using the Mersenne prime
mpz_class generatePerfectNumber(const mpz_class& n, const mpz_class& mersennePrime) {
    mpz_class perfectNumber;
    mpz_ui_pow_ui(perfectNumber.get_mpz_t(), 2, (n - 1).get_ui());
    perfectNumber *= mersennePrime;
    return perfectNumber;
}

// Function to check if the perfect number is valid based on the config
bool isValidPerfectNumber(const mpz_class& perfectNumber, const Config& config) {
    std::string perfectNumberStr = perfectNumber.get_str();
    return (perfectNumber >= config.LLN) && (perfectNumber <= config.ULN) &&
           (config.LLD <= 0 || perfectNumberStr.length() >= config.LLD) &&
           (config.ULD <= 0 || perfectNumberStr.length() <= config.ULD);
}

// Main function to find perfect numbers based on the config
std::vector<mpz_class> findPerfectNumbersWithConfig(const Config& config = Config()) {
    std::vector<mpz_class> perfectNumbers;
    mpz_class foundCount = 0;
    mpz_class n = config.LMPN;

    while (true) {
        if (isPrime(n)) {
            mpz_class mersennePrime = generateMersennePrime(n);

            if (isValidMersennePrime(mersennePrime, config)) {
                mpz_class perfectNumber = generatePerfectNumber(n, mersennePrime);

                if (isValidPerfectNumber(perfectNumber, config)) {
                    perfectNumbers.push_back(perfectNumber);
                    foundCount++;

                    if (config.PNL > 0 && foundCount >= config.PNL) break;
                }
            }
        }

        n++;
        if (n > config.UMPN) break;
    }

    return perfectNumbers;
}

// Function to display the found perfect numbers
void displayPerfectNumbers(const std::vector<mpz_class>& perfectNumbers) {
    std::cout << "Found Perfect Numbers: " << std::endl;
    for (const auto& num : perfectNumbers) {
        std::cout << num << std::endl;
    }
}

// Main driver function
int main() {
    // Create configuration
    Config config;
    config.LLN = 1000;    // Search for perfect numbers >= 1000
    config.ULN = 100000;  // Search up to perfect numbers <= 100000
    config.LMPN = 2;      // Start searching from the second Mersenne prime exponent
    config.UMPN = 10;     // Search up to the 10th Mersenne prime exponent
    config.PNL = 5;       // Find the first 5 perfect numbers

    // Find perfect numbers based on configuration
    std::vector<mpz_class> perfectNumbers = findPerfectNumbersWithConfig(config);

    // Display the found perfect numbers
    displayPerfectNumbers(perfectNumbers);

    return 0;
}
// Check README for more information 
