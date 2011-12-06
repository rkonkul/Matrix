Ryan Konkul
rkonku2
CS340
Project 2: Matrix Library

The data structures I chose were very simple: a 1 dimensional array and an int for rows and an int for cols. For simplicity, I chose to use a 1d array to represent a 2d Matrix. I store the values in the array in row major form, that is each row is right next to each other in the array. To properly implement the array on the heap, I use a pointer. To manage the memory, I overload the deconstructor, copy constructor and assignment operator. The deconstructor simply deletes the array residing on heapspace. Copy constructor copies the data from the parameter and returns a new Matrix. The assignment operator first checks for self-assignment. Then it deallocates the memory in the left side operand. And finally it copies the new data.

The default constructor is a 2x2 matrix with only zeros. This is to avoid situations that may occur when the matrix is empty. The scalar multiplicated had to be implemented as functions to enable the double be the left side operand. In addition, and multiplication, I pass all matrices by value to enable cascading of operations such as
a = b * c + d * d;

The overloaded outstream(<<) operator outputs the matrix in a form that is readily accepted back with the instream: 
[row] [col]
[a11] [a12]
[a21] [a22]

To deal with errors in general, I report the error, and return a bogus value or bogus matrix to signify an error has occurred.

