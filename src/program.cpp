/*
 * Connect Four - with Alpha Beta Search Algorithm
 * Copyright (C) 2012 David Pertiller <http://pertiller.me>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "precomp.h"
#include "program.h"
#include "Game.h"
#include <ClanLib/application.h>

CL_ClanApplication clanapp(&Program::main);

int Program::main(const std::vector<CL_String> &args)
{	
	try
	{
		CL_SetupCore setup_core;
		CL_SetupDisplay setup_display;
		CL_SetupGL setup_gl;
		CL_SetupGUI setup_gui;


		CL_DisplayWindowDescription desc;
		desc.set_title("Vier Gewinnt - David Pertiller");
		desc.set_size(CL_Size(600, 550), false);
		desc.set_allow_resize(false);

		CL_DisplayWindow window(desc);
		CL_InputContext ic = window.get_ic();
		CL_InputDevice keyboard = ic.get_keyboard();

		window.sig_window_maximized();

		Game Game(window);
		Game.Run(window);

		return 0;

	}
	catch(CL_Exception &exception)
	{
		// Create a console window for text-output if not available
		CL_ConsoleWindow console("Console", 80, 160);
		CL_Console::write_line("Exception caught: " + exception.get_message_and_stack_trace());
		console.display_close_message();

		return -1;
	}
}
