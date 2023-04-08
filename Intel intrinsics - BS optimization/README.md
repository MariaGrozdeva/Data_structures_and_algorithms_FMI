# Intrinsics

Intrinsics are a set of assembly-coded functions that allow developers to use C++ function calls and variables in place of assembly instructions. They are designed to enhance performance by providing inline expansions of the code, which eliminates the overhead of a function call. Additionally, intrinsics improve the readability of the code, assist with instruction scheduling, and reduce debugging time.

[Here you can see a full list of **Intel intrinsics**](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html).

One example of intrinsics (the one I used for my solution) is the [**Advanced Vector Extensions (AVX)**](https://en.wikipedia.org/wiki/Advanced_Vector_Extensions), which is an instruction set extension for x86 processors. AVX provides 256-bit floating-point operations and enables parallel processing of multiple data elements, which significantly enhances the performance of vectorized algorithms.

To evaluate the performance of AVX, a series of tests were conducted to compare the speed of an ordinary Binary Search with that of an AVX Binary Search. The tests used various datasets and were repeated multiple times to ensure accuracy. The results showed a significant improvement in performance for the AVX Binary Search across all tests, indicating the efficacy of using intrinsics for optimization purposes.

![alt_text](https://github.com/MariaGrozdeva/Data_structures_and_algorithms_FMI/blob/main/Intel%20intrinsics%20-%20BS%20optimization/Tests.png)
