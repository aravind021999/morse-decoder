#include <Bounce2.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);
char dot = '.';
char dash = '-';
int diff1, diff2, increment1, increment2;
int pos_time = 50;
String morse_string;
String sentance;
#define BUTTON_PIN 2
#define BUTTON_PIN1 3
int temp = 0;
int end_time1 = 5000, end_time2 = 5000;
int start_time1 = 0, start_time2 = 0;
int pos = 0, check1 = 0, check2 = 0;
int j=1;
static String letters[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
                           ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"};

int prepos = 0; int p = 0;
Bounce debouncer1 = Bounce(); // Instantiate a Bounce object
Bounce debouncer2 = Bounce();
void setup()
{

  debouncer1.attach(BUTTON_PIN, INPUT_PULLUP);
  debouncer2.attach(BUTTON_PIN1, INPUT_PULLUP);
  debouncer1.interval(5); //
  debouncer2.interval(5);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
 display.clearDisplay();
  display.display();
  // display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(27,0);
  display.print("Decoading morse code..");
  display.display();
  Serial.begin(115200);

}
void displaystring(char x)
{
  morse_string += x;
  Serial.println(morse_string);
}
void morse(String x)
{

  Serial.println(x);
  for (int i = 0; i < 25; ++i)
  {
    if (letters[i] == x)
    {
      decoder(i);
      break;

    }

  }
}
void decoder(int z)
{
  String s[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
  sentance += s[z];
   display.clearDisplay();
  display.display();
  // display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(27,0);
  display.print(sentance);
  display.display();
  Serial.println(sentance);

}
void append()
{ check1 = millis() - pos_time;
  if (check1 >= 2.5*end_time1 && check1 <=3.5*end_time1 || check1>=(2.5/3)*end_time2 && check1<=end_time2 )
  {
    morse(morse_string);
    Serial.println(morse_string);
    morse_string = "";
    Serial.println(check1);
  }
  if (check1 >= 4.5* end_time1 && 5<=end_time1|| check1 >= (4.5/12)*end_time2 && check1<= (5/12)*end_time2)
  {if(j==1){
  sentance += " ";
  Serial.println(sentance);
  Serial.println(check1);
  j=0;}
  
  }
  
}


void loop() {

  //////////////////
  //ENCODER_UPDATE//
  /////////////////

  //---------------------------------------------------------------------------

  debouncer1.update(); // Update the Bounce instance
  debouncer2.update();
  if ( debouncer1.fell() )
  {
    if (digitalRead(3) == HIGH)
    {
      ++pos;
    }
    else
    {
      --pos;
    }
  }
  if ( debouncer2.fell())
  {
    if (digitalRead(2) == LOW)
    {
      ++pos;
    }
    else
    {
      --pos;
    }
  }
  //------------------------------------------------------------------------------


  if (increment1 == 1)
  {
    start_time1 = millis();
  }

  if (increment2 == -1)
  {
    start_time2 = millis();
  }

  if (pos == prepos)
  { append();
  }

  if (prepos != pos)
  {check1=0;
  j=1;
    pos_time = millis();
    Serial.print("pos  :");
    Serial.println(pos);
    if (pos > prepos)
    {
      //Append dot
      diff1 = pos - prepos;
      increment2 = 0;
      increment1 = increment1 + diff1;
      Serial.print("increment1   :"); Serial.println(increment1);
      if (increment1 >= 40)
      {
        increment1 = 0;
        displaystring(dot);
        end_time1 = millis() - start_time1;                                //Time for dot
        Serial.print("Time Period dot :"); Serial.println(end_time1);
      }
    }
    if (pos < prepos)
    {
      //Append dash
      diff2 = pos - prepos;
      increment1 = 0;
      increment2 = increment2 + diff2;
      Serial.print("increment2   :"); Serial.println(increment2);
      if (increment2 <= -40)
      {
        increment2 = 0;
        displaystring(dash);
        end_time2 = millis() - start_time2;                               //Time for dash
        Serial.print("Time Period dash :"); Serial.println(end_time2);
      }

    }
    prepos = pos;
  }
}
