// LEDs
int yellowLed = 4;
int greenLed = 5;
int redLed = 6;
int blueLed = 7;

// Buttons
int yellowButton = 8;
int greenButton = 9;
int redButton = 10;
int blueButton = 11;

// Buzzer
int buzzer = 12;

// Round, high score and game
int round = 1;
int highScore = 0;
bool gameActive = false;

// Sequence memory
int generatedSequence[100];
int playerSequence[100];


void setup() {

  Serial.begin(9600);

  randomSeed(analogRead(A0));

  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(yellowButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(redButton, INPUT_PULLUP);
  pinMode(blueButton, INPUT_PULLUP);
}


void loop() {

  // -------------------------
  // MENU
  // -------------------------

  if (gameActive == false) {

    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW);
    digitalWrite(blueLed, LOW);

    noTone(buzzer);

    Serial.println("=== SIMON SAYS ===");
    Serial.println("Press any key to start");

    while (Serial.available() == 0) {
      // Waiting
    }

    Serial.read();

    gameActive = true;
    round = 1;

    Serial.println("Game started");
  }


  // -------------------------
  // ROUND VARIABLES
  // -------------------------

  int playerPresses = 0;

  bool defeat = false;
  bool success = false;


  // -------------------------
  // GENERATE NEW COLOR
  // -------------------------

  int randomColor = random(4, 8);

  generatedSequence[round - 1] = randomColor;


  // -------------------------
  // SHOW SEQUENCE
  // -------------------------

  for (int i = 0; i < round; i++) {

    digitalWrite(generatedSequence[i], HIGH);

    if (generatedSequence[i] == yellowLed) {
      tone(buzzer, 1200);
    }

    else if (generatedSequence[i] == greenLed) {
      tone(buzzer, 1000);
    }

    else if (generatedSequence[i] == redLed) {
      tone(buzzer, 800);
    }

    else if (generatedSequence[i] == blueLed) {
      tone(buzzer, 600);
    }

    delay(500);

    digitalWrite(generatedSequence[i], LOW);

    noTone(buzzer);

    if (i < round - 1) {
      delay(250);
    }
  }


  // -------------------------
  // PLAYER TIME
  // -------------------------

  // Maximum time between button presses
  unsigned long maxTime = 3000;

  // Time after entering the entire sequence
  unsigned long finalCheckTime = 1500;

  unsigned long lastPressTime = millis();


  // -------------------------
  // BUTTON CONTROL
  // -------------------------

  bool yellowReady = true;
  bool greenReady = true;
  bool redReady = true;
  bool blueReady = true;

  unsigned long yellowReleaseTime = 0;
  unsigned long greenReleaseTime = 0;
  unsigned long redReleaseTime = 0;
  unsigned long blueReleaseTime = 0;

  unsigned long releaseTime = 50;


  // -------------------------
  // PLAYER LIGHT AND SOUND
  // CONTROL
  // -------------------------

  int activeLed = -1;

  unsigned long soundStartTime = 0;

  unsigned long soundDuration = 500;


  // -------------------------
  // PLAYER INPUT
  // -------------------------

  while (defeat == false && success == false) {

    bool yellowState = digitalRead(yellowButton);
    bool greenState = digitalRead(greenButton);
    bool redState = digitalRead(redButton);
    bool blueState = digitalRead(blueButton);


    // -------------------------
    // TURN OFF LIGHT AND SOUND
    // -------------------------

    if (activeLed != -1) {

      if (millis() - soundStartTime >= soundDuration) {

        digitalWrite(activeLed, LOW);

        noTone(buzzer);

        activeLed = -1;
      }
    }


    // -------------------------
    // YELLOW RELEASE
    // -------------------------

    if (yellowReady == false) {

      if (yellowState == HIGH) {

        if (yellowReleaseTime == 0) {
          yellowReleaseTime = millis();
        }

        if (millis() - yellowReleaseTime >= releaseTime) {
          yellowReady = true;
          yellowReleaseTime = 0;
        }
      }

      else {
        yellowReleaseTime = 0;
      }
    }


    // -------------------------
    // GREEN RELEASE
    // -------------------------

    if (greenReady == false) {

      if (greenState == HIGH) {

        if (greenReleaseTime == 0) {
          greenReleaseTime = millis();
        }

        if (millis() - greenReleaseTime >= releaseTime) {
          greenReady = true;
          greenReleaseTime = 0;
        }
      }

      else {
        greenReleaseTime = 0;
      }
    }


    // -------------------------
    // RED RELEASE
    // -------------------------

    if (redReady == false) {

      if (redState == HIGH) {

        if (redReleaseTime == 0) {
          redReleaseTime = millis();
        }

        if (millis() - redReleaseTime >= releaseTime) {
          redReady = true;
          redReleaseTime = 0;
        }
      }

      else {
        redReleaseTime = 0;
      }
    }


    // -------------------------
    // BLUE RELEASE
    // -------------------------

    if (blueReady == false) {

      if (blueState == HIGH) {

        if (blueReleaseTime == 0) {
          blueReleaseTime = millis();
        }

        if (millis() - blueReleaseTime >= releaseTime) {
          blueReady = true;
          blueReleaseTime = 0;
        }
      }

      else {
        blueReleaseTime = 0;
      }
    }


    // -------------------------
    // YELLOW
    // -------------------------

    if (yellowState == LOW && yellowReady == true) {

      yellowReady = false;

      // Turn off previous effect
      if (activeLed != -1) {
        digitalWrite(activeLed, LOW);
      }

      noTone(buzzer);

      // New effect
      digitalWrite(yellowLed, HIGH);
      tone(buzzer, 1200);

      activeLed = yellowLed;
      soundStartTime = millis();

      if (playerPresses == round) {

        Serial.println("Defeat");
        defeat = true;
      }

      else {

        playerSequence[playerPresses] = 4;

        if (playerSequence[playerPresses] != generatedSequence[playerPresses]) {
          Serial.println("Defeat");
          defeat = true;
        }

        playerPresses++;

        lastPressTime = millis();
      }
    }


    // -------------------------
    // GREEN
    // -------------------------

    else if (greenState == LOW && greenReady == true) {

      greenReady = false;

      // Turn off previous effect
      if (activeLed != -1) {
        digitalWrite(activeLed, LOW);
      }

      noTone(buzzer);

      // New effect
      digitalWrite(greenLed, HIGH);
      tone(buzzer, 1000);

      activeLed = greenLed;
      soundStartTime = millis();

      if (playerPresses == round) {

        Serial.println("Defeat");
        defeat = true;
      }

      else {

        playerSequence[playerPresses] = 5;

        if (playerSequence[playerPresses] != generatedSequence[playerPresses]) {
          Serial.println("Defeat");
          defeat = true;
        }

        playerPresses++;

        lastPressTime = millis();
      }
    }


    // -------------------------
    // RED
    // -------------------------

    else if (redState == LOW && redReady == true) {

      redReady = false;

      // Turn off previous effect
      if (activeLed != -1) {
        digitalWrite(activeLed, LOW);
      }

      noTone(buzzer);

      // New effect
      digitalWrite(redLed, HIGH);
      tone(buzzer, 800);

      activeLed = redLed;
      soundStartTime = millis();

      if (playerPresses == round) {

        Serial.println("Defeat");
        defeat = true;
      }

      else {

        playerSequence[playerPresses] = 6;

        if (playerSequence[playerPresses] != generatedSequence[playerPresses]) {
          Serial.println("Defeat");
          defeat = true;
        }

        playerPresses++;

        lastPressTime = millis();
      }
    }


    // -------------------------
    // BLUE
    // -------------------------

    else if (blueState == LOW && blueReady == true) {

      blueReady = false;

      // Turn off previous effect
      if (activeLed != -1) {
        digitalWrite(activeLed, LOW);
      }

      noTone(buzzer);

      // New effect
      digitalWrite(blueLed, HIGH);
      tone(buzzer, 600);

      activeLed = blueLed;
      soundStartTime = millis();

      if (playerPresses == round) {

        Serial.println("Defeat");
        defeat = true;
      }

      else {

        playerSequence[playerPresses] = 7;

        if (playerSequence[playerPresses] != generatedSequence[playerPresses]) {
          Serial.println("Defeat");
          defeat = true;
        }

        playerPresses++;

        lastPressTime = millis();
      }
    }


    // -------------------------
    // CHECK TIME
    // -------------------------

    if (defeat == false) {

      // There are still colors left to enter
      if (playerPresses < round) {

        if (millis() - lastPressTime >= maxTime) {
          Serial.println("Defeat");
          defeat = true;
        }
      }

      // All colors have been entered
      else if (playerPresses == round) {

        if (millis() - lastPressTime >= finalCheckTime) {
          success = true;
        }
      }
    }
  }


  // -------------------------
  // TURN OFF PLAYER EFFECT
  // -------------------------

  if (activeLed != -1) {
    digitalWrite(activeLed, LOW);
  }

  noTone(buzzer);


  // -------------------------
  // END OF ROUND
  // -------------------------

  if (defeat == true) {

    // -------------------------
    // DEFEAT EFFECT
    // -------------------------

    for (int i = 0; i < 3; i++) {

      digitalWrite(yellowLed, HIGH);
      digitalWrite(greenLed, HIGH);
      digitalWrite(redLed, HIGH);
      digitalWrite(blueLed, HIGH);

      tone(buzzer, 300);

      delay(300);

      digitalWrite(yellowLed, LOW);
      digitalWrite(greenLed, LOW);
      digitalWrite(redLed, LOW);
      digitalWrite(blueLed, LOW);

      noTone(buzzer);

      delay(200);
    }


    // -------------------------
    // GAME RESULT
    // -------------------------

    int reachedRound = round - 1;

    Serial.println();

    Serial.print("You reached round: ");
    Serial.println(reachedRound);


    // -------------------------
    // CHECK HIGH SCORE
    // -------------------------

    if (reachedRound > highScore) {

      highScore = reachedRound;

      Serial.println("NEW HIGH SCORE!");

      victoryMelody();
    }

    Serial.print("High score: ");
    Serial.println(highScore);

    Serial.println();


    // Restart game
    round = 0;
    gameActive = false;
  }

  else if (success == true) {
    round++;
  }
}


// =====================================================
// VICTORY MELODY
// =====================================================

void victoryMelody() {

  // First part
  tone(buzzer, 659);
  delay(120);
  noTone(buzzer);
  delay(40);

  tone(buzzer, 784);
  delay(120);
  noTone(buzzer);
  delay(40);

  tone(buzzer, 988);
  delay(120);
  noTone(buzzer);
  delay(40);

  tone(buzzer, 1047);
  delay(180);
  noTone(buzzer);
  delay(60);

  tone(buzzer, 988);
  delay(120);
  noTone(buzzer);
  delay(40);

  tone(buzzer, 1175);
  delay(120);
  noTone(buzzer);
  delay(40);

  tone(buzzer, 1319);
  delay(300);
  noTone(buzzer);

  delay(120);


  // Second part
  tone(buzzer, 1047);
  delay(120);
  noTone(buzzer);
  delay(40);

  tone(buzzer, 1175);
  delay(120);
  noTone(buzzer);
  delay(40);

  tone(buzzer, 1319);
  delay(120);
  noTone(buzzer);
  delay(40);

  tone(buzzer, 1568);
  delay(200);
  noTone(buzzer);
  delay(60);

  tone(buzzer, 1319);
  delay(120);
  noTone(buzzer);
  delay(40);

  tone(buzzer, 1568);
  delay(120);
  noTone(buzzer);
  delay(40);

  tone(buzzer, 1760);
  delay(300);
  noTone(buzzer);

  delay(120);


  // Final part
  tone(buzzer, 1319);
  delay(120);
  noTone(buzzer);
  delay(40);

  tone(buzzer, 1568);
  delay(120);
  noTone(buzzer);
  delay(40);

  tone(buzzer, 1760);
  delay(150);
  noTone(buzzer);
  delay(40);

  tone(buzzer, 1865);
  delay(500);
  noTone(buzzer);
}
