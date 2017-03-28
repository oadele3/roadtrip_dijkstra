# hw7 roadtrip, due: Saturday, Nov 10, 11:50 p.m.

You will create a C++ program that will simulate roadtrip(s) a student takes to do on-site job interviews in various Texas cities.
The fundamental data structure concept to practice is graphs (via finding shortest path).

## Input

The input file contains information of distance between cities and what trip(s) to plan.
The information on this file will correspond to a weighted graph (undirected).

Example cities input-file:

      # city1, city2, distance
      Tyler	Longview	1
      Texarkana	Longview	3
      Texarkana	Sherman	6
      WichitaFalls	Sherman	7
      Dallas	FortWorth	1
      WichitaFalls	FortWorth	5
      Abiline	FortWorth	7
      Dallas	Sherman	2
      Longview	Sherman	5
      Dallas	Tyler	3
      Odessa	Midland	4
      Lubbock	Midland	6
      Lubbock	Abiline	9
      Lubbock	Odessa	8
      Lubbock	WichitaFalls	14
      Amarillo	WichitaFalls	18
      ElPaso	Odessa	13
      ElPaso	Midland	16
      ElPaso	SanAntonio	30
      SanAngelo	SanAntonio	17
      Waco	Killeen	3
      Austin	Killeen	4
      FortWorth	Killeen	6
      Abiline	Killeen	8
      Waco	Tyler	4
      McAllen	Brownsville	2
      McAllen	Laredo	6
      Austin	SanAntonio	3
      Laredo	SanAntonio	9
      SanAngelo	Abiline	3
      SanAngelo	Odessa	6
      SanAngelo	Midland	4
      Victoria	CorpusChristi	3
      McAllen	CorpusChristi	7
      Laredo	CorpusChristi	8
      Brownsville	CorpusChristi	6
      Houston	Beaumont	3
      CollegeStation	Beaumont	7
      Austin	CollegeStation	4
      Houston	CollegeStation	4
      Tyler	CollegeStation	7
      Houston	Victoria	6
      Houston	Austin	7
      trip   Houston  Austin
      trip   Houston  McAllen
      trip   Dallas  ElPaso

The items of each line are separated by one tab character and are as follows:

1. The name of a city.

2. The name of another city.

3. The distance between the two cities.

After all cities and their distances are listed, there will be one or more **trip** lines that indicate the departure city, and destination of a trip.
In the example, the student is in Houston and goes to interview to Austin on her first trip.
On her second trip, she departs from Houston but goes to interview to McAllen.
On her third trip, she departs from Dallas and goes to interview to ElPaso.

## Program specification

The main program should be called `roadtrip` and the syntax in which it will be tested is as follows:

`./roadtrip "input=FILENAME"`

The parameter input specifies the name of the input file.

Example of program calls:

`./roadtrip "input=example.txt"`

The source code will be compiled as follows:

`g++ -std=c++11 -o roadtrip -I ./ *.cpp`


For each trip, your program will:

  * Figure out the shortest-path from the departure to the destination city (determined via Dijkstra's shortest-path algorithm).
  * Output each city of the path starting with the departure city upto and including the destination city.
    * Any city in the path (other than the departure and destination cities) is an `intermediate` city.
  * Figure out the return trip via the shortest-path from the original destination city back to the original departure city (determined via Dijkstra's shortest-path algorithm).
    * Any `intermediate` city already visited should never be part of the return path. This is because the student wants to visit new cities on the way back.
  * Output each city of the return path starting with the destination city upto and including the departure city.
    * Similarly as on the path to do the on-site interview, any city along the return path (other than the departure and destination cities) is an `intermediate` city.
    * Every `intermediate` city should never be visited again.

# Output

Your program will output (such as via cout) the names of the cities along the various paths found, one per line.
Each line must be in the format of a city name followed by end-line character; for example: `cout << city << endl;`

Your program must follow the output format exactly to allow for automated grading
(and to avoid failing test cases due to things such as output of an empty line at the end).

## Output for the example input file

The first trip to be figured out is from Houston to Austin (and back). These two cities happen to be directly connected via the shortest path.
Hence the subset of the output for the first trip is:

    Houston
    Austin
    Austin
    Houston

The second trip to be figured out is from Houston to McAllen; maybe our student is going for on-site interview at Hamer Enterprises.
The subset of the output corresponding to the second trip is:

    Houston
    Victoria
    CorpusChristi
    McAllen
    McAllen
    Laredo
    SanAntonio
    Austin
    Houston

The third trip to be figured out is from Dallas to ElPaso.
The subset of the output corresponding to the third trip is:

    Dallas
    FortWorth
    Abiline
    SanAngelo
    Odessa
    ElPaso
    ElPaso
    Midland
    Lubbock
    WichitaFalls
    Sherman
    Dallas

## Assumptions

It is OK for you to assume the following:

  * Names of cities will contain letters only, and the names will be exactly one word (of at least one letter but no bigger than 156 letters)
  * Each input file can fit in main memory (not larger than 100Kb).
  * Lines are terminated with an end-of-line character.
  * Lines that start with the symbol `#` should be considered comments and therefore skipped.
  * All items in the input file (that is, columns) will be separated by one tab character (namely, `\t`).
  * The maximum number of roads connecting a city is 4.
  * There will not be test cases where two (or more) different shortest paths can be found.
  * The maximum distance of a road is 99.
  * There will not be test cases such as: `trip	Houston	Houston`

## Requirements

* Place your codes in a folder named: `hw7` (Failure to do so will cause your program to have a zero grade due to inability for doing automated grading).
* Your program should not produce any unexpected output because doing so will interfere with automated grading and some test cases will fail.
* You must code your own implementation of Dijkstra's algorithm.

## Last note

Maybe-useful map for the sample data in this assignment. See also the annotated file: map-texas.png in this folder.

![Texas Cities, subset](http://www.bls.gov/regions/southwest/images/18795.png)
