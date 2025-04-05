const int ldrPin = 32;

void setup() {
  // put your setup code here, to run once:
    pinMode(ldrPin,INPUT);

    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   int ldrValue = analogRead(ldrPin); 
   if( ldrValue <= 600){
    Serial.println(" Helmet Detected ");
   }
   else{
      Serial.println(" Helmet Not Detected ");
   }
   
   Serial.println(ldrValue);
   delay(1000);
}
