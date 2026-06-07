/*
==============================================
  마이크로프로세서 실습 코드 모음
==============================================
*/

/* =============================================
   실습문제 2-1
   기본 예제: LED 깜빡이기
============================================= */
/*
#include "mbed.h"
#define BLINK_DELAY 500ms
DigitalOut led0(PA_4);
DigitalOut led1(PA_5);
DigitalOut led2(PA_6);
DigitalOut led3(PA_7);

int main() {
    while (1) {
        led0=0;led1=0;led2=0;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=1;led1=1;led2=1;led3=1;
        ThisThread::sleep_for(BLINK_DELAY);
    }
}
*/

/* =============================================
   실습문제 2-1-1: 번갈아 키기
   ●○●○ -> ○●○●
============================================= */
/*
#include "mbed.h"
#define BLINK_DELAY 500ms
DigitalOut led0(PA_4);
DigitalOut led1(PA_5);
DigitalOut led2(PA_6);
DigitalOut led3(PA_7);

int main() {
    while (1) {
        led0=1;led1=0;led2=1;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=0;led1=1;led2=0;led3=1;
        ThisThread::sleep_for(BLINK_DELAY);
    }
}
*/

/* =============================================
   실습문제 2-1-2: 불빛 왕복
   ○○○○->●○○○->○●○○->○○●○->○○○●->○○●○->○●○○->●○○○->○○○○
============================================= */
/*
#include "mbed.h"
#define BLINK_DELAY 200ms
DigitalOut led0(PA_4);
DigitalOut led1(PA_5);
DigitalOut led2(PA_6);
DigitalOut led3(PA_7);

int main() {
    while (1) {
        led0=0;led1=0;led2=0;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=1;led1=0;led2=0;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=0;led1=1;led2=0;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=0;led1=0;led2=1;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=0;led1=0;led2=0;led3=1;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=0;led1=0;led2=1;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=0;led1=1;led2=0;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=1;led1=0;led2=0;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
    }
}
*/

/* =============================================
   실습문제 2-1-3: 2진 계수
   ○○○○->○○○●->○○●○->○○●●-> ... ->●●●●->○○○○
============================================= */
/*
#include "mbed.h"
#define BLINK_DELAY 300ms
BusOut leds(PA_4, PA_5, PA_6, PA_7);

int main() {
    while (1) {
        for(int i = 0; i <= 15; i++) {
            leds = i;
            ThisThread::sleep_for(BLINK_DELAY);
        }
    }
}
*/

/* =============================================
   코드2-3: PortOut 클래스를 이용한 병렬 I/O
   LED 순서대로 ON
============================================= */
/*
#include "mbed.h"
#define LED_MASK 0x000000f0
#define BLINK_DELAY 500ms
PortOut leds(PortA, LED_MASK);

int main() {
    while (1) {
        leds = 0;
        ThisThread::sleep_for(BLINK_DELAY);
        for(int i = 0; i <= 3; i++) {
            leds = 0b00010000 << i;
            ThisThread::sleep_for(BLINK_DELAY);
        }
    }
}
*/

/* =============================================
   실습문제 2-2-1: 2진 계수 (PortOut 방식)
   ○○○○->○○○●->○○●○->○○●●-> ... ->●●●●->○○○○
============================================= */
/*
#include "mbed.h"
#define LED_MASK 0x000000f0
#define BLINK_DELAY 300ms
PortOut leds(PortA, LED_MASK);

int main() {
    while (1) {
        for(int i = 0; i <= 15; i++) {
            leds = i << 4;
            ThisThread::sleep_for(BLINK_DELAY);
        }
    }
}
*/

/* =============================================
   실습문제 2-2-2: 불빛 왕복 (PortOut 방식)
   ○○○○->●○○○->○●○○->○○●○->○○○●->○○●○->○●○○->●○○○->○○○○
============================================= */
/*
#include "mbed.h"
#define LED_MASK 0x000000f0
#define BLINK_DELAY 200ms
PortOut leds(PortA, LED_MASK);

int main() {
    while (1) {
        leds = 0;
        ThisThread::sleep_for(BLINK_DELAY);
        for(int i = 0; i <= 3; i++) {
            leds = 0x10 << i;
            ThisThread::sleep_for(BLINK_DELAY);
        }
        for(int i = 2; i >= 0; i--) {
            leds = 0x10 << i;
            ThisThread::sleep_for(BLINK_DELAY);
        }
    }
}
*/

/* =============================================
   실습문제 2-2-3: 불빛 움직이기1
   ○○○○->●○○○->●●○○->●●●○->●●●●->●●●○->●●○○->●○○○->○○○○
============================================= */
/*
#include "mbed.h"
#define LED_MASK 0x000000f0
#define BLINK_DELAY 200ms
PortOut leds(PortA, LED_MASK);

int main() {
    while (1) {
        leds = 0;
        ThisThread::sleep_for(BLINK_DELAY);
        for(int i = 0; i <= 3; i++) {
            leds = ((1 << (i+1)) - 1) << 4;
            ThisThread::sleep_for(BLINK_DELAY);
        }
        for(int i = 2; i >= 0; i--) {
            leds = ((1 << (i+1)) - 1) << 4;
            ThisThread::sleep_for(BLINK_DELAY);
        }
    }
}
*/

/* =============================================
   실습문제 2-2-4: 불빛 움직이기2
   ○○○○->●○○○->●●○○->●●●○->●●●●->○●●●->○○●●->○○○●->○○○○
============================================= */
/*
#include "mbed.h"
#define LED_MASK 0x000000f0
#define BLINK_DELAY 200ms
PortOut leds(PortA, LED_MASK);

int main() {
    int pattern[] = {0x00, 0x10, 0x30, 0x70, 0xF0, 0xE0, 0xC0, 0x80, 0x00};
    while (1) {
        for(int i = 0; i <= 8; i++) {
            leds = pattern[i];
            ThisThread::sleep_for(BLINK_DELAY);
        }
    }
}
*/

/* =============================================
   실습문제 3-1 1번
============================================= */
/*
#include "mbed.h"

BusOut leds(A2, D13, D12, D11);
DigitalIn btn1(PC_0, PullDown);

int main() {
    int count = 0;
    leds = 0;

    while (1) {
        if (btn1 == 1) {
            ThisThread::sleep_for(20ms);
            if (btn1 == 1) {
                count = (count + 1) % 16;
                leds = count;
                while(btn1 == 1);
            }
        }
    }
}
*/

/* =============================================
   실습문제 3-1 2번
============================================= */
/*
#include "mbed.h"

BusOut leds(A2, D13, D12, D11);
DigitalIn btn_up(PC_0, PullDown);
DigitalIn btn_down(PC_1, PullDown);

int main() {
    int count = 0;
    leds = 0;

    while (1) {
        if (btn_up == 1) {
            ThisThread::sleep_for(20ms);
            if (btn_up == 1) {
                count = (count + 1) % 16;
                leds = count;
                while(btn_up == 1);
            }
        }
        if (btn_down == 1) {
            ThisThread::sleep_for(20ms);
            if (btn_down == 1) {
                count = (count == 0) ? 15 : count - 1;
                leds = count;
                while(btn_down == 1);
            }
        }
    }
}
*/

/* =============================================
   실습문제 3-1 3번
============================================= */
/*
#include "mbed.h"

BusOut leds(A2, D13, D12, D11);
DigitalIn btn_right(PC_0, PullDown);
DigitalIn btn_left(PC_1, PullDown);

int main() {
    int pos = 1;
    leds = pos;

    while (1) {
        if (btn_right == 1) {
            pos = (pos >= 8) ? 1 : pos << 1;
            leds = pos;
            ThisThread::sleep_for(200ms);
        }
        else if (btn_left == 1) {
            pos = (pos <= 1) ? 8 : pos >> 1;
            leds = pos;
            ThisThread::sleep_for(200ms);
        }
        ThisThread::sleep_for(10ms);
    }
}
*/

/* =============================================
   실습문제 4-1 1번
============================================= */
/*
#include "mbed.h"

AnalogIn mypot(PA_0);
BusOut leds(PA_4, PA_5, PA_6, PA_7);

int main() {
    int last_step = -1;

    while(1) {
        unsigned int sum = 0;
        for(int i = 0; i < 20; i++) {
            sum += mypot.read_u16();
        }
        unsigned short avg_val = sum / 20;

        int current_step = avg_val / 3500;
        if(current_step > 15) current_step = 15;

        if (current_step != last_step) {
            leds = current_step;
            last_step = current_step;
        }

        ThisThread::sleep_for(100ms);
    }
}
*/

/* =============================================
   실습문제 4-1 2번
============================================= */
/*
#include "mbed.h"

AnalogIn pot(PA_0);

int main() {
    printf("--- 4-1 (2) Voltage Comparison Start ---\r\n");

    while(1) {
        float raw_ratio = pot.read();
        float calc_v = raw_ratio * 3.3f;
        float direct_v = pot.read_voltage();

        if (direct_v < 0.01f && raw_ratio > 0.01f) {
            direct_v = calc_v;
        }

        int v1_i = (int)calc_v;
        int v1_f = (int)((calc_v - v1_i) * 1000.0f);
        int v2_i = (int)direct_v;
        int v2_f = (int)((direct_v - v2_i) * 1000.0f);

        printf("(1) Computed: %d.%03d V | (2) Direct: %d.%03d V\r\n", v1_i, v1_f, v2_i, v2_f);
        thread_sleep_for(500);
    }
}
*/

/* =============================================
   실습문제 5-1 1번
============================================= */
/*
#include "mbed.h"

AnalogIn temp_in(PA_0);
DigitalOut leds[] = {PA_4, PA_5, PA_6, PA_7};

int main() {
    printf("Problem 1: LED On/Off by Temperature\r\n");

    while(1) {
        float temp_c = temp_in.read() * 330.0f;
        printf("Current Temp: %.2f C\r\n", temp_c);

        if (temp_c >= 20.0f) {
            for(int i=0; i<4; i++) leds[i] = 1;
        } else {
            for(int i=0; i<4; i++) leds[i] = 0;
        }
        thread_sleep_for(500);
    }
}
*/

/* =============================================
   실습문제 5-1 2번
============================================= */
/*
#include "mbed.h"

AnalogIn temp_in(PA_0);
DigitalOut led1(PA_4);
DigitalOut led2(PA_5);
DigitalOut led3(PA_6);
DigitalOut led4(PA_7);

int main() {
    while(1) {
        float temp_c = temp_in.read() * 330.0f;
        printf("Current Temp: %.2f C\r\n", temp_c);

        if (temp_c >= 20.0f) {
            led1 = 1; led2 = 1; led3 = 1; led4 = 1;
            thread_sleep_for(500);
            led1 = 0; led2 = 0; led3 = 0; led4 = 0;
            thread_sleep_for(500);
        } else {
            led1 = 0; led2 = 0; led3 = 0; led4 = 0;
        }
    }
}
*/

/* =============================================
   실습문제 5-1 3번
============================================= */
/*
#include "mbed.h"

AnalogIn temp_in(PA_0);
DigitalOut led1(PA_4);
DigitalOut led2(PA_5);
DigitalOut led3(PA_6);
DigitalOut led4(PA_7);

int main() {
    printf("--- Temperature LED Control Start ---\r\n");

    while(1) {
        float temp_c = temp_in.read() * 330.0f;
        printf("Current Temp: %.2f C\r\n", temp_c);

        if (temp_c < 36.0f) {
            led1 = 0; led2 = 0; led3 = 0; led4 = 0;
        } else if (temp_c < 37.0f) {
            led1 = 1; led2 = 0; led3 = 0; led4 = 0;
        } else if (temp_c < 38.0f) {
            led1 = 1; led2 = 1; led3 = 0; led4 = 0;
        } else if (temp_c < 39.0f) {
            led1 = 1; led2 = 1; led3 = 1; led4 = 0;
        } else {
            led1 = 1; led2 = 1; led3 = 1; led4 = 1;
        }
        thread_sleep_for(200);
    }
}
*/

/* =============================================
   실습문제 5-2 1번
============================================= */
/*
#include "mbed.h"

AnalogIn cds_in(PA_0);
DigitalOut led1(PA_4);
DigitalOut led2(PA_5);
DigitalOut led3(PA_6);
DigitalOut led4(PA_7);

int main() {
    printf("--- Photoresistor Lab 1: All ON/OFF ---\r\n");

    while(1) {
        float val = cds_in.read();
        printf("Current Light: %.3f\r\n", val);

        if (val < 0.150f) {
            led1 = 1; led2 = 1; led3 = 1; led4 = 1;
        } else {
            led1 = 0; led2 = 0; led3 = 0; led4 = 0;
        }
        thread_sleep_for(100);
    }
}
*/

/* =============================================
   실습문제 5-2 2번
============================================= */
/*
#include "mbed.h"

AnalogIn cds_in(PA_0);
DigitalOut L1(PA_4);
DigitalOut L2(PA_5);
DigitalOut L3(PA_6);
DigitalOut L4(PA_7);

int main() {
    printf("--- Photoresistor Final Test ---\r\n");

    while(1) {
        float val = cds_in.read();
        printf("Value: %.3f\r\n", val);

        if (val < 0.090f) {
            L1 = 1; L2 = 1; L3 = 1; L4 = 1;
        } else if (val < 0.140f) {
            L1 = 1; L2 = 1; L3 = 1; L4 = 0;
        } else if (val < 0.190f) {
            L1 = 1; L2 = 1; L3 = 0; L4 = 0;
        } else if (val < 0.230f) {
            L1 = 1; L2 = 0; L3 = 0; L4 = 0;
        } else {
            L1 = 0; L2 = 0; L3 = 0; L4 = 0;
        }
        wait_us(100000);
    }
}
*/

/* =============================================
   실습문제 5-3 1번
============================================= */
/*
#include "mbed.h"

DigitalOut trigger(PC_7);
DigitalIn  echo(PB_6);
Timer timer;
DigitalOut L1(PA_4);
DigitalOut L2(PA_5);
DigitalOut L3(PA_6);
DigitalOut L4(PA_7);

int main() {
    float distance = 0.0;
    printf("--- Practice 5-3: Problem 1 Start ---\r\n");

    while(1) {
        trigger = 1;
        timer.reset();
        wait_us(10);
        trigger = 0;

        while(echo == 0) {};
        timer.start();
        while(echo == 1) {};
        timer.stop();

        auto round_trip_time = timer.elapsed_time().count();
        distance = round_trip_time * 0.0173;
        printf("Distance = %.2f cm\r\n", distance);

        if (distance > 0.1f && distance <= 5.0f) {
            L1 = 1; L2 = 1; L3 = 1; L4 = 1;
            ThisThread::sleep_for(200ms);
            L1 = 0; L2 = 0; L3 = 0; L4 = 0;
            ThisThread::sleep_for(200ms);
        } else {
            L1 = 0; L2 = 0; L3 = 0; L4 = 0;
            ThisThread::sleep_for(500ms);
        }
    }
}
*/

/* =============================================
   실습문제 5-3 2번
============================================= */
/*
#include "mbed.h"

DigitalOut trigger(PC_7);
DigitalIn  echo(PB_6);
Timer timer;
DigitalOut L1(PA_4);
DigitalOut L2(PA_5);
DigitalOut L3(PA_6);
DigitalOut L4(PA_7);

int main() {
    float distance = 0.0;
    printf("--- Practice 5-3: Problem 2 Start ---\r\n");

    while(1) {
        trigger = 1;
        timer.reset();
        wait_us(10);
        trigger = 0;

        while(echo == 0) {};
        timer.start();
        while(echo == 1) {};
        timer.stop();

        auto round_trip_time = timer.elapsed_time().count();
        distance = round_trip_time * 0.0173;
        printf("Distance = %.1f cm\r\n", distance);

        if (distance > 0.0f && distance <= 5.0f) {
            L1=1; L2=1; L3=1; L4=1;
        } else if (distance <= 10.0f) {
            L1=1; L2=1; L3=1; L4=0;
        } else if (distance <= 15.0f) {
            L1=1; L2=1; L3=0; L4=0;
        } else if (distance <= 20.0f) {
            L1=1; L2=0; L3=0; L4=0;
        } else {
            L1=0; L2=0; L3=0; L4=0;
        }
        ThisThread::sleep_for(200ms);
    }
}
*/

/* =============================================
   실습문제 5-4 1번
============================================= */
/*
#include "mbed.h"

DigitalIn alarm(D7, PullDown);
BusOut blue_leds(D13, A2);
BusOut green_leds(D11, D12);

int main() {
    ThisThread::sleep_for(2000ms);

    while(1) {
        green_leds = 0x3;
        blue_leds = 0;

        if (alarm.read() == 1) {
            ThisThread::sleep_for(50ms);
            if (alarm.read() == 1) {
                green_leds = 0;
                for(int i = 0; i < 5; i++) {
                    blue_leds = 0x3;
                    ThisThread::sleep_for(300ms);
                    blue_leds = 0;
                    ThisThread::sleep_for(300ms);
                }
                while(alarm.read() == 1) {
                    ThisThread::sleep_for(50ms);
                }
                ThisThread::sleep_for(500ms);
            }
        }
    }
}
*/

/* =============================================
   실습문제 6-1 1번
============================================= */
/*
#include "mbed.h"

#define DS3231_ADDR (0x68)
#define REG_SEC     (0x00)
#define REG_MIN     (0x01)
#define REG_HOUR    (0x02)
#define REG_WEEK    (0x03)
#define REG_DAY     (0x04)
#define REG_MONTH   (0x05)
#define REG_YEAR    (0x06)

I2C i2c(I2C_SDA, I2C_SCL);

void write_data(uint8_t addr, uint8_t reg, uint8_t data);
uint8_t read_data(uint8_t addr, uint8_t reg);
uint8_t bcd_to_decimal(uint8_t bcd);
uint8_t decimal_to_bcd(uint8_t decimal);

int main() {
    char week[8][4] = {"nul", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    char month_name[13][4] = {"nul", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    uint8_t addr = DS3231_ADDR << 1;
    unsigned char times[7];

    write_data(addr, REG_SEC,   decimal_to_bcd(0));
    write_data(addr, REG_MIN,   decimal_to_bcd(30));
    write_data(addr, REG_HOUR,  decimal_to_bcd(22));
    write_data(addr, REG_WEEK,  decimal_to_bcd(3));
    write_data(addr, REG_DAY,   decimal_to_bcd(18));
    write_data(addr, REG_MONTH, decimal_to_bcd(5));
    write_data(addr, REG_YEAR,  decimal_to_bcd(21));

    printf("RTC Start!\n");

    while(1) {
        ThisThread::sleep_for(1000ms);

        times[0] = bcd_to_decimal(read_data(addr, REG_SEC));
        times[1] = bcd_to_decimal(read_data(addr, REG_MIN));
        times[2] = bcd_to_decimal(read_data(addr, REG_HOUR));
        times[3] = bcd_to_decimal(read_data(addr, REG_WEEK));
        times[4] = bcd_to_decimal(read_data(addr, REG_DAY));
        times[5] = bcd_to_decimal(read_data(addr, REG_MONTH));
        times[6] = bcd_to_decimal(read_data(addr, REG_YEAR));

        int h24 = times[2];
        int h12 = h24;
        const char* ampm = "AM";

        if (h24 >= 12) {
            ampm = "PM";
            if (h24 > 12) h12 = h24 - 12;
        } else if (h24 == 0) {
            h12 = 12;
        }

        printf("현재시간 : %02d:%02d %s %s, %s %d, 20%02d\n",
                h12, times[1], ampm, week[times[3]], month_name[times[5]], times[4], times[6]);
    }
}

void write_data(uint8_t addr, uint8_t reg, uint8_t data) {
    char byte[2] = {reg, data};
    i2c.write(addr, byte, 2);
}

uint8_t read_data(uint8_t addr, uint8_t reg) {
    char cmd[1] = {reg};
    char data[1];
    i2c.write(addr, cmd, 1, 1);
    i2c.read(addr, data, 1);
    return data[0];
}

uint8_t bcd_to_decimal(uint8_t bcd) { return (bcd >> 4) * 10 + (bcd & 0x0F); }
uint8_t decimal_to_bcd(uint8_t decimal) { return ((decimal / 10) << 4) | (decimal % 10); }
*/

/* =============================================
   실습문제 6-2 1번
============================================= */
/*
#include "mbed.h"

#define DS3231_ADDR (0x68 << 1)
#define REG_TEMP_MSB 0x11
#define REG_TEMP_LSB 0x12

I2C i2c(I2C_SDA, I2C_SCL);

uint8_t read_data(uint8_t reg) {
    char data[1];
    char cmd[1];
    cmd[0] = reg;
    i2c.write(DS3231_ADDR, cmd, 1, 1);
    i2c.read(DS3231_ADDR, data, 1, 0);
    return data[0];
}

int main() {
    printf("--- DS3231 Temperature Sensor Test ---\n");

    while(1) {
        int8_t temp_msb = read_data(REG_TEMP_MSB);
        uint8_t temp_lsb = read_data(REG_TEMP_LSB);

        float fraction = (temp_lsb >> 6) * 0.25f;
        float current_temp = (float)temp_msb + fraction;

        printf("현재 온도 : %.2f C\n", current_temp);
        ThisThread::sleep_for(1000ms);
    }
}
*/

/* =============================================
   실습문제 7-1 OLED 제어 테스트
============================================= */
/*
#include "mbed.h"
#include "Adafruit_SSD1306.h"

I2C i2c(D14, D15);
Adafruit_SSD1306_I2c oled(i2c, NC, 0x78, 64, 128);

void oled_write_string(const char *str);

int main() {
    i2c.frequency(50000);
    oled.begin();

    oled.clearDisplay();
    ThisThread::sleep_for(10ms);

    oled.setTextSize(1);
    oled.setTextCursor(0, 0);
    oled_write_string("Hello, World!");

    oled.setTextSize(2);
    oled.setTextCursor(0, 15);
    oled_write_string("SSD1306");
    oled.display();

    ThisThread::sleep_for(5000ms);

    oled.clearDisplay();
    ThisThread::sleep_for(10ms);
    oled.display();
    ThisThread::sleep_for(2000ms);

    oled.setTextSize(2);
    oled.setTextCursor(0, 15);
    oled_write_string("10:25 AM");
    oled.display();

    while(1) { }
}

void oled_write_string(const char *str) {
    for(int i = 0; str[i]; i++) {
        oled.writeChar(str[i]);
    }
}
*/

/* =============================================
   실습문제 7-1 실습
============================================= */
/*
#include "mbed.h"
#include "Adafruit_SSD1306.h"
#include <cstdio>

I2C i2c(D14, D15);
Adafruit_SSD1306_I2c oled(i2c, NC, 0x78, 64, 128);

void oled_write_string(const char *str);

int main() {
    i2c.frequency(50000);
    oled.begin();

    char buff[20];
    int i2c_address = 0x78;
    sprintf(buff, "Addr: %X", i2c_address);

    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextCursor(0, 0);
    oled_write_string(buff);
    oled.display();

    while(1) { }
}

void oled_write_string(const char *str) {
    for(int i = 0; str[i]; i++) {
        oled.writeChar(str[i]);
    }
}
*/

/* =============================================
   실습문제 7-2 (DS3231 + SSD1306 디지털 시계)
============================================= */
/*
#include "mbed.h"
#include "Adafruit_SSD1306.h"

I2C i2c(D14, D15);
Adafruit_SSD1306_I2c oled(i2c, NC, 0x78, 64, 128);

#define DS3231_ADDR 0xD0

int bcd2dec(int bcd) {
    return (bcd >> 4) * 10 + (bcd & 0x0F);
}

void write_string(const char* str) {
    while(*str) oled.writeChar(*str++);
}

int main() {
    oled.begin();
    i2c.frequency(100000);

    char timeBuff[30] = {0};
    char tempBuff[30] = {0};

    while(1) {
        char cmd = 0x00;
        char data[7] = {0};
        i2c.write(DS3231_ADDR, &cmd, 1, true);
        i2c.read(DS3231_ADDR, data, 7);

        int min  = bcd2dec(data[1]);
        int hour = bcd2dec(data[2] & 0x3F);

        char tempCmd = 0x11;
        char tempData[2] = {0, 0};
        i2c.write(DS3231_ADDR, &tempCmd, 1, true);
        i2c.read(DS3231_ADDR, tempData, 2);
        float temp = (int8_t)tempData[0] + ((tempData[1] >> 6) * 0.25f);
        sprintf(tempBuff, "Temp: %dC", (int)temp);

        const char* ampm = (hour >= 12) ? "PM" : "AM";
        int h12 = hour % 12;
        if(h12 == 0) h12 = 12;

        sprintf(timeBuff, "%02d:%02d %s", h12, min, ampm);

        oled.clearDisplay();

        oled.setTextSize(1);
        oled.setTextCursor(10, 0);
        write_string("Mon, 20 May 2021");

        oled.setTextSize(2);
        oled.setTextCursor(5, 14);
        write_string(timeBuff);

        oled.setTextSize(1);
        oled.setTextCursor(10, 45);
        write_string(tempBuff);

        oled.display();
        ThisThread::sleep_for(1000ms);
    }
}
*/

/* =============================================
   실습문제 8-1 1번
============================================= */
/*
#include "mbed.h"

PwmOut myLed(A0);
AnalogIn cds(A1);

int main() {
    myLed.period(0.01f);

    while(1) {
        float val = cds.read();
        float brightness = 1.0f - val;

        if (val < 0.2f) {
            brightness = 0.0f;
        }

        myLed.write(brightness);
        printf("CDS: %.2f | LED: %.2f\n", val, brightness);
        ThisThread::sleep_for(100ms);
    }
}
*/

/* =============================================
   실습문제 8-2
============================================= */
/*
#include "mbed.h"

Timer t;
DigitalOut trig(D9);
DigitalIn echo(D10);
PwmOut buzzer(D3);

int main() {
    float duration, distance;

    while(1) {
        trig = 0;
        wait_us(2);
        trig = 1;
        wait_us(10);
        trig = 0;

        while(!echo);
        t.start();
        while(echo);
        t.stop();

        duration = t.read_us();
        distance = duration * 0.0343f / 2.0f;
        t.reset();

        printf("Distance: %.2f cm\n", distance);

        if (distance > 0 && distance < 10.0f) {
            buzzer.period_us(1000);
            buzzer.write(0.5f);
        } else {
            buzzer.write(0.0f);
        }
        ThisThread::sleep_for(100ms);
    }
}
*/

/* =============================================
   실습문제 8-2 사이렌 소리
============================================= */
/*
#include "mbed.h"

Timer t;
Timer sirenTimer;
DigitalOut trig(D9);
DigitalIn echo(D10);
PwmOut buzzer(D3);

int main() {
    float duration, distance;

    while(1) {
        trig = 0;
        wait_us(2);
        trig = 1;
        wait_us(10);
        trig = 0;

        while(!echo);
        t.start();
        while(echo);
        t.stop();

        duration = t.read_us();
        distance = duration * 0.0343f / 2.0f;
        t.reset();

        if (distance > 0 && distance < 10.0f) {
            sirenTimer.reset();
            sirenTimer.start();

            while (sirenTimer.read() < 5.0f) {
                for (int freq = 500; freq < 1500; freq += 10) {
                    buzzer.period(1.0f / (float)freq);
                    buzzer.write(0.5f);
                    wait_us(1000);
                }
                for (int freq = 1500; freq > 500; freq -= 10) {
                    buzzer.period(1.0f / (float)freq);
                    buzzer.write(0.5f);
                    wait_us(1000);
                }
            }
            sirenTimer.stop();
            buzzer.write(0.0f);
            ThisThread::sleep_for(2000ms);
        } else {
            buzzer.write(0.0f);
        }
        ThisThread::sleep_for(100ms);
    }
}
*/

/* =============================================
   실습문제 10-2: 인터럽트 연습 2
============================================= */
/*
#include "mbed.h"

InterruptIn button(BUTTON1);
DigitalOut led1(LED1);
DigitalOut led2(PA_4);

void toggle() {
    led2 = !led2;
}

int main() {
    button.rise(&toggle);
    while (1) {
        led1 = !led1;
        ThisThread::sleep_for(500ms);
    }
}
*/

/* =============================================
   실습문제 10-1-2
============================================= */
/*
#include "mbed.h"

InterruptIn button(BUTTON1);
DigitalOut buzzer(D3);
int my_counter = 10;
bool running = true;

void toggle_countdown() {
    running = !running;
}

int main() {
    button.rise(&toggle_countdown);
    printf("Counter: %d\n", my_counter);

    while (1) {
        ThisThread::sleep_for(1s);

        if (running && my_counter > 0) {
            my_counter--;
            printf("Counter: %d\n", my_counter);

            if (my_counter == 0) {
                printf("Boom!\n");
                for (int i = 0; i < 200; i++) {
                    buzzer = 1;
                    ThisThread::sleep_for(1ms);
                    buzzer = 0;
                    ThisThread::sleep_for(1ms);
                }
            }
        }
    }
}
*/

/* =============================================
   실습문제 10-3
============================================= */
/*
#include "mbed.h"

InterruptIn button(BUTTON1);
DigitalOut led1(LED1);
DigitalOut led_external(PA_4);
Ticker flipper;

void toggle_external() {
    led_external = !led_external;
}

void flip_internal() {
    led1 = !led1;
}

int main() {
    button.rise(&toggle_external);
    flipper.attach(&flip_internal, 0.5);

    while (1) {
        ThisThread::sleep_for(1s);
    }
}
*/

/* =============================================
   실습문제 10-4-2
============================================= */
/*
#include "mbed.h"

InterruptIn button(BUTTON1);
DigitalOut buzzer(D3);
bool buzzer_on = false;
Timer debounce_timer;

void toggle_buzzer() {
    if (chrono::duration_cast<chrono::milliseconds>(debounce_timer.elapsed_time()).count() > 200 ||
        chrono::duration_cast<chrono::milliseconds>(debounce_timer.elapsed_time()).count() == 0) {
        buzzer_on = !buzzer_on;
        debounce_timer.reset();
    }
}

int main() {
    debounce_timer.start();
    button.rise(&toggle_buzzer);

    while (1) {
        if (buzzer_on) {
            buzzer = 1;
            ThisThread::sleep_for(1ms);
            buzzer = 0;
            ThisThread::sleep_for(1ms);
        } else {
            buzzer = 0;
            ThisThread::sleep_for(50ms);
        }
    }
}
*/

/* =============================================
   실습문제 11-1
============================================= */
/*
#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(PA_4);
DigitalOut led3(PA_7);
InterruptIn button(BUTTON1);

Thread thread_led2;
Thread thread_led3;

void led2_blink() {
    while (1) {
        led2 = !led2;
        ThisThread::sleep_for(200ms);
    }
}

void led3_blink() {
    while (1) {
        led3 = !led3;
        ThisThread::sleep_for(500ms);
    }
}

void toggle() {
    led1 = !led1;
}

int main() {
    button.rise(toggle);
    thread_led2.start(led2_blink);
    thread_led3.start(led3_blink);

    ThisThread::sleep_for(10s);
    thread_led3.terminate();

    while (1) { }
}
*/

/* =============================================
   실습문제 11-2
============================================= */
/*
#include "mbed.h"

DigitalOut buzzer(PB_0);
DigitalOut led(PA_4);
AnalogIn cds(A0);
DigitalOut trig(D9);
DigitalIn  echo(D10);

Thread thread_ultrasonic;
Thread thread_cds;
Timer pulse_timer;

void ultrasonic_task() {
    while (1) {
        trig = 0;
        wait_us(2);
        trig = 1;
        wait_us(10);
        trig = 0;

        while (echo == 0);
        pulse_timer.start();
        while (echo == 1);
        pulse_timer.stop();

        float duration = pulse_timer.elapsed_time().count();
        float distance = duration * 0.0343f / 2.0f;
        pulse_timer.reset();

        if (distance > 0 && distance <= 10.0f) {
            int loop_count = 5000000 / 500;
            for (int i = 0; i < loop_count; i++) {
                buzzer = 1;
                wait_us(250);
                buzzer = 0;
                wait_us(250);
            }
        }
        ThisThread::sleep_for(100ms);
    }
}

void cds_task() {
    while (1) {
        float cds_val = cds.read();
        led = (cds_val < 0.3f) ? 1 : 0;
        ThisThread::sleep_for(100ms);
    }
}

int main() {
    thread_ultrasonic.start(ultrasonic_task);
    thread_cds.start(cds_task);

    while (1) {
        ThisThread::sleep_for(1s);
    }
}
*/

/* =============================================
   기말과제: 비상경보시스템
============================================= */
#include "mbed.h"

DigitalIn pir(D4, PullDown);
AnalogIn cds(A0);
DigitalOut red_led(D5);
DigitalOut yellow_led(D6);
DigitalOut blue_led(D8);
PwmOut buzzer(D7);
DigitalOut trig(D11);
DigitalIn echo(D12);
InterruptIn user_btn(PC_13);

bool blue_state = false;

void btn_pressed() {
    blue_state = !blue_state;
    blue_led = blue_state;
}

float getDistance() {
    trig = 0;
    wait_us(2);
    trig = 1;
    wait_us(10);
    trig = 0;

    Timer t;
    while(echo == 0);
    t.start();
    while(echo == 1);
    t.stop();

    return t.elapsed_time().count() / 1000000.0f * 34300.0f / 2.0f;
}

// 1. 접근 경보 - 초음파
void thread_distance() {
    while(1) {
        float dist = getDistance();
        if(dist < 20.0f) {
            buzzer.period(1.0/2000.0);
            buzzer.write(0.5f);
            ThisThread::sleep_for(100ms);
            buzzer.write(0.0f);
            ThisThread::sleep_for(100ms);
        } else {
            buzzer.write(0.0f);
            ThisThread::sleep_for(200ms);
        }
    }
}

// 2. 움직임 경보 - PIR
void thread_pir() {
    ThisThread::sleep_for(2000ms);
    while(1) {
        int count = 0;
        for(int i = 0; i < 5; i++) {
            if(pir == 1) count++;
            ThisThread::sleep_for(10ms);
        }
        if(count >= 4) {
            red_led = 1;
            ThisThread::sleep_for(500ms);
            red_led = 0;
        } else {
            red_led = 0;
        }
    }
}

// 3. 조명제어1 - 조도센서
void thread_cds() {
    while(1) {
        float val = cds.read();
        yellow_led = (val < 0.2f) ? 1 : 0;
        ThisThread::sleep_for(100ms);
    }
}

Thread t1, t2, t3;

int main() {
    user_btn.fall(&btn_pressed);

    t1.start(thread_distance);
    t2.start(thread_pir);
    t3.start(thread_cds);

    while(1) {
        ThisThread::sleep_for(1000ms);
    }
}
