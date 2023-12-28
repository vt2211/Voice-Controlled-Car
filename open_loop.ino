//#define LEFT_MOTOR                  6
//#define RIGHT_MOTOR                 5
//
//#define RXLED 17
//#define TXLED 30
//
//#define RUN_TIME                    (20*1000)
//#define SAMPLING_INTERVAL           100
//#define SAMPLE_LEN                  (RUN_TIME/SAMPLING_INTERVAL)
//
//#define JOLT_STEPS                  2
//
//int step_num = 0;
//
///*---------------------------*/
///*      CODE BLOCK CON1      */
///*---------------------------*/
//float theta_left = .3031;
//float theta_right = .2664;
//float beta_left = -32.56;
//float beta_right = -37.35;
//float v_star = 73.3;
//
//// PWM inputs to jolt the car straight
//int left_jolt = 220;
//int right_jolt = 240;
///*---------------------------*/
///*---------------------------*/
///*---------------------------*/
//
///*---------------------------*/
///*      CODE BLOCK CON2      */
///*---------------------------*/
//float driveStraight_left(float v_star) {
//  return (v_star + beta_left)/theta_left;
//}
//
//float driveStraight_right(float v_star) {
//  return (v_star+ beta_right)/theta_right;
//}
///*---------------------------*/
///*---------------------------*/
///*---------------------------*/
//
//void setup() {
//  Serial.begin(38400);
//  
//  pinMode(LEFT_MOTOR, OUTPUT);
//  pinMode(RIGHT_MOTOR, OUTPUT);
//  
//  pinMode(LED_BUILTIN, OUTPUT);
//  pinMode(RXLED, OUTPUT);
//  pinMode(TXLED, OUTPUT);
//  delay(500);
//
//  write_pwm(0, 0);
//  digitalWrite(LED_BUILTIN, HIGH);
//  digitalWrite(TXLED, LOW);
//  digitalWrite(RXLED, LOW);
//  delay(1000);
//  digitalWrite(LED_BUILTIN, LOW);
//  delay(1000);
//  digitalWrite(TXLED, HIGH);
//  delay(1000);
//  digitalWrite(RXLED, HIGH);
//  delay(1000);
//}
//
//void loop() {
//  if (step_num < JOLT_STEPS) {
//    write_pwm(left_jolt, right_jolt);
//    step_num++;
//
//    digitalWrite(RXLED, (step_num / 5) % 2);
//    digitalWrite(TXLED, ((step_num / 5) + 1) % 2);
//  }
//  else if (step_num < SAMPLE_LEN) {
//    /*---------------------------*/
//    /*      CODE BLOCK CON3      */
//    /*---------------------------*/
//    // Attempt to drive straight using open loop control
//    // Compute the PWM input required for each wheel based on v_star
//    int left_cur_pwm = driveStraight_left(v_star);
//    int right_cur_pwm = driveStraight_right(v_star);
//    /*---------------------------*/
//    /*---------------------------*/
//    /*---------------------------*/
//    
//    write_pwm(left_cur_pwm, right_cur_pwm);
//    step_num++; 
//
//    digitalWrite(RXLED, (step_num / 5) % 2);
//    digitalWrite(TXLED, ((step_num / 5) + 1) % 2);
//  }
//  else {
//    write_pwm(0, 0);
//    digitalWrite(RXLED, HIGH);
//    digitalWrite(TXLED, HIGH);
//  }
//  delay(SAMPLING_INTERVAL);
//}
//
///*---------------------------*/
///*     Helper functions      */
///*---------------------------*/
//
//void write_pwm(int pwm_left, int pwm_right) {
//  analogWrite(LEFT_MOTOR, (int) min(max(0, pwm_left), 255));
//  analogWrite(RIGHT_MOTOR, (int) min(max(0, pwm_right), 255));
//}
