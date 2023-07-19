#include <LiquidCrystal.h>
#define RED_PIN 9
#define GREEN_PIN 6
#define BLUE_PIN 10
const int trigPin = 13;    // Trig pin of the ultrasonic sensor connected to Arduino digital pin 2
const int echoPin = 7;    // Echo pin of the ultrasonic sensor connected to Arduino digital pin 3
int state = 0;
int buzzerPin = 8;  // The digital pin connected to the buzzer

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // Create the LCD object, specifying the corresponding pins.

void setup() {
  Serial.begin(115200); // Setting the baud rate for my serial monitor
  pinMode(RED_PIN, OUTPUT); //Sets the corresponding Arduino pins as output pins
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  lcd.begin(16, 2);  // Initialize the LCD module with its dimensions (16 columns and 2 rows).

  pinMode(trigPin, OUTPUT); //Initializes the trigger pin as output, and the echo pin as input
  pinMode(echoPin, INPUT);

  analogWrite(RED_PIN, 255);
  analogWrite(GREEN_PIN, 255);
  analogWrite(BLUE_PIN, 255);

  pinMode(buzzerPin, OUTPUT);

  lcd.print("Wave to Turn On");
  delay(500);
}

void loop() {

  // Generate a tone of 1000Hz for 1 second

  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the duration of the echo pulse
  long duration = pulseIn(echoPin, HIGH);

   // Calculate the distance based on the speed of sound
  float distance = duration * 0.034 / 2;  // Divide by 2 as the sound travels to the object and back
  //At this point we know roughly how close an object is to the sensor. 
  // From the desk to the roof, is approximately 160 cm. 

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  if ( distance <= 15.0 && state == 0 ){ //If something goes infront of the sensor at a close range, of specified threshold, execute this block.
      // Set the LED strip to red

      state = 1; 

      analogWrite(RED_PIN, 255);
      analogWrite(GREEN_PIN, 0); // A value of 0 is High (Brightest), and 255 is Low (Dimmest/Off). You can pick any value within this range.
      analogWrite(BLUE_PIN, 255);

      lcd.clear();
      lcd.setCursor(0, 0); // set cursor for the first column, and first row
      lcd.print("    System ON"); //begin printing on the first line
      lcd.setCursor(0, 1); // set cursor for the first column, and second row
      lcd.print("     Green!!!"); // begin printing on the second row

  }

    else if (distance <= 15.0 && state == 1){

    state = 2; // we use a binary toggle to switch between the two states.

    // In this second, state we want to turn off the lights, and display that the system is turned off.
     analogWrite(RED_PIN, 0);
     analogWrite(GREEN_PIN, 255);
     analogWrite(BLUE_PIN, 255);

    lcd.clear();
    lcd.setCursor(0, 0); // set cursor for the first column, and first row
    lcd.print("    System ON"); //begin printing on the first line
    lcd.setCursor(0, 1);
    lcd.print("     Red!!!"); // begin printing on the second row
  }

  else if (distance <= 15.0 && state == 2){

    state = 3; // we use a binary toggle to switch between the two states.

    // In this second, state we want to turn off the lights, and display that the system is turned off.
     analogWrite(RED_PIN, 255);
     analogWrite(GREEN_PIN, 255);
     analogWrite(BLUE_PIN, 0);

    lcd.clear();
    lcd.setCursor(0, 0); // set cursor for the first column, and first row
    lcd.print("    System ON"); //begin printing on the first line
    lcd.setCursor(0, 1);
    lcd.print("     Blue!!!"); // begin printing on the second row

  }

  else if (distance <= 15.0 && state == 3){

    state = 0; // we use a binary toggle to switch between the two states.

    // In this second, state we want to turn off the lights, and display that the system is turned off.
     analogWrite(RED_PIN, 255);
     analogWrite(GREEN_PIN, 255);
     analogWrite(BLUE_PIN, 255);

    lcd.clear();
    lcd.setCursor(0, 0); // set cursor for the first column, and first row
    lcd.print("   System OFF"); //begin printing on the first line
    lcd.setCursor(0, 1); // set cursor for the first column, and first row
    lcd.print("Wave to Turn On");
  }

  delay(500); // Delay for 3 second
}
