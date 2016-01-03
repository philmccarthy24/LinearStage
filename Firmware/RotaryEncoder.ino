//From bildr article: http://bildr.org/2012/08/rotary-encoder-arduino/

//these pins can not be changed 2/3 are special pins
int encoderPin1 = 2;
int encoderPin2 = 3;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

const unsigned short SAMPLE_PERIOD = 50; // in ms

void setup() {
  Serial.begin (9600);

  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);

}

void loop(){ 
  long prevEncoderVal = encoderValue;
  
  // pause for the sampling period
  delay(SAMPLE_PERIOD);
  
  // only emit a delta update if something's changed
  if (prevEncoderVal != encoderValue)
  {
    // protocol is {dialId[2]}{samplePeriodMS[2]}{delta[4]}
    //char buf[8] = {0};
    //*(short*)(buf + sizeof(short)) = SAMPLE_PERIOD;
    //*(int*)(buf + (sizeof(short) * 2)) = (int)(encoderValue - prevEncoderVal);
    int delta = encoderValue - prevEncoderVal;
    String encoderUpdate = String(0) + String(' ') + String(SAMPLE_PERIOD) + String(' ') + String(delta);
    Serial.println(encoderUpdate);
  }
}


void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}
