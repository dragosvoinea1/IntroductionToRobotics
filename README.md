# Introduction to Robotics (2023 - 2024)
_Description about the repo.
Sample projects encompass a range of coursework, such as laboratory assignments from the 'Introduction to Robotics' course, completed during the third year at the Faculty of Mathematics and Computer Science, University of Bucharest. These assignments comprise detailed instructions, implementation specifics, as well as code and associated image files._

# Homeworks

<details>
<summary> <h2>Homework 1</h2> </summary>
<br>

### Task: RGB LED control using 3 potentiometers. This control must leverage digital electronics.

### Code: [click here](https://github.com/dragosvoinea1/IntroductionToRobotics/blob/main/homework_1.ino)
  
### Youtube video that shows how it works: [watch it here](https://www.youtube.com/shorts/YShnfBhUUPg)
<br>
Components used:
<ul>
  <li>RGB LED </li>
  <li>Potentiometers (3)</li>
  <li>x3 Resistors 330 Ω
  <li>Wires as needed</li>
</ul>

### Electronic scheme + image of the project:

![Electronic scheme](https://github.com/dragosvoinea1/IntroductionToRobotics/assets/115077134/c6e1f4ad-d741-48be-b050-e26b4286f1f5)

![homework_2](https://github.com/dragosvoinea1/IntroductionToRobotics/assets/115077134/c1b04518-b1ce-4769-ae25-8ba3c1627aa1)

</details>


<details>
<summary> <h2>Homework 2</h2> </summary>
<br>

### Task: Simulating a 3-floor elevator control system using LEDs, buttons, and a buzzer with Arduino.

#### Detailed task: Design a control system that simulates a 3-floor elevator using the Arduino platform. Here are the specific requirements:

<ul>
  <li>LED Indicators: Each of the 3 LEDs should represent one of the 3 floors.
The LED corresponding to the current floor should light up. Additionally,
another LED should represent the elevator’s operational state. It should
blink when the elevator is moving and remain static when stationary.
  </li>
  <li>Buttons: Implement 3 buttons that represent the call buttons from the
3 floors. When pressed, the elevator should simulate movement towards
the floor after a short interval (2-3 seconds).
  </li>
  <li>Buzzer:
The buzzer should sound briefly during the following scenarios: 
    <ul>
    <li>Elevator arriving at the desired floor (something resembling a ”cling”).</li>
    <li>Elevator doors closing and movement.</li>
    </ul>
  </li>
  <li>State Change & Timers: If the elevator is already at the desired floor, pressing the button for that floor should have no effect.  Otherwise, after a button press, the elevator should ”wait for the doors to close” and then ”move”  to  the  corresponding  floor.   If  the  elevator  is  in  movement,  it should either do nothing or it should stack its decision (get to the first programmed floor,  open the doors,  wait, close them and then go to the next desired floor).
  </li>
 <li>
   Debounce: to avoid unintentional repeated button presses.
 </li>
  
</ul>


### Code: [click here](https://github.com/dragosvoinea1/IntroductionToRobotics/blob/main/homework_2.ino)
  
### Youtube video that shows how it works: [watch it here](https://youtube.com/shorts/Pl9DIoiuy20)

<br>

Components used:
<ul>
  <li>LEDs (4): 3 for floors, 1 operational LED </li>
  <li>Buttons (3)</li>
  <li>x4 Resistors 330 Ω </li>
  <li>x1 Resistor 100 Ω </li>
  <li>Wires as needed</li>
</ul>

### Electronic scheme + image of the project:

![image](https://github.com/dragosvoinea1/IntroductionToRobotics/assets/115077134/4418ba26-eaeb-4240-a905-b1ddcb82f148)

![hw_2_photo](https://github.com/dragosvoinea1/IntroductionToRobotics/assets/115077134/da6d4427-1614-46a6-a780-5788b8e11121)

</details>


<details>
<summary> <h2>Homework 3</h2> </summary>
<br>

### Task: 7 segment display drawing

#### Description for the task: 
You will use the joystick to control the position of the segment and ”draw” on the display. The movement between segments should be natural, meaning they should jump from the current position only to neighbors, but without passing through ”walls”. The initial position should be on the DP. The current position always blinks (irrespective of the fact that the segment is on or off). Use the joystick to move from one position to neighbors (see table for corresponding movement). Short pressing the button toggles the segment state from ON to OFF or from OFF to ON. Long pressing the button resets the entire display by turning all the segments OFF and moving the current position to the decimal point.
<br> <br>
Components used:
<ul>
  <li>1x 7-segment display</li>
  <li>1x joystick (3)</li>
  <li>x8 Resistors 330 Ω / 220 Ω (for each LED of the 7-segment)</li>
  <li>Wires as needed</li>
</ul>

### Code: [click here](https://github.com/dragosvoinea1/IntroductionToRobotics/blob/main/homework_3.ino)

### Youtube video that shows how it works: [watch it here](https://www.youtube.com/shorts/cIUrOn5i0F8)

### Image of the project:

![hw3_img](https://github.com/dragosvoinea1/IntroductionToRobotics/assets/115077134/eb2c8017-2870-4e94-8c0d-1ac8beb50413)

</details>


<details>
<summary> <h2>Homework 4</h2> </summary>
<br>

### Task: Create a stopwatch timer with a 4-digit 7-segment display and three buttons. The timer should measure time in tenths of a second and include a lap-saving feature similar to basic stopwatch functions found on most phones.
<br>

#### Initialize the 4-digit 7-segment display with the starting value "000.0". Assign the following functionalities to the buttons:
<ul>
  <li>Button 1: Start/pause.</li>
  <li>Button 2: Reset (when in pause mode) and reset saved laps (when in lap viewing mode).</li>
  <li>Button 3: Save lap (when in counting mode) and cycle through the last saved laps (up to 4 laps).</li>
</ul>

### Code: [click here](https://github.com/dragosvoinea1/IntroductionToRobotics/blob/main/homework_4.ino)
  
### Youtube video that shows how it works: [watch it here](https://www.youtube.com/shorts/TDRnEpl_gec)

<br>
Components used:
<ul>
  <li>x1 4 digit 7-segment display</li>
  <li>3 buttons</li>
  <li>x8 Resistors 330 Ω or 220 Ω
  <li>Wires as needed</li>
</ul>

### Image of the project:

![WhatsApp Image 2023-11-13 at 23 54 48](https://github.com/dragosvoinea1/IntroductionToRobotics/assets/115077134/6f3663bf-dba5-40ca-8034-3fdd638af9b5)



</details>

<details>
  
  <summary> <h2>Homework 5</h2> </summary>
  
</details>


<details>
  
  <summary> <h2>Homework 6</h2> </summary>

  ### Task: Create a simple 8x8 matrix game featuring three distinct elements: a slowly blinking player, fast-blinking bombs/bullets, and stationary walls. The objective is to navigate the player through the matrix, destroying walls. Generate walls randomly, covering 50% to 75% of the matrix. Choose a game style, whether Bomberman or terminator-tanks, or unleash your creativity in designing the gameplay.

  ### My game: Random leds spawn on the matrix and you have to turn them off as fast as possible using the joystick.

  <br>
Components used:
<ul>
  <li>Joystick</li>
  <li>8x8 LED Matrix</li>
  <li>MAX7219
  <li>Resistors and capacitors as needed</li>
  <li>Breadboard and connecting wires</li>
</ul>

### Code: [click here](https://github.com/dragosvoinea1/IntroductionToRobotics/blob/main/homework_6.ino)
  
### Youtube video that shows how it works: [watch it here](https://youtube.com/shorts/SDmUzrmQGgE?feature=share)

### Image of the project:
![f7c21c4a-dee2-4627-a31b-e622f73366fc](https://github.com/dragosvoinea1/IntroductionToRobotics/assets/115077134/3e1dda84-431f-45f6-8a88-53362518fbb5)

  
</details>


