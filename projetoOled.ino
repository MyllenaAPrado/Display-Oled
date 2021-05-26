#include "oled.h"

void setup(){
  
  display_Oled display_Oled;
  display_Oled.init();
  display_Oled.write_caracter("TESTE");
  display_Oled.scroll_mode("HU");
  display_Oled.active_scroll();
  display_Oled.blink_display(5);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
