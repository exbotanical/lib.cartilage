# lib.cartilage

classical implementations of list and ring data structures for the C programming language

## Dynamic Linking

Linking to `lib.cartilage`:

```bash
# 1) include and use lib.cartilage in your project
# 2) generate object file for your project
gcc -I ../path/to/libcartilage -c main.c -o main.o
# 3) generate shared object file
make
# 4) link your project to lib.cartilage
gcc -o main main.o -L../path/to/libcartilage -llibcartilage
# you may need to add the lib location to your PATH
```

Linking to `lib.cartilage` on Windows:

```bash
# 1) include and use lib.cartilage in your project
# 2) generate object file for your project
gcc -I ../path/to/libcartilage -c main.c -o main.o
# 3) generate shared object file
make win
# 3) link your project to lib.cartilage
gcc -o main.exe main.o -L /path/to/lib.cartilage -llib_cartilage.dll
# you may need to add the lib location to your PATH
```
