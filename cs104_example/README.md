To run with QT Creator:
1) Open hw8.pro and configure
2) Projects -> Build -> Change build directory to where cs104_example is located, ie /Users/derekcheng/GitHub/mct-usc/cs104_example
3) Projects -> Run -> Change working directory to where cs104_example is located, ie /Users/derekcheng/GitHub/mct-usc/cs104_example
4) Projects -> Run ->  Command line arguments -> twitter.dat
5) Projects -> Run -> Uncheck "Add build library search path to DYLD_LIBRARY_PATH"
6) Run with Command + R

On Linux:
hw8.pro is the .pro file for this program. Compile with qmake and make, and run with 
./hw8 twitter.dat