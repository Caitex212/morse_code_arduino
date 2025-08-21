char* letters[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};

char* numbers[] = {
  "-----", ".----", "..---", "...--", "....-", ".....",
  "-....", "--...", "---..", "----."
};

String input = "";

int arraySize = sizeof(letters) / sizeof(letters[0]);

unsigned long buttonPressedAt = 0;
bool buttonReleased = false;
byte buttonPrevState = 0;
const int buttonPin = 2;

unsigned long buttonReleasedAt = 0;
bool buttonJustPressed = false;
bool alreadyPrinted = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int state = digitalRead(buttonPin);
  buttonJustPressed = false;

  if (state == LOW) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

  if (state != buttonPrevState) {
    if (state == LOW) {
      buttonReleased = false;
      buttonJustPressed = true;
      buttonPressedAt = millis();
    } else {
      buttonReleased = true;
      buttonReleasedAt = millis();
    }
    buttonPrevState = state;
  }

  if (buttonReleased == true) {
    after3Sec();
    buttonReleased = false;
    buttonPressedAt = 0;
  }

  // else if (buttonJustPressed == true) {
  //   long diff = millis() - buttonReleasedAt;
  //   if (diff > 700) {
  //     int index = findIndex(input.c_str());
  //
  //
  //     if (index > -1) {
  //       Serial.println(input + " -> " + char(index + 97));
  //     }
  //
  //     Serial.println("");
  //     buttonReleasedAt = 0;
  //
  //     input = "";
  //   }
  // }

  else if (alreadyPrinted == false) {
    long diff = millis() - buttonReleasedAt;
    if (diff > 1200) {
      int index = findIndex(input.c_str());

      if (index > -1) {
        Serial.println(input + " -> " + char(index + 97));
      }

      Serial.println("");
      buttonReleasedAt = 0;
      alreadyPrinted = true;

      input = "";
    }
  }
}

void after3Sec() {
  long diff = millis() - buttonPressedAt;
  if (diff > 200) {
    // Serial.print("-");
    input += '-';
  } else {
    // Serial.print(".");
    input += ".";
  }
  alreadyPrinted = false;
  // Serial.println(input);
  delay(50);
}

int findIndex(const char* target) {
  for (int i = 0; i < arraySize; i++) {
    if (strcmp(letters[i], target) == 0) {
      return i;
    }
  }
  return -1;
}
