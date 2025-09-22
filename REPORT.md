# OS1 Project

## Part 2: Linking rule `$(TARGET): $(OBJECTS)`

The rule indicates that the **target binary** depends on the list of object files.  
Whenever any `.o` file changes, the target is rebuilt.  

When linking against a library, you pass `-L` (library path) and `-l` (library name).  
The linker then searches for symbols inside archives (`.a`) or shared objects (`.so`) rather than linking each object file directly.

---

## Part 3: Static and Dynamic Libraries

### a) `ar` / `ranlib`
- `ar` creates a static library archive (e.g., `libmyutils.a`) by bundling `.o` files together.  
- `ranlib` builds an index inside the archive, so the linker can quickly find symbols.  

### b) PIC (Position Independent Code)
- Shared libraries (`.so`) must run no matter where they are loaded in memory.  
- Compiling with `-fPIC` generates code that is position-independent, so the library can be mapped at any address without errors.  

### c) `LD_LIBRARY_PATH`
- An environment variable that tells the dynamic linker where to look for shared libraries at runtime.  
- If the `.so` is not in a system directory, we export the path manually:  
  ```bash
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib
  ./bin/client_dynamic

## Part 4: `nm` and Symbols

### The `nm` command
- `nm` lists symbols (functions, variables) contained in object files, static libraries, or executables.  
- It helps us see which symbols are defined, undefined, or external.  
- Example usage:
  ```bash
  nm lib/libmyutils.a
  nm lib/libmyutils.so
