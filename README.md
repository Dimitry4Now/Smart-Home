# Arduino smart home project

## General idea

This started as a team project for a subject called Microprocessors systems. The initial idea was to make an Arduino uno controlled lights.

After a while we decided to make an Android application in order to control everything via Bluetooth. 

## The project

The project consists of two parts:
- Android application
- Arduino Uno microcontroller, with:
  - HC-05 Bluetooth module
  - LEDs that simulate light bulbs in different rooms(one of those is RGB)
  - LCD1602 I2C display for displaying status
  - LDR sensor(Photoresistor)
  - HC-SR04 ultrasonic sensor for distance
  - Resistors, wires, protoboard

## Android part

We designed the android application with the help of [MIT App Inventor](https://appinventor.mit.edu) website. It uses simple predefined components that help with design by drag and dropping, and the coding part is done using the Scratch visual programming language.

First idea was to send numbers for the buttons, but we encountered a problem with the serial communication. The problem was that when we send a two digit number the digits are sent seperately(for 10, it sends 1 and 0). So we settled on sending letters. We used the numbers(1-9) for the intensity of the lights.

Namely, the code is very simple:
- 
