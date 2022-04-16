# Lab03

*Коротов Максим*
___

### Задание 1
Вам поручили перейти на систему автоматизированной сборки **CMake**.
Исходные файлы находятся в директории [formatter_lib](formatter_lib).
В этой директории находятся файлы для статической библиотеки *formatter*.
Создайте `CMakeList.txt` в директории [formatter_lib](formatter_lib),
с помощью которого можно будет собирать статическую библиотеку *formatter*.

```sh
$ cd ./formatter_lib
$ cat > CMakeLists.txt <<EOF
> cmake_minimum_required(VERSION 3.4)
> project (lab03)
> 
> set(CMAKE_CXX_STANDARD 11)
> set(CMAKE_CXX_STANDARD_REQUIRED ON)
> 
> add_library(formatter STATIC ${CMAKE_CURRENT_SOURCE_DIR}/formatter.cpp)
>
> include_directories(${CMAKE_CURRENT_SOURCE_DIR})
> EOF
```

```shell
$ cmake -H. -B_build

-- Configuring done
-- Generating done
-- Build files have been written to: /home/Dogifu/workspace/projects/lab03/formatter_lib/_build
```

```shell
$ cmake --build _build

Scanning dependencies of target formatter
[ 50%] Building CXX object CMakeFiles/formatter.dir/formatter.cpp.o
[100%] Linking CXX static library libformatter.a
[100%] Built target formatter

```


### Задание 2
У компании "Formatter Inc." есть перспективная библиотека,
которая является расширением предыдущей библиотеки. Т.к. вы уже овладели
навыком созданием `CMakeList.txt` для статической библиотеки *formatter*, ваш
руководитель поручает заняться созданием `CMakeList.txt` для библиотеки
*formatter_ex*, которая в свою очередь использует библиотеку *formatter*.

```shell
$ cd ./formatter_ex_lib
$ cat > CMakeLists.txt <<EOF
> cmake_minimum_required(VERSION 3.4)
> project(lab03)
> 
> set(CMAKE_CXX_STANDART 11)
> set(CMAKE_CXX_STANDART_REQUIRED ON)
> 
> include_directories("../formatter_lib")
>
> add_library(formatter_ex_lib STATIC ${CMAKE_CURRENT_SOURCE_DIR}/formatter_ex.cpp)
>
> target_link_libraries(formatter_ex_lib formatter_lib)
> EOF
```

```shell
$ cmake -H. -B _build

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
-- Build files have been written to: /home/Dogifu/workspace/projects/lab03/formatter_ex_lib/_build
```

```shell
$ cmake --build _build

Scanning dependencies of target formatter_ex_lib
[ 50%] Building CXX object CMakeFiles/formatter_ex_lib.dir/formatter_ex.cpp.o
[100%] Linking CXX static library libformatter_ex_lib.a
[100%] Built target formatter_ex_lib

```

### Задание 3
Конечно же ваша компания предоставляет примеры использования своих библиотек.
Чтобы продемонстрировать как работать с библиотекой *formatter_ex*,
вам необходимо создать два `CMakeList.txt` для двух простых приложений:
* *hello_world*, которое использует библиотеку *formatter_ex*;
```shell
$ cd ./hello_world_application
$ cat > CMakeLists.txt <<EOF
> cmake_minimum_required(VERSION 3.4)
> project(lab03)
>
> set(CMAKE_CXX_STANDART 11)
> set(CMAKE_CXX_STANDART_REQUIRED ON)
>
> add_library(hello_world_application ${CMAKE_CURRENT_SOURCE_DIR}/hello_world.cpp)
>
> include_directories("../formatter_ex_lib")
> EOF
```

```shell
$ cmake -H. -B_build

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
-- Build files have been written to: /home/Dogifu/workspace/projects/lab03/hello_world_application/_build
```

```shell
$ cmake --build _build

Scanning dependencies of target hello_world_application
[ 50%] Building CXX object CMakeFiles/hello_world_application.dir/hello_world.cpp.o
[100%] Linking CXX static library libhello_world_application.a
[100%] Built target hello_world_application
```
* *solver*, приложение которое испольует статические библиотеки *formatter_ex* и *solver_lib*.
```shell
$ cd ./solver_application
$ cat > CMakeLists.txt <<EOF
> cmake_minimum_required(VERSION 3.4) 
> project(lab03_3)
> 
> set(CMAKE_CXX_STANDARD 11)
> set(CMAKE_CXX_STANDARD_REQUIRED ON)
> 
> add_library(solver STATIC ${CMAKE_CURRENT_SOURCE_DIR}/equation.cpp)
> add_library(solver_lib STATIC ${CMAKE_CURRENT_SOURCE_DIR} "../solver_lib/solver.cpp")
> add_library(formatter_ex STATIC ${CMAKE_CURRENT_SOURCE_DIR} "../formatter_ex_lib/formatter_ex.cpp")
>
> include_directories("../formatter_ex_lib")
> include_directories("../formatter_lib")
> include_directories("../solver_lib")
> include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
> include_directories(${CMAKE_CURRENT_SOURCE_DIR}/stdexcept)
> include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cmath)
>
> target_link_libraries(solver formatter_ex)
> target_link_libraries(formatter_ex formatter_lib)
> target_link_libraries(solver "../solver_lib")
> target_link_libraries(solver_application solver_lib)
> add_library(solver_application ${CMAKE_CURRENT_SOURCE_DIR}/equation.cpp)
> EOF
```

<details>

```c++
.../solver_lib/solver.cpp:14:21: error: ‘sqrtf’ is not a member of ‘std’
   14 |     x1 = (-b - std::sqrtf(d)) / (2 * a);
      |                     ^~~~~
   15 |     x2 = (-b + std::sqrtf(d)) / (2 * a);
      |                     ^~~~~

```
```c++
.../solver_lib/solver.cpp:

$ edit solver.cpp

+ #include <cmath>
```

```c++
.../solver_lib/solver.cpp:15:21: error: ‘sqrtf’ is not a member of ‘std’; did you mean ‘sqrt’?
   15 |     x1 = (-b - std::sqrtf(d)) / (2 * a);
      |                     ^~~~~
      |                     sqrt
   16 |     x2 = (-b + std::sqrtf(d)) / (2 * a);
      |                     ^~~~~
      |                     sqrt

```

```c++
.../solver_lib/solver.cpp:

$ edit solver.cpp

-   15 |     x1 = (-b - std::sqrtf(d)) / (2 * a);
-   16 |     x2 = (-b + std::sqrtf(d)) / (2 * a);

+   15 |     x1 = (-b - sqrtf(d)) / (2 * a);
+   16 |     x2 = (-b + sqrtf(d)) / (2 * a);
```

</details>

```shell
$ cmake -H. -B_build

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
-- Build files have been written to: /home/Dogifu/workspace/projects/lab03/solver_application/_build
```

```shell
$ cmake --build _build
Scanning dependencies of target solver_lib
[ 12%] Building CXX object CMakeFiles/solver_lib.dir/home/Dogifu/workspace/projects/lab03/solver_lib/solver.cpp.o
[ 25%] Linking CXX static library libsolver_lib.a
[ 25%] Built target solver_lib
Scanning dependencies of target solver_application
[ 37%] Building CXX object CMakeFiles/solver_application.dir/equation.cpp.o
[ 50%] Linking CXX static library libsolver_application.a
[ 50%] Built target solver_application
Scanning dependencies of target formatter_ex
[ 62%] Building CXX object CMakeFiles/formatter_ex.dir/home/Dogifu/workspace/projects/lab03/formatter_ex_lib/formatter_ex.cpp.o
[ 75%] Linking CXX static library libformatter_ex.a
[ 75%] Built target formatter_ex
Scanning dependencies of target solver
[ 87%] Building CXX object CMakeFiles/solver.dir/equation.cpp.o
[100%] Linking CXX static library libsolver.a
[100%] Built target solver
```

**Удачной стажировки!**

## Links
- [Основы сборки проектов на С/C++ при помощи CMake](https://eax.me/cmake/)
- [CMake Tutorial](http://neerc.ifmo.ru/wiki/index.php?title=CMake_Tutorial)
- [C++ Tutorial - make & CMake](https://www.bogotobogo.com/cplusplus/make.php)
- [Autotools](http://www.gnu.org/software/automake/manual/html_node/Autotools-Introduction.html)
- [CMake](https://cgold.readthedocs.io/en/latest/index.html)

```
