int MOTOR_LEFT_CHANNEL = 12;
int MOTOR_LEFT_BRAKE = 9;
int MOTOR_LEFT_SPEED = 3;

int MOTOR_RIGHT_CHANNEL = 13;
int MOTOR_RIGHT_BRAKE = 8;
int MOTOR_RIGHT_SPEED = 11;

const int SPEED = 255;

enum towards
{
  STOP = 0,
  RIGHT_FORWARD = 1,
  STRAIGHT_FORWARD = 2,
  LEFT_FORWARD = 3,
  LEFT_BACKWARD = 4,
  STRAIGHT_BACKWARD = 5,
  RIGHT_BACKWARD = 6
};

void setup()
{
  //Setup Channel LEFT
  pinMode(MOTOR_LEFT_CHANNEL, OUTPUT);    //Initiates Motor Channel LEFT pin
  pinMode(MOTOR_LEFT_BRAKE, OUTPUT);      //Initiates Brake Channel LEFT pin

  //Setup Channel RIGHT
  pinMode(MOTOR_RIGHT_CHANNEL, OUTPUT);   //Initiates Motor Channel RIGHT pin
  pinMode(MOTOR_RIGHT_BRAKE, OUTPUT);     //Initiates Brake Channel RIGHT pin

  Serial1.begin(9600);                    //set baud rate, BT communication
}

void loop()
{
  manageComm();
}


void manageComm()
{
  int res = -1;

  // BT reading
  if (Serial1.available()) res = int(Serial1.read());

  if (res < 0)return;

  switch (res - 48)
  {
    case STRAIGHT_FORWARD:
      straight(true);
      break;

    case STRAIGHT_BACKWARD:
      straight(false);
      break;

    case STOP:
      stopMotors();
      break;

    case LEFT_BACKWARD:
      left(true);
      break;

    case LEFT_FORWARD:
      left(false);
      break;

    case RIGHT_FORWARD:
      right(true);
      break;

    case RIGHT_BACKWARD:
      right(false);
      break;
  }
}

void right(bool forward)
{
  digitalWrite(MOTOR_RIGHT_BRAKE, HIGH);                    // Engage the Brake for Channel RIGHT

  digitalWrite(MOTOR_LEFT_CHANNEL, forward ? LOW : HIGH);   // Establishes forward direction of Channel LEFT
  digitalWrite(MOTOR_LEFT_BRAKE, LOW);                      // Disengage the Brake for Channel LEFT
  analogWrite(MOTOR_LEFT_SPEED, SPEED);                     // Spins the motor on Channel LEFT at full speed
}

void left(bool forward)
{
  digitalWrite(MOTOR_LEFT_BRAKE, HIGH);                     // Eengage the Brake for Channel LEFT

  digitalWrite(MOTOR_RIGHT_CHANNEL, forward ? LOW : HIGH);  // Establishes forward direction of Channel RIGHT
  digitalWrite(MOTOR_RIGHT_BRAKE, LOW);                     // Disengage the Brake for Channel RIGHT
  analogWrite(MOTOR_RIGHT_SPEED, SPEED);                    // Spins the motor on Channel RIGHT at full speed
}

// straight : forward or backward
void straight(bool forward)
{
  digitalWrite(MOTOR_LEFT_CHANNEL, forward ? LOW : HIGH);   // Establishes forward direction of Channel LEFT
  digitalWrite(MOTOR_LEFT_BRAKE, LOW);                      // Disengage the Brake for Channel LEFT
  analogWrite(MOTOR_LEFT_SPEED, SPEED);                     // Spins the motor on Channel LEFT at full speed

  digitalWrite(MOTOR_RIGHT_CHANNEL, forward ? HIGH : LOW);  // Establishes backward direction of Channel RIGHT
  digitalWrite(MOTOR_RIGHT_BRAKE, LOW);                     // Disengage the Brake for Channel RIGHT
  analogWrite(MOTOR_RIGHT_SPEED, SPEED);                    // Spins the motor on Channel RIGHT at full speed
}

// stop
void stopMotors()
{
  analogWrite(MOTOR_LEFT_SPEED, 0);
  analogWrite(MOTOR_LEFT_SPEED, 0);

  digitalWrite(MOTOR_RIGHT_BRAKE, HIGH);                    // Engage the Brake for Channel RIGHT
  digitalWrite(MOTOR_LEFT_BRAKE, HIGH);                     // Engage the Brake for Channel LEFT
}
