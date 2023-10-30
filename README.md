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
  <li>State Change & Timers: If the elevator is already at the desired floor, pressing the button for that floor should have no effect.  Otherwise, aftera button press, the elevator should ”wait for the doors to close” and then”move”  to  the  corresponding  floor.   If  the  elevator  is  in  movement,  itshould either do nothing or it should stack its decision (get to the firstprogrammed floor,  open the doors,  wait, close them and then go to thenext desired floor).
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

### Image of the project:

![hw_2_photo](https://github.com/dragosvoinea1/IntroductionToRobotics/assets/115077134/da6d4427-1614-46a6-a780-5788b8e11121)

</details>


