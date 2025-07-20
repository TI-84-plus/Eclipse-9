Eclipse 9
==================

Eclipse 9 is an open, infinite-world game inspired by Factorio, built entirely from scratch — including the custom game engine. Every core system, from terrain generation and chunk streaming to autotiling and entity logic, was handcrafted and tightly integrated into the gameplay. This isn’t just a game project — it’s a full-stack engine and world simulation built for performance, scale, and creative flexibility.


Images
======

<img width="1920" height="1080" alt="Screenshot_20250721_020436" src="https://github.com/user-attachments/assets/63c35173-8a00-47f8-887c-3bae4ba7d2dc" />
<img width="1920" height="1080" alt="Screenshot_20250721_020744" src="https://github.com/user-attachments/assets/fb62e474-53e6-4f14-8d61-7432f90edebe" />



Compilation
===========

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

    



