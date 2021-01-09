#include <SwitchControlLibrary.h>

enum {
  RIGHT = '>',
  LEFT = '<',
  UP = 'u',
  DOWN = 'd',
  A = 'a',
  B = 'b',
  X = 'x',
  Y = 'y',
  R = 'r',
  L = 'l',
  ZR = 'R',
  ZL = 'L',
  RSTICK = '0',
  LSTICK = '1',
  RCLICK = '2',
  LCLICK = '3',
  HOME = '4',
  CAPTURE = '5',
  PLUS = '+',
  MINUS = '-'
};

enum {
  PRESS = '.',
  RELEASE = '/'
};

void setup() {
  Serial1.begin(57600);
  
  //connect to switch
  for (int i = 0; i < 3; ++i) {
    SwitchControlLibrary().PressButtonZR();
    SwitchControlLibrary().PressButtonZL();
    delay(500);
    SwitchControlLibrary().ReleaseButtonZR();
    SwitchControlLibrary().ReleaseButtonZL();
    delay(500);
  }

  Serial1.println("Ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial1.available()) {
    char button_type = Serial1.read();
    while (!Serial1.available()) {}
    char button_command = Serial1.read();
    Serial1.println("recv");

    switch (button_type) {
      case RIGHT:
        if (button_command == PRESS) {
          SwitchControlLibrary().MoveHat(2);
        } else if (button_command == RELEASE) {
          SwitchControlLibrary().MoveHat(8);
        }
        break;
      case LEFT:
        if (button_command == PRESS) {
          SwitchControlLibrary().MoveHat(6);
        } else if (button_command == RELEASE) {
          SwitchControlLibrary().MoveHat(8);
        }
        break;
      case UP:
        if (button_command == PRESS) {
          SwitchControlLibrary().MoveHat(0);
        } else if (button_command == RELEASE) {
          SwitchControlLibrary().MoveHat(8);
        }
        break;
      case DOWN:
        if (button_command == PRESS) {
          SwitchControlLibrary().MoveHat(4);
        } else if (button_command == RELEASE) {
          SwitchControlLibrary().MoveHat(8);
        }
        break;
      case A:
        if (button_command == PRESS) {
          SwitchControlLibrary().PressButtonA();
        } else if (button_command == RELEASE) {
          SwitchControlLibrary().ReleaseButtonA();
        }
        break;
      case B:
        if (button_command == PRESS) {
          SwitchControlLibrary().PressButtonB();
        } else if (button_command == RELEASE) {
          SwitchControlLibrary().ReleaseButtonB();
        }
        break;
      case X:
        if (button_command == PRESS) {
          SwitchControlLibrary().PressButtonX();
        } else if (button_command == RELEASE) {
          SwitchControlLibrary().ReleaseButtonX();
        }
        break;
      case Y:
        if (button_command == PRESS) {
          SwitchControlLibrary().PressButtonY();
        } else if (button_command == RELEASE) {
          SwitchControlLibrary().ReleaseButtonY();
        }
        break;
      case R:
        if (button_command == PRESS) {
          SwitchControlLibrary().PressButtonR();
        } else if (button_command == RELEASE) {
          SwitchControlLibrary().ReleaseButtonR();
        }
        break;
      case L:
        if (button_command == PRESS) {
          SwitchControlLibrary().PressButtonL();
        } else if (button_command == RELEASE) {
          SwitchControlLibrary().ReleaseButtonL();
        }
        break;
      case ZR:
        if (button_command == PRESS) {
          SwitchControlLibrary().PressButtonZR();
        } else if (button_command == RELEASE) {
          SwitchControlLibrary().ReleaseButtonZR();
        }
        break;
      case ZL:
        if (button_command == PRESS) {
          SwitchControlLibrary().PressButtonZL();
        } else if (button_command == RELEASE) {
          SwitchControlLibrary().ReleaseButtonZL();
        }
        break;
      case RCLICK:
        if (button_command == PRESS) {
          SwitchControlLibrary().PressButtonRClick();
        } else if (button_command == RELEASE) {
          SwitchControlLibrary().ReleaseButtonRClick();
        }
        break;        
      case LCLICK:
        if (button_command == PRESS) {
          SwitchControlLibrary().PressButtonLClick();
        } else if (button_command == RELEASE) {
          SwitchControlLibrary().ReleaseButtonLClick();
        }
        break;
      case HOME:
        if (button_command == PRESS) {
          SwitchControlLibrary().PressButtonHome();
        } else if (button_command == RELEASE) {
          SwitchControlLibrary().ReleaseButtonHome();
        }
        break;
      case CAPTURE:
        if (button_command == PRESS) {
          SwitchControlLibrary().PressButtonCapture();
        } else if (button_command == RELEASE) {
          SwitchControlLibrary().ReleaseButtonCapture();
        }
        break;
      case PLUS:
        if (button_command == PRESS) {
          SwitchControlLibrary().PressButtonPlus();
        } else if (button_command == RELEASE) {
          SwitchControlLibrary().ReleaseButtonPlus();
        }
        break;
      case MINUS:
        if (button_command == PRESS) {
          SwitchControlLibrary().PressButtonMinus();
        } else if (button_command == RELEASE) {
          SwitchControlLibrary().ReleaseButtonMinus();
        }
        break;                
    }
  }
}
