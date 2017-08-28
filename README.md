# mct-usc
Mathematica Controls Tool @ USC

To run a new project on QT Creator, first update the build/run options as such:
1) Open .pro file
2) Projects -> Build -> Disable Shadow Build
3) Projects -> Run -> Change working directory to where .pro is located, ie /Users/derekcheng/GitHub/mct-usc/cs104_example
4) Add Command Line Arguments (if necessary) with Projects -> Run ->  Command line arguments
5) Projects -> Run -> Uncheck "Add build library search path to DYLD_LIBRARY_PATH"
6) Build with Command + B
7) Run with Command + R