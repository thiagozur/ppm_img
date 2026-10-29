# Compilación

PS:

```powershell
gcc iv.c -o iv.exe -I"<path-to-sdl2.x.x>/x86_64-w64-mingw32/include/SDL2" -L"<path-to-sdl2.x.x>/x86_64-w64-mingw32/lib" -lmingw32 -lSDL2main -lSDL2 -mwindows
```

# Uso

cmd:

```cmd
type <path-to-image.ppm> | .\iv.exe
```