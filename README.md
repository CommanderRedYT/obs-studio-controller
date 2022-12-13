# obs-studio-controller
DIY hardware + software to control obs studio


## What is this?
This project will be a do-it-yourself solution to control OBS Studio.

It will have a custom PCB, based on the ESP32, with rotary encoders, buttons and and optional tft display.
I am planning on having a NodeJS backend as there are already great librarys to connect to OBS Studio!
The backend will also host a website to configure the device.

I am also planning on making a Video series showing my path on creating this project.

Tl;Dr:

## Features

- [ ] Custom PCB containing digital and analog inputs, based on the Espressif 32 Microcontroller.
- [ ] A 3D printable housing for the electronics
- [ ] NodeJS backend for configuring or updating the device

More will be added after designing and testing!

## Updating
I am planning to implement Over The Air Updates as well as flashing via USB C.

The ESP32 software will be using the ESP-IDF. From experience I have noticed some usability problems, so I will be using GitHub CI to build and then host the binaries.

## Contributing
If you encounter any problems, or have improvements, feel free to open an Issue or even a Pull Request!
