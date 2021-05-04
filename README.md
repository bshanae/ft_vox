![](resources/gifs/demo.gif)

# ft_vox

This project is about creating a minecraft engine in C++ and OpenGL.
Main goal is efficiency - chunk generation is done with asynchronous tasks system. 

## Features

* Block adding/removing
* Optimized algorithm for generating chunks
* Simple UI
* Many biomes : plain, mountains, lakes, forest, desert
* Collision test
* Transparent water
* Clouds
* Decorations : trees, grass and other

## Installation

Firstly install external libraries : 
```
./tools/install_libraries.sh
```

Then build the project :
```
./tools/build_project.sh
```

Now you can run executable :
```
./ft_vox
```

## Controls

* escape - exit
* left mouse - remove a block
* right mouse - put a block (the one you removed last time)
* w/a/s/d/space - move around
* shift + w/a/s/d/space - move faster
* cmd + p - enable/disable wireframe mod
* cmd + s - enable/disable skybox
* cmd + v - switch visibility distance (if this option is enabled in defines.h)
* cmd + f + '+' - increase FOV
* cmd + f + '-' - decrease FOV

## Resources

* [A Fast Voxel Traversal Algorithm for Ray Tracing](http://www.cse.yorku.ca/~amana/research/grid.pdf) - Ray casting for partitioned space
* [Cast ray to select block in voxel game](https://gamedev.stackexchange.com/questions/47362/cast-ray-to-select-block-in-voxel-game) 
* [Generating terrain in Cuberite](http://mc-server.xoft.cz/docs/Generator.html) - Generation of biomes and other stuff
* [OpenGL, Color mixing](https://habr.com/ru/post/343096/) - Transparency sorting
* [MUTEX: Write Your First Concurrent Code](https://medium.com/swlh/c-mutex-write-your-first-concurrent-code-69ac8b332288) - C++ multithreading
* [Generating terrain in Cuberite](http://mc-server.xoft.cz/docs/Generator.html) - Insights for terrain generation
* [6 Types of Noise Textures in Godot, and how to make them!](https://www.youtube.com/watch?v=ybbJz6C9YYA) - Simple implementations of some noise algorithms 