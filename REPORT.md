# OS1

 Linking rule $(TARGET): $(OBJECTS)
Explain that the rule indicates the target depends on the object files; when any object changes, the target is rebuilt. When linking against a library, you pass `-L` and `-l` and the linker searches archives/shared objects rather than linking each object directly 

 git tag...
Annotated vs lightweight: annotated stores metadata and signed comment; lightweight is just a name pointing to a commit.

Purpose of Release on GitHub
To provide downloadable binaries (lib and executables) and a snapshot for graders.

Part 3: Static and Dynamic Libraries

a) ar / ranlib

ar is used to create a static library archive (e.g. libmyutils.a) by grouping .o files together.

ranlib builds an index inside the archive, allowing the linker to quickly locate symbols when linking.

b) PIC (Position Independent Code)

Shared libraries must run no matter where they’re loaded in memory.

Compiling with -fPIC generates position-independent code, so the library can be loaded at any address without errors.

c) LD_LIBRARY_PATH

An environment variable that tells the runtime linker where to search for .so files.

If your library is not in a standard system path, you must export this variable:
