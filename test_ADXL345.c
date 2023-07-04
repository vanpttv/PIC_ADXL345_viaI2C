#include <16f887.h> 
#fuses hs, put, noprotect
#use delay(clock=20MHz)
#USE   I2C(MASTER,SLOW,SDA=PIN_C4,SCL=PIN_C3) 
//#define adxl345_address 0x53
#include "D:\HK1_2223\DATN\I2C_Interface\ADXL345\ADXL345.c"
#include <lcd.c> 

float ax, ay, az;


void main()
{
   lcd_init();
   i2c_adx345_setup(0x53);
   i2c_start();
   i2c_write(adxl345_address<<1);
   i2c_write(0x00);
//   i2c_write(0x2D);
//   i2c_write(8);
   i2c_start();
   i2c_write((adxl345_address<<1)|0x01);
   int id=i2c_read(0);
   i2c_stop();
   
   lcd_gotoxy(1,1);
   lcd_putc("hello");
   lcd_gotoxy(1,2);
   printf(lcd_putc,"id=%x",id);
   delay_ms(2000);
   
   while(true)
   {
      i2c_adx345_read_value();
      lcd_gotoxy(1,1);
      printf(lcd_putc,"%ld, %ld, %ld         ",x_axis, y_axis, z_axis);
//!      lcd_gotoxy(1,1);
//!      printf(lcd_putc,"%x %x, %ld    ",z_data_low, z_data_high, z_axis);
//!      lcd_gotoxy(1,2);
//!      printf(lcd_putc,"%x, %x, %ld, %ld  ",y_data_low,y_data_high,y_axis, z_axis);
      ax=x_axis*0.0039;
      ay=y_axis*0.0039;
      az=z_axis*0.0039;
      lcd_gotoxy(1,2);
      printf(lcd_putc,"%f, %f, %f         ",ax, ay, az);
      delay_ms(500);
   }
}



//==============================================================================
//!#include <16f887.h> 
//!#fuses hs, put, noprotect
//!#use delay(clock=20MHz)
//!//#define adxl345_address 0x53
//!#include <lcd.c> 
//!
//!
//!void main()
//!{
//!   lcd_init();
//!   lcd_gotoxy(1,1);
//!   lcd_putc("helloooo");
//!   
//!   while(true)
//!   {
//!      for (unsigned int8 i=0;i<200;i++)
//!      {
//!         lcd_gotoxy(1,2);
//!         printf(lcd_putc,"x=%03d",i);
//!         delay_ms(2000);
//!      }
//!   }
//!}

