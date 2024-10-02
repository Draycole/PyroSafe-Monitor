#include <SoftwareSerial.h>

#define flame 2
#define buzzer 9
#define stableLED 5
#define fireLED 6

SoftwareSerial BTSerial(10, 11); //arduinoRX, arduino TX

bool fireDetected = false;  // To track if the fire was previously detected

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

  pinMode(flame, INPUT);
  pinMode(stableLED, OUTPUT);
  pinMode(fireLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  Serial.println("PyroSafe Monitoring System Active");
  BTSerial.println("PyroSafe Monitoring System Active");
  digitalWrite(stableLED, HIGH);
}

void loop() {
  int fire = digitalRead(flame);

  if (fire == LOW && !fireDetected) {  // Fire just detected
    fireDetected = true;  // Update state

    Serial.println("");
    BTSerial.println("");
    // Print fire message once
    Serial.println("Fire! Fire!");
    BTSerial.println("Fire! Fire!");

    // Beeping and LED flashing (continuous while fire is present)
    digitalWrite(stableLED, LOW);   // Peace LED off
  }

  if (fireDetected) {  // If fire was detected, keep beeping and flashing
          // Send 1KHz sound
    digitalWrite(fireLED, HIGH);  // Turn fire LED on
    Serial.println("Fire! Fire!");
    BTSerial.println("Fire! Fire!");
    tone(buzzer, 1000); 
    delay(100);              // Wait 100 ms

    noTone(buzzer);          // Turn buzzer off
    digitalWrite(fireLED, LOW);  // Turn fire LED off
    //Serial.println("Fire! Fire!");
   // BTSerial.println("Fire! Fire!");
    delay(100);              // Pause 100 ms before next beep
  }

  if (fire == HIGH && fireDetected) {  // Fire gone, state change
    fireDetected = false;  // Update state

    for(int i=0; i<25; i++)
    {
      Serial.print("-");
      BTSerial.print("- ");
      delay(100);
    }
    Serial.println("-");
    BTSerial.println("-");
    //Serial.println("-----------------------------------");
    //BTSerial.println("------------------------------------");
    // Print peace message once
    Serial.println("Environment is Stable");
    //Serial.println(analogRead(A0));
    BTSerial.println("Environment is Stable");

    digitalWrite(stableLED, HIGH);  // Peace LED on
    digitalWrite(fireLED, LOW);    // Fire LED off
    noTone(buzzer);                // Ensure buzzer is off
  }

  delay(200);  // Short delay for responsiveness
}
