Connect Four
=============
With alpha-beta pruning search algorithm. Built with C++ and ClanLib

What is it?
------------
It's a simple implementation of the board game [Connect Four](http://en.wikipedia.org/wiki/Connect_Four).
Use the keys 1-7 to throw a coin into the according column.

![Screenshot](/docs/Screenshot.jpg?raw=true)

Requirements
------------
What you need for compiling:
* Visual C++ or rather Visual Studio 2010 or above
* DirectX SDK June 2010 (http://www.microsoft.com/en-us/download/details.aspx?id=6812)
* ClanLib Game SDK (http://clanlib.org/wiki/Download)

How to compile
------------
1. Set up ClanLib by following these instructions: http://clanlib.org/wiki/MainDocs:Visual_C%2B%2B_on_Windows
2. Get the source code and open the project in Visual Studio
3. In the menu bar, click on VIEW and open the PROPERTY MANAGER
4. In the Property Manager Window, expand the tree and double click "Microsoft.CPP.Win32.user" under "Debug | Win32"
5. You will see the Property Pages Window. Click VC++ Directories
6. Edit the Include Directories and add the include directory of your DirectX SDK, e.g. "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include", as well as the include directory of ClanLib.
7. Click okay and edit the Library Directories. Add the Lib Directories of your DirectX SDK, e.g. "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x86" and "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x64"
8. Also add the lib\win32 Directory of ClanLib
9. Close the Property Pages Window and repeat steps 4-9 but with "Microsoft.CPP.Win32.user" under "Release | Win32"
10. Hit Build :)

License
------------
(The MIT License)
Copyright (c) 2012 David Pertiller <david@pertiller.me>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
