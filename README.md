# Project Description
<p>
This is a Smart Home System project<br> 

It consists of two microcontrollers <b>STM32F401CC</b>: one Master and one Slave. Through the Master, we can access the system to control the home.<br>

First, the Master asks the Admin to set a password the first time that they enter the system. After that, it ask them to enter the password displaying on the LCD. The digits are entered using the keypad. If password is wrong three times, an alarm turns on. However, if the password entered is right, they can access the system. The same applies to the Guest, but the Admin has more control than the Guest.

<br>Our system consists of two rooms and a reception area, each one contains a lamp and a fan. There is also a central air conditioner controlled by a temperature sensor. If the temperature exceeds a certain limit, the air conditioner turns on.

<br>Some components are connected to the Master, while others are connected to the Slave. For example, the temperature sensor is connected to the Master, and if the temperature exceeds the limit, it sends a signal to the Slave microcontroller via UART to turn on the air conditioner.

<br>Both the Admin and the Guest can access the system to control the lamps or fans in the rooms or reception area, but only the Admin can control the air conditioner.
</p>

# Used Drivers
GPIO
<br>ADC
<br>RCC
<br>KEYPAD
<br>LCD
<br>NVIC
<br>SYSTICK
<br>UART
<br>Each driver is divided into four files:
<br>.program
<br>.interface
<br>.private
<br>.configuration
<br>
Each file has specific function.

<br>The interface file contains the APIs, the private file contains any magic numbers or anything I don’t want to expose to the user, the program file contains the implementation of each API, and the configuration file is where I configure what will be used in the microcontroller.

# Snapshots 
![image alt](https://github.com/MahmoudRabea20/Smart-home-system/blob/main/Images/Screenshot%202024-12-16%20195350.png?raw=true)
<br>
![image alt](https://github.com/MahmoudRabea20/Smart-home-system/blob/main/Images/Screenshot%202024-12-16%20195706.png?raw=true)
<br>
![image alt](https://github.com/MahmoudRabea20/Smart-home-system/blob/main/Images/Screenshot%202024-12-16%20195851.png?raw=true)
<br>
![image alt](https://github.com/MahmoudRabea20/Smart-home-system/blob/main/Images/Screenshot%202024-12-16%20200048.png?raw=true)
<br>
![image alt](https://github.com/MahmoudRabea20/Smart-home-system/blob/main/Images/Screenshot%202024-12-16%20200306.png?raw=true)
<br>
![image alt](https://github.com/MahmoudRabea20/Smart-home-system/blob/main/Images/Screenshot%202024-12-16%20200355.png?raw=true)
<br>
![image alt](https://github.com/MahmoudRabea20/Smart-home-system/blob/main/Images/Screenshot%202024-12-16%20200447.png?raw=true)
<br>
![image alt](https://github.com/MahmoudRabea20/Smart-home-system/blob/main/Images/Screenshot%202024-12-16%20200609.png?raw=true)
<br>
![image alt](https://github.com/MahmoudRabea20/Smart-home-system/blob/main/Images/Screenshot%202024-12-16%20200632.png?raw=true)
<br>
![image alt](https://github.com/MahmoudRabea20/Smart-home-system/blob/main/Images/Screenshot%202024-12-16%20200702.png?raw=true)
<br>
![image alt](https://github.com/MahmoudRabea20/Smart-home-system/blob/main/Images/Screenshot%202024-12-16%20200727.png?raw=true)
<br>
![image alt](https://github.com/MahmoudRabea20/Smart-home-system/blob/main/Images/Screenshot%202024-12-16%20200744.png?raw=true)
