/********************************************************/
/********************************************************/
/***                                                  ***/
/*** Constants and global variables from turning.ino. ***/
/***                                                  ***/
/********************************************************/
/********************************************************/

#define LEFT_MOTOR                  6
#define LEFT_ENCODER                3
#define RIGHT_MOTOR                 5
#define RIGHT_ENCODER               2

#define RXLED                       17
#define TXLED                       30

#define SAMPLING_INTERVAL           100
#define NUM_COMMANDS                4
int sample_lens[NUM_COMMANDS] = {0};

// Operation modes
#define MODE_LISTEN                 0
#define MODE_DRIVE                  1

#define NUM_COMMANDS                4
#define DRIVE_FAR                   0
#define DRIVE_LEFT                  1
#define DRIVE_CLOSE                 2
#define DRIVE_RIGHT                 3

#define JOLT_STEPS                  2

boolean loop_mode = MODE_DRIVE;
int drive_mode = 0;

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
/*      CODE BLOCK CON2      */
/*      From turning.ino     */
/*---------------------------*/
float driveStraight_left(float v_star, float delta) {
  return ((v_star + beta_left)/theta_left)-((f_left/theta_left)*delta);
}

float driveStraight_right(float v_star, float delta) {
  return ((v_star + beta_right)/theta_right)+((f_right/theta_right)*delta);
}

/*---------------------------*/
/*      CODE BLOCK CON3      */
/*      From turning.ino     */
/*---------------------------*/

float delta_ss = 0;

/*---------------------------*/
/*      CODE BLOCK CON4      */
/*      From turning.ino     */
/*---------------------------*/

#define CAR_WIDTH                   15.0 // in cm
#define TURN_RADIUS                 200 // in cm - 6 feet diameter
// #define TURN_RADIUS                 60 // in cm - 4 feet diameter

/*---------------------------*/
/*    PREPROGRAMMED PATH     */
/*---------------------------*/
int run_times[NUM_COMMANDS] = {4000, 2300, 2000, 2300}; // length of commands roughly in ms
int drive_modes[NUM_COMMANDS] = {DRIVE_FAR, DRIVE_LEFT, DRIVE_CLOSE, DRIVE_RIGHT}; // 
/*---------------------------*/
/*      CODE BLOCK CON5      */
/*      From turning.ino     */
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
/*      CODE BLOCK CON6      */
/*      From turning.ino     */
/*---------------------------*/
#define INFINITY                    (3.4e+38)
#define STRAIGHT_RADIUS             INFINITY

float straight_correction(int i) {
  // YOUR CODE HERE
  return 0; // Replace this line
}

/*********************************************************/
/*********************************************************/
/***                                                   ***/
/*** Constants and glboal variables from classify.ino. ***/
/***                                                   ***/
/*********************************************************/
/*********************************************************/

#define SIZE                        5504
#define ADC_TIMER_MS                0.35
#define AVG_SHIFT                   5
#define AVG_SIZE                    (int) pow(2, AVG_SHIFT)
#define SIZE_AFTER_FILTER           (int) SIZE / AVG_SIZE

#define MIC_INPUT                   A2

/*---------------------------*/
/*      CODE BLOCK PCA1      */
/*     From classify.ino     */
/*---------------------------*/

#define SNIPPET_SIZE                  80
#define PRELENGTH                     5
#define THRESHOLD                     0.5
#define BASIS_DIM                     3

#define EUCLIDEAN_THRESHOLD           .03
#define LOUDNESS_THRESHOLD            400

/*---------------------------*/
/*      CODE BLOCK PCA2      */
/*     From classify.ino     */
/*---------------------------*/

float pca_vec1[80] = {0.010146608025165765, -0.008016047170881446, -0.0203292497940587, -0.042871405863204815, -0.03774067236177029, 0.06947440441407787, 0.09949163251272455, 0.06790509635578622, 0.04505416722747538, 0.03400774677080343, 0.027648839520510733, 0.016827590803603926, 0.01839131981967028, 0.04154010698622987, 0.09122956280158502, 0.18023641897326012, 0.2562809469396683, 0.2735473789832322, 0.3036852769526307, 0.2949443312661428, 0.29722046682678416, 0.26843404223547296, 0.26093854380261955, 0.2320660566603194, 0.19081937317633055, 0.12421918188449252, 0.055184482439441324, 0.006815416251563131, -0.038554840396561825, -0.0796821964803827, -0.12093441463613847, -0.1321864521429118, -0.145590602093948, -0.13533424021780507, -0.1238556044384681, -0.12094855464104523, -0.10643115686643442, -0.10935929527623567, -0.09239860125880624, -0.09335435890532424, -0.08668285341727061, -0.08400291875850449, -0.08305772074263118, -0.07565008936446069, -0.07554749340269423, -0.06903722885421741, -0.0683844686779747, -0.07255555518652604, -0.06796350832448265, -0.07552846248568733, -0.07378344410219073, -0.07423172191467094, -0.07830103330446146, -0.07871210089800441, -0.0746572380969933, -0.07084461882814808, -0.06823762055729618, -0.06484219992790972, -0.06146948109940064, -0.05784382988810007, -0.05793712752354972, -0.05440069593457291, -0.0518799714397168, -0.04046177208376862, -0.03810493320115312, -0.03282615140412291, -0.023319806109776076, -0.019640036960042614, -0.015505489540185578, -0.013099475345560543, -0.011794533646285042, -0.009428463098659112, -0.005131946443402754, -0.01007148809666493, -0.0031571468112321227, -0.007770408039843181, -0.0016653263440328827, -0.0010087316387682387, -0.003615919039962138, 0.0036317114473106153};
float pca_vec2[80] = {0.015084281023069156, 0.032028764022749234, 0.040341378028937724, 0.07551038589855574, 0.09272734671875402, 0.11696150547160199, 0.14561254557778366, 0.17843583159953386, 0.17969757681967774, 0.1952573722914158, 0.2169786825799128, 0.22621489789279403, 0.2313753483505412, 0.15606707002176193, 0.04527318260039809, -0.07704438845669896, -0.14900715167681436, -0.1549966118104183, -0.13113198261937864, -0.11518884271737032, -0.10863771895937176, -0.08000287285374874, -0.058941151809373406, -0.0011791393761716605, 0.08414233675744702, 0.19400833239717777, 0.25408582197214014, 0.23154968975620846, 0.2170830873650961, 0.1750227353204247, 0.14146703202710417, 0.11300862144242514, 0.08720453707283303, 0.05589218994733236, 0.025445932918982297, 0.017320572102953454, -0.03150036465641688, -0.03077701042277659, -0.06305133327066124, -0.07975793438244633, -0.0988578376128619, -0.10999244311839208, -0.13960318986118245, -0.13930137492946967, -0.142267000957563, -0.1518168260853615, -0.14632819279216785, -0.1322033351736896, -0.10800250779658367, -0.09985507225078573, -0.0905719041752702, -0.09331633010512916, -0.10552113538195296, -0.10725797740158928, -0.09451966757643943, -0.09475606492448453, -0.08334651810667242, -0.0839529076321144, -0.07339614386918268, -0.06850667092199782, -0.06198662662218128, -0.060842231370142684, -0.05456754203925841, -0.049872872219125404, -0.04168533053286286, -0.04035910843903639, -0.02838930326598855, -0.027119105548051827, -0.017161386916428916, -0.007541933623246462, -0.006931212193801444, -0.0012280097069055724, 0.0038196249312369528, 0.007594913001020295, 0.01275918708201956, 0.018290140175786198, 0.01427883944973679, 0.014952505615748204, 0.014533536232428854, 0.012248461695979186};
float pca_vec3[80] = {0.0009971493047510852, 0.004937060481040301, 0.021868250738183544, 0.053737829290087316, 0.08074193700361654, 0.1273096136785984, 0.11190452573840848, 0.1253856792788488, 0.14333128724240166, 0.15492331810976484, 0.16033583766166062, 0.15177435976317638, 0.15159211739408887, 0.14658170423149935, 0.1596663036960597, 0.09497580198966442, 0.034041773113295065, -0.018245454219805834, -0.07038352143605658, -0.10527299419841676, -0.12371903372052621, -0.1311276516600032, -0.12679869799363255, -0.14253479214647355, -0.1492876157213838, -0.1344006793223884, -0.14294248222407077, -0.1361869467217271, -0.17924451728191207, -0.17955041273688624, -0.1897279115597619, -0.18307819861496644, -0.19164383769639423, -0.17836726128878216, -0.19299988561117334, -0.17653324686527158, -0.17095353464476112, -0.1607210453474959, -0.15022234920020403, -0.13806768737363445, -0.1314092771841819, -0.1206139058825104, -0.11188778150719421, -0.08234469084147271, -0.056368632967017294, -0.04678942003593145, 0.007398178325189295, 0.038601294408217024, 0.052552239405414335, 0.08159735328656903, 0.0889091987041387, 0.08307947865816423, 0.08326132271803932, 0.08299863451701327, 0.09579767537612519, 0.1162409518882192, 0.10042466315487529, 0.11098427531865779, 0.11820020368046245, 0.10865434808245132, 0.10868982209201025, 0.10609247933919927, 0.09340440476662175, 0.09110904378084815, 0.08691115224491036, 0.07369039026151526, 0.0633387542569839, 0.0660486283861738, 0.059340842424068126, 0.047956167552261286, 0.030961499737959083, 0.03708980832961136, 0.02873812881377148, 0.022504588547997806, 0.024084127174291498, 0.018760650063977567, 0.02138877282970931, 0.019223934355702143, 0.017978476809933044, 0.01130742799781037};
float projected_mean_vec[3] = {0.030859569158017935, 0.0440744121028308, -0.009673512377754049};
float centroid1[3] = {-0.030659013281576716, 0.040641724556916614, 0.0034136771069584737};
float centroid2[3] = {0.05370370156582855, 0.004917375148457834, 0.0203444055660385};
float centroid3[3] = {-0.042690722620658976, -0.024958994220201116, 0.02320926015336457};
float centroid4[3] = {0.003859810486804021, -0.019470399057539244, -0.02115722807800355};
float* centroids[4] = {
  (float *) &centroid1, (float *) &centroid2,
  (float *) &centroid3, (float *) &centroid4
};

/*---------------------------*/
/*---------------------------*/
/*---------------------------*/

//data array and index pointer
int16_t out[SIZE_AFTER_FILTER] = {0};
volatile int re_pointer = 0;

int16_t re0[AVG_SIZE] = {0};
int16_t re1[AVG_SIZE] = {0};
int write_arr = 0;

int16_t * get_re(int loc){
  switch(loc){
    case 0:
      return re0;
    case 1:
      return re1;
    default:
      return re0;
  }
}

float result[SNIPPET_SIZE] = {0};
float proj1 = 0;
float proj2 = 0;
float proj3 = 0;

/*---------------------------*/
/*       Norm functions      */
/*---------------------------*/

// Compute the L2 norm of (dim1, dim2) and centroid
// input: dim1: 1st dimension coordinate
//        dim2: 2nd dimension coordinate
//        centroid: size-2 array containing centroid coordinates
// output: L2 norm (Euclidean distance) between point and centroid
float l2_norm(float dim1, float dim2, float* centroid) {
  return sqrt(pow(dim1-centroid[0],2) + pow(dim2-centroid[1],2));
}

// Compute the L2 norm of (dim1, dim2, dim3) and centroid
// input: dim1: 1st dimension coordinate
//        dim2: 2nd dimension coordinate
//        dim3: 3rd dimension coordinate
//        centroid: size-3 array containing centroid coordinates
// output: L2 norm (Euclidean distance) between point and centroid
float l2_norm3(float dim1, float dim2, float dim3, float* centroid) {
  return sqrt(pow(dim1-centroid[0],2) + pow(dim2-centroid[1],2) + pow(dim3-centroid[2],2));
}

void setup(void) {
  Serial.begin(38400);

  pinMode(LEFT_MOTOR, OUTPUT);
  pinMode(LEFT_ENCODER, INPUT);
  pinMode(RIGHT_MOTOR, OUTPUT);
  pinMode(RIGHT_ENCODER, INPUT);
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RXLED, OUTPUT);
  pinMode(TXLED, OUTPUT);
  pinMode(MIC_INPUT, INPUT);
  delay(500);

  re_pointer = 0;
      
  cli();
  //set timer1 interrupt at 1Hz * SAMPLING INTERVAL / 1000
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15.624 * ADC_TIMER_MS;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();

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

  for (int i = 0; i < 4; i++) {
    sample_lens[i] = run_times[i] / SAMPLING_INTERVAL;
  }

  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER), flag_right, CHANGE);
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER), flag_left, CHANGE);
  
  start_listen_mode();
}

void loop(void) {
  if (re_pointer%AVG_SIZE == 0){
    write_arr = !write_arr;
    envelope_small(get_re(!write_arr), out, re_pointer>>AVG_SHIFT);
  }
  if (re_pointer == (int) (SIZE / 3)) {
    digitalWrite(TXLED, LOW);
  }
  if (re_pointer == (int) (SIZE * 2 / 3)) {
    digitalWrite(RXLED, LOW);
  }
  if (loop_mode == MODE_LISTEN && re_pointer == SIZE) {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(TXLED, HIGH);
    digitalWrite(RXLED, HIGH);
    write_pwm(0, 0);
    
    // if enveloped data is above some preset value
    if(envelope(out, result)) {

      // Reset projection result variables declared above
      proj1 = 0;
      proj2 = 0;
      proj3 = 0;

      /*---------------------------*/
      /*      CODE BLOCK PCA3      */
      /*     From classify.ino     */
      /*     with more changes     */
      /*---------------------------*/

      // Project 'result' onto the principal components
      // YOUR CODE HERE
for (int i = 0; i < SNIPPET_SIZE; i++) {
        proj1 += result[i] * pca_vec1[i];
        proj2 += result[i] * pca_vec2[i];
        proj3 += result[i] * pca_vec3[i];
      }

      // Demean the projection
      proj1 -= projected_mean_vec[0];
      proj2 -= projected_mean_vec[1];
      proj3 -= projected_mean_vec[2];

      // Classification
      // Use the function 'l2_norm3' defined above
      // ith centroid: 'centroids[i]'
      float best_dist = 999999;
      int best_index = -1;
      float temp = 0;
      // YOUR CODE HERE
      for (int i = 0; i < 4; i++) {
          temp = l2_norm3(proj1, proj2, proj3, centroids[i]);
          if (temp < best_dist) {
              best_dist = temp;
              best_index = i;
          }
      }

      // Compare 'best_dist' against the 'EUCLIDEAN_THRESHOLD' and print the result
      // If 'best_dist' is less than the 'EUCLIDEAN_THRESHOLD', the recording is a word
      // Otherwise, the recording is noise
      // YOUR CODE HERE
      if (best_dist < EUCLIDEAN_THRESHOLD) {
          if (best_index == 0) {
              drive_mode = DRIVE_FAR;
          } else if(best_index == 1){
              drive_mode = DRIVE_LEFT;
          } else if(best_index == 2) {
              drive_mode = DRIVE_CLOSE;
          } else if(best_index == 3) {
              drive_mode = DRIVE_RIGHT;
          }
          start_drive_mode();
          Serial.println(best_index);
          
      } else {
          Serial.print("Above EUCLIDIAN_THRESHOLD ");
          Serial.println(best_dist);
      }

      /*---------------------------*/
      /*---------------------------*/
      /*---------------------------*/
    } else {
     Serial.println("Below LOUDNESS_THRESHOLD.");
   }

    delay(2000);
    re_pointer = 0; // start recording from beginning if we don't start driving
    
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

      // Drive straight using feedback
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
    digitalWrite(RXLED, (!(((drive_mode == DRIVE_FAR) || (drive_mode == DRIVE_CLOSE) || (drive_mode == DRIVE_RIGHT)) && ((step_num / 5) % 2))));
    digitalWrite(TXLED, (!(((drive_mode == DRIVE_FAR) || (drive_mode == DRIVE_CLOSE) || (drive_mode == DRIVE_LEFT)) && ((step_num / 5) % 2))));

    if (step_num == sample_lens[drive_mode]) {
      // Completely stop and go back to listen MODE after 3 seconds
      start_listen_mode();
    }
    delay(SAMPLING_INTERVAL);
  }
}

/*---------------------------*/
/*     Helper functions      */
/*---------------------------*/

void envelope_small(int16_t* data, int16_t* data_out, int index){
  int32_t avg = 0;
  for (int i = 0; i < AVG_SIZE; i++) {
      avg += data[i];
  }
  
  avg = avg >> AVG_SHIFT;
  data_out[index] = abs(data[0] - avg);  
  
  for (int i = 1; i < AVG_SIZE; i++) {
      data_out[index] += abs(data[i] - avg);
  }
}

// Enveloping function with thresholding and normalizing,
// returns snippet of interest (containing speech)
bool envelope(int* data, float* data_out) {
  float maximum = 0;
  int32_t total = 0;
  int block;

  // Apply enveloping filter while finding maximum value
  for (block = 0; block < SIZE_AFTER_FILTER; block++) {
    if (data[block] > maximum) {
      maximum = data[block];
    }
  }

  // If not loud enough, return false
  if (maximum < LOUDNESS_THRESHOLD) {
    Serial.println(maximum);
    return false;
  }

  // Determine threshold
  float thres = THRESHOLD * maximum;

  // Figure out when interesting snippet starts and write to data_out
  block = PRELENGTH;
  while (data[block++] < thres && block < SIZE_AFTER_FILTER);
  if (block > SIZE_AFTER_FILTER - SNIPPET_SIZE) {
    block = SIZE_AFTER_FILTER - SNIPPET_SIZE;
  }
  for (int i = 0; i < SNIPPET_SIZE; i++) {
    data_out[i] = data[block-PRELENGTH+i];
    total += data_out[i];
  }

  // Normalize data_out
  for (int i = 0; i < SNIPPET_SIZE; i++) {
    data_out[i] = data_out[i] / total;
  }

  return true;
}

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
  delay(3000);
  loop_mode = MODE_LISTEN;
}

/*---------------------------*/
/*    Interrupt functions    */
/*---------------------------*/

ISR(TIMER1_COMPA_vect){//timer1 interrupt 8Khz toggles pin 13 (LED)
  if (re_pointer < SIZE && loop_mode != MODE_DRIVE) {
    digitalWrite(RXLED, LOW);
    get_re(write_arr)[re_pointer%AVG_SIZE] = (analogRead(MIC_INPUT) >> 4) - 128;
    re_pointer += 1;
  }
}
