/*
 * Author: Alex Mills, Daniel Atkinson
 */

// Wiring example
// +5    o---LDR--.--R1---o GND
//                |
// Pin 0 o--------

int speakerPin = 9;
int ldrPin = 10;  //define a pin for LDR
int ldrValue = 0;
int randomNumber;
int targetTime;

int length = 26; // the number of notes
char notes[] = "eeeeeeegcde fffffeeeeddedg"; // a space represents a rest
int beats[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,};
int tempo = 200;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    Serial.println(analogRead(ldrPin));
    if(analogRead(ldrPin)>300){
      randomLights(100);
      if (names[i] == note) {
        playTone(tones[i], duration);
      }  
    }
  }
}

void setPinMode(int low, int high) {
  for (int thisPin = low; thisPin < high; thisPin++) {
    pinMode(thisPin, OUTPUT);
  }
}

void offLights(int low, int high) {
// Turn off all the LEDs
  for (int thisPin = low; thisPin < high; thisPin++) {
    digitalWrite(thisPin, LOW);
  }
}

void randomLights(int timeout) {
  randomNumber = random(1,6);
  if(millis() > targetTime){
    targetTime = millis() + timeout;
    offLights(0,10);
    digitalWrite(randomNumber, HIGH);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(speakerPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  setPinMode(0,10);
}

void loop() {
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
    // pause between notes
    delay(tempo / 2);
  }
}
