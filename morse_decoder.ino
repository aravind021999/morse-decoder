
  static String letters[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
                             ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
int i =0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
 String code = ".-"; 
 morse(code);
}  
void morse(String x)
{
  
  Serial.println(x);
  for(i = 0;i<25;++i)
  {
    if(letters[i]==x)
    {
      decoder(i);
      break;
    }
    
  }
}
void decoder(int z)
{
  String s[] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
  Serial.println(s[z]);
}
