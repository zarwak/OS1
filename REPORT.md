REPORT.md — Feature 2 (Multi-file Project using Make Utility)

1. Short summary
Feature-2 demonstrates how to build a C project composed of multiple .c files using a recursive Makefile approach. The project compiles source files in src/, places object files in obj/, and the final executable in bin/client. This feature also includes versioning via a git branch, an annotated tag, and a GitHub release with the compiled binary.

2. What I implemented (files & structure)
BSDSF23A001-OS-A01/
├── src/
│   ├── main.c
│   ├── mystrfunctions.c
│   └── myfilefunctions.c
├── include/
│   ├── mystrfunctions.h
│   └── myfilefunctions.h
├── bin/
│   └── client        # compiled executable (uploaded to GitHub release)
├── obj/
│   └── *.o           # compiled object files
├── Makefile          # top-level (recursive) Makefile
├── src/Makefile      # src Makefile that builds objects and links
├── test.txt
└── REPORT.md
3. How to build and run (reproducible steps)
From project root:

# Build everything (top-level Makefile delegates to src/)
make

# or build only in src
make -C src

# Run the program
./bin/client
# or make -C src run
If you need debug symbols instead of optimization:

make -C src DEBUG=1
4. Makefile notes (what I used and why)
Top-level Makefile: simply calls make inside src/ so the build can be separated by directory. This is the recursive approach and keeps the root Makefile short and clear.

src/Makefile (key parts):

CC := gcc — compiler variable so it can be easily changed.
CFLAGS := -Wall -Wextra -I../include — enable warnings and tell compiler where headers are.
Debug switch: build with DEBUG=1 to enable -g -O0.
SOURCES := $(wildcard $(SRCDIR)/*.c) — auto-collects .c files.
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES)) — maps sources to object files.
Pattern rule $(OBJDIR)/%.o: $(SRCDIR)/%.c compiles each .c into an .o.
Link rule: $(TARGET): $(OBJECTS) links object files into the final binary.
Why this layout? It keeps intermediate files in obj/, keeps the binary in bin/, and ensures make only rebuilds what changed.

5. Report questions — answered plainly
Q1: Explain the linking rule $(TARGET): $(OBJECTS). How does it differ from linking against a library?
Answer (plain): This rule says: "to make the final program (TARGET), first make sure every object file in $(OBJECTS) is present; then call the linker to combine those object files into an executable." When linking against a library, instead of feeding many object files directly to the linker, you give the linker a pre-built archive (a .a file) or shared library (.so) via flags like -L (where to look) and -l (which library). The linker then extracts only the needed pieces from the library. With $(OBJECTS) you are linking raw object files you built just now; with a library the objects are packaged and potentially reused across multiple programs.

Q2: What is a git tag and why is it useful? Difference between simple and annotated tags?
Answer (plain): A git tag is a named pointer to a particular commit used to mark a release point (like "v0.1.1"). A lightweight tag is just a name pointing to a commit (quick and simple). An annotated tag stores extra information (tagger, date, message) and is preferred for releases because it carries metadata and a message describing the release.

Q3: What is the purpose of creating a GitHub "Release" and what is the significance of attaching binaries?
Answer (plain): A GitHub Release is a nice public page that ties a tag to human-readable release notes and optional downloadable files. Attaching binaries (like bin/client) makes it easy for people (or graders) to download a ready-to-run program without compiling the source code themselves.

6. Commands I ran (important log entries)
Examples you can paste into a terminal to verify your state:

# Check current branch
git branch --show-current

# Show recent commits
git log --oneline --decorate -n 10

# Check tags
git tag -l

# Show tag details
git show v0.1.1-multifile

# Ensure local main is up to date after merging on GitHub
git checkout main
git pull origin main

# Push any outstanding tags
git push origin --tags

# Commit and push REPORT.md (if not yet pushed):
git add REPORT.md
git commit -m "Add REPORT for Feature-2: Makefile, build, release"
git push origin main
7. Verification checklist (what I completed)
 Created multifile-build branch and worked there.
 Implemented mystrfunctions.h / myfilefunctions.h.
 Implemented mystrfunctions.c, myfilefunctions.c, main.c.
 Created test.txt for file function tests.
 Created recursive Makefiles (top-level + src/Makefile).
 Built and tested the binary bin/client using make.
 Created annotated tag v0.1.1-multifile and pushed it.
 Drafted and published GitHub Release and attached bin/client.
 Merged multifile-build into main.
If all of the above are true on your GitHub repository, Feature-2 is complete.

8. Next steps and notes
If you merged on GitHub using the web UI, run git checkout main && git pull origin main locally so your local main matches remote.
Ensure REPORT.md is added, committed, and pushed to the main branch (or leave it in multifile-build until you are ready to merge).
Push any remaining tags: git push origin --tags.
9. Sample GitHub release description (copy/paste)
Title: Version 0.1.1: Multi-file Build

Description: Basic multi-file compilation for libmyutils. This release contains:

Sources in src/ (string and file utilities)
Recursive Makefiles (top-level and src/)
Compiled binary bin/client (Linux x86_64)
End of Feature-2

FEATURE 3
Q1: Compare Makefile (Part 2) vs Makefile (Part 3). Key differences enabling static library

Part 2 Makefile compiled every .c and linked all resulting .o files into the executable directly (
(
T
A
R
G
E
T
)
:
(OBJECTS)).

Part 3 Makefile separates utility sources from main.c. It compiles utility sources into object files and then archives them into lib/libmyutils.a (using ar). The final executable is linked either by passing the .a file directly or by using -L/-l. So new variables: LIBDIR, LIB_SRCS, LIB_OBJECTS, LIB. New rules: build archive (ar/ranlib) and link main.o with the archive. This makes reuse and packaging easier.

Q2: What is ar and why use ranlib?

ar is the archiver: it packs one or more object files into a single archive file (.a). This archive is a static library that can be linked into executables.

ranlib creates (or updates) an index in the archive. This index speeds up the linker and makes archive contents discoverable by the linker on some systems. Many ar implementations support -s or rcs to create the index already; running ranlib afterward is a standard step to ensure portability.

Q3: When you run nm on client_static, are mystrlen symbols present? What does that tell you?

Yes — because static linking copies the needed object code from the archive into the final executable, symbols like mystrlen commonly appear inside the executable’s symbol table (unless stripped or aggressively optimized away). This shows the library’s code is embedded in the executable at link time, and the program no longer needs the .a file at runtime.

FEATURE 4
Feature-4 — Dynamic Library (shared object)
What I implemented
Built position-independent objects and created a shared library lib/libmyutils.so.
Modified Makefile to generate both static and dynamic versions and their respective executables: bin/client_static and bin/client_dynamic.
Demonstrated runtime library resolution using LD_LIBRARY_PATH and analyzed symbols with nm and readelf.
Answers to report questions
1) What is Position-Independent Code (-fPIC) and why is it needed?
Position-Independent Code (PIC) is compiled so the CPU instructions inside the compiled object do not assume the code will be loaded at a fixed memory address. Shared libraries can be loaded at different addresses in different processes, so PIC ensures code will work correctly no matter where it ends up in memory. We compile our library objects with -fPIC so they can be combined into a .so.

2) Why is there a size difference between static and dynamic clients?
The static client (client_static) includes copies of the library code inside the executable itself, so it grows larger. The dynamic client (client_dynamic) keeps the library code in libmyutils.so and only stores references to it; the actual code is loaded at runtime. This makes the dynamic executable much smaller.

3) What is LD_LIBRARY_PATH and why was it necessary?
LD_LIBRARY_PATH is an environment variable that tells the dynamic loader extra directories to search for shared libraries at program start. We set it to our project lib/ because the loader does not search project folders by default. This shows the loader is responsible for finding .so files at runtime; the linker step only notes the library name, the loader must locate it when the program runs.

FEATURE 5
Feature 5: Creating and Accessing Man Pages

Compare the Makefile (before vs after)
Before Feature 5: The Makefile only handled building the project and linking static or dynamic libraries. It did not support installation or documentation.

After Feature 5: A new install target was added.

It creates standard system directories (/usr/local/bin, /usr/local/share/man/man1).

It copies the compiled program (client) into /usr/local/bin so it can be run from anywhere.

It installs the man page (client.1) into /usr/local/share/man/man1 so users can read documentation using the man command.

Key Difference: The new Makefile simulates real-world software installation, not just compilation.

What is the purpose of man pages?
Man pages are the official Linux documentation system.

They allow users to access help directly from the terminal by typing man .

In our project, the client.1 man page provides a description, usage, and author information for the program.

This makes the project feel professional and user-friendly, because the program has built-in documentation accessible like any standard Linux command.

Why add an install target?
Without install, the user would have to run the program from the build folder and remember paths manually.

With install, the program and man page are copied into the system-wide directories where Linux expects them.

This means:

Users can just type client instead of ./bin/client.

Users can type man client to see documentation.

In professional projects, this is how software is packaged and distributed, making it easy for anyone to use after installation.
