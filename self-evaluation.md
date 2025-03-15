# Self-Evaluation

## Name(s): 

Out of 25 points. Use output.txt created using 
`./create-output.sh > output.txt 2>&1` for guidance.

Complete all questions with "Q:"

Q: Does the program compile and run to completion: Yes

- If the program does not compile or gives a segmentation error when run, 
the maximum possible grade is 50%. No need to continue with the rest of self-evaluation

Q: All public functions have been implemented: 0

- -2 for each functionality not implemented

For each command, state Full, Partial or None to indicate 
if it has been fully, partially or not implemented at all.
Explain any partial implementations.

Inventory: Full
History: Full
Borrow: Full
Return: Full


Q: -1 for each compilation warning, min -3: 0

- Check under *1. Compiles without warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-tidy warning, min -3: 0

- Check under *3. clang-tidy warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-format warning, min -3: 0

- Check under *4. clang-format does not find any formatting issues*


Q: -2 for any detected memory leak: 0

- Check under *5. No memory leaks using g++*
- Check under *6. No memory leaks using valgrind*

Q: Do the tests sufficiently test the code: 0

- -1 for each large block of code not executed
- -2 for each function that is never called when testing
- Check under *7. Tests have full code coverage* paying attention to *The lines below were never executed*

Q: Are all functions in .h and .cpp file documents (min -3): 0

- -1 for each function not documented

## Location of error message or functionality

State the file and function where the information can be found

invalid command code: command.cpp: CommandFactory::create

invalid movie type: movie.cpp; MovieFactory::create

invalid customer ID: borrow.cpp Execute(); 
 
invalid movie: TODO(student)

factory classes: movie.h, movie.cpp, drama.h, drama.cpp, classic.h, classic.cpp, comedy.h, comedy.cpp

hashtable: alphaHash.h; used for storing movie and command factories, and "parser" Movie objects

container used for comedy movies: store.h: map<char, vector<Movie *>, greater<char>> inventory;

function for sorting comedy movies: store.cpp AddMovie(): sort(list.begin(), list.end(), [](Movie *a, Movie *b) { return *a < *b; });

function where comedy movies are sorted: store.cpp AddMovie()

functions called when retrieving a comedy movie based on title and year: store.cpp findInInventory(); comedy.cpp getSorters()

functions called for retrieving and printing customer history: history.cpp: Execute

container used for customer history: customer.h vector<pair<char, Movie *>> history;

functions called when borrowing a movie: borrow.cpp Execute

explain borrowing a movie that does not exist: borrow.cpp Execute()

explain borrowing a movie that has 0 stock: borrow.cpp Execute()

explain returning a movie that customer has not checked out: return.cpp Execute()

any static_cast or dynamic_cast used: all operator< overload in drama.cpp, classic.cpp and comedy.cpp

## Bonus +5

Are there multiple files, of the form runit-without-XXX, where the same set of files will compile and run excluding some of the commands or genres? yes (runit-without-comedy.sh, runit-without-history.sh, runit-without-inventory.sh, runit-without-classic.sh)




Q: Total points: 25