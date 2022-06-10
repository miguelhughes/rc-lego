# RC lego
DIY project for building remote controlled lego cars and adding power functions to lego, using Arduino, 3d printer and cheap available electronic components

Here you'll find code, 3d models & parts list for getting started with you own version of this, and/or mix & match to get the best for your requirements. Contributions are welcome and encouraged!

The motors & servos are controlled with PS3 controller, and can be also easily modified to work with a PS4 (Although I haven't tried yet)

# Why?

My kid was always bugging me to get him a Remote Controlled car for his birthday. As much as I understood his feeling, I didn't want to get him something that would end up in a landfill in 1-2 years, and would add nothing to his development and creativity. So I decided to make him a power Lego kit with arduino and 3d printed parts, so that he can build his own RC car and other stuff as well!
This kit is easily fixed and upgraded, and can be an entryway to programming and electronics for your kids as well

# Videos & Photos:
[Here's a version of a tank mode car](https://youtu.be/UGNO0eF9Yjw), that drives very much like a bob cat. Very easy to build and fun to drive.

With some lego technic, I was also able to build a [car with steering](https://youtu.be/Ge-JHIiQ8DI). Not the prettiest, but still fun!

complete photo & video collection:
https://photos.app.goo.gl/P4w6zJVzxgqLykxx8

# Parts list:
## Required: 

- Play Station Controller (PS3 recommended, others not tested) 
- Arduino Uno
- Arduino motor shield
- Arduino USB shield
- Bluetooth USB Dongle

## Recommended
- 2x 18650 Li-ion batteries *
- 18650 battery holder *
- Up to 4 TT Gearbox Dc motors https://www.adafruit.com/product/3777

*I tried using 4x 1.2v rechargable AA batteries, and I didn't like the result. On their own they could move a couple of the motors, but through the arduino shield they would barely move. I didn't try a 9v battery, I've seen a couple of projects using that so it might work. If you do try that route, let me know! The motor shield would handle the different voltages without issues.

## Optional
- 2 SG90 micro servos

## 3d parts

see 3d models/readme.md

# Control
Right hat's Y axis controls motor 4, X controls Servo 2. Likewise, Left hat Y controls motor 3 and X axis servo 1. 
arrows up & down will control motor 1 and left & right motor 2. 
So to use tank mode, you must plug the two right motors to motor 4 terminal, and the two left motors to motor 3 terminal. Why not one motor to each terminal, you might wonder? Because there's a conflict between the motor shield and the usb shield, and sadly motor 1 has no "speed" control, it always goes full speed.

To help wiring here I build 4 2-to-1 female to male jumper wires. (TODO: Add pictures)
 


