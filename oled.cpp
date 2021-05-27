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
   *  clear - set cursor to clear the display
  */
  const uint8_t cursor_begin[6] = {0x21, 0x30, 0x7F, 0x22, 0x00, 0x01};
  const uint8_t cursor_middle[6] = {0x21, 0x30, 0x7F, 0x22, 0x02, 0x04};
  const uint8_t cursor_end[6] = {0x21, 0x30, 0x7F, 0x22, 0x05, 0x07};
  const uint8_t cursor_clear[6] = {0x21, 0x00, 0x7F, 0x22, 0x00, 0x07};
  
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
  if(position_cursor == "clear"){
    for(int i=0; i < 6; i++){
      write_command(cursor_clear[i]);
    }
  }
}

void display_Oled::clear_display(){
  set_cursor("clear");
  for(int i=0; i < (192); i++){
    for(int i=0; i < 6; i++){
      write_data(caracters[0][i]);
    }    
  }
  set_cursor("clear");
  for(int i=0; i < (192); i++){
    for(int i=0; i < 6; i++){
      write_data(caracters[10][i]);
    }    
  }
  set_cursor("clear");
  for(int i=0; i < (192); i++){
    for(int i=0; i < 6; i++){
      write_data(caracters[0][i]);
    }    
  }
}

void display_Oled::write_phrase(String phrase, String cursor_position){
  
  set_cursor(cursor_position);
  
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
  write_command(ZERO_HEX);
  //scroll_setup();
  write_command(DEACTIVE_SCROLL);
}

void display_Oled::scroll_setup(){
  const uint8_t scroll_hor_left[5] = {SCROLL_HOR_LEFT, 0xB0, 0xC7, 0xD5, 0x2F};//example of scroll
  const uint8_t scroll_hor_right[5] = {SCROLL_HOR_RIGHT, 0xB0, 0xC7, 0xD5, 0x2F};//example of scroll
  const uint8_t scroll_vert_left[5] = {SCROLL_VERT_LEFT, 0xB0, 0xC7, 0xD5, 0x2F};//example of scroll
  const uint8_t scroll_vert_right[5] = {SCROLL_VERT_RIGHT, 0xB0, 0xC7, 0xD5, 0x2F};//example of scroll
  for(int i=0; i < 5; i++){
    write_command(scroll_hor_left[i]);
  }
  
  for(int i=0; i < 5; i++){
    write_command(scroll_hor_right[i]);
  }
  
  for(int i=0; i < 5; i++){
    write_command(scroll_vert_left[i]);
  }
  
  for(int i=0; i < 5; i++){
    write_command(scroll_vert_right[i]);
  }
  
}

void display_Oled::active_scroll(String mode){
  if(mode =="HR"){
    write_command(SCROLL_HOR_RIGHT);
  }
  if(mode =="HL"){
    write_command(SCROLL_HOR_LEFT);
  }
  if(mode =="VR"){
    write_command(SCROLL_VERT_RIGHT);
  }
  if(mode =="VL"){
    write_command(SCROLL_VERT_LEFT);
  }
  write_command(ZERO_HEX);
  write_command(ACTIVE_SCROLL);
  
}

void display_Oled::deactive_scroll(){
  write_command(ZERO_HEX);
  write_command(DEACTIVE_SCROLL);
}

void display_Oled::blink_display(int time_of_blink){

  for(int i =0; i< time_of_blink; i++){
    write_command(OLED_DISPLAY_OFF);
    delay(300);
    write_command(OLED_DISPLAY_ON);
    delay(500);
  }
 
}
