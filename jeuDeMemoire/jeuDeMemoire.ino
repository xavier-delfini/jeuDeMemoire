#include <LiquidCrystal.h>
int displaytime=400;
LiquidCrystal lcd(13,12, 4,18, 2,3 );
int color_array[32];
int input_sequence[32];
int turn=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(A3,INPUT);//Bouton3
  pinMode(5,INPUT);//Bouton4
  pinMode(6,INPUT);//Bouton2
  pinMode(7,INPUT);//Bouton1
  pinMode(8,OUTPUT);//Led1
  pinMode(9,OUTPUT);//Led2
  pinMode(10,OUTPUT);//Led3
  pinMode(11,OUTPUT);//Led4
  pinMode(19,OUTPUT);//Buzzer
  randomSeed(analogRead(A0));
  lcd.begin(16, 2);
}
void pick_random(){
  color_array[turn]=random(8,12);
}
void play_sequence(){
  int i=0;
  
    while (i<turn){
      digitalWrite(color_array[i],HIGH);
      delay(displaytime);
      digitalWrite(color_array[i],LOW);
      delay(500);      
      i++;
    }   
}
void get_sequence(){
  int i=0;
  while (turn>i){
    int j=0;
    while (true){
      
    
      if (digitalRead(7)==1){
        j=8;
        break;
      }
      else if(digitalRead(6)==1){
        j=9;
        break;
      }
      else if(digitalRead(5)==1){
        j=11;
        break;
      }
      else if(digitalRead(A3)==1){
        j=10;
        break;      
      }
    
    }
    digitalWrite(j,HIGH);
      delay(displaytime);
      digitalWrite(j,LOW);
      delay(200);
    input_sequence[i]=j;
    i++;
}
}
bool verify_sequence(){
  int i=0;
while(i<turn){
  if (color_array[i]!=input_sequence[i]){
    return 1;
  }
  i++;
}
return 0;  
  }

void display_system(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Niveau ");
    lcd.print(turn);
    lcd.setCursor(0, 1);
    lcd.print("Score: ");
    lcd.print(turn-1);
}
void Menu(){
  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print("Appuyez sur ");
  lcd.setCursor(0, 1); 
  lcd.print("un bouton pour");
  delay(250);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("un bouton pour");
  lcd.setCursor(0,1);
  lcd.print("change de niveau");
  delay(250);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("change de niveau");
  lcd.setCursor(0,1);
  lcd.print("de difficulte");
  delay(250);
    if (digitalRead(7)==1){//Easy
      displaytime=3000;
    }
    else if(digitalRead(6)==1){//Medium
      displaytime=500;
    }
    else if(digitalRead(5)==1){//Impossible
      displaytime=25;
    }
    else if(digitalRead(A3)==1){//Hard
      displaytime=300;      
    }
    if (displaytime!=400){
      Main();
      displaytime=400;
    }
}
void Main(){
    turn=0;
    while(true){//Boucle de jeu
      display_system();
      pick_random();
      play_sequence();
      get_sequence();
      if (verify_sequence()==1){
        digitalWrite(19,HIGH);
        delay(500);
        digitalWrite(19,LOW); 
        break;
      }
        
        turn++;
        }
}
void loop() {

  Menu();
}
