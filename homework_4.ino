// I've used resources from Laboratory no. 5 and I used ChatGPT at some points of this code (didn't really help me that much)
// The code only has pause and reset buttons functional. I've had multiple tries on making the lap button work properly, but I didn't manage to get a solution even close of what I wanted.

// Define the pins for controlling the 7-segment display
const int latchPin = 11;
const int clockPin = 10;
const int dataPin = 12;

// Define the pins for buttons 
int displayDigits[] = {4, 5, 6, 7};
const int displayCount = 4;

const int start_pause_PIN = 3;
const int reset_PIN = 2;
const int lap_PIN = 9;

//Define initial states for the buttons
int temp_start_ButtonState = HIGH;
int last_start_ButtonState = HIGH;
int temp_buttonStateReset = HIGH;
int last_ButtonStateReset = HIGH;

// Variables to track button state and timer status
bool is_PressedStart = false;
bool is_Paused = false;

// Variable to store the last displayed number on the 7-segment display
unsigned long lastDisplayedNumber = 0;

// Variables for button debouncing
unsigned long last_DebounceTime_Start = 0;
unsigned long last_DebounceTimeReset = 0;
unsigned long debounceDelay = 20;

// Define the encoding for each digit and the decimal point
const int encodingsNumber = 11;
byte byteEncodings[encodingsNumber] = {
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B00000001  // Decimal point
};

// Variables for controlling timer and display
unsigned long lastIncrement = 0;
unsigned long delayCount = 100;
unsigned long number = 0;

void setup() {
  // Set pin modes for 7-segment display control
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  // Set pin modes for buttons
  pinMode(start_pause_PIN, INPUT_PULLUP);
  pinMode(reset_PIN, INPUT_PULLUP);
  pinMode(lap_PIN, INPUT_PULLUP);
  
  // Initialize the display with zero (000.0) (works only after reset, idk why)
  writeNumber(0);
  
  // Set pin modes for individual display digits
  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }
  
  Serial.begin(9600);
}

void loop() {
  // Read the state of the buttons
  int start_ButtonState = digitalRead(start_pause_PIN);
  int reset_ButtonState = digitalRead(reset_PIN);

  // Button debouncing for the start/pause button
  if (start_ButtonState != last_start_ButtonState) {
    last_DebounceTime_Start = millis();
  }

  // Button debouncing for the reset button
  if (reset_ButtonState != last_ButtonStateReset) {
    last_DebounceTimeReset = millis();
  }

  // Check for button press after debouncing
  if ((millis() - last_DebounceTime_Start) > debounceDelay) {
    if (start_ButtonState != temp_start_ButtonState) {
      temp_start_ButtonState = start_ButtonState;

      // Toggle timer pause state on button press
      if (temp_start_ButtonState == LOW) {
        if (is_PressedStart) {
          is_Paused = !is_Paused;
          
          // Increment timer if not paused
          if (!is_Paused) {
            number++;
            number %= 10000; //Max 999.9 on display
          }
        } else {
          is_PressedStart = true;
        }
      }
    }
  }

  // Check for button press after debouncing
  if ((millis() - last_DebounceTimeReset) > debounceDelay) {
    if (reset_ButtonState != temp_buttonStateReset) {
      temp_buttonStateReset = reset_ButtonState;

      // Reset the timer and lap times when the reset button is pressed and the timer is paused
      if (temp_buttonStateReset == LOW && is_Paused) {
        number = 0;
      }
    }
  }

  // Store the current button states for the next iteration
  last_start_ButtonState = start_ButtonState;
  last_ButtonStateReset = reset_ButtonState;

  // Update the timer and display based on button states and timer pause state
  if (is_PressedStart && !is_Paused) {
    if (millis() - lastIncrement > delayCount) {
      number++;
      number %= 10000;
      lastIncrement = millis();
    }

    writeNumber(number);
  } else if (is_Paused) {
    writeNumber(number);
  }
}

// Shifting out a byte to the 7-segment display
void writeReg(int digit) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  digitalWrite(latchPin, HIGH);
}

// Function to activate a specific display digit
void activateDisplay(int displayNumber) {
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  digitalWrite(displayDigits[displayNumber], LOW);
}

// Function to display a number on the 7-segment display
void writeNumber(int number) {
  int second_digit = 2;
  int decimal_point = 10;
  // Check if the number is 0 to display "000.0"
  if (number == 0) {
    for (int i = 0; i < displayCount; i++) 
      if(i!=second_digit){ // Activate displays without decimal point
          activateDisplay(i);
          writeReg(byteEncodings[0]);  // Display '0'
          writeReg(0);  // clears display register so it doesn't overwrite segments after this
        }else{
            activateDisplay(second_digit);  // Activate the third display for the decimal point
            writeReg(byteEncodings[0]);// Display '0'
            writeReg(byteEncodings[decimal_point]);  // Display the decimal point
            writeReg(0);  // clears display register so it doesn't overwrite segments after this
        }
  } else {
    // Display the actual number
    int currentNumber = number;
    int displayDigit = 3;
    int lastDigit = 0;

    while (currentNumber != 0) {
      lastDigit = currentNumber % 10;
      activateDisplay(displayDigit);

      // Display the decimal point for the second digit
      if (displayDigit == second_digit) {
        writeReg(byteEncodings[lastDigit]); 
        writeReg(byteEncodings[decimal_point]); //Lights up the decimal point
      } else {
        writeReg(byteEncodings[lastDigit]);
      }
      writeReg(0);  // Turn off the display
      displayDigit--;
      currentNumber /= 10;
    }
  }
}
