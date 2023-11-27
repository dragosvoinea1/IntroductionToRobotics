//I've used a code from lab. 7 for the movement of the player on the matrix and ChatGPT as help for some bugs and some comments
//It still sometimes has a buggy movement 
//note: i used the notation "random LED" for the 10 random leds that light up when I run the program
#include "LedControl.h"

// Pin configurations for MAX7219 and joystick
const byte dinPin = 12;           // DIN pin connected to MAX7219
const byte clockPin = 11;         // CLK pin connected to MAX7219
const byte loadPin = 10;          // LOAD pin connected to MAX7219
const byte matrixSize = 8;        // Size of LED matrix
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); // MAX7219 initialization
byte matrixBrightness = 2;        // LED matrix brightness

// Joystick and switch configurations
const int pinSW = 2;              // Digital pin connected to switch output
const int pinX = A0;              // Analog pin connected to X output
const int pinY = A1;              // Analog pin connected to Y output
byte swState = LOW;                 // Current switch state
byte lastSwState = LOW;             // Last recorded switch state
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 500; // Debounce delay for switch

// Player and joystick position variables
int playerRow = 0;
int playerCol = 0;
bool playerBlinkState = HIGH;     // Initial state for player LED blinking

// Joystick movement and LED matrix update variables
int xValue = 0;
int yValue = 0;
bool joyMoved = false;
int minThreshold = 400;
int maxThreshold = 600;
const byte moveInterval = 200;    // Timing variable to control the speed of LED movement
unsigned long long lastMoved = 0; // Tracks the last time the LED moved
bool matrixChanged = true;        // Flag to track if the matrix display needs updating

// Player and random LED positions
int row_pos = 0;
int col_pos = 0;
int row_LastPos = 0;
int col_LastPos = 0;

int row_rand[10] = {0};
int col_rand[10] = {0};

const int ON = 1;
const int OFF = 0;

const int total_random = 10;

// LED matrix representation
byte matrix[matrixSize][matrixSize] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

void setup() {
  // LED matrix setup
  lc.shutdown(0, false);          // Turn off power saving, enables display
  lc.setIntensity(0, matrixBrightness); // Sets brightness (0~15 possible values)
  lc.clearDisplay(0);              // Clear the LED matrix display
  // Switch setup
  pinMode(pinSW, INPUT_PULLUP);    // Set the pin for the switch as INPUT 
  Serial.begin(9600);
  // Random seed setup for generating random LED positions (without this i used to get the same random LEDs every time i ran the program)
  randomSeed(analogRead(2));
  for (int i = 0; i < total_random; i++) {
    do {
      // Generate random positions for 10 LEDs and saving them in 2 vectors (need these later)
      row_rand[i] = random(0, matrixSize);
      col_rand[i] = random(0, matrixSize); 
    } while (matrix[row_rand[i]][col_rand[i]] == ON); // Check if the position is already occupied
    matrix[row_rand[i]][col_rand[i]] = ON; // Mark the generated position as occupied
  }
  matrix[row_pos][col_pos] = ON; // Initialize the starting position of the LED
}

void loop() {
  // Read switch state
  swState = digitalRead(pinSW);
  Serial.println(swState);
  
  // Check for switch press and update matrix accordingly
  if (swState == LOW && swState != lastSwState) {
    matrix[row_pos][col_pos] = OFF;
    matrixChanged = true;
  }
  lastSwState = swState;

  // Debounce switch input and update player LED blinking state
  if (millis() - lastDebounceTime > debounceDelay) {
    lastDebounceTime = millis();
    playerBlinkState = !playerBlinkState;
    lc.setLed(0, row_pos, col_pos, playerBlinkState);
  }

  // Check if it's time to move the LED and update positions
  if (millis() - lastMoved > moveInterval) {
    updatePositions();
    lastMoved = millis();
  }

  // Check if the matrix display needs updating
  if (matrixChanged == true) {
    updateMatrix();
    matrixChanged = false;
  }
}

// Update LED matrix display
void updateMatrix() {
  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      lc.setLed(0, row, col, matrix[row][col]);  // Set each LED individually
    }
  }
}

// Update player and random LED positions based on joystick input
void updatePositions() {
  // Read joystick values
  int xValue = analogRead(pinX);
  int yValue = analogRead(pinY);

  // Store the last positions of the LED
  row_LastPos = row_pos;
  col_LastPos = col_pos;

  // Update row_pos based on joystick movement (X-axis)
  if (xValue < minThreshold) {
    if (row_pos < matrixSize - 1) {
      row_pos++;
    } 
    else {
      row_pos = 0;
    }
  }
  if (xValue > maxThreshold) {
    if (row_pos > 0) {
      row_pos--;
    }
    else {
      row_pos = matrixSize - 1;
    }
  }

  // Update col_pos based on joystick movement (Y-axis)
  if (yValue > maxThreshold) {
    if (col_pos < matrixSize - 1) {
      col_pos++;
    } 
    else {
      col_pos = 0;
    }
  }
  if (yValue < minThreshold) {
    if (col_pos > 0) {
      col_pos--;
    }
    else {
      col_pos = matrixSize - 1;
    }
  }

  // Check if the current position is a random LED
  bool isRandomLED = false;
  for (int i = 0; i < total_random; i++) {
    int randomRow = row_rand[i];
    int randomCol = col_rand[i];
    if (row_pos == randomRow && col_pos == randomCol && matrix[row_pos][col_pos] == ON) {
      isRandomLED = true;
      break;
    }
  }

  // Check if the last position was a random LED
  bool last_isRandomLED = false;
  for (int i = 0; i < total_random; i++) {
    int randomRow = row_rand[i];
    int randomCol = col_rand[i];
    if (row_LastPos == randomRow && col_LastPos == randomCol && matrix[row_LastPos][col_LastPos] == ON) {
      last_isRandomLED = true;
      break;
    }
  }

  // If the position has changed, update the matrix
  if (row_pos != row_LastPos || col_pos != col_LastPos) {
    matrixChanged = true;
    //These conditions are used to not light up / turn off unwanted LEDS
    // If the actual position is on a "random" LED and the previous one is a normal LED
    if (isRandomLED == true && last_isRandomLED == false) {
      matrix[row_LastPos][col_LastPos] = OFF;
      matrix[row_pos][col_pos] = ON;
    }
    // If the actual position is on a normal LED and the previous one is a "random" LED
    if (isRandomLED == false && last_isRandomLED == true) {
      matrix[row_LastPos][col_LastPos] = ON;
      matrix[row_pos][col_pos] = OFF;
    }
    // If 2 random leds are lit up next to eachother
    if (isRandomLED == true && last_isRandomLED == true) {
      matrix[row_LastPos][col_LastPos] = ON;
      matrix[row_pos][col_pos] = ON;
    }
  }
}
