capture_window
--------------

Take a screenshot of a window from the commandline.

Usage
-----

```
  capture_window.exe [OPTION...] [optional args]

  -d, --decorations  Capture window decorations
  -c, --clsid arg    Window class identifier (default: )
  -t, --title arg    Window title (default: )
  -o, --output arg   Output filename
  -l, --list arg     List windows
  -h, --help         Print help
```

Examples
--------

On Windows 10, open a shell and run notepad

```shell
C:> notepad
```

List window class ids and titles:

```shell
C:> capture_window -l
Class Identifier              Title:
Shell_TrayWnd
Notepad                       Untitled - Notepad
CabinetWClass                 thirdparty
```


Capture a picture of the content of the window using its class id:

```shell
C:> capture_window -o notepad1.png Notepad
```

Use -d to also capture window decorations

```shell
C:> capture_window -d -o notepad2.png Notepad
```


Use -t to find the window by its title:

```shell
C:> capture_window -o notepad2.png -t "Untitled - Notepad"
```


Build - Visual Studio CMake
---------------------------

capture_window can be built using visual studios CMake support, after
right clicking the CMakefiles.txt and regenerating the cache.
