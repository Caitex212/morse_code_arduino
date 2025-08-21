int ledPin = 13;

char* letters[] = {
".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", // A-I
".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R 
"...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." // S-Z
};

char* numbers[] = {
  "-----", ".----", "..---", "...--", "....-", ".....",
"-....", "--...", "---..", "----."
};

int timeUnit = 100;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    if (isspace(receivedChar)) {
      send_morse_space();
    } else if (isalpha(receivedChar)) {
      char lowerChar = tolower(receivedChar);
      send_morse(letters[lowerChar - 'a']);
    } else if (isdigit(receivedChar)) {
      int digitIndex = receivedChar - '0';
      send_morse(numbers[digitIndex]);
    }
  }

}

void send_morse(String character) {
  for (int i = 0; i < character.length(); i++) {
    if (character[i] == '-') {
      digitalWrite(ledPin, HIGH);
      delay(3 * timeUnit);                
      digitalWrite(ledPin, LOW);
      delay(timeUnit);
    } else if (character[i] == '.') {
      digitalWrite(ledPin, HIGH);
      delay(timeUnit);   
      digitalWrite(ledPin, LOW);
      delay(timeUnit); 
    }
    delay(3 * timeUnit);
  }
  Serial.println("char done: " + character);
}

void send_morse_space() {
  delay(4 * timeUnit); // 4+3 are 7 (We already have a delay of 3 in send_morse)
}

