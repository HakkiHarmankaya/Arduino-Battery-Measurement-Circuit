# 🔋 Arduino #17: Pil Ölçer Yapımı (16x2 LCD ile)

Bu projede, **Arduino**, **potansiyometre** ve **16x2 LCD ekran** kullanarak bir **basit pil doluluk göstergesi** tasarlanır.  
Analog giriş üzerinden ölçülen voltaj değeri, yüzdelik doluluk olarak LCD'de görüntülenir.

🔗 [Web Siteme Bakmak İçin Tıkla](https://www.hakkiharmankaya.com/)  
🔗 [Tinkercad Tasarımına Göz At](https://www.tinkercad.com/things/1zQtFUpj9eT?sharecode=P0Q11Q-oSi0VTK9RhqRiAr-6FmRMuXYTRtqDSnsE3BI)

---

## 🧰 Gerekli Malzemeler

- 1 adet **Arduino**
- 1 adet **potansiyometre**
- 1 adet **10kΩ direnç**
- 1 adet **16x2 LCD ekran**
- **Jumper kabloları**
- **Breadboard**

---

## ⚙️ Adım Adım Devre Kurulumu

### 🔹 LCD Ekran Bağlantıları

| LCD Pin | Arduino Pin     |
|---------|-----------------|
| 1 (GND) | GND             |
| 2 (VCC) | 5V              |
| 3 (VO)  | Potansiyometre orta bacak |
| 4 (RS)  | D12             |
| 5 (RW)  | GND             |
| 6 (EN)  | D11             |
| 11 (D4) | D5              |
| 12 (D5) | D4              |
| 13 (D6) | D3              |
| 14 (D7) | D2              |
| 15 (LED+) | 5V           |
| 16 (LED-) | GND           |

**Potansiyometre Bağlantısı**:

- Sol bacak → **5V**
- Sağ bacak → **GND**
- Orta bacak → **LCD VO (3. pin)**

**Pil Bağlantısı**:

- **Artı uç** → **A0**
- **Eksi uç** → **GND**

---

## 🔹 Arduino Kodunu Yazın ve Yükleyin

```cpp
#include <LiquidCrystal.h>

int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define pil A0
int gerilim = 0;
int min = 246; // Minimum voltaja karşılık gelen ADC değeri (1.2V)
float yuzde = 0;
float deger = 0;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.clear();
}

void loop() {
  gerilim = analogRead(pil);

  if (gerilim >= 338) gerilim = 338; // 1.65V üzeri yok say
  if (gerilim <= 246) gerilim = 246; // 1.2V altı yok say

  yuzde = gerilim - min;
  deger = (100.00 / 92.00) * yuzde; // 92 = 338 - 246

  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("Doluluk: % ");
  lcd.print(deger);

  Serial.println(deger);
}
