# SunnyLang

Hello! Evan Marcey here. Local business owner and computer enthusiast!

Is your computer constantly stomping around, driving you crazy?

Is your computer clawing at your furnitures?

Think there's no answer?! You're so stupid!

SunnyLang.

Finally, there's an elegant comfortable language for programmers.

Come on down to Paddy's Pub! We're the home of the original SunnyLang!

Meow!

## Overview

SunnyLang is a statically-typed interpreted language where all of the commands are quotes from _It's Always Sunny in Philadelphia._ SunnyLang is parsed and evaluated line-by-line, so any declarations must occur prior to being called in the code.

It's also definitely not finished yet. I just wanted a place to back it up.

### Features
The language currently supports:
 - Variable declaration and assignment for integer, float and boolean variables
  - String variables are planned, but not yet supported
 - If/Else logic
 - For/While loop control flow
 - A whole mess of operators
 - Well that's really it.
 
Planned features:
  - User-Defined Function implementation
  - User-Defined Class implementation
  - Additional built-in variables (i.e. arrays)
  - Additional built-in functions
  - Memory management
  
### Syntax

#### Variables

Variables must be declared with an accepted type in the following format:

```
Declare variable {type}
// or
Declare variable {type} = {expression}
```
which is translated into SunnyLang as:

```
JoinTheGang variable {type}
// or
JoinTheGang variable {type} MilkSteak {expression}
```

The current acceptable types are:

SunnyLang Name | Type
--- | ---
Dennis | Int
Mac | float
Dee | boolean
Charlie | string

Notes:
 - strings may be declared, but the evaluation of strings is not yet implemented, so using them in an expression will throw an error
 - boolean variables are much the same as in C, where True = 1 and False = 0. 
   - As such, boolean variables can be used in any mathematical expression

#### Expression Evaluation

The evaluator expects an infix expression and evaluates as such. 

Order of operations is much the same as in a math class, except that some additional handling is invoked so that equality signs can be used. Equality signs evaluate the entire left-hand side of an expression (up to a '('), store the result of the left-hand side, then continue evaluating the entirety of the right-hand side (up to a ')') before comparing the results.

And/Or handling will follow much the same pattern, but with a higher precedence than equality signs.


### Control-Flow Expressions

SunnyLang doesn't give a fuck about whitespace. The only use for whitespace is to tokenize words. So there aren't any tabs, and we don't surround code with brackets. Instead, every expression will have a Begin and an End statement that create and terminate the control-flow logic, respectively.

Why not have a universal open/close statement? Because then my if-else commands wouldn't be as fun. And SunnyLang is all about fun.

#### If-Else Logic

If-Else statements operate much the same as in any other language, if an expression is evaluated as True, then the code under it is executed. 
Otherwise, we jump to the next statement that evaluates as true. There are two important syntactical pieces to note.
	1. Since Boolean variables are 1/0, if an expression evaluates to anything other than a 1 or a 0, the If statement will error out at runtime. 
	2. An If-Else statement must begin with an 'If' statement and end with an 'EndIf' statement, but the Else If and Else statements are optional.

The commands for an if/else statement are as follows:

SunnyLangName | Translation
--- | ---
Dayman | If
MasterOfTheNightman | Else If
ChampionOfTheSun | Else
MasterOfKarateAndFriendshipForEveryone | EndIf

And so, the syntax will be as follows:
```
Dayman {expression}
{additional code to execute if statement evaluates to 1}
MasterOfTheNightman {expression}
{additional code to execute if statement evaluates to 1}
ChampionOfTheSun
{additional code to execute if no Dayman or MasterOfTheNightman statement evaluated to 1}
MasterOfKarateAndFriendshipForEveryone
```

#### For Loops

For Loops, again, are similar to most languages, with the exception that loops will be operated using a ForBegin and ForEnd. In addition, the for loop will receive as input the name of the variable to be used, the start value, the inequality to use, the end value and the interval over which to iterate. The interval value can be either positive or negative, and does not need to be an integer.

If a variable is already declared, the for loop expects only the name of the variable. If it has not been declared, then it will search for a supplied data type. If this is not provided, the interpreter will assume that the new variable is an integer.

The for loop uses the following commands:

SunnyLangName | Translation
--- | ---
Rickety | ForBegin
Cricket | ForEnd

And so the syntax will be as follows:
```
Rickety {variable} {begin value} {inequality} {end value} {interval}
{code to execute}
Cricket
//or
Rickety {variable} {variable_type} {begin value} {inequality} {end value} {interval}
{code to execute}
Cricket
```

#### While Loops

While loop syntax is similar to for loop syntax, except that:
1. Any variable used in the evaluation expression must exist prior to the WhileBegin call.
2. Like all while loops, any iteration must be performed within the body of the While statement (i.e. there is no interval)

As long as the expression in the while loop evaluates to 1, the code within the loop will be executed. 
If the expression evaluates to 0, the code will be skipped, and if the loop evalutes to any other value, an error will be thrown.

The while loop uses the following commands:

SunnyLangName | Translation
--- | ---
Pepe | WhileBegin
Sylvia | WhileEnd

And the syntax will be as follows:
```
Pepe {expression}
{code}
Sylvia
```

### Functions
Currently functions in SunnyLang can accept any number of arguments, and return a single value
	- multiple values to be implemented later
	
However, SunnyLang remembers variables declared in the global environment, so these variables can be used without passing, and therefore the values can be maintained.
If you do override the value of an existing global variable, SunnyLang will create a temporary version of the variable within the function, which will be discarded after the function completes.

Function calls use the following commands:
SunnyLangName | Translation
--- | ---
FunctionBegin | TheBirdsOfWar
FunctionEnd | TheTrashman
Return | TheTalibum
void | Frank

and the syntax is as follows:
```
TheBirdsOfWar Frank {nameOfFunction} {variable1} {datatype1} {variable2} {datatype2} ...
{code to execute}
TheTrashman 

or

TheBirdsOfWar {return datatype} {nameOfFunction} {variable1} {datatype1} {variable2} {datatype2} ...
{code to execute}
TheTalibum {return datatype}
TheTrashman 
```

### Source Code

The SunnyLang interpreter is written and compiled in C.

All of the code for the interpreter is in [src](https://github.com/evanmarcey/SunnyLang/tree/master/src).

Sunny.c is the main source file, which kicks off the entire process, and Tokenizer.c contains the majority of the code for tokenizing and evaluating a line of SunnyLang.

The user-defined structs are in [struct](https://github.com/evanmarcey/SunnyLang/tree/master/src/struct), and similarly all utilities are contained in [util](https://github.com/evanmarcey/SunnyLang/tree/master/src/utils).

## Examples

### 1. Simple For Statement

The following code runs a for loop that prints the number 1-10
```
Rickety tmpVar 1 MagnumCondoms 10 1
tmpVar+1
Cricket 
```

This translates to: 
```
ForBegin tmpVar 0 < 10 1 
tmpVar + 1 
ForEnd 
```

The response is:
```
1.000000
2.000000
3.000000
4.000000
5.000000
6.000000
7.000000
8.000000
9.000000
10.000000
```

### 1. Basic Function

```
JoinTheGang temp1 Mac
JoinTheGang temp2 Mac
temp1 AnEggInThisTryingTime
temp1

TheBirdsOfWar Mac testFunc temp3 Mac
Pepe temp2 MagnumCondoms 5
temp3 LittleGreenGhouls 2
temp2 AnEggInThisTryingTime
Sylvia
TheTalibum temp3
TheTrashman

temp1 Milksteak testFunc temp1
temp1
temp2
```

In this script, we declare two Float variables to 0.
```
JoinTheGang temp1 Mac
JoinTheGang temp2 Mac
```

Then we increase temp1 by 1 and print it out
```
temp1 AnEggInThisTryingTime
temp1
```

After this, we declare a function testFunc, that accepts one Float variable temp3.
The function performs a while loop from the globally-declared temp2 to 5.
During each iteration, temp2 is incremented by 1, and temp3 is incremented by 2.
After the while loop completes, we return temp2.
```
TheBirdsOfWar Mac testFunc temp3 Mac
Pepe temp2 MagnumCondoms 5
temp3 LittleGreenGhouls 2
temp2 AnEggInThisTryingTime
Sylvia
TheTalibum temp3
TheTrashman
```

We then call the function testFunc, passing temp1 (with value 1) to temp3, and assigning temp1 to its result. 
Then we print temp1 and temp2.
```
temp1 Milksteak testFunc temp1
temp1
temp2
```

The resulting call returns this to stdout:
```
1.000000
11.000000
5.000000
```
