# Register-Sim

A distributed execution simulator written in C that takes as input a number of processors and simulates how they transfer information from a register to another. In simulation there are several operations that are used:
* set X Y - set value of Y in register X
* add X Y - add value of X to Y
* mul X Y - set value of register X to product between Y and old value of X
* mod X Y - set value of X to X modulo Y
* jgz X Y - jump if greater than zero (X > 0) Y instructions (negative Y means jump back and positive Y means jump forword)
* snd X - send value of X to another processor
* rcv X - receive value from another processor and save it in register X
The simulation stops when there are no more events or deadlock occured.


## Installation
```
git clone https://github.com/andrei-stratila/Register-Sim.git
cd Register-Sim && make
```

## How it works!

The generated executable takes two folders as arguments: first is the input filename and the second is the output filename.
```
./register-sim *<input_file>* *<output_file>*
```
The input file has on the first line number of the processors used and the followings contains a different event on each line.
The output file contains on line i the not-null value of registers in the processor i.
