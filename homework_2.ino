const int floor_PIN[] = {3, 4, 5}; // red LEDs
const int button_PIN[] = {13, 12, 11};   // buttons
const int buzzer_PIN = 9;              // buzzer
const int operational_PIN = 2;      // green LED

bool moving = 0;    // elevator state
bool blinking = 0;  // to know if the green led is blinking or not, we initialize it as not blinking first

int current_floor = 0;   // elevator starts at floor 0
unsigned long  last_blink = 0; //for debouncing for operational LED
const unsigned  blink_interval = 500; // operational LED will blink every 0.5 sec during the elevator's movement
unsigned long  last_time = 0; //for debouncing in loop
unsigned movement_time = 1500; //duration of the elevator's movement


void setup() {
  for (int i = 0; i < 3; i++) { //from ground floor up to 2nd floor
    pinMode(floor_PIN[i], OUTPUT);
    pinMode(button_PIN[i], INPUT_PULLUP);
  }
  pinMode(buzzer_PIN, OUTPUT);
  pinMode(operational_PIN, OUTPUT);
}

void loop() {
  for (int i = 0; i < 3; i++) {
    if (digitalRead(button_PIN[i]) == LOW && i!= current_floor) {
        moveElevator(i);     
    }
  }

  if (moving) {
    state_operationalLED(); //green led starts blinking
    BuzzerSoundLong(); //sound during the movement of the elevator
    if (millis() - last_time >= movement_time) { //checking if it needs to stop
      moving = 0;
      state_operationalLED(); // green led stops blinking
      BuzzerSoundShort(); // short *beep* that indicates arrival
      state_FloorLED();
    }
  } else {
    digitalWrite(operational_PIN, HIGH); // if the elevator is stationary, the green operational led will stay ON
  }
}

void moveElevator(int desired_floor) {
  bool two_floors = (current_floor == 0 && desired_floor == 2) || (current_floor == 2 && desired_floor == 0);

  if (two_floors) {
    movement_time = 3000;  // set the movement_time to 3 seconds
    BuzzerSoundLong();    // calling this function to extend the duration of the longer *beep* from 1.5 to 3 sec
  } else {
    movement_time = 1500;  // reset the movement_time to 1.5 seconds
    //Sound remains 2 sec
  }
  
  if (current_floor < desired_floor && (desired_floor - current_floor) ==1 ) { 
    current_floor++;
  } 
  else if (current_floor > desired_floor && (current_floor - desired_floor) == 1 ) {
    current_floor--;                                                                       //these are for the if above
  }
  else if (current_floor < desired_floor && (desired_floor - current_floor) == 2 ){
    current_floor+=2;
  }
  else if (current_floor > desired_floor && (current_floor - desired_floor) == 2 ){
    current_floor-=2;
  }

  moving = 1;
  last_time = millis();
  state_operationalLED();  // green led starts blinking
}



void state_operationalLED() {
  if (moving) {
    unsigned long currentMillis = millis();
    if (currentMillis - last_blink >= blink_interval) { //blink interval = 0.5 s
      blinking = !blinking; //on off on off on off while it's moving
      digitalWrite(operational_PIN, blinking);
      last_blink = currentMillis;
    }
  } else {
    digitalWrite(operational_PIN, HIGH); // elevator stationary, operational LED ON
  }
}

void state_FloorLED() {  //this is used to light up the leds
  for (int i = 0; i < 3; i++) {
    if(i == current_floor)
      digitalWrite(floor_PIN[i], 1);
      else digitalWrite(floor_PIN[i], 0);
  }

}

void BuzzerSoundShort() { //for the short *beep* when it reaches the specific floor
  tone(buzzer_PIN, 1000, 100); 
}

void BuzzerSoundLong() { //for the longer *beeeeeeeep* during the process
  tone(buzzer_PIN, 500, 1500); 
}
