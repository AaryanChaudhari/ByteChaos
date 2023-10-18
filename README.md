# **ByteChaos**


## Create a Build Directory
```console
foo@bar:~$ mkdir build
```




## Run CMake Commands

### Check your CMake Version and Update it in CMakeLists.txt if any error. ###

```console
foo@bar:~$ cmake -B build/ -S .
```

<details>
  <summary>View Output</summary>

```console
-- The C compiler identification is GNU 9.4.0 
-- The CXX compiler identification is GNU 9.4.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/usr/root_dir/ByteChaos/build

```
</details>

### Build the Executable ' okto ' 

```console
foo@bar:~$ cmake --build build/
```
<details>
  <summary>View Output</summary>
  
  ```console
[ 50%] Building CXX object CMakeFiles/okto.dir/src/main.cpp.o
[100%] Linking CXX executable okto
[100%] Built target okto
  ```
</details>

### Input your code with the  '.okto' extension

```console
foo@bar:~$ ./build/okto ./src/test.okto
```

### Run the Executable file

```console
foo@bar:~$ ./src/i_files/main
```







