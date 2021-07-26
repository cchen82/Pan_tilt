## Arduino Pan_Tilt
Our project is intended to build a movable pan and tilt. As modern technology progresses, more and more robots are joining the manual labor force. In order to make those robots more capable, we need to develop a self-balancing system. So robots can handle more complex and humanoid tasks, such as keeping a glass of water stable while moving  as a waiter robot. To balance a platform, we need perception of platform attitude and control of it.

## Motivation
In some so called robot restraunts, there exist the robot waiters/waitressed. However, these robots are basically "wheeled plate" that can only deliver the food instead of serving them. This project tries to design a robot arm that could maintain the balance of the plate, which then can be used to serve a drink without spilling.

## Hardware
![alt text](https://github.com/cchen82/Pan_tilt/blob/wuji/image/image.PNG?raw=true)
## Demo Video is here:  
https://youtu.be/7a1tUkKl7bg  
## introduction video is here:  
https://drive.google.com/file/d/1Is1hj_6t_KWVfk3MZAUc0cFzajiSkAoP/view?usp=sharing  
## Tech/framework used
Arduino UNO, FreeRTOS, Accelerometer, Gyroscope, Servo Motors, and Motion Tracking Algorithm.

## Control System Diagram
![alt text](https://github.com/Kenny-Z/Pan_Tilt/blob/main/image/digram.PNG?raw=true)

## Methodology
The essential idea of the project is to use a feedback loop to keep the attitude of a platform as a desired value during movement.   
As is shown in the loop, the controlled variable is attitude, which will be measured by a combination of 3-axis gyroscope and accelerometer. The algorithm to track the motion (the attitude) will use the idea of quaternion and sensor fusion. We utilized IMU and ARHS(Attitude and Heading Reference System) sensor fusion algorithms based on an open-sourced version of Sebastian Madgwick’s work.  
The controller, Arduino, will process the error between the attitude setpoint and the actual attitude obtained from the sensor and take action accordingly, i.e. one classic PID control loop for each axis. If time permits, some feedforward control algorithms will also be tested for better performance.  
The actuators will be two servo motors which are set to control the row and pitch axis separately to keep the platform balanced. Another servo motor will be controlled by the joystick to simulate the movement of the whole platform.

## Credits
This is a group work. Credits go to my team members: Chen Chen, Wuji Zhang  
Motion tracking alogorithm:  
x-io Technologies. "Open source IMU and AHRS algorithm." X-IO Technologies,   
https://x-io.co.uk/open-source-imu-and-ahrs-algorithms.

## License
MIT license

MIT © [cchen82]()
 
