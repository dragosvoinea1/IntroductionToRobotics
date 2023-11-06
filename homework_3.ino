// Declare joystick pins:
const int pinX = A0; //analog pin connected to X output
const int pinY = A1; //analog pin connected to Y output
const int pinSW = 2; //digital pin connected to switch output

// Declare all the segments pins
const int pinA = 12;
const int pinB = 10;
const int pinC = 9;
const int pinD = 8;
const int pinE = 7;
const int pinF = 6;
const int pinG = 5;
const int pinDP = 4;

const int segSize = 8;

byte state = HIGH;
byte swState = LOW;        //defining states for LEDs and switch
byte last_swState = LOW;

int xValue = 0;
int yValue = 0;

bool joyMoved = false;
int minThreshold = 400;
int maxThreshold = 600;
int segments[segSize] = { pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP};

const int directions = 4; //up, down, left, right
const int up = 0;
const int down = 1;
const int left = 2;
const int right = 3;

bool initial_state = LOW;
bool seg_state[segSize]={initial_state,initial_state,initial_state,initial_state,initial_state,initial_state,initial_state,initial_state};
int current_seg = segSize - 1; //7 - starting from dp
unsigned long last_blink = 0;  //used for debouncing
unsigned long last_reset_time = 0;  //used for debouncing
unsigned long reset_time = 2000; //hold the joystick for 2 seconds in order to reset it
const unsigned blink_interval = 500; //hovered leds blink every 0.5 sec


//up=x, down = y, left = z, right = t
int matrix[segSize][directions] = { //neighbour matrix, given in lab. 4 pdf
  //  x  y  z  t
    {-1, 6, 5, 1},//a - 0
    { 0, 6, 5,-1},//b - 1
    { 6, 3, 4, 7},//c - 2
    { 6,-1, 4, 2},//d - 3
    { 6, 3,-1, 2},//e - 4
    { 0, 6,-1, 1},//f - 5
    { 0, 3,-1,-1},//g - 6
    {-1,-1, 2,-1}//dp - 7
};

void setup() {
 for(int  i=0; i < segSize; i++){
   pinMode(segments[i],OUTPUT); //set the pins for each segment as OUTPUT
 }
 pinMode(pinSW, INPUT_PULLUP); // set the pin for the switch as INPUT 
 Serial.begin(9600);
}

void loop() {
  xValue = analogRead(pinX); //reading the analog values from X and Y axis of the joystick
  yValue = analogRead(pinY);
  swState = digitalRead(pinSW); //read the digital state of the switch

  if(swState == 0)
    if(swState != last_swState){ 
      seg_state[current_seg] = !seg_state[current_seg]; //toggle the state of the current segment based on the switch (turns it off or on)
      last_reset_time = millis(); //recording the current time for switch debouncing
    }

  last_swState = swState; //updating the last switch state, this helps us below to know if the switch has been pressed long enough
 
  if(swState ==0 && last_swState == 0 && (millis() - last_reset_time > reset_time) ){
    reset(); //if the switch is held for a specific time (2 sec in our case), it calls the reset function that is located at the end of the code
 }
  
  //for blinking
  if(millis() - last_blink > blink_interval){ //blinks every 0.5 sec
    last_blink = millis();
    state = !state; //toggle the state to control the LED blinking
    digitalWrite(segments[current_seg], state); // update the LED segment state based on the toggled state (ON/OFF)
 }

  if (!joyMoved) {
    if (yValue < minThreshold) move_segments(up);// if the joystick is moved up, call move_segments() with the "up" direction
    if (yValue > maxThreshold) move_segments(down);// if the joystick is moved down, call move_segments() with the "up" direction
    if (xValue > maxThreshold) move_segments(right);// if the joystick is moved right, call move_segments() with the "up" direction
    if (xValue < minThreshold) move_segments(left);// if the joystick is moved left, call move_segments() with the "up" direction
  }
 
  if (yValue > minThreshold && yValue < maxThreshold && xValue < maxThreshold && xValue > minThreshold)
    joyMoved = false; //if the joystick is centered, reset joyMoved to false = joystick is not moving
}

void move_segments(int direction) {
  joyMoved = true; //set the joystick movement flag to true
  int new_seg = matrix[current_seg][direction]; // get the new segment index based on the direction
  if (new_seg != -1) { //it should not go on elements marked with -1 in matrix
    digitalWrite(segments[current_seg], seg_state[current_seg]); // Turn off the current segment
    current_seg = new_seg; // update the current segment to the new one
  }
}

void reset(){
  for(int i = 0; i < segSize; i++){
    seg_state[i] = false; //turn off all segments
    digitalWrite(segments[i], LOW); // set all segments to LOW (OFF)
  }
  current_seg = segSize - 1; //7 - setting it back to dp
}