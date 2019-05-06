Code that simulates the behavior of logic gates.

This project will accept a file that contains a circuit description (specificed below). It will read this description and output the complete truthtable representative of all possibilities of the circuit's output behavior.

Input format:

• INPUT n : i1 · · ·in Declares n input variables. This directive must always occur first in a circuit description.

• OUTPUT n : o1 · · · on Declares n output variables. This directive must always occur second in a circuit description.

• NOT i : o Represents a not gate in logic design. Computes o = i.

• AND i1 i2 : o Represents an and gate in logic design. Computes o = i1i2.

• OR i1 i2 : o Represents an or gate in logic design. Computes o = i1 + i2.

• NAND i1 i2 : o Represents a nand gate in logic design. Computes o = i1i2

• NOR i1 i2 : o Represents a nor gate in logic design. Computes o = i1 + i2

• XOR i1 i2 : o Represents an xor gate in logic design. Computes o = i1 ⊕ i2, where ⊕ indicates exclusive or.

• DECODER n : i1 · · ·in : o0 · · · o2n−1 Represents an n : 2n decoder gate in logic design. The first argument gives the number of inputs, n. The next n parameters are the inputs, followed by 2n parameters indicating the outputs. The inputs are interpreted as an n-bit binary number s in the range 0, · · · , 2n − 1. The output os will be 1 and all others will be 0.

• MULTIPLEXER n : i0 · · ·i2n−1 : i01· · ·i0n : o Represents a 2n : 1 multiplexer gate in logic design. The inputs to a multiplexer are either regular inputs or selectors, indicated by i and i0, respectively. The first parameter, n, gives thenumber of selectors. The next 2n parameters give the regular inputs, followed by n selector inputs, and finally the output.The selector inputs are interpreted as an n-bit binary number s in the range 0, · · · , 2n −1. The output is o = is.

• PASS i : o Represents the absence of a gate. Computes o = i. This may be used to convert a temporary variable into an output variable.

Example Inputs + Outputs:

INPUT 4 w x y z

OUTPUT 4 a b c d

OR w 0 a

AND x 1 b

NAND y 1 c

NOR z 0 d

Output:

0 0 0 0 | 0 0 1 1

0 0 0 1 | 0 0 1 0

0 0 1 0 | 0 0 0 1

0 0 1 1 | 0 0 0 0

0 1 0 0 | 0 1 1 1

0 1 0 1 | 0 1 1 0

0 1 1 0 | 0 1 0 1

0 1 1 1 | 0 1 0 0

1 0 0 0 | 1 0 1 1

1 0 0 1 | 1 0 1 0

1 0 1 0 | 1 0 0 1

1 0 1 1 | 1 0 0 0

1 1 0 0 | 1 1 1 1

1 1 0 1 | 1 1 1 0

1 1 1 0 | 1 1 0 1

1 1 1 1 | 1 1 0 0

INPUT 3 IN1 IN3 IN4

OUTPUT 1 OUT1

MULTIPLEXER 2 1 0 1 0 IN3 IN4 temp1

MULTIPLEXER 1 temp1 1 IN1 OUT1

Output:

0 0 0 | 1

0 0 1 | 0

0 1 0 | 1

0 1 1 | 0

1 0 0 | 1

1 0 1 | 1

1 1 0 | 1

1 1 1 | 1

INPUT 2 IN1 IN2

OUTPUT 16 OUT1 OUT2 OUT3 OUT4 OUT5 OUT6 OUT7 OUT8 OUT9 OUT10 OUT11 OUT12 OUT13 OUT14 OUT15 OUT16

DECODER 2 IN1 IN2 temp1 temp2 temp3 temp4

DECODER 4 temp1 temp2 temp3 temp4 OUT1 OUT2 OUT3 OUT4 OUT5 OUT6 OUT7 OUT8 OUT9 OUT10 OUT11 OUT12 OUT13 OUT14 OUT15 OUT16

Output:

0 0 | 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0

0 1 | 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0

1 0 | 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0

1 1 | 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0

INPUT 20 IN1 IN2 IN3 IN4 IN5 IN6 IN7 IN8 IN9 IN10 IN11 IN12 IN13 IN14 IN15 IN16 IN17 IN18 IN19 IN20

OUTPUT 1 OUT1

MULTIPLEXER 4 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 IN1 IN2 IN3 IN4 temp1

MULTIPLEXER 4 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 IN5 IN6 IN7 IN8 temp2

MULTIPLEXER 4 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 IN9 IN10 IN11 IN12 temp3

MULTIPLEXER 4 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 IN13 IN14 IN15 IN16 temp4

MULTIPLEXER 4 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 IN17 IN18 IN19 IN20 temp5

MULTIPLEXER 4 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 temp1 temp2 temp3 temp4 temp6

MULTIPLEXER 2 0 1 0 1 temp5 temp6 OUT1

Output:

44 MB truthtable, will not copy paste it here. (Takes approximately 15 seconds to generate)

Code Description: The project was accomplished using a large amount of array manipulation, and was a great practice for problem solving. In the project there are 12 main arrays, along with an additional linked list that comprise the data strucutres used in this project. The main steps of the process is as follows: To reduce the time needed to produce each row of the truth table, the file is read only once at the start with its information recorded and stored. In addition, to further reduce the time needed to generate the table, the truthtable is produced one row at a time, rather than storing the entire table in an array then traversing it and printing it at the end.

Reading the file: Used strtok and fgets to tokenize each line
a.	Inputs and Outputs: For the first 2 lines which will always describe inputs and outputs, tokenize both lines and advance past the first token on each to read the number of inputs and outputs. For the first line INPUTS, store variables into variableArray(1), and once you start tokenizing the second line, store the outputs into variableArray and outputArr, and once you reach the third line where the gate information is located, store what is currently in variableArray (only inputs and outputs) into copyArray (3) (will be used later). Then continue the same process, storing the variable names into variableArray.

b.	Everything else: When you tokenize each line after the second (output) line, it will always be the name of the gate first, which is stored into the gates(4) array. Use strcmp to see if the gate is either multiplexer or decoder, for which you need to record the number of inputs into array decMultN(5). Afterwards, record every variable into variableArray. At the end of reading the file, we should have a variableArray that stores each variable, copyArray which contains the names of input and output variables, and outputArr, which stores the names of output variables. 2.	Identifying temporary variables and variable occurrences:

a.	Now that we have variableArray(1) with every single variable used, and copyArray, which stores input and output variables, we make a new array compareArr, which will represent each unique variable as a unique digit. The first 2 indexes of compareArr are set to 0 and 1, which will be explained later. Afterwards, we scan variableArray until we hit the index 2 (from 0 and 1 in the first 2 indexes) + the number of input and output variables, which we know from reading the file earlier. As none of these variables repeat by nature of being input and output variables within these first 2 lines, we can assign their values equal to their index. For example, given

INPUT 3 A B C

OUTPUT 1 D

A will be assigned 2, B will be assigned 3, C will be assigned 4, and D will be assigned 5. Afterwards, using copyArray in which the names of both input and output variables are stored, we use a nested for loop to scan each variable in variableArray with those in copyArray. If they are equal, they are assigned numbers as described above- using the same example, every A in variableArray will be 2 in compareArr, every B in variableArray will be 3 in compareArr, and so on.

b.	Therefore, in each comparison if a variable in variableArray is not in copyArray, it means that it is neither an input or output variable, and is therefore a temporary variable. Because we are only given the number of input and output variables, we don’t know the number of temp variables, and will then have to store them in a linked list of variable size. In compareArr, we will assign them a -1.

c.	At the end of this process in A and B, we copy the linked list into an array called linkedList, and make another array called linkedListNum that eventually does that same thing described in A for temporary variables. At this point, in compareArr we have every input and output variable represented as a unique number, and every temp variable represented as a -1. We also have an array of temporary variables.

Generating the table
a.	In an outer loop, we first assign the inputs by making each row of the truthtable, starting with 0’s for each, and print out 0’s (for the first line) for each number of input variable, followed by a “ | “ character.

b.	We store each line of inputs into an array called array, and then store it into an array called table1, which is later copied into an array called table.

c.	At this point we have table, where the first indexes represent the inputted variable values of either 0 or 1 according to the current line in the truth table. Afterwards, the rest of the array is populated according to each line in the inputted file.

d.	To start populating the table array, we make an inner loop that traverses the gates array and tells us which gate is operated on using strcmp. There are 3 main cases, which are the PASS and NOT gates, the MULTIPLEXER and DECODER gates, and everything else. This is because PASS and NOT only have 1 input and output, while MULTIPLEXER and DECODER have variable numbers of inputs and outputs, and everything else only have 2 inputs and 1 output.

e.

As a recap, the arrays in order of appearance are:

variableArray

outputArr

copyArray

gates

decMultN

compareArr

firstList (linked list that is then copied into array called linkedList)

linkedListNum

array

table1

table

outputArray

THIS README IS INCOMPLETE, AND WILL BE FINISHED AT A LATER DATE -Eric
