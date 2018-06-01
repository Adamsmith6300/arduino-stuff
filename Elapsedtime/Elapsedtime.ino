int seconds;
int minutes;
void setup() {
  // put your setup code here, to run once:
seconds = 0;
minutes = 0;
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print(minutes);
Serial.print(":");
Serial.println(seconds);
delay(1000);
seconds++;
if(seconds == 60)
{
  minutes++;
  seconds = 0;
}
}
