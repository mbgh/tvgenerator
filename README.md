TVGenerator
===========

A test vector file generator written in C++ for creating stimuli and expected
response files for hardware designs. These files can then be read by an
arbitrary test bench and applied to the design under test. The `TVGenerator` can
either generate a single test vector file containing both the stimuli and the
expected responses within a single file, or it can distribute it to two
distinct files.

Documentation
-------------

A documentation of the `TVGenerator` class, created using
[Doxygen](http://www.doxygen.org/), is available
[here](http://mbgh.github.io/tvgenerator/).

Prerequisites
-------------

The `TVGenerator` uses the
[`StdLogicVector`](https://github.com/mbgh/stdlogicvector) class in order to
represent signals of arbitrary length and to provide an easy to use conversion
between number representations of several bases (decimal, binary, hexadecimal,
etc.).

Usage
-----

Personally, I usually use the `TVGenerator` as a dynamic library and link it
against a certain *main* program, which uses it to generate the respective test
vector file(s). This *main* program is most of the time a testing environment
for a software model I have written for a certain hardware architecture I am
going to design.
