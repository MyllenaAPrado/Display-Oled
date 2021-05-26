#include "oled.h"
#include "Arduino.h"


//write comand i2C
void display_Oled::write_command(uint8_t command)
{
  Wire.beginTransmission(DISPLAY_ADDRESS);
  Wire.write(OLED_MODE_WRITE_COMMAND);
  Wire.write(command);
  Wire.endTransmission();  
}

//write data i2C
void display_Oled::write_data (uint8_t data)
{
  Wire.beginTransmission(DISPLAY_ADDRESS);
  Wire.write(OLED_MODE_WRITE_DATA);
  Wire.write(data);
  Wire.endTransmission(); 
}

void display_Oled::set_cursor(String position_cursor){
  /* 
   *  Set cursos for three diferente position:
   *  begin - begin od display
   *  middle - middle of display
   *  end - end of display
  */
  const uint8_t cursor_middle[6] = {0x21, 0x24, 0x7F, 0x22, 0x0A, 0x3F};
  const uint8_t cursor_begin[6] = {0x21, 0x00, 0x7F, 0x22, 0x00, 0x3F};
  const uint8_t cursor_end[6] = {0x21, 0x7F, 0x7F, 0x22, 0x3F, 0x3F};

  
  if(position_cursor == "middle"){
    for(int i=0; i < 6; i++){
      write_command(cursor_middle[i]);
    }  
  }
  if(position_cursor == "begin"){
    for(int i=0; i < 6; i++){
      write_command(cursor_begin[i]);
    }  
  }
  if(position_cursor == "end"){
    for(int i=0; i < 6; i++){
      write_command(cursor_end[i]);
    }
  }
}

void display_Oled::write_caracter(String phrase){
  
  //pass string to array of char
  int str_len = phrase.length() + 1;
  char char_array[str_len];
  phrase.toCharArray(char_array, str_len);

  //print each carachter on display
  for (int i=0; i < (str_len- 1); i++) {
    int idx = char_array[i] - 32;
    for(int i=0; i < 6; i++){
      write_data(caracters[idx][i]);
    }
  }
}

void display_Oled::init(){
  Wire.begin();
  write_command(OLED_DISPLAY_ON); //turn on display
  set_cursor("middle");
}

//ainda implementar
void display_Oled::clear_display(){
  set_cursor("begin");
}

void display_Oled::scroll_mode(String mode){
  /*
   * Set the parameters of scroll
   * HU - horizontal to up side
   * HD - horizontal to down side
   * VL - vertical to left
   * VR - vertical to right
  */
  const uint8_t scroll_hor_up[5] = {0x2A, 0xB0, 0xC1, 0xD5, 0x2F};//example of scroll
  const uint8_t scroll_hor_down[5] = {0x2A, 0xB0, 0xC1, 0xD5, 0x2F};//example of scroll
  const uint8_t scroll_vert_left[5] = {0x2A, 0xB0, 0xC1, 0xD5, 0x2F};//example of scroll
  const uint8_t scroll_vert_right[5] = {0x2A, 0xB0, 0xC1, 0xD5, 0x2F};//example of scroll

  if(mode == "HU"){
    for(int i=0; i < 5; i++){
      write_command(scroll_hor_up[i]);
    }
  }
  if(mode == "HD"){
    for(int i=0; i < 5; i++){
      write_command(scroll_hor_down[i]);
    }
  }
  if(mode == "VL"){
    for(int i=0; i < 5; i++){
      write_command(scroll_vert_left[i]);
    }
  }

  if(mode == "VR"){
    for(int i=0; i < 5; i++){
      write_command(scroll_vert_right[i]);
    }
  }
}


void display_Oled::active_scroll(){
  write_command(ACTIVE_SCROLL);
}

void display_Oled::deactive_scroll(){
  write_command(DEACTIVE_SCROLL);
}

void display_Oled::blink_display(int time_of_blink){

  for(int i =0; i< time_of_blink; i++){
    write_command(OLED_DISPLAY_OFF);
    delay(500);
    write_command(OLED_DISPLAY_ON);
    delay(500);
  }
 
}
