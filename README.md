# OS1

## Part 2: Linking rule $(TARGET): $(OBJECTS)
Explain that the rule indicates the target depends on the object files; when any object changes, the target is rebuilt. When linking against a library, you pass `-L` and `-l` and the linker searches archives/shared objects rather than linking each object directly.

## What is a git tag...
Annotated vs lightweight: annotated stores metadata and signed comment; lightweight is just a name pointing to a commit.

## Purpose of Release on GitHub
To provide downloadable binaries (lib and executables) and a snapshot for graders.

## Part 3: Static and Dynamic Libraries

### a) `ar` and `ranlib`
- `ar` creates a static library archive (e.g., `libmyutils.a`) from multiple `.o` files.  
- `ranlib` adds an index to the archive so the linker can quickly look up symbols inside the static library.

### b) PIC (Position Independent Code)
- Shared libraries (`.so`) must be loaded at arbitrary memory addresses.  
- Compiling with `-fPIC` ensures the code can run regardless of where it is loaded in memory.

### c) `LD_LIBRARY_PATH`
- Environment variable that tells the dynamic linker where to search for shared libraries at runtime.  
- Example:
  ```bash
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib
  ./bin/client_dynamic
## Part 4: `nm` and Symbols

### Using `nm`
- The `nm` command lists symbols (functions and variables) in object files, libraries, and executables.  
- Example:
  ```bash
  nm bin/client_static
  nm lib/libmyutils.a
  nm bin/client_dynamic
  nm lib/libmyutils.so

