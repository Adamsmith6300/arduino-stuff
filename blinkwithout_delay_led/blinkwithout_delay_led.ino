int misterState = LOW;
const int misterPin = 5; 
unsigned long previousMillis = 0;
const long OnTime = 3000;
const long OffTime = 5000;

void setup() {
  // put your setup code here, to run once:
pinMode(misterPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
unsigned long currentMillis = millis();
if ((misterState == HIGH) && (currentMillis - previousMillis >= OnTime)) 
{
  misterState = LOW;
  previousMillis = currentMillis;
  digitalWrite(misterPin, misterState);
}
 else if ((misterState == LOW) && (currentMillis - previousMillis >= OffTime))
 {
  misterState = HIGH;
  previousMillis = currentMillis;
  digitalWrite(misterPin, misterState);
  }
}

