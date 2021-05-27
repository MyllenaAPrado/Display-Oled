#include "oled.h"

void setup(){
  loop();

}

void loop() {
  display_Oled display_Oled;
  display_Oled.init();
  display_Oled.clear_display();
  display_Oled.write_phrase("VIVA", "begin");
  display_Oled.write_phrase("LA", "middle");
  display_Oled.write_phrase("VIDA", "end");
  delay(5000);
  display_Oled.blink_display(2);
  display_Oled.clear_display();
  display_Oled.write_phrase("* = *", "middle");
  display_Oled.write_phrase("  ?  ", "begin");
  display_Oled.write_phrase("(   )", "end");
  delay(5000);
  display_Oled.blink_display(5);
  display_Oled.clear_display();
}
