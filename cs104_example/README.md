Derek Cheng - CSCI-104 - Summer 2015

To run with QT Creator:
1) Projects -> Build -> Change build directory
2) Projects -> Build -> Build Steps -> Add make argument filename.dat
3) Projects -> Run -> Uncheck "Add build library search path to DYLD_LIBRARY_PATH"
4) Run with Command + R

hw8.pro is the .pro file for this program. Compile with qmake and make, and run with 
./hw8 filename.dat

Problem 2 
    a)
        i) This is a valid min heap
        ii) This is invalid, 5 is out of place
        iii) This is invalud, 5 is out of place

    b) Attached in problem1b.pdf

Problem 3
    My GUI interface has two main windows. 1) the login screen, and 2) the user's main menu. A user cannot use any of the twitter interface until they are logged in or register as a new user. Once logged in, the user can perform AND/OR searches (search), save the twitter data (save user data), save the connected components (save connected components), view trending topics (trending topics), or add tweets/followers (show tweets). Clicking show tweets will open up a new window where the user can add tweets, followers, and view his/her main and mention feeds.

    To switch users, simply logout from the user's main menu and log in as a different user. A user can only view and add tweets as themself; that is, Tommy cannot add tweets for Jill.

Also note that I accidentally pushed TwitLogin.h. This file is useless and isn't referenced by any class, which is why the code is all commented out. I didn't know how to remove it from the submission.


