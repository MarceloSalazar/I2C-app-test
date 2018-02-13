#include "mbed.h"


DigitalOut led1(LED1, 0);

#if 1
#if 1
#include "LM75B.h"
LM75B temperature100(MBED_CONF_APP_I2C_SDA, MBED_CONF_APP_I2C_SCL, LM75B::ADDRESS_0, 100000);
LM75B temperature250(MBED_CONF_APP_I2C_SDA, MBED_CONF_APP_I2C_SCL, LM75B::ADDRESS_0, 250000);
LM75B temperature400(MBED_CONF_APP_I2C_SDA, MBED_CONF_APP_I2C_SCL, LM75B::ADDRESS_0, 400000);
#endif

#if 1
#include "I2CEeprom.h"
I2CEeprom memory(MBED_CONF_APP_I2C_SDA, MBED_CONF_APP_I2C_SCL, MBED_CONF_APP_I2C_EEPROM_ADDR, 32, 0);
#endif
#endif


int main(void)
{
    printf("hello world\r\n");

    float temp;
    char buffer[10];

    I2C i2c(MBED_CONF_APP_I2C_SDA, MBED_CONF_APP_I2C_SCL);
    I2C m_I2C(MBED_CONF_APP_I2C_SDA, MBED_CONF_APP_I2C_SCL);

    int retval = -1;


    for (;;)
    {
#if 1 // 0
        temp = temperature100.temp();
        printf("temp1: %f\r\n", temp);

        temp = temperature250.temp();
        printf("temp2: %f\r\n", temp);

        temp = temperature400.temp();
        printf("temp3: %f\r\n", temp);
#endif
        char reg = 0x00;
        char buff[2];

        int one = m_I2C.write(0x90, &reg, 1, true);
        int two = m_I2C.read(0x90, buff, 2);

        if ((one != 0) || (two != 0))
        {
            printf("error\r\n");
            break;
        }

#if 1 // 0
        i2c.start();
        i2c.write(0x90);
        i2c.write(0x00);
        i2c.start();
        i2c.write(0x91);
        int byte1 = i2c.read(0);
        int byte2 = i2c.read(1);

        printf("retval: %02X %02X\r\n", byte1, byte2);
#endif

#if 1 // 0
        int address = 0;
        char read = '0';

        memory.write(address, 'A');
        memory.read(address, buffer, 1);

        printf("data: %c\r\n", buffer[0]);
#endif

        led1 = !led1;
    }
}


