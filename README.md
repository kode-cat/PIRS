# PIRS (Perfect Internet Search)

PIRS is a C++ program designed to efficiently find perfect numbers, leveraging Mersenne primes. It allows you to search for perfect numbers within a specified range, while offering flexibility and configuration options.

## Features

- **Modular design**: Each function has a single responsibility, making the code easier to maintain and extend.
- **Configurable search**: Specify limits for Mersenne primes, perfect numbers, and their respective digit lengths.
- **GPU acceleration**: Designed to easily integrate GPU computation (optional) for faster searches.
- **Output**: Displays the found perfect numbers based on the configuration.

## Requirements

- **C++ Compiler** with GMP and GMPXX libraries.
  - Install GMP and GMPXX using your package manager:
    - On **Ubuntu**:
      ```bash
      sudo apt-get install libgmp-dev libgmpxx4ldbl
      ```
    - On **MacOS** (using Homebrew):
      ```bash
      brew install gmp
      ```
- **C++11 or higher** for the code compilation.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/pirs.git
   cd pirs
   ```

2. Compile the program:
   ```bash
   g++ -o pirs pirs.cpp -lgmp -lgmpxx
   ```

3. Run the program:
   ```bash
   ./pirs
   ```

## Configuration

You can modify the search behavior by adjusting the configuration parameters defined in the `Config` struct. Here are the available options:

### Configuration Parameters:

- **`LLN`**: Lower limit for the perfect number search (default: 1).
- **`ULN`**: Upper limit for the perfect number search (default: 10,000).
- **`LLD`**: Minimum number of digits for perfect numbers (default: 1).
- **`ULD`**: Maximum number of digits for perfect numbers (default: unlimited).
- **`LMPN`**: Lower limit for the Mersenne prime exponent (default: 2).
- **`UMPN`**: Upper limit for the Mersenne prime exponent (default: 20).
- **`LMPD`**: Minimum number of digits for Mersenne primes (default: 1).
- **`UMP`**: Maximum number of digits for Mersenne primes (default: 10).
- **`PNL`**: Maximum number of perfect numbers to find. Set to `-1` for infinite results (default: -1).
- **`RUN`**: Flag to enable or disable detailed output (default: true).

### Example Configuration

```cpp
Config config;
config.LLN = 1000;      // Search for perfect numbers >= 1000
config.ULN = 100000;    // Search up to perfect numbers <= 100000
config.LMPN = 2;        // Start searching from the second Mersenne prime exponent
config.UMPN = 10;       // Search up to the 10th Mersenne prime exponent
config.PNL = 5;         // Find the first 5 perfect numbers
```

## Core Logic

1. **Prime Check**: We start by checking if `n` is a prime number, since Mersenne primes are related to prime exponents.
2. **Mersenne Prime Generation**: Once a prime `n` is found, a Mersenne prime is generated using the formula:  
   \[
   M_n = 2^n - 1
   \]
3. **Perfect Number Generation**: For each valid Mersenne prime `M_n`, a perfect number is generated using the formula:
   \[
   P_n = 2^{(n-1)} \times (2^n - 1)
   \]
4. **Validation**: The generated perfect number is validated against the specified range (`LLN` to `ULN`) and digit length constraints (`LLD` to `ULD`).

### Example Output:

```
Found Perfect Numbers:
6
28
496
8128
33550336
```

## Code Structure

### `Config` Structure

The `Config` structure defines all the parameters that control the search process. You can adjust these parameters to fine-tune the search based on your requirements.

### Functions

- **`isPrime(mpz_class num)`**: Checks whether a number is prime.
- **`generateMersennePrime(mpz_class n)`**: Generates a Mersenne prime for a given `n`.
- **`isValidMersennePrime(mpz_class mersennePrime)`**: Checks if the Mersenne prime meets the required digit length.
- **`generatePerfectNumber(mpz_class n, mpz_class mersennePrime)`**: Generates a perfect number from the Mersenne prime.
- **`isValidPerfectNumber(mpz_class perfectNumber)`**: Checks if the perfect number meets the required range and digit length constraints.
- **`findPerfectNumbersWithConfig(Config config)`**: Finds perfect numbers based on the configuration.
- **`displayPerfectNumbers(std::vector<mpz_class> perfectNumbers)`**: Outputs the found perfect numbers.

### `pirs.cpp`

- **Main Logic**: Contains all the core functions for generating Mersenne primes, calculating perfect numbers, and validating them.
- **Modularization**: Each function is responsible for a single task, ensuring readability, maintainability, and reusability.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

## Contributions

Contributions are welcome! Feel free to fork the repository, make improvements, and submit pull requests.
