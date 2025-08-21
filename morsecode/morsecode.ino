int pin = 10;

char* letters[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", // A-I
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R 
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." // S-Z
};

char* numbers[] = {
  "-----", ".----", "..---", "...--", "....-", ".....",
  "-....", "--...", "---..", "----."
};

int timeUnit = 50;

void setup() {
  pinMode(pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    
    if (isspace(receivedChar)) {
      send_morse_space();
    } 
    else if (isalpha(receivedChar)) {
      char lowerChar = tolower(receivedChar);
      send_morse(letters[lowerChar - 'a']);
    } 
    else if (isdigit(receivedChar)) {
      int digitIndex = receivedChar - '0';
      send_morse(numbers[digitIndex]);
    }
  }
}

void send_morse(String character) {
  for (int i = 0; i < character.length(); i++) {
    if (character[i] == '-') {
      tone(pin, 3000, 3 * timeUnit);
      delay(3 * timeUnit);
      //analogWrite(ledPin, 100);
      //delay(3 * timeUnit);
      //analogWrite(ledPin, 0);
      //lay(timeUnit);
      Serial.println("_");
    } 
    else if (character[i] == '.') {
      tone(pin, 3000, timeUnit);
      delay(timeUnit);
      //analogWrite(ledPin, 100);
      //delay(timeUnit);
      //analogWrite(ledPin, 0);
      //delay(timeUnit);
      Serial.println(".");
    }
    delay(timeUnit);
  }
  delay(2 * timeUnit);
  Serial.println("char done: " + character);
}

void send_morse_space() {
  delay(7 * timeUnit);
}
