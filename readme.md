#Linear Stage Controller v0.2 source#

24/05/2016
Phil McCarthy

---

##Overview##

This repository contains a simple web app written in Python to control a linear stage using a web user interface. 

##Build instructions##

Get [Python](https://www.python.org/) for your particular platform, install it, then goto the repository directory and type

	pip install -r requirements.txt
	RunShim.py

Open a browser (currently needs to be on same machine as script is run from, but that's modifiable) and go to http://127.0.0.1:5000. You will see the GUI, and moving the dial will send data to a function running in the script (to be wired up).

##Legal stuff##

Copyright (c) 2016 Phil McCarthy

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

jQuery-Knob is Copyright (c) 2016 Anthony Terrien, see https://github.com/aterrien/jQuery-Knob for code and license.

##TO DO##

- Plug in actual code to control the stage.