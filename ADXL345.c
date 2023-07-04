#define BAUD_RATE    0X2C
#define POWER_CTL    0x2D
#define DATA_FORMAT  0X31
#define DATAX        0X32

unsigned int8 adxl345_address;  //0x53
//!unsigned int8 device_id=0x00;
unsigned char x_data_low, x_data_high, y_data_low, y_data_high, z_data_low, z_data_high;
signed int16 x_axis, y_axis, z_axis;

void i2c_adx345_setup(unsigned int8 adxl345_add)
{
   adxl345_address=adxl345_add;
   i2c_start();
   i2c_write(adxl345_address<<1);
   i2c_write(BAUD_RATE);
   i2c_write(0X0B);
   i2c_write(POWER_CTL);
   i2c_write(0X08);
   i2c_write(DATA_FORMAT);
   i2c_write(0X00);
   i2c_stop();
}

void i2c_adx345_read_value()
{
   i2c_start();
   i2c_write(adxl345_address<<1);
//!   i2c_write(POWER_CTL);
//!   i2c_write(0X08);
   i2c_write(DATAX);
   
   i2c_start();  
   i2c_write((adxl345_address<<1)|0x01);
   x_data_low=i2c_read(); 
   x_data_high=i2c_read();
   
   y_data_low=i2c_read();
   y_data_high=i2c_read();
   
   z_data_low=i2c_read();
   z_data_high=i2c_read(0); //not ack
   i2c_stop();
   
   x_axis=make16(x_data_high,x_data_low);
   y_axis=make16(y_data_high,y_data_low);
   z_axis=make16(z_data_high,z_data_low);
}
