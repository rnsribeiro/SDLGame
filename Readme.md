### Para compilar um código escrito em SDL

```bash
g++ -std=c++11 main.cc Game.cc TextureManager.cc GameObject.cc Player.cc -o main `sdl2-config --cflags --libs` -lSDL2_image
```

### Para executar o programa

```bash
./a.out
```