# mystl
`mystl` is a **from-scratch implementation of the C++ Standard Template Library (STL)**.  
It aims to be *faithful to the official STL design*, covering containers, iterators, and algorithms, while also providing **extra data structures and utilities** for interview preparation and practice.  

## Structure
- **mystl:** Implemenation of container, algorithm and iterator faithful to STL.  
- **test:** Unit test written using [Google Test (gtest)](https://google.github.io/googletest/)
- **extensions:** Useful data structures and algorithms inspired by [Coding Interview University](https://github.com/jwasham/coding-interview-university) (not included in STL).

## Running the Tests

### 1. Initial Setup (Run once)
``` bash
git clone https://github.com/jjjllxx/mystl.git
cd mystl
mkdir build
```

### 2. Compile the Project
``` bash
cd build
cmake -DMYSTL_TEST=on ..
make -j16
```

### 3. Run Unit Tests
``` bash
cd bin
./mystl_test
```

### 4. (Optional) Check for Memory Leaks
For Linux
``` bash
valgrind --leak-check=full ./mystl_test
```

For MacOS
```bash
export MallocStackLogging=1
leaks --atExit --list -- ./mystl_test
```

## Features
✅ STL-like containers (vector, map, set, unordered_map, etc.)  
✅ STL-compliant iterators  
✅ Common algorithms (sort, find, etc.)  
✅ Unit tested with GoogleTest  
⚡ Extensions: useful interview-style data structures (not in STL)