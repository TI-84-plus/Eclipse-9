2D Open-World Game
==================

A work in progress game inspired by factorio and minecraft, its a 2D inifinite open world.

its a personal project that i have been working on for long time. iam doing Procedural map generation using opensimplex noise.

iam using sfml library for graphics, inputs, networking, audio etc.


Images
======

![Screenshot_20250123_214745](https://github.com/user-attachments/assets/8f19d678-982e-4af1-9319-41f58b954be4)
![Screenshot_20250123_214101](https://github.com/user-attachments/assets/9c94fd5c-3614-4f49-87d5-ecc9f536029b)


Compilation
===========

the sfml source is already provided with the repo so no need to install it seperately

Windows
-------

- Install [CMake](https://cmake.org/download/) if you dont already have it

Linux
-----

- install [CMake](https://cmake.org.download/) if you dont already have it:
  - Installation by PPA
    ```sh
    sudo apt-get install software-properties-common
    sudo add-apt-repository ppa:george-edison55/cmake-3.x
    sudo apt-get update

    sudo apt-get install cmake
    ```

  - Installation by compiling source 
    - Download:
      ```sh
      $ wget http://www.cmake.org/files/v2.8/cmake-2.8.3.tar.gz
      ```
    - Extration of cmake source code from downloaded file:
      ```sh
      $ tar xzf cmake-2.8.3.tar.gz
      $ cd cmake-2.8.3
      ```
    - Configuration:
        ```sh
        make
        ```
    - Installation:
        ```sh
        make install
        ```
Building
========

- Clone the repository:

  ```sh
  git clone https://github.com/TI-84-plus/SFML-procedural_terrain_generation/
  ```
- cd into repo and create build directory:
    ```sh
      cd Proc_Gen
      mkdir build
      cd build/
    ```
- build
  ```sh
      cmake ..
  ```
  run
  ```sh
    ./bin/CMakeSFMLProject
  ```

  more features, bugfixes etc are coming soon.....

    



