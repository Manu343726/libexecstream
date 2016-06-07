# libexecstream

CMake-ready [libexecstream
0.3](https://sourceforge.net/projects/libexecstream/?source=navbar)
library.

## Changes from original libexecstream 0.3

 - CMake scripts to build the library.
 - Sources moved to `src/` and `include/libexecstream/` directories.
 - Removed unnamed namespaces (Some implementation types from that
   namespaces are being exposed to the API). Eliminates
   `-Wsubobject-linkage` GCC warning.
 - Use `const char*` instead of `char*` for string literals. Eliminates
   `-Wwrite-strings` GCC warning.


