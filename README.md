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

We designed the android application with the help of [MIT App Inventor](https://appinventor.mit.edu) website. It uses simple predefined components that help with design by drag and dropping, and the coding part is done using the [Scratch](https://en.wikipedia.org/wiki/Scratch_(programming_language)) visual programming language.

First idea was to send numbers for the buttons, but we encountered a problem with the serial communication. The problem was that when we send a two digit number the digits are sent seperately(for 10, it sends 1 and 0). So we settled on sending letters. We used the numbers(1-9) for the intensity of the lights.

Here is the preview of the code:

![MIT_Scratch](https://github.com/Dimitry4Now/Smart-Home/assets/68469701/a2913e98-5b47-4ebb-a9b6-f491c7272767)

The application looks something like this(the preview on the website is worse, it looks better on a real device):

![MIT_Screen](https://github.com/Dimitry4Now/Smart-Home/assets/68469701/255ceb4a-22fc-47e1-8db2-f219210a1909)

The project file(.aia) can be found in the android folder of this project.

## Arduino part

On the arduino side of things, we are parsing the input from the bluetooth(recieved by the Android application) and doing stuff according to it. We tried to segment the code into functions so it is more readable.We tried to comment all parts of the code as well.

Here is the schematic of the project:

![ArduinoMaketa](https://github.com/Dimitry4Now/Smart-Home/assets/68469701/605375c0-7b4a-49ee-adde-d3bf5909054d)

The arduino source code can be found under the arduino folder of this project.

## Demo(Application in action):

[DEMO #1 - General functionality](https://www.youtube.com/watch?v=KkPbJu2hXiY)

[DEMO #2 - Distance sensor and photoresistor](https://www.youtube.com/watch?v=q9nXN4759RY)

Made by: [Predrag Spasovski](https://github.com/predrag1998) & [Dimitar Betinski](https://github.com/dimitry4now)
