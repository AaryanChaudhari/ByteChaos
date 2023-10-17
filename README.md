# **ByteChaos**


## Create a Build Directory
```console
<font size="3"> foo@bar:~$ mkdir build  </font>

```




## Run CMake Commands

### Check your CMake Version and Update it in CMakeLists.txt if any error. ###

```console
foo@bar:~$ cmake -B build/ -S .
```

<details>
  <summary>View CMake Output</summary>

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

```console
foo@bar:~$ cmake --build build/ 
```





