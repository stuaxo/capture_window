capture_window
--------------

Take a screenshot of a window from the commandline.



Examples
--------

On Windows 10, open a shell and run notepad

```shell
C:> notepad
```

Capture a picture of the content of the window using its class id:

```shell
C:> notepad -o notepad1.png Notepad
```

Use -d to also capture window decorations

```shell
C:> notepad -d -o notepad2.png Notepad
```


Use -t to find the window by its title:

```shell
C:> notepad -o notepad2.png -t "Untitled - Notepad"
```


Build - Visual Studio CMake
---------------------------

capture_window can be built using visual studios CMake support, after
right clicking the CMakefiles.txt and regenerating the cache.