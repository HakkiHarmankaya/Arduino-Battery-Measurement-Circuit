#include <LiquidCrystal.h>
int rs=12, en=11, d4=5, d5=4, d6=3, d7=2;//LCD ekran pinleri tanımı.
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define pil A0
//338 max - 1.65 V
//246 min - 1.2 V
int gerilim = 0;
int min = 246;
float yuzde = 0;
float deger = 0;
void setup()
{
  lcd.begin(16,2); //Ekran boyutu tanımı.
  Serial.begin(9600);
  lcd.clear();
}

void loop() 
{
  gerilim = analogRead(pil);
  if(gerilim >= 338)
  gerilim = 338;

  if(gerilim <= 246)
  gerilim = 246;

  yuzde = gerilim - min;
  deger = (100.00/92.00) * yuzde;
  delay(500);
  lcd.setCursor(0,1);
  lcd.print("Doluluk: % ");
  lcd.print(deger);
  Serial.println(deger);
}
