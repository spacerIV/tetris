tetris
=========

## with C, OpenGL & GLUT

![game](https://github.com/vichou/tetris/raw/master/screenshots/game.png)

![menu](https://github.com/vichou/tetris/raw/master/screenshots/menu.png)

Written quickly as a student ( it shows )

### OSX Compile 

    gcc -o tetris -framework glut -framework OpenGL tetris.c

### Linux Compile 

    gcc -Wall -g tetris.c -lGL -lGLU -lglut -o tetris

and ignore the hundreds of deprecated api warnings.
