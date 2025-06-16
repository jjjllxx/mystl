# coding-interview-university-cpp
This repository contains C++ implementations of data structures and algorithms inspired by the [Coding Interview University](https://github.com/jwasham/coding-interview-university) project. 

**Note:**
1. The goal of this repository is to learn and implement core concepts from scratch.
2. The implementations may differ from the C++ Standard Template Library (STL). 
3. STL is avoided intentionally to reinforce understanding of the internal workings of data structures.

## Structure
- **Data Structures:** Implemented in the [`DS`](DS) directory  
- **Unit Tests:** Written using [Google Test (gtest)](https://google.github.io/googletest/)

## Running the Tests

### 1. Initial Setup (Run once)
``` bash
cd coding-interview-university-cpp
mkdir bin
mkdir build
```

### 2. Compile the Project
```
cd build
cmake -DDSA_TEST=on ..
make -j16
```

### 3. Run Unit Tests
```
cd bin
./dsa_test
```

### 4. (Optional) Check for Memory Leaks
```
valgrind --leak-check=full ./dsa_test
```