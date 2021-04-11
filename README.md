# mearm-stm32f429i
Control the MeArm robotic arm (Kitronik MeArm Classic Maker Kit) from STM32F429I-DISC1 board. Project was made in TouchGFX and STM32CubeIDE.

# Table of contents

* [General info](#general-info)
* [Pinout](#pinout)
* [Schematic](#schematic)
* [Screens](#screens)
* [Video](#video)
* [TODO](#todo)


# General info

The goal of this project was to create interface for MeArm robotic arm. I chose STM32F429I-DISCO1 board with touch screen. 

# Pinout

Pinout of STM32F429ZI is shown below:
<p align="center">
  <img align="center" src="/Img/pinout.png">
</p>

# Schematic

<p align="center">
  <img align="center" src="/Schematic/circuit diagram.png">
</p>

# Screens

## Main screen

<p align="center">
  <img align="center" src="/Img/screenshot.png">
</p>

On this screen you can control position of robotic arm with 3 sliders. State of manipulator (opened - closed) is controlled with button.

## Sequence recorder

<p align="center">
  <img align="center" src="/Img/screenshot2.png">
</p>
<p align="center">
  <img align="center" src="/Img/screenshot3.png">
</p>

On this screen you can record sequences of positions and play them with different speeds. Screen description below:
 1 - Save button - Save created sequence to flash memory to restore it after microcontroller restart
 2 - Info text area - Displays information and errors
 3 - Clear button
 - Short press - Delete last position from the list
 - Long press - Delete all positions from the list

 4 - Positions list - Scrollable list of all added positions. Click on element to move arm to clicked position
 5 - Back button - Close window and go back to Main screen
 6 - Add new position - Add current arm position to positions list
 7 - Play sequence - Start playing created sequence of positions
 8 - Change speed button - Change sequence speed
 9 - Pause/Resume button - Pause/Resume sequence
 10 - Stop button - Stop playing created sequence of positions

# Video

<p align="center">
<a href="http://www.youtube.com/watch?feature=player_embedded&v=v-BcKC6yjKo
" target="_blank"><img src="http://img.youtube.com/vi/v-BcKC6yjKo/0.jpg" 
alt="YouTube video" border="10" /></a>
</p>
<p align="center">
<a href="http://www.youtube.com/watch?feature=player_embedded&v=I4xNoNbD62k
" target="_blank"><img src="http://img.youtube.com/vi/I4xNoNbD62k/0.jpg" 
alt="YouTube video" border="10" /></a>
</p>

# [More info (in polish)](https://narolski.eu/2021/02/28/mearm-stm32f429i/)

# TODO
- Increase resolution of PWM duty
