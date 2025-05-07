// library for LDR sensor and LCD screen
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// pin declaration

int livingRoomIntensity=9;
int bedroomIntensity=9;

const int livingRoom=11;
const int bedroom=10;
const int garage=9;
const int yard=8;

const int roomRed=7;
const int roomGreen=6;
const int roomBlue=5;

int roomFlag=0; 
int livingRoomFlag=0;
int bedroomFlag=0;

const int trigPin = 3;
const int echoPin = 2;

long duration;
int distance;

const int ldr_pin = A0;

// Initialization for helper variables
int colorPin=roomRed;
int color=1;

int all=1;
int sensorDistance=-1;
int sensorLight=-1;

// Initialization for LCD screen
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  // Start serial communication for observing values on a serial monitor
  Serial.begin(9600);
  // Setting the pins in the appropriate read/write mode
  pinMode(livingRoom, OUTPUT); 
  pinMode(bedroom, OUTPUT);
  pinMode(garage, OUTPUT);
  pinMode(yard, OUTPUT);
  pinMode(roomRed, OUTPUT);
  pinMode(roomGreen, OUTPUT);
  pinMode(roomBlue, OUTPUT);
  pinMode(ldr_pin,INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Start setup for LCD screen
  lcd.init();        
  lcd.backlight();    
 }

void loop() {
  // Reading data received from bluetooth
 if(Serial.available()>0){
       char data = Serial.read(); 

       // Logic for distance sensor
        if(sensorDistance==1){
              digitalWrite(trigPin, LOW);
              delayMicroseconds(2);
              digitalWrite(trigPin, HIGH);
              delayMicroseconds(10);
              digitalWrite(trigPin, LOW);
              duration = pulseIn(echoPin, HIGH);
              distance= duration*0.034/2;           // calculation for distance
              Serial.print("Distance: "); 
              Serial.println(distance);
              if(distance <= 17){
                digitalWrite(garage, HIGH);
              }
              else{
                digitalWrite(garage, LOW);
              }
           }

      // Logic for LDR sensor
          if(sensorLight==1){
              Serial.println("sensorLight");
              Serial.write(sensorLight);
              if(digitalRead(ldr_pin)==1)
              digitalWrite(yard,HIGH);
              else digitalWrite(yard,LOW);
          }
           
       // Logic for data received from bluetooth   
      switch(data)
      {
        // Living room
        case 'b': analogWrite(livingRoom, 28*livingRoomIntensity);   //9 levels of intensity from android application 28=254/9
                  livingRoomFlag=1;
                  Serial.println(28*livingRoomIntensity);
                  lcd.clear();
                  lcd.setCursor (0, 0);                     // Set the cursor to 1st line
                  lcd.print("livingRoom ON");               // print the message
                  lcd.setCursor (5, 1);                     // Set the cursor to 2nd line
                  lcd.print(28*livingRoomIntensity);        // print the message
                  break; 
        case 'a': digitalWrite(livingRoom, LOW);
                  livingRoomFlag=0;
                  lcd.clear();
                  lcd.setCursor (0, 0);
                  lcd.print("livingRoom OFF");
                  break;

        // Bedroom
        case 'd': analogWrite(bedroom,28*bedroomIntensity);     //9 levels of intensity from android application 28=254/9
                  Serial.println(28*bedroomIntensity);
                  bedroomFlag=1;
                  lcd.clear();
                  lcd.setCursor (0, 0);
                  lcd.print("Bedroom ON");
                  lcd.setCursor (5, 1);
                  lcd.print(28*bedroomIntensity);
                  break;
        case 'c': digitalWrite(bedroom,LOW);
                  bedroomFlag=0;
                  lcd.clear();
                  lcd.setCursor (0, 0);
                  lcd.print("Bedroom OFF");
                  break;

        // Garage
        case 'f': digitalWrite(garage,HIGH);
                  lcd.clear();
                  lcd.setCursor (0, 0);
                  lcd.print("Garage ON");
                  break;
        case 'e': digitalWrite(garage,LOW);
                  lcd.clear();
                  lcd.setCursor (0, 0);
                  lcd.print("Garage OFF");
                  break;

        // Yard
        case 'h': digitalWrite(yard,HIGH);
                  lcd.clear();
                  lcd.setCursor (0, 0);
                  lcd.print("Yard ON");
                  break;
        case 'g': digitalWrite(yard,LOW);
                  lcd.clear();
                  lcd.setCursor (0, 0);
                  lcd.print("Yard OFF");
                  break;

        // Children's room
        case 'p': digitalWrite(colorPin,HIGH);
                  roomFlag=1;
                  if(colorPin == 5){
                    lcd.clear();
                    lcd.setCursor (0, 0);
                    lcd.print("Children's room ON");
                    lcd.setCursor (5, 1);
                    lcd.print("Blue");
                  }
                  if(colorPin == 6){
                    lcd.clear();
                    lcd.setCursor (0, 0);
                    lcd.print("Children's room ON");
                    lcd.setCursor (5, 1);
                    lcd.print("Green");
                  }
                  if(colorPin == 7){
                    lcd.clear();
                    lcd.setCursor (0, 0);
                    lcd.print("Children's room ON");
                    lcd.setCursor (5, 1);
                    lcd.print("Red");
                  }
                  break;
        case 'o': 
                digitalWrite(roomRed,LOW);
                digitalWrite(roomGreen,LOW);
                digitalWrite(roomBlue,LOW);
                roomFlag=0;
                lcd.clear();
                lcd.setCursor (0, 0);
                lcd.print("Children's room OFF");
                break;  
        
        // Intensity for light in living room
        case 'k':
                delay(50);
                livingRoomIntensity=(int)Serial.read()-48;
//                Serial.println(livingRoomIntensity);
                if(livingRoomFlag==1){
                  analogWrite(livingRoom, 28*livingRoomIntensity);
                  lcd.setCursor (5, 1);
                  lcd.print(28*livingRoomIntensity);
                }
                break;
                
        // Intensity in bedroom
        case 'l':                      
                bedroomIntensity=Serial.read()-48;          //intensity range 1-9  ASCII 49=1
                if(bedroomFlag==1){
                  analogWrite(bedroom,28*bedroomIntensity);
                  lcd.setCursor (5, 1);
                  lcd.print(28*bedroomIntensity);
                }
                break;

                
        //Light color
        case 'q':                       
                color=(int)Serial.read()-48;
                Serial.println("colorPin"); 
        
                if(color==1)
                colorPin=roomRed;
                else if(color==2)
                colorPin=roomGreen;
                else colorPin=roomBlue;
                if(roomFlag==1){
                  digitalWrite(roomRed,LOW);
                  digitalWrite(roomGreen,LOW);
                  digitalWrite(roomBlue,LOW);
                  digitalWrite(colorPin,HIGH);
                  if(colorPin == 5){
                    lcd.clear();
                    lcd.setCursor (0, 0);
                    lcd.print("Children's room ON");
                    lcd.setCursor (5, 1);
                    lcd.print("Blue");
                  }
                  if(colorPin == 6){
                    lcd.clear();
                    lcd.setCursor (0, 0);
                    lcd.print("Children's room ON");
                    lcd.setCursor (5, 1);
                    lcd.print("Green");
                  }
                  if(colorPin == 7){
                    lcd.clear();
                    lcd.setCursor (0, 0);
                    lcd.print("Children's room ON");
                    lcd.setCursor (5, 1);
                    lcd.print("Red");
                  }
                }
                break;

        // Logic for sensors
        case 'm':                         
                sensorDistance*=-1;
                Serial.println(sensorDistance); 
                break;

        case 'n':                         
                if(sensorLight == 1){
                  digitalWrite(yard, LOW);
                }
                sensorLight*=-1; 
                if(sensorLight==1){
                  Serial.println("sensorLight");
                  Serial.write(sensorLight);
                  if(digitalRead(ldr_pin)==1)
                  digitalWrite(yard,HIGH);
                  else digitalWrite(yard,LOW);
               } 
                break;

        // On/Off all
        case 'i':         
                if(all==1){
                digitalWrite(livingRoom, HIGH);
                digitalWrite(bedroom,HIGH);
                digitalWrite(garage,HIGH);
                digitalWrite(yard,HIGH);
                digitalWrite(colorPin,HIGH);
                roomFlag=1;
                livingRoomFlag=1;
                bedroomFlag=1;
                all*=-1;
                Serial.println("All ON");
                lcd.clear();
                lcd.setCursor (0, 0);
                lcd.print("All ON");
                break;
                }
                else {
                digitalWrite(livingRoom, LOW);
                digitalWrite(bedroom,LOW);
                digitalWrite(garage,LOW);
                digitalWrite(yard,LOW);
                digitalWrite(roomRed,LOW);
                digitalWrite(roomGreen,LOW);
                digitalWrite(roomBlue,LOW);
                roomFlag=0;
                livingRoomFlag=0;
                bedroomFlag=0;
                
                Serial.println("All OFF");
                lcd.clear();
                lcd.setCursor (0, 0);
                lcd.print("All OFF");
                all*=-1;
                break;
                }


        // Alarm 
        case 'j': 
                Serial.println("Alarm!!!");
                for(int x = 0; x < 7; x++){
                   blinker();
                }
                lcd.setCursor (0, 0);  
                lcd.print("ALARM OFF");
                break;
                
        default:
        break;
      }
      
      //Serial.println(data);
      }
   delay(50);
}

// Alarm function
void blinker(){
  digitalWrite(livingRoom, HIGH);
  digitalWrite(bedroom,HIGH);
  digitalWrite(garage,HIGH);
  digitalWrite(yard,HIGH);

  lcd.clear();
  lcd.setCursor (0, 0);
  lcd.print("!!!!!!ALARM!!!!!");

  delay(600);
  digitalWrite(livingRoom, LOW);
  digitalWrite(bedroom,LOW);
  digitalWrite(garage,LOW);
  digitalWrite(yard,LOW);
  lcd.clear();
  delay(600);
}
