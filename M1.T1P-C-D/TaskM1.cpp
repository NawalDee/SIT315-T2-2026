#include <avr/io.h>
#include <avr/interrupt.h>

// Pin setup
const byte redLED = 5;
const byte greenLED = 6;
const byte buzzer = 7;

// System states
enum SystemState
{
  READY,
  MONITORING,
  WARNING,
  EMERGENCY
};

volatile SystemState currentState = READY;

// Button flags
volatile bool button1Pressed = false;
volatile bool button2Pressed = false;
volatile bool button3Pressed = false;

volatile byte seconds = 0;
volatile bool blink = false;

// Set up Timer1
void setupTimer1()
{
  cli();

  TCCR1A = 0;
  TCCR1B = 0;

  OCR1A = 15624;

  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);

  TIMSK1 |= (1 << OCIE1A);

  sei();
}

// Set up Pin Change Interrupt
void setupPCI()
{
  PCICR |= (1 << PCIE0);

  PCMSK0 |= (1 << PCINT0);
  PCMSK0 |= (1 << PCINT1);
  PCMSK0 |= (1 << PCINT2);
}

// Setup
void setup()
{
  Serial.begin(9600);

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);

  setupPCI();
  setupTimer1();

  digitalWrite(greenLED, HIGH);

  Serial.println("READY");
}

// Main program
void loop()
{
  if (button1Pressed)
  {
    button1Pressed = false;

    if (currentState == READY)
    {
      currentState = MONITORING;
      seconds = 0;

      Serial.println("Monitoring Started");
    }
  }

  if (button2Pressed)
  {
    button2Pressed = false;

    currentState = READY;
    seconds = 0;

    noTone(buzzer);

    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);

    Serial.println("System Reset");
  }

  if (button3Pressed)
  {
    button3Pressed = false;

    // Emergency works only during warning
    if (currentState == WARNING)
    {
      currentState = EMERGENCY;

      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, LOW);

      tone(buzzer, 1000);

      Serial.println("EMERGENCY");
    }
  }
}

// Timer interrupt
ISR(TIMER1_COMPA_vect)
{
  blink = !blink;

  switch (currentState)
  {

    case READY:

      digitalWrite(greenLED, HIGH);
      digitalWrite(redLED, LOW);
      noTone(buzzer);

      break;

    case MONITORING:

      seconds++;

      digitalWrite(greenLED, blink);

     if (seconds >= 5)
{
  currentState = WARNING;
  seconds = 0;

  Serial.println("WARNING");
}

      break;

    case WARNING:

      digitalWrite(redLED, blink);

      if (blink)
        tone(buzzer, 1000);
      else
        noTone(buzzer);

      break;

    case EMERGENCY:

      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, LOW);

      tone(buzzer, 1000);

      break;
  }
}

// Pin Change Interrupt
ISR(PCINT0_vect)
{
  if (digitalRead(8) == LOW)
    button1Pressed = true;

  if (digitalRead(9) == LOW)
    button2Pressed = true;

  if (digitalRead(10) == LOW)
    button3Pressed = true;
}