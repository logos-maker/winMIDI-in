# winMIDI-in
A MIDI in example in C code for Windows. It will print out incomming MIDI messages to the CMD command prompt.

## Compilation on Windows
MinGW-w64 can be used to compile the code on Windows. I would recommend downloading [TDM-GCC](https://jmeubank.github.io/tdm-gcc/articles/2021-05/10.3.0-release) and downloading the installer named tdm64-gcc-10.3.0-2.exe Then after that you should be able to compile from the CMD Command Prompt. You can compile to generate a plugin .dll with a command like...
```
gcc plug_template.c -o win_MIDI_in.c -o win_MIDI_in.exe -lwinmm
```
If you don't want to use the CMD Command Prompt you can use a text editor that can run the single command needed for compilation is for example [Geany](https://www.geany.org/) or [Sublime Text](https://www.sublimetext.com/).

## Compilation on Linux (cross compilation to Windows)
Install the needed compiler commands with...
```
sudo apt -y install mingw-w64
```
If you want a 64-bit Windows plugin compile with a command like...
```
x86_64-w64-mingw32-gcc win_MIDI_in.c -o win_MIDI_in.exe -lwinmm
```
