int segmentPins[] = {2, 3, 4, 5, 6, 7, 8}; //creates an array for all segment pins
int digitPins[] = {12, 11, 10, 9}; //creates an array for all digit pins
int dpPin = 13; //sets the DP pin to pin 13

const byte digits[10][7] = { //these 10 lines are a table for which segment pins to turn on for each number
  {1,1,1,1,1,1,0}, //#0
  {0,1,1,0,0,0,0}, //#1
  {1,1,0,1,1,0,1}, //#2
  {1,1,1,1,0,0,1}, //#3
  {0,1,1,0,0,1,1}, //#4
  {1,0,1,1,0,1,1}, //#5
  {1,0,1,1,1,1,1}, //#6
  {1,1,1,0,0,0,0}, //#7
  {1,1,1,1,1,1,1}, //#8
  {1,1,1,1,0,1,1}  //#9
};

void setup() {
  for (int i = 0; i < 7; i++) { //these 3 lines use a for loop to set every segment pin to an output
    pinMode(segmentPins[i], OUTPUT);
  }

  for (int i = 0; i < 4; i++) { //these 3 lines use a for loop to set every digit pin to an output
    pinMode(digitPins[i], OUTPUT);
  }

  pinMode(dpPin, OUTPUT); //sets the DP pin to an output

  digitalWrite(dpPin, LOW); //turns off the decimal point
}

void displayDigit(int digit, int number) {
  // Turn off all digits first
  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], HIGH);
  }

  // Turn off all segments first
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], LOW);
  }

  // Activate the correct digit
  digitalWrite(digitPins[digit], LOW);

  // Turn on the correct segments for this number
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], digits[number][i]);
  }

  // Turn off decimal point (optional)
  digitalWrite(dpPin, LOW);

  delay(5);  // Short delay to simulate full display
}


void loop() {
  static int number = 0;

  // Break number into individual digits
  int digitsArray[4] = {
    (number / 1000) % 10,
    (number / 100) % 10,
    (number / 10) % 10,
    number % 10
  };

  // Figure out how many digits to show
  int numDigits;
  if (number < 10)
    numDigits = 1;
  else if (number < 100)
    numDigits = 2;
  else if (number < 1000)
    numDigits = 3;
  else
    numDigits = 4;

  // Display digits aligned to the right (on D4, D3, D2, D1)
  unsigned long startTime = millis();
  while (millis() - startTime < 1000) {
    for (int i = 0; i < numDigits; i++) {
      int digitPosition = 4 - numDigits + i;       // D4 = index 3, D3 = 2, etc.
      int valueIndex = i + (4 - numDigits);        // Pull correct digit from array
      displayDigit(digitPosition, digitsArray[valueIndex]);
    }
  }

  number++;
  if (number > 9999) number = 1;
}
