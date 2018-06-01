int ledPin = 3;
int misterPin = 5;
void setup() {
  // put your setup code here, to run once:
pinMode (ledPin, OUTPUT);
pinMode (misterPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(ledPin, HIGH);
delay(5000);
digitalWrite(misterPin,HIGH);
delay(3000)
digitalWrite(ledPin,LOW);
delay(5000);
digitalWrite(misterPin,LOW)

}
