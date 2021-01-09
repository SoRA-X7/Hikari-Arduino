#include <SoftwareSerial.h>

/*
Command format:

PPT commands:
"<(<#60(^" Left, RotateLeft, Left, Softdrop 60f, RotateLeft, HardDrop

<  left
>  right
)  rotateRight
(  rotateLeft
*  hold
^  hardDrop
#xx  softDrop for xx frames (in 60fps)
*/

#define FRAME_RATE 30

SoftwareSerial ss(2, 3);  // RX,TX
char lastMsg = 0;
long frames = 0;
char commands[32];
int cmdIndex = -1;
int cmdLength = 0;
int waitFrames = 0;

void setup() {
  Serial.begin(57600);
  ss.begin(57600);
  Serial.println("Connected");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  while (1000 * frames > millis() * FRAME_RATE) {
    ;
  }  // Spin wait to sync framerate
  frames++;
  if (frames % FRAME_RATE == 0) {
    digitalWrite(LED_BUILTIN, (frames / FRAME_RATE) % 2);
  }

  while (ss.available())
  {
    Serial.write(ss.read());
  }
  

  if (Serial.available()) {
    readCommand();
  }

  if (waitFrames > 0) {
    waitFrames--;
    return;
  }

  if (cmdIndex < 0) return;

  char m = lastMsg;
  if (lastMsg != 0) {
    sendSerial(lastMsg);
    sendSerial('/');
    lastMsg = 0;
  }

  if (cmdIndex >= cmdLength) {
    cmdIndex = -1;
    return;
  }

  getOpcode();
  if (m != 0 && m == lastMsg) {
    cmdIndex--;
    lastMsg = 0;
  } else if (lastMsg != 0) {
    sendSerial(lastMsg);
    sendSerial('.');
  }
}

void readCommand() {
  if (Serial.available() && Serial.peek() == '!') {
    Serial.print("RAW:");
    Serial.read();
    while (true) {
      while (!Serial.available()) {}
      char r = Serial.read();
      if (r == '\n' || r == '!') {
        Serial.println("|END");
        break;
      } else {
        Serial.write(r);
        ss.write(r);
      }
    }
    return;
  }

  int i = 0;
  while (i < 32) {
    while (!Serial.available()) {}
    char msg = Serial.read();
    if (msg == '\n') break;
    commands[i++] = msg;
  }
  cmdLength = i;
  if (i > 0) {
    cmdIndex = 0;
    Serial.write('\n');
  }
}

void getOpcode() {
  if (cmdIndex >= cmdLength) return;
  char cmd = commands[cmdIndex++];
  switch (cmd) {
    case '<':
      lastMsg = '<';
      break;
    case '>':
      lastMsg = '>';
      break;
    case ')':
      lastMsg = 'a';
      break;
    case '(':
      lastMsg = 'b';
      break;
    case '^':
      lastMsg = 'u';
      break;
    case '*':
      lastMsg = 'r';
      break;
    case '#':
      waitFrames = asciiToInt(commands[cmdIndex++]) * 10 +
                   asciiToInt(commands[cmdIndex++]);
      lastMsg = 'd';
      break;
    default:
      // digitalWrite(LED_BUILTIN, HIGH);
      break;
  }
}

void sendSerial(char c) {
  Serial.write(c);
  ss.write(c);
}

int asciiToInt(char c) { return c - 0x30; }
