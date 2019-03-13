#include <Tone.h>

// We need a Tone
Tone speaker;

// Redefinition of useful notes
int ff = NOTE_F6;
int ee = NOTE_E6;
int dd = NOTE_D6;
int cc = NOTE_C6;
int b  = NOTE_B5;
int b_ = NOTE_AS5;
int a  = NOTE_A5;
int g  = NOTE_G5;
int f  = NOTE_F5;
int e  = NOTE_E5;
int d  = NOTE_D5;
int c  = NOTE_C5;
int B  = NOTE_B4;
int B_ = NOTE_AS4;
int A  = NOTE_A4;
int G  = NOTE_G4;
int F  = NOTE_F4;

// Silent note (pause)
int p = 0;

// System variables
int micIn = 0;      // Microphone input pin
int speakerOut = 9; // Speaker is on PWM output (digital 9, 10 or 11)
int ledPin = 12;    // LED output pin
int potar = 1;      // Potentiometer input for trigger level
int noise = 0;      // Sound level from microphone
int trigger = 0;    // Trigger level

// Each phrase consists of an array of notes (as defined above) and an array of beats
// Whole note = 16
// Half note = 8
// Quarter = 4
// etc.

// Teresa Teng's "Lovesick by the small window"
int intro[]         = { d,   f, g,   b_, a, g, b_, a, g, f, p, dd,  cc, ff, dd, cc, b_, p };
float intro_beats[] = { 4, 4+2, 2,  4+2, 2, 2,  2, 2, 2, 4, 2,  2, 4+2,  2,  4,  4,  8, 4 };

int melody_1[]         = { d,   f, g, g, f, d, c,   d, c, B_, p, d, f, d, f,   g, b_, cc, cc, b_, g, f,   g, p };
float melody_1_beats[] = { 4, 4+2, 2, 2, 2, 2, 2, 4+2, 2,  8, 4, 4, 4, 2, 2, 4+2,  2,  4,  1,  1, 1, 1, 8+4, 8 };

int melody_2[]         = { b_, g,  b_, cc, b_, g, f, d, c, B_, p, d,   c, f,   d, c, c, B_, G, B_, c, p };
float melody_2_beats[] = {  2, 2, 4+2,  2,  4, 2, 2, 2, 2,  4, 4, 4, 4+2, 2, 4+2, 2, 2,  2, 2,  2, 8, 4 };

int melody_3[]         = { d,   f, g, g, f, d, c,   d, c, B_, p, d, f, d, f,   g, b_, cc, cc, b_, g, f,   g, p };
float melody_3_beats[] = { 4, 4+2, 2, 2, 2, 2, 2, 4+2, 2,  8, 4, 4, 4, 2, 2, 4+2,  2,  4,  1,  1, 1, 1, 4+2, 8 };

int melody_4[]         = { b_, g,  b_, cc, b_, g, f, d, c, B_, p, d,   c, f,   d, c, c, B_, G, F,  B_, p };
float melody_4_beats[] = {  2, 2, 4+2,  2,  4, 2, 2, 2, 2,  4, 4, 4, 4+2, 2, 4+2, 2, 2,  2, 2, 2, 8+4, 8 };

int melody_5[]         = { B_, c,   d, f,   d, c, d, p, c, d, f, d, f,   g, cc, b_,   b_,    g,    f,   g, p };
float melody_5_beats[] = {  2, 2, 4+2, 2, 4+2, 2, 8, 4, 2, 2, 4, 2, 2, 4+2,  2,  4, 4./3, 4./3, 4./3, 8+4, 8 };

int melody_6[]         = { f, g,  b_, cc,  b_, g, b_, p, cc, b_, g, b_, g,   f, d, c, d, c, d, f, p };
float melody_6_beats[] = { 2, 2, 4+2,  2, 4+2, 2,  8, 4,  2,  2, 4,  2, 2, 4+2, 2, 4, 1, 1, 2, 8, 4 };

int melody_7[]         = { d,   f, g, g, f, d, c,   d, c, B_, p, d, f, d, f,   g, b_, cc, cc, b_, g, f,   g, p };
float melody_7_beats[] = { 4, 4+2, 2, 2, 2, 2, 2, 4+2, 2,  8, 4, 4, 4, 2, 2, 4+2,  2,  4,  1,  1, 1, 1, 8+4, 8 };

int zeend[]       = { B_, c, d,   f, d,  b_, a,   g, dd,  cc, dd, dd, cc, ff, dd, dd, cc, B_, B_, d, f, g,  b_,  b_,  p };
float end_beats[] = {  2, 2, 2, 2+2, 2, 4+2, 2, 4+2,  2, 4+2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2, 2+1, 1+4, 16 };

// Set tempo
float tempo = 78;
float time = 60./tempo*1000./4;

// Play a note
void playNote(int tone_, float duration) {

  duration *= time;

  if (tone_>0) // Normal note
  {    
    speaker.play(tone_);
    delay(duration);
    speaker.stop();
    delay(time/50); // Small pause between notes
  }
  else // Pause
  {
    delay(duration);
  }

}


// Play a single phrase
void playPhrase(int phrase[], float beats[], int zesize) {

    zesize/=2;

    for (int i=0; i<zesize; i++)
    {
      playNote(phrase[i], beats[i]);
    }

}


// Main the whole melody
void playMelody() {

  playPhrase(intro, intro_beats, sizeof(intro));

  playPhrase(melody_1, melody_1_beats, sizeof(melody_1));
  playPhrase(melody_2, melody_2_beats, sizeof(melody_2));
  playPhrase(melody_3, melody_3_beats, sizeof(melody_3));
  playPhrase(melody_4, melody_4_beats, sizeof(melody_4));
  playPhrase(melody_5, melody_5_beats, sizeof(melody_5));
  playPhrase(melody_6, melody_6_beats, sizeof(melody_6));
  playPhrase(melody_7, melody_7_beats, sizeof(melody_7));

  playPhrase(melody_1, melody_1_beats, sizeof(melody_1));
  playPhrase(melody_2, melody_2_beats, sizeof(melody_2));
  playPhrase(melody_3, melody_3_beats, sizeof(melody_3));
  playPhrase(melody_4, melody_4_beats, sizeof(melody_4));
  playPhrase(melody_5, melody_5_beats, sizeof(melody_5));
  playPhrase(melody_6, melody_6_beats, sizeof(melody_6));
  playPhrase(melody_7, melody_7_beats, sizeof(melody_7));

  playPhrase(zeend, end_beats, sizeof(zeend));

  return;
}


// Setup fonction
void setup() {
  
  pinMode(speakerOut, OUTPUT);
  pinMode(ledPin, OUTPUT); 
  
  speaker.begin(9);
//  Serial.begin(9600); // For debugging

}


// Loop function, runs forever
void loop() {

  // read noise level from a microphone
  noise = analogRead(micIn);

  // read trigger level from a potentiometer
  trigger = analogRead(potar);

  // does the baby cry ?
  if (noise >= trigger/5) {
    digitalWrite(ledPin, HIGH);
    playMelody();
    digitalWrite(ledPin, LOW);
  }

  // give the Arduino some rest
  delay(100);

}

