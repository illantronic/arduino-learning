// VARIABLE DECLARATION
int red = 6;
int yellow = 5;
int green = 4;
int mode = 0;


// NORMAL MODE VARIABLES
int normalPhase = 0;
unsigned long normalTime = 0;


// BLINKING MODE VARIABLES
bool blinkingState = false;
unsigned long blinkingTime = 0;


// FUNCTION TO BLINK AN LED WITHOUT DELAY (PIN, STATE, PREVIOUS TIME)
void blink(int pin, bool &state, unsigned long &previousTime) {

  // IF LESS THAN 500 MS HAVE PASSED, DO NOT CHANGE THE STATE.
  // OTHERWISE, CHANGE THE STATE AND UPDATE THE PREVIOUS TIME.
  // IT IS NOT RESET TO 0 BECAUSE MILLIS() KEEPS INCREASING.
  if (millis() - previousTime >= 500) {

    state = !state;

    digitalWrite(pin, state);

    previousTime = millis();
  }
}


// FUNCTION TO DISPLAY THE MAIN MENU
void showMenu() {

  Serial.println("--------------------");
  Serial.println("Select a new mode:");
  Serial.println("0 - Exit, Off");
  Serial.println("1 - Normal");
  Serial.println("2 - Blinking yellow");
  Serial.println("3 - Simple manual");
  Serial.println("4 - Advanced manual");
}


// FUNCTION TO DISPLAY THE SIMPLE MANUAL MENU
void showSimpleManualMenu() {

  Serial.println("--------------------");
  Serial.println("SIMPLE MANUAL MODE");
  Serial.println("Select a light:");
  Serial.println("1 - Red");
  Serial.println("2 - Yellow");
  Serial.println("3 - Green");
  Serial.println("0 - Exit, Off");
  Serial.println("--------------------");
}


// FUNCTION TO DISPLAY THE ADVANCED MANUAL MENU
void showAdvancedManualMenu() {

  Serial.println("--------------------");
  Serial.println("ADVANCED MANUAL MODE");
  Serial.println("Select an option:");
  Serial.println("1 - Solid red");
  Serial.println("2 - Solid yellow");
  Serial.println("3 - Solid green");
  Serial.println("4 - Blinking red");
  Serial.println("5 - Blinking yellow");
  Serial.println("6 - Blinking green");
  Serial.println("0 - Exit, Off");
  Serial.println("--------------------");
  Serial.println("EXTRA:");
  Serial.println("Select the same mode again to turn it off.");
  Serial.println("Another mode for the same LED replaces the previous one.");
  Serial.println("--------------------");
}


void setup() {

  // SET PINS AS OUTPUT
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  // START SERIAL COMMUNICATION WITH THE COMPUTER
  Serial.begin(9600);

  // WHILE MODE REMAINS 0 (DEFAULT MODE)
  while (mode == 0) {

    Serial.println(" ");
    Serial.println("Select a mode:");
    Serial.println("0 - Off");
    Serial.println("1 - Normal");
    Serial.println("2 - Blinking yellow");
    Serial.println("3 - Simple manual");
    Serial.println("4 - Advanced manual");


    // WHILE NO CHARACTER IS RECEIVED, KEEP ALL LEDS OFF
    while (Serial.available() == 0) {

      digitalWrite(red, LOW);
      digitalWrite(yellow, LOW);
      digitalWrite(green, LOW);
    }

    // WHEN A CHARACTER IS RECEIVED, EXIT THE WHILE LOOP AND READ IT
    char input = Serial.read();


    // CHECK FOR AN INVALID VALUE USING ASCII
    // THIS ALSO ALLOWS INVALID CHARACTERS SUCH AS LETTERS TO BE DETECTED
    if (input < '0' || input > '4') {

      Serial.println("--------------------");
      Serial.println("Invalid value.");
      Serial.println("--------------------");

      mode = 0;
    }

    // IF VALID, MODE BECOMES THE VALUE READ FROM THE SERIAL MONITOR
    else {

      // SINCE WE ARE USING ASCII, SUBTRACT '0'
      // TO CONVERT THE CHARACTER INTO ITS NUMERIC VALUE
      mode = input - '0';


      if (mode == 0) {

        Serial.println("--------------------");
        Serial.println("Selected mode: 0 - Off");
        Serial.println("--------------------");
      }


      else if (mode == 1) {

        Serial.println("--------------------");
        Serial.println("Selected mode: 1 - Normal");

        // START THE NORMAL CYCLE WITH THE RED LIGHT
        normalPhase = 0;
        normalTime = millis();

        digitalWrite(red, HIGH);
        digitalWrite(yellow, LOW);
        digitalWrite(green, LOW);

        showMenu();
      }


      else if (mode == 2) {

        Serial.println("--------------------");
        Serial.println("Selected mode: 2 - Blinking yellow");

        // STORE THE INITIAL STATE AND CURRENT TIME
        blinkingState = false;
        blinkingTime = millis();

        digitalWrite(red, LOW);
        digitalWrite(yellow, LOW);
        digitalWrite(green, LOW);

        showMenu();
      }


      else if (mode == 3) {

        Serial.println("--------------------");
        Serial.println("Selected mode: 3 - Simple manual");
      }


      else if (mode == 4) {

        Serial.println("--------------------");
        Serial.println("Selected mode: 4 - Advanced manual");
      }
    }
  }
}



void loop() {


  // CHECK IF A NEW VALUE HAS BEEN SENT THROUGH SERIAL
  if (Serial.available() > 0) {

    char input = Serial.read();


    // CHECK IF THE VALUE IS INVALID
    if (input < '0' || input > '4') {

      Serial.println("--------------------");
      Serial.println("Invalid value.");
      Serial.println("--------------------");

      mode = 0;
    }

    else {

      mode = input - '0';


      if (mode == 0) {

        Serial.println("--------------------");
        Serial.println("Selected mode: 0 - Off");

        showMenu();
      }


      else if (mode == 1) {

        Serial.println("--------------------");
        Serial.println("Selected mode: 1 - Normal");

        // RESTART THE TRAFFIC LIGHT FROM RED
        normalPhase = 0;
        normalTime = millis();

        digitalWrite(red, HIGH);
        digitalWrite(yellow, LOW);
        digitalWrite(green, LOW);

        showMenu();
      }


      else if (mode == 2) {

        Serial.println("--------------------");
        Serial.println("Selected mode: 2 - Blinking yellow");

        // STORE THE INITIAL STATE AND CURRENT TIME
        blinkingState = false;
        blinkingTime = millis();

        digitalWrite(red, LOW);
        digitalWrite(yellow, LOW);
        digitalWrite(green, LOW);

        showMenu();
      }


      else if (mode == 3) {

        Serial.println("--------------------");
        Serial.println("Selected mode: 3 - Simple manual");
      }


      else if (mode == 4) {

        Serial.println("--------------------");
        Serial.println("Selected mode: 4 - Advanced manual");
      }
    }
  }



  // MODE 0: OFF

  if (mode == 0) {

    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
  }


  // MODE 1: NORMAL WITHOUT DELAY

  else if (mode == 1) {


    // PHASE 0: RED
    if (normalPhase == 0) {

      // ONLY CHANGE COLOR AFTER 3000 MS HAVE PASSED
      // SINCE THE PREVIOUS TIME REFERENCE
      if (millis() - normalTime >= 3000) {

        digitalWrite(red, LOW);
        digitalWrite(green, HIGH);

        normalPhase = 1;
        normalTime = millis();
      }
    }


    // PHASE 1: GREEN
    else if (normalPhase == 1) {

      if (millis() - normalTime >= 3000) {

        digitalWrite(green, LOW);
        digitalWrite(yellow, HIGH);

        normalPhase = 2;
        normalTime = millis();
      }
    }


    // PHASE 2: YELLOW
    else if (normalPhase == 2) {

      if (millis() - normalTime >= 500) {

        digitalWrite(yellow, LOW);
        digitalWrite(red, HIGH);

        normalPhase = 0;
        normalTime = millis();
      }
    }
  }



  // MODE 2: BLINKING YELLOW WITHOUT DELAY

  else if (mode == 2) {

    if (millis() - blinkingTime >= 500) {

      blinkingState = !blinkingState;

      digitalWrite(yellow, blinkingState);

      blinkingTime = millis();
    }
  }



  // MODE 3: SIMPLE MANUAL

  else if (mode == 3) {

    showSimpleManualMenu();


    while (mode == 3) {

      // READ INPUT FROM SERIAL MONITOR
      if (Serial.available() > 0) {

        char lightInput = Serial.read();


        // CHECK FOR INVALID VALUES
        if (lightInput < '0' || lightInput > '3') {

          Serial.println("Invalid value.");
        }

        else {

          int light = lightInput - '0';


          // RED
          if (light == 1) {

            digitalWrite(red, HIGH);
            digitalWrite(yellow, LOW);
            digitalWrite(green, LOW);
          }


          // YELLOW
          else if (light == 2) {

            digitalWrite(red, LOW);
            digitalWrite(yellow, HIGH);
            digitalWrite(green, LOW);
          }


          // GREEN
          else if (light == 3) {

            digitalWrite(red, LOW);
            digitalWrite(yellow, LOW);
            digitalWrite(green, HIGH);
          }


          // EXIT
          else if (light == 0) {

            digitalWrite(red, LOW);
            digitalWrite(yellow, LOW);
            digitalWrite(green, LOW);

            mode = 0;
          }
        }
      }
    }

    showMenu();
  }



  // MODE 4: ADVANCED MANUAL

  else if (mode == 4) {

    showAdvancedManualMenu();


    // CURRENT MODE OF EACH LED:
    // 0 = OFF
    // 1 = SOLID
    // 2 = BLINKING

    int redMode = 0;
    int yellowMode = 0;
    int greenMode = 0;


    // CURRENT STATE OF EACH LED
    bool redState = false;
    bool yellowState = false;
    bool greenState = false;


    // LAST CHANGE TIME OF EACH LED
    unsigned long redTime = 0;
    unsigned long yellowTime = 0;
    unsigned long greenTime = 0;


    while (mode == 4) {

      // IF DATA IS RECEIVED THROUGH SERIAL
      if (Serial.available() > 0) {

        char advancedInput = Serial.read();


        // INVALID VALUE
        if (advancedInput < '0' || advancedInput > '6') {

          Serial.println("Invalid value.");
        }


        // VALID VALUE
        else {

          int option = advancedInput - '0';


          // SOLID RED
          if (option == 1) {

            // IF IT IS ALREADY SOLID, TURN IT OFF.
            // OTHERWISE, SET IT TO SOLID.
            if (redMode == 1) {

              redMode = 0;
            }

            else {

              redMode = 1;
            }
          }


          // SOLID YELLOW
          else if (option == 2) {

            // IF IT IS ALREADY SOLID, TURN IT OFF.
            // OTHERWISE, SET IT TO SOLID.
            if (yellowMode == 1) {

              yellowMode = 0;
            }

            else {

              yellowMode = 1;
            }
          }


          // SOLID GREEN
          else if (option == 3) {

            // IF IT IS ALREADY SOLID, TURN IT OFF.
            // OTHERWISE, SET IT TO SOLID.
            if (greenMode == 1) {

              greenMode = 0;
            }

            else {

              greenMode = 1;
            }
          }


          // BLINKING RED
          else if (option == 4) {

            if (redMode == 2) {

              redMode = 0;
            }

            else {

              redMode = 2;
            }
          }


          // BLINKING YELLOW
          else if (option == 5) {

            if (yellowMode == 2) {

              yellowMode = 0;
            }

            else {

              yellowMode = 2;
            }
          }


          // BLINKING GREEN
          else if (option == 6) {

            if (greenMode == 2) {

              greenMode = 0;
            }

            else {

              greenMode = 2;
            }
          }


          // EXIT
          else if (option == 0) {

            digitalWrite(red, LOW);
            digitalWrite(yellow, LOW);
            digitalWrite(green, LOW);

            mode = 0;
          }
        }
      }


      // RED CONTROL

      if (redMode == 0) {

        digitalWrite(red, LOW);
        redState = false;
      }

      else if (redMode == 1) {

        digitalWrite(red, HIGH);
        redState = true;
      }

      else if (redMode == 2) {

        blink(red, redState, redTime);
      }


      // YELLOW CONTROL

      if (yellowMode == 0) {

        digitalWrite(yellow, LOW);
        yellowState = false;
      }

      else if (yellowMode == 1) {

        digitalWrite(yellow, HIGH);
        yellowState = true;
      }

      else if (yellowMode == 2) {

        blink(yellow, yellowState, yellowTime);
      }


      // GREEN CONTROL

      if (greenMode == 0) {

        digitalWrite(green, LOW);
        greenState = false;
      }

      else if (greenMode == 1) {

        digitalWrite(green, HIGH);
        greenState = true;
      }

      else if (greenMode == 2) {

        blink(green, greenState, greenTime);
      }
    }


    showMenu();
  }
}
