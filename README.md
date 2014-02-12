tetris
=========

## with C, OpenGL & GLUT

![tetris](https://github.com/vichou/tetris/raw/master/screenshots/tetris-1.png)

Written quickly as a student ( it shows )

### OSX Compile 

    gcc -o tetris -framework glut -framework OpenGL tetris.c

### Linux Compile 

    gcc -o tetris -lglut -lGLU -std=gnu99 -lm tetris.c

and ignore the hundreds of deprecated api warnings.
