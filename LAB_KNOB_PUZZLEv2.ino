#define KNOB_1 32
#define KNOB_2 34
#define KNOB_3 36
#define KNOB_4 38
#define KNOB_LOCK 40

int KNOB_STATE;

int phaseState = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(KNOB_1, INPUT_PULLUP);
  pinMode(KNOB_2, INPUT_PULLUP);
  pinMode(KNOB_3, INPUT_PULLUP);
  pinMode(KNOB_4, INPUT_PULLUP);
  pinMode(KNOB_LOCK, OUTPUT);

  phaseState = 1;
}

void loop() {

  
  // put your main code here, to run repeatedly:
  KNOB_STATE = digitalRead(KNOB_1) + digitalRead(KNOB_2) + digitalRead(KNOB_3) + digitalRead(KNOB_4);
  Serial.print("Debug - KNOB: ");
  Serial.println(KNOB_STATE);
  if (KNOB_STATE == 4) {
    phaseState = 1;
  }
  if (KNOB_STATE == 3) {
    phaseState = 2;
  }
  if (KNOB_STATE == 2) {
    phaseState = 3;
  }
  if (KNOB_STATE == 1) {
    phaseState = 4;
  }
  if (KNOB_STATE == 0) {
    phaseState = 5;
    digitalWrite(KNOB_LOCK, HIGH);
  }

  if(Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    if(data == "6") {
      phaseState = 5;
      Serial.println("Debug - Knob Puzzle Unlocked");
      digitalWrite(KNOB_LOCK, HIGH)
    }
    if(data == "99") {
      reset();
      Serial.println("Debug - Puzzle Reset");
    }
  }

  Serial.println(phaseState);
}

void reset() {
  digitalWrite(KNOB_LOCK, LOW);
  phaseState = 1;
}
