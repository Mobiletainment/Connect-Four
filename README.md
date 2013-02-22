Connect Four
=============
With alpha-beta pruning search algorithm. Built with C++ and ClanLib

What is it?
------------
It's a simple implementation of the board game {Connect Four}[http://en.wikipedia.org/wiki/Connect_Four].

Requirements
------------
What you need:
* Visual C++ or rather Visual Studio 2010 or above
* DirectX SDK June 2010 (http://www.microsoft.com/en-us/download/details.aspx?id=6812)
* ClanLib Game SDK (http://clanlib.org/wiki/Download)

Getting Started
------------
1. Set up ClanLib by following these instructions: http://clanlib.org/wiki/MainDocs:Visual_C%2B%2B_on_Windows
2. Get the source code and open the project in Visual Studio
3. In the menu bar, click on VIEW and open the PROPERTY MANAGER
4. In the Property Manager Window, expand the tree and double click "Microsoft.CPP.Win32.user" under "Debug | Win32"
5. You will see the Property Pages Window. Click VC++ Directories
6. Edit the Include Directories and add the Include Directory of your DirectX SDK, e.g. "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include"
7. Also add the Include Directory of ClanLib
8. Click okay and edit the Library Directories. Add the Lib Directories of your DirectX SDK, e.g. "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x86" and "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x64"
9. Also add the lib\win32 Directory of ClanLib
10. Close all Windows and hit Build :)

License
------------
(The MIT License)
Copyright (c) 2012 David Pertiller <david@pertiller.me>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
