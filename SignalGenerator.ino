
#include <TimerOne.h>

#define SIGNAL_OUT_PIN 9
String message_buffer;
int waveState = LOW;
bool stopped=false;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(SIGNAL_OUT_PIN, OUTPUT);
  Timer1.initialize(1000);
  Timer1.pwm(SIGNAL_OUT_PIN,512,1000);
}

void loop() {
  if (Serial.available() > 0){
    int numChar = Serial.available();
    byte received_byte=0;
    while (numChar--){
      received_byte=Serial.read();
      //execute on carriage return
      if (received_byte==13){
        handle_message();
      }
      else {
        //discard line feeds
        if (received_byte!=10 && isDigit(received_byte)) {
          message_buffer=message_buffer + char(received_byte);
          Serial.write(received_byte);
        }
      }
    }    
  }
}

void handle_message(){
  if (message_buffer.equals("0")){
    stopsignal(LOW);
    return;
  }
  if (message_buffer.equals("1")){
    stopsignal(HIGH);
    return;
  }
  resumesignal();
  unsigned long frequency=1000;
  frequency=message_buffer.toInt();
  Serial.println("");
  Serial.println("Command: " + message_buffer);
  message_buffer="";
  if (frequency<32){
    frequency=32;
  }
  if (frequency>1000000){
    frequency=1000000;
  }
  float fperiod=(1/((float)frequency))*1000000;
  unsigned long period=(int)fperiod;
  Timer1.pwm(SIGNAL_OUT_PIN,512,fperiod);
  Serial.println("Set: " + String(1000000/period));
}

void stopsignal(int pinState){
  Serial.println("");
  Serial.println("Command: " + message_buffer);
  Serial.println("Stopped.  Output " + String(pinState));
  message_buffer="";
  stopped=true;
  Timer1.stop();
  digitalWrite(SIGNAL_OUT_PIN, pinState);
}

void resumesignal(){
  if (stopped){
    Timer1.restart();
  }
}



