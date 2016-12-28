Linear - Line Follower
===

This sketch defines a basic line follower Arduino bot.

## Libraries used:  
* Pololu QTR Sensors [link](https://www.pololu.com/docs/0J19/all)
* Pololu DRV8835MotorShield [link](https://github.com/pololu/drv8835-motor-shield)

The sketch uses a P[Ignored]D loop to determine what speeds to add/deduct from the current speed of each motor based on a reflectance sensor's readings. These readings tell the robot how far the robot has deviated to the left or right of the line based on the distance from the center of the sensor.
