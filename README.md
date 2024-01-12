# CEW-OEL
<br>
#Project Description:
<br>
Construct an integrated environmental monitoring system in C, covering a range of fundamental concepts and practical applications. The project involves interacting with a free API that provides real-time environmental data. The system's core functionalities include data retrieval, processing, analysis, and reporting. The project has been created on Linux OS and the main program will run on a shell script on Linux’s terminal. It is designed to display the visibility of a certain location on an hourly basis and send an alert if the visibility of the location goes below a certain value. The program will generate a report at the end of the day.
<br>
#How to use this project?
<br>
To run the program, you need to compile all C files and run the main.sh file on the Linux terminal.
<br>
#Jansson Library
<br>
The project uses Jansson library that needs to be installed.
open the terminal and write the following commands one by one
<br>
command 1: sudo apt install cmake 
<br>
command 2: wget https://digip.org/jansson/releases/jansson-2.13.tar.gz  <br>
command 3: tar -xf jansson-2.13.tar.gz  <br>
command 4: cd jansson-2.13  <br>
command 5: cmake .  <br>
command 6: sudo make install  <br>
to compile the file= Command: gcc datafetching.c -o datafetching -ljansson -lcurl  <br>
