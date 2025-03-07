# Motion-Control
ME 360 Arduino Controlled 12V DC Motor Project

speed_readout uses the 12V motor encoder to tell you the speed the motor is spinning

fast_motor_control creates a velocity profile with constant acceleration up to a target speed before returning to a stop

fast_motor_displacement rotated the motor one full rotation and holds it in place. if you try to turn the motor further it returns to the location after one rotation.

the final file was used to move a cart a specified distance before returning to the start. this program includes a variable kp control to try and limit large jumps in voltage when the motor is spinning at lower speeds. radius, dist and amax are changed to specify a target distance and acceleration for a given wheel radius.
