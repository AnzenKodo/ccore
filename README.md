## MSVC Flags

```sh
$protection="-GS -EHa /guard:cf -sdl -Qspectre -fsanitize=address"
$checks="-W4 -analyze"
cl main.c -c -nolog -Z7 $protection $checks -I<include_path> -Fo<obj_path>

$protection="-CETCOMPAT -DYNAMICBASE -HIGHENTROPYVA"
link <obj_path> <libs_path> -DEBUG -OUT:<output_path> $protection -logo
```


## Interesting Projects

- [Writing a C Compiler](https://norasandler.com/book/)
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)

## Helpful Links

- [CS50 Manual Pages](https://manual.cs50.io)
- [Pre-defined C/C++ Compiler Macros](https://github.com/cpredef/predef)

## Libraries

- [C Language Tools](https://www.c-language.org/tools)
- [Handmade Math](https://github.com/HandmadeMath/HandmadeMath)
- [gb](https://github.com/gingerBill/gb)

### Lists

- [stb](https://github.com/nothings/stb)
- [C Algorithms Library](https://fragglet.github.io/c-algorithms/doc/)
- [A list of open source C libraries](https://en.cppreference.com/w/c/links/libs)
- [List of single-file C/C++ libraries](https://github.com/r-lyeh/single_file_libs)

## Reference

- [Handmade Hero](https://github.com/cj1128/handmade-hero)
- [draw a circle in c lang.](https://gist.github.com/corehello/3fb71d7bde82d1cf161ab8ed07949d6a)
- [OpenGL Xlib Example](https://github.com/vbsw/opengl-xlib-example)
- [Create an OpenGL context using Xlib and EGL](https://gist.github.com/pedrominicz/2d81559c5fb66d23d6bb627570956605)
