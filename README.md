# README

This is a possible implementation of a hash table data structure in C++.
This hash table uses **open addressing** and **STL tuples** instead of a custom node class.
Also, it allows substituting hash algorithm on a template level.

### Overview

Specifics of this implementation is that it, again, uses open addressing and its code looks stylish and complemented with comments.
Also, I decided to store the implementation of a class in a separated `.cpp` file, rather than keep it inside the `.h` file. 
It supposed to improve, in order, code performance, since functions treated as regular ones, rather than inline and, in my opinion, readability, since absent inline code does not distract reader, while header file still provides enough information about API of the class.

This class was written as a test case for an internship application.

##### Additional info

If you would have prefered to have the implementation in the same `.h` file, it's as easy as copypasting the source and removing unneeded anymore constructions.

Otherwise, to use it, one has to include `.cpp` file into one's project instead of `.h`. 
Like `#include "../hash_map_implementation.cpp"` and so on.
Look up `./test/` folder (check `Makefile`) for example(s).

## LICENSE

This code was written by me from scratch, so I have all the power to give it away with no restrictions.
Feel free to use it however you want. If this code was useful to you in any way, the author is glad to help.
If so, feel free to star this repository. 

