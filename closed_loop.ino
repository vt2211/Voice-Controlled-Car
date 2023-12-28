#define LEFT_MOTOR                  6
#define LEFT_ENCODER                3
#define RIGHT_MOTOR                 5
#define RIGHT_ENCODER               2


#define RXLED 17
#define TXLED 30

#define RUN_TIME                    (20*1000)
#define SAMPLING_INTERVAL           100
#define SAMPLE_LEN                  (RUN_TIME/SAMPLING_INTERVAL)

#define JOLT_STEPS                  2

int step_num = 0;
volatile int left_count = 0;
volatile int right_count = 0;

int16_t deltaArr[SAMPLE_LEN] = {0};
int16_t lpos[SAMPLE_LEN] = {0};
int16_t rpos[SAMPLE_LEN] = {0};
uint8_t lpwm[SAMPLE_LEN] = {0};
uint8_t rpwm[SAMPLE_LEN] = {0};

/*---------------------------*/
/*      CODE BLOCK CON1      */
/*     From open_loop.ino    */
/*       with changes        */
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
/*---------------------------*/
float delta_ss = 0;
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
  
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER), flag_right, CHANGE);
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER), flag_left, CHANGE);
}

void loop() {
  if (step_num < JOLT_STEPS) {
    write_pwm(left_jolt, right_jolt);
    step_num++;

    digitalWrite(RXLED, (step_num / 5) % 2);
    digitalWrite(TXLED, ((step_num / 5) + 1) % 2);
  }
  else if (step_num < SAMPLE_LEN) {
    // Save positions because left_position and right_position
    // can change in the middle of one loop.
    int left_position = left_count;
    int right_position = right_count;

    /*---------------------------*/
    /*      CODE BLOCK CON4      */
    /*---------------------------*/
    /*--------------------------------------*/
    /*     Add the steady-state value of    */
    /*    delta from this calculation to    */
    /*    compensate for initial turning    */
    /*--------------------------------------*/
    float delta = left_position - right_position + delta_ss;
    
    // Drive straight using feedback
    // Compute the needed pwm values for each wheel using delta and v_star
    int left_cur_pwm = driveStraight_left(v_star, delta);
    int right_cur_pwm = driveStraight_right(v_star, delta);
    write_pwm(left_cur_pwm, right_cur_pwm);
    /*---------------------------*/
    /*---------------------------*/
    /*---------------------------*/

    lpos[step_num] = left_position;
    rpos[step_num] = right_position;
    deltaArr[step_num] = delta;
    lpwm[step_num] = left_cur_pwm;
    rpwm[step_num] = right_cur_pwm;

    step_num++;
    digitalWrite(RXLED, (step_num / 5) % 2);
    digitalWrite(TXLED, ((step_num / 5) + 1) % 2);
          
  } else {
    write_pwm(0, 0);
    digitalWrite(RXLED, HIGH);
    digitalWrite(TXLED, HIGH);
    
    if (Serial.available() > 0) {
      if ( Serial.read() == 10){
       print_vals(); 
      }
    }
  }
  delay(SAMPLING_INTERVAL);
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

void print_vals() {
  Serial.println("delta");
  for (int i = 0; i < SAMPLE_LEN; i++) {
     Serial.println(lpos[i] - rpos[i]);
  }
}
