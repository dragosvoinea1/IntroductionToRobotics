//I've used chatgpt and resources from arduino LCD website

#include <LedControl.h>
#include <LiquidCrystal.h>

const byte rs = 9;
const byte en = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;
const byte backlightPin = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
LedControl lc = LedControl(12, 11, 10, 1); // Pins: DIN, CLK, CS, Number of MAX7219 devices

// Joystick
const int pinSW = 2;
const int pinX = A0;
const int pinY = A1;
byte swState = LOW;
byte lastSwState = LOW;
unsigned long lastUpdateTime = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 40;
unsigned long debounceDelayButton = 10;
unsigned long lastButtonPressTime = 0;
int centerXValue = 512;
int incrementThreshold = 50;
int incrementState = 0;

enum State {
  STARTING,
  MAIN_MENU,
  SETTINGS_MENU,
  BRIGHTNESS_SUBMENU,
  DIFFICULTY_SUBMENU,
  ABOUT 
};

unsigned long startTime;
State currentState = STARTING;

// Main menu elements
String menuElements[] = {"START", "RULES", "HIGHSCORE", "SETTINGS", "ABOUT"};
int currentElement = 0;

// Settings menu elements
String settingsOptions[] = {"DIFFICULTY", "BRIGHTNESS", "RESET HIGHSCORE", "EXIT"};
int currentSettingElement = 0;

// Submenu variables
int brightnessLevel = 5;
int difficultyLevel = 2;
int incrementThresholdDifficulty = 50;

// ABOUT message
String aboutMessage = "Game name: Snake;   Game creator: Voinea Dragos;    Github: https://github.com/dragosvoinea1";
int scrollPosition = 0;
unsigned long lastScrollTime = 0;
const unsigned long scrollInterval = 200; // Adjust this value for the scrolling speed
const int screen_text = 16;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("STARTING SNAKE...");
  pinMode(pinSW, INPUT_PULLUP);

  pinMode(backlightPin, OUTPUT);
  analogWrite(backlightPin, 255);

  startTime = millis();
}

void loop() {
  swState = digitalRead(pinSW);

  // State machine
  switch (currentState) {
    case STARTING:
      // Display "MAIN MENU" after 2 seconds
      if (millis() - startTime >= 2000) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("MAIN MENU");
        lcd.setCursor(0, 1);
        lcd.print(menuElements[currentElement]);
        currentState = MAIN_MENU;
      }
      break;

    case MAIN_MENU:
      // Handle the main menu logic
      handleMainMenu();
      break;

    case SETTINGS_MENU:
      // Handle the settings menu logic
      handleSettingsMenu();
      break;

    case BRIGHTNESS_SUBMENU:
      // Handle the brightness submenu logic
      handleBrightnessSubmenu();
      break;

    case DIFFICULTY_SUBMENU:
      // Handle the difficulty submenu logic
      handleDifficultySubmenu();
      break;

    case ABOUT:
      // Handle the ABOUT state logic
      handleAbout();
      break;
  }

  lastSwState = swState;
}

// Function to handle the main menu logic
void handleMainMenu() {
  int xValue = analogRead(pinX);
  swState = digitalRead(pinSW);

  // Check for joystick movement and debounce button press
  if ((millis() - lastDebounceTime) > debounceDelay) {
    int xDifference = xValue - centerXValue;

    // Increment to the next menu element
    if (xDifference > incrementThreshold) {
      if (incrementState == 0) {
        incrementState = 1;
        if (currentElement < sizeof(menuElements) / sizeof(menuElements[0]) - 1) {
          currentElement++;
          updateLCD();
        }
      }
    }
    // Decrement to the previous menu element
    else if (xDifference < -incrementThreshold) {
      if (incrementState == 0) {
        incrementState = -1;
        if (currentElement > 0) {
          currentElement--;
          updateLCD();
        }
      }
    } else {
      incrementState = 0;
    }

    lastDebounceTime = millis();
  }

  // Check for button press and navigate to ABOUT or SETTINGS
  if (swState == LOW && lastSwState == HIGH && (millis() - lastButtonPressTime) > debounceDelayButton) {
    if (menuElements[currentElement] == "ABOUT") {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ABOUT");
      currentState = ABOUT;
      lastButtonPressTime = millis();
    } else if (menuElements[currentElement] == "SETTINGS") {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SETTINGS MENU");
      lcd.setCursor(0, 1);
      lcd.print(settingsOptions[currentSettingElement]);
      currentState = SETTINGS_MENU;
      lastButtonPressTime = millis();
    }
  }
}

// Function to handle the ABOUT state logic
void handleAbout() {
  if (millis() - lastScrollTime >= scrollInterval) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ABOUT");

    String displayText = aboutMessage.substring(scrollPosition, scrollPosition + screen_text);
    lcd.setCursor(0, 1);
    lcd.print(displayText);

    scrollPosition = (scrollPosition + 1) % (aboutMessage.length() + screen_text);
    
    lastScrollTime = millis();
  }

  // Check for button press to return to MAIN MENU
  swState = digitalRead(pinSW);
  if (swState == LOW && lastSwState == HIGH && (millis() - lastButtonPressTime) > debounceDelayButton) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MAIN MENU");
    lcd.setCursor(0, 1);
    lcd.print(menuElements[currentElement]);
    currentState = MAIN_MENU;
    lastButtonPressTime = millis();
  }

  lastSwState = swState;
}

// Function to handle the settings menu logic
void handleSettingsMenu() {
  int xValue = analogRead(pinX);
  swState = digitalRead(pinSW);

  // Check for joystick movement and debounce button press
  if ((millis() - lastDebounceTime) > debounceDelay) {
    int xDifference = xValue - centerXValue;

    // Increment to the next setting element
    if (xDifference > incrementThreshold) {
      if (incrementState == 0) {
        incrementState = 1;
        if (currentSettingElement < sizeof(settingsOptions) / sizeof(settingsOptions[0]) - 1) {
          currentSettingElement++;
          updateLCD();
        }
      }
    }
    // Decrement to the previous setting element
    else if (xDifference < -incrementThreshold) {
      if (incrementState == 0) {
        incrementState = -1;
        if (currentSettingElement > 0) {
          currentSettingElement--;
          updateLCD();
        }
      }
    } else {
      incrementState = 0;
    }

    lastDebounceTime = millis();
  }

  // Check for button press and navigate to MAIN MENU, BRIGHTNESS, or DIFFICULTY
  if (swState == LOW && swState != lastSwState && (millis() - lastButtonPressTime) > debounceDelayButton) {
    if (settingsOptions[currentSettingElement] == "EXIT") {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("MAIN MENU");
      lcd.setCursor(0, 1);
      lcd.print(menuElements[currentElement]);
      currentState = MAIN_MENU;
    } else if (settingsOptions[currentSettingElement] == "BRIGHTNESS") {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("BRIGHTNESS LEVEL");
      lcd.setCursor(0, 1);
      lcd.print("Level: " + String(brightnessLevel));
      currentState = BRIGHTNESS_SUBMENU;
    } else if (settingsOptions[currentSettingElement] == "DIFFICULTY") {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("DIFFICULTY LEVEL");
      lcd.setCursor(0, 1);
      lcd.print("Level: " + String(difficultyLevel));
      currentState = DIFFICULTY_SUBMENU;
    }
    lastButtonPressTime = millis();
  }
}

// Function to handle the brightness submenu logic
void handleBrightnessSubmenu() {
  int xValue = analogRead(pinX);
  swState = digitalRead(pinSW);

  // Check for joystick movement and debounce button press
  if ((millis() - lastDebounceTime) > debounceDelay) {
    int xDifference = xValue - centerXValue;

    // Increment or decrement brightness level
    if (xDifference > incrementThreshold) {
      if (incrementState == 0) {
        incrementState = 1;
        brightnessLevel = min(brightnessLevel + 1, 5);//Max 5 levels
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("BRIGHTNESS LEVEL");
        lcd.setCursor(0, 1);
        lcd.print("Level: " + String(brightnessLevel));
      }
    } else if (xDifference < -incrementThreshold) {
      if (incrementState == 0) {
        incrementState = 1;
        brightnessLevel = max(brightnessLevel - 1, 1);//Don't go below 1
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("BRIGHTNESS LEVEL");
        lcd.setCursor(0, 1);
        lcd.print("Level: " + String(brightnessLevel));
      }
    } else {
      incrementState = 0;
    }

    lastDebounceTime = millis();
  }

  // Update LED brightness and check for button press to return to SETTINGS MENU
  if (millis() - lastUpdateTime >= 100) {
    int intensity = brightnessLevel;
    lc.setIntensity(0, intensity);
    lastUpdateTime = millis();
  }

  // Check for button press to return to SETTINGS MENU
  if (swState == LOW && swState != lastSwState && (millis() - lastButtonPressTime) > debounceDelayButton) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SETTINGS MENU");
    lcd.setCursor(0, 1);
    lcd.print(settingsOptions[currentSettingElement]);
    currentState = SETTINGS_MENU;
    lastButtonPressTime = millis();
  }
}

// Function to handle the difficulty submenu logic
void handleDifficultySubmenu() {
  int xValue = analogRead(pinX);
  swState = digitalRead(pinSW);

  // Check for joystick movement and debounce button press
  if ((millis() - lastDebounceTime) > debounceDelay) {
    int xDifference = xValue - centerXValue;

    // Increment or decrement difficulty level
    if (xDifference > incrementThreshold) {
      if (incrementState == 0) {
        incrementState = 1;
        difficultyLevel = min(difficultyLevel + 1, 3); //Max 3 levels
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("DIFFICULTY LEVEL");
        lcd.setCursor(0, 1);
        lcd.print("Level: " + String(difficultyLevel));
      }
    } else if (xDifference < -incrementThreshold) {
      if (incrementState == 0) {
        incrementState = 1;
        difficultyLevel = max(difficultyLevel - 1, 1); //Don't go below 1
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("DIFFICULTY LEVEL");
        lcd.setCursor(0, 1);
        lcd.print("Level: " + String(difficultyLevel));
      }
    } else {
      incrementState = 0;
    }

    lastDebounceTime = millis();
  }

  // Check for button press to return to SETTINGS MENU
  if (swState == LOW && swState != lastSwState && (millis() - lastButtonPressTime) > debounceDelayButton) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SETTINGS MENU");
    lcd.setCursor(0, 1);
    lcd.print(settingsOptions[currentSettingElement]);
    currentState = SETTINGS_MENU;
    lastButtonPressTime = millis();
  }
}

// Function to update LCD display
void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  if (currentState == SETTINGS_MENU) {
    lcd.print("SETTINGS MENU");
  } else {
    lcd.print("MAIN MENU");
  }
  lcd.setCursor(0, 1);
  if (currentState == SETTINGS_MENU) {
    lcd.print(settingsOptions[currentSettingElement]);
  } else {
    lcd.print(menuElements[currentElement]);
  }
}
