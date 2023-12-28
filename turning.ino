#define LEFT_MOTOR                  6
#define LEFT_ENCODER                3
#define RIGHT_MOTOR                 5
#define RIGHT_ENCODER               2

#define RXLED  17
#define TXLED  30 

#define SAMPLING_INTERVAL           100

#define MODE_LISTEN                 0
#define MODE_DRIVE                  1

#define NUM_COMMANDS                4
#define DRIVE_STRAIGHT              0
#define DRIVE_LEFT                  1
#define DRIVE_RIGHT                 2
#define STOP                        3

#define JOLT_STEPS                  2

boolean loop_mode = MODE_DRIVE;
int drive_mode;
int program_count;
int sample_lens[NUM_COMMANDS] = {0};

int step_num = 0;

volatile int left_count = 0;
volatile int right_count = 0;

/*---------------------------*/
/*      CODE BLOCK CON1      */
/*    From closed_loop.ino   */
/*---------------------------*/
float theta_left = .3031;
float theta_right = .2664;
float beta_left = -32.56;
float beta_right = -37.35;
float v_star = 73.3;

// PWM inputs to jolt the car straight
int left_jolt = 110;
int right_jolt = 120;

// Control gains
float f_left = .9;
float f_right = .9;
/*---------------------------*/
/*---------------------------*/
/*---------------------------*/

/*---------------------------*/
/*      CODE BLOCK CON2      */
/*    From closed_loop.ino   */
/*---------------------------*/
float driveStraight_left(float v_star, float delta) {
  return ((v_star + beta_left)/theta_left)-((f_left/theta_left)*delta);
}

float driveStraight_right(float v_star, float delta) {
  return ((v_star + beta_right)/theta_right)+((f_right/theta_right)*delta);
}
/*---------------------------*/
/*---------------------------*/
/*---------------------------*/

/*---------------------------*/
/*      CODE BLOCK CON3      */
/*    From closed_loop.ino   */
/*---------------------------*/
float delta_ss = 0;
/*---------------------------*/
/*---------------------------*/
/*---------------------------*/

/*---------------------------*/
/*      CODE BLOCK CON4      */
/*---------------------------*/
#define CAR_WIDTH                   15.0 // in cm
#define TURN_RADIUS                 200 // in cm - 6 feet diameter
// #define TURN_RADIUS                 60 // in cm - 4 feet diameter
/*---------------------------*/
/*---------------------------*/
/*---------------------------*/

/*---------------------------*/
/*    PREPROGRAMMED PATH     */
/*---------------------------*/
int run_times[NUM_COMMANDS] = {4000, 2300, 4000, 2300}; // length of commands roughly in ms
int drive_modes[NUM_COMMANDS] = {DRIVE_STRAIGHT, DRIVE_LEFT, DRIVE_STRAIGHT, DRIVE_RIGHT}; // commands: [DRIVE_STRAIGHT, DRIVE_LEFT, DRIVE_RIGHT]


/*---------------------------*/
/*      CODE BLOCK CON5      */
/*---------------------------*/
float delta_reference(int i) {
    float delta_i = CAR_WIDTH*(v_star/5)*i/TURN_RADIUS;  
    // YOUR CODE HERE
  // Remember to divide the v* value you use in this function by 5 because of sampling interval differences!
  if (drive_mode == DRIVE_RIGHT) { // Return a NEGATIVE expression
    return -1 * delta_i;
  }
  else if (drive_mode == DRIVE_LEFT) { // Return a POSITIVE expression
    return delta_i;
  }
  else { // DRIVE_STRAIGHT
    return 0.0;
  }
}
/*---------------------------*/
/*---------------------------*/
/*---------------------------*/


/*---------------------------*/
/*      CODE BLOCK CON6      */
/*---------------------------*/
#define INFINITY                    (3.4e+38)
#define STRAIGHT_RADIUS             INFINITY

float straight_correction(int i) {
  // YOUR CODE HERE
  return 0; // Replace this line
}

/*---------------------------*/
/*---------------------------*/
/*---------------------------*/


void setup() {
  Serial.begin(38400);

  pinMode(LEFT_MOTOR, OUTPUT);
  pinMode(LEFT_ENCODER, INPUT);
  pinMode(RIGHT_MOTOR, OUTPUT);
  pinMode(RIGHT_ENCODER, INPUT);
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RXLED, OUTPUT);
  pinMode(TXLED, OUTPUT);
  delay(500);

  write_pwm(0, 0);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(TXLED, LOW);
  digitalWrite(RXLED, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(TXLED, HIGH);
  delay(1000);
  digitalWrite(RXLED, HIGH);
  delay(1000);
  for (int j = 0; j < NUM_COMMANDS; j++) {
    sample_lens[j] = run_times[j] / SAMPLING_INTERVAL;
  }

  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER), flag_right, CHANGE);
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER), flag_left, CHANGE);

  program_count = 0;
  start_drive_mode();
}

void loop() {
  if (loop_mode == MODE_LISTEN) {
    // In the integration phase of the project, this section will listen
    // to the microphone and switch to the specified mode.
    // For now, we simply cycle through them.
    
    if (program_count < 4) {
      drive_mode = drive_modes[program_count];
      start_drive_mode();
    } else {
      digitalWrite(RXLED, HIGH);
      digitalWrite(TXLED, HIGH);
    }
  } else if (loop_mode == MODE_DRIVE) {
    if (step_num < JOLT_STEPS) {
      write_pwm(left_jolt, right_jolt);
    } else {
      // Save positions because _left_position and _right_position
      // can change in the middle of one loop.
      int left_position = left_count;
      int right_position = right_count;

       /*---------------------------*/
      /*      CODE BLOCK CON0      */
      /*---------------------------*/

      float delta = left_position - right_position + delta_ss;
      delta = delta + delta_reference(step_num) + straight_correction(step_num);

      // Drive using feedback
      // Compute the needed pwm values for each wheel using delta and v_star
      int left_cur_pwm = driveStraight_left(v_star, delta);
      int right_cur_pwm = driveStraight_right(v_star, delta);
      write_pwm(left_cur_pwm, right_cur_pwm);
      /*---------------------------*/
      /*---------------------------*/
      /*---------------------------*/
      
    }

    // Counter for how many times loop is executed since entering DRIVE MODE
    step_num++;
    digitalWrite(RXLED, (!(((drive_mode == DRIVE_STRAIGHT) || (drive_mode == DRIVE_RIGHT)) && ((step_num / 5) % 2))));
    digitalWrite(TXLED, (!(((drive_mode == DRIVE_STRAIGHT) || (drive_mode == DRIVE_LEFT)) && ((step_num / 5) % 2))));

    if (step_num == sample_lens[program_count]) {
      // Completely stop and go back to listen MODE after 3 seconds
      program_count += 1;
      digitalWrite(RXLED, HIGH);
      digitalWrite(TXLED, LOW);
      start_listen_mode();
    }
    delay(SAMPLING_INTERVAL);
  }
}

/*---------------------------*/
/*     Helper functions      */
/*---------------------------*/

void write_pwm(int pwm_left, int pwm_right) {
  analogWrite(LEFT_MOTOR, (int) min(max(0, pwm_left), 255));
  analogWrite(RIGHT_MOTOR, (int) min(max(0, pwm_right), 255));
}

void flag_left() {
  if(digitalRead(LEFT_ENCODER)) {
    left_count++;
  }
}

void flag_right() {
  if(digitalRead(RIGHT_ENCODER)) {
    right_count++;
  }
}

void start_drive_mode(void) {
  loop_mode = MODE_DRIVE;
  step_num = 0;
  left_count = 0;
  right_count = 0;
}

void start_listen_mode(void) {
  write_pwm(0, 0);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
  loop_mode = MODE_LISTEN;
}
