To run with QT Creator:
1) Open hw8.pro
1) Projects -> Build -> Change build directory
2) Projects -> Build -> Build Steps -> Add make argument filename.dat
3) Projects -> Run -> Uncheck "Add build library search path to DYLD_LIBRARY_PATH"
4) Run with Command + R

On Linux:
hw8.pro is the .pro file for this program. Compile with qmake and make, and run with 
./hw8 filename.dat
