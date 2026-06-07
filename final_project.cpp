/*
==============================================
  마이크로프로세서 실습 코드 모음
  - 실습 2-1 ~ 11-2 + 기말과제
==============================================
*/

/* =============================================
   실습문제 2-1 기본 예제: LED 깜빡이기
   - 4개 LED 동시에 0.5초 간격으로 ON/OFF 반복
============================================= */
/*
#include "mbed.h"
#define BLINK_DELAY 500ms          // 깜빡임 간격 500ms 상수 정의

// LED 4개 핀 선언
DigitalOut led0(PA_4);
DigitalOut led1(PA_5);
DigitalOut led2(PA_6);
DigitalOut led3(PA_7);

int main() {
    while (1) {
        led0=0;led1=0;led2=0;led3=0;   // 모든 LED 끄기
        ThisThread::sleep_for(BLINK_DELAY);
        led0=1;led1=1;led2=1;led3=1;   // 모든 LED 켜기
        ThisThread::sleep_for(BLINK_DELAY);
    }
}
*/

/* =============================================
   실습문제 2-1-1: 번갈아 키기
   ●○●○ -> ○●○● 패턴 반복
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
        // 홀수 번째 LED(0,2) ON / 짝수 번째 LED(1,3) OFF
        led0=1;led1=0;led2=1;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        // 홀수 번째 LED(0,2) OFF / 짝수 번째 LED(1,3) ON
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
        // 모두 끄기
        led0=0;led1=0;led2=0;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        // 왼쪽에서 오른쪽으로 이동
        led0=1;led1=0;led2=0;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=0;led1=1;led2=0;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=0;led1=0;led2=1;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=0;led1=0;led2=0;led3=1;
        ThisThread::sleep_for(BLINK_DELAY);
        // 오른쪽에서 왼쪽으로 복귀
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
   BusOut으로 0~15까지 2진수 표현
============================================= */
/*
#include "mbed.h"
#define BLINK_DELAY 300ms

// BusOut: 여러 핀을 하나의 버스로 묶어서 숫자로 제어
BusOut leds(PA_4, PA_5, PA_6, PA_7);  // LSB -> MSB 순서

int main() {
    while (1) {
        for(int i = 0; i <= 15; i++) {  // 0(0000)~15(1111) 순서로 출력
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
#define LED_MASK 0x000000f0    // PA_4~PA_7 핀 마스크 (비트4~7)
#define BLINK_DELAY 500ms

// PortOut: 포트 단위로 여러 핀을 동시 제어 (BusOut보다 빠름)
PortOut leds(PortA, LED_MASK);

int main() {
    while (1) {
        leds = 0;              // 모든 LED 끄기
        ThisThread::sleep_for(BLINK_DELAY);
        for(int i = 0; i <= 3; i++) {
            leds = 0b00010000 << i;  // 비트 시프트로 순서대로 켜기
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
            leds = i << 4;    // PA_4부터 시작하므로 4비트 왼쪽 시프트
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
        // 왼쪽 -> 오른쪽
        for(int i = 0; i <= 3; i++) {
            leds = 0x10 << i;
            ThisThread::sleep_for(BLINK_DELAY);
        }
        // 오른쪽 -> 왼쪽 복귀
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
   LED가 하나씩 쌓였다가 하나씩 줄어드는 패턴
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
        // 하나씩 추가 (0001 -> 0011 -> 0111 -> 1111)
        for(int i = 0; i <= 3; i++) {
            leds = ((1 << (i+1)) - 1) << 4;  // 비트 마스크로 누적 켜기
            ThisThread::sleep_for(BLINK_DELAY);
        }
        // 하나씩 감소 (0111 -> 0011 -> 0001)
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
   LED가 채워졌다가 왼쪽부터 꺼지는 패턴
============================================= */
/*
#include "mbed.h"
#define LED_MASK 0x000000f0
#define BLINK_DELAY 200ms

PortOut leds(PortA, LED_MASK);

int main() {
    // 각 단계의 LED 패턴을 배열로 미리 정의
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
   실습문제 3-1 1번: 버튼으로 2진 상향 계수
   버튼 누를 때마다 0~15 순서로 LED에 2진수 표시
============================================= */
/*
#include "mbed.h"

BusOut leds(A2, D13, D12, D11);        // LED 4개 (LSB->MSB)
DigitalIn btn1(PC_0, PullDown);         // 버튼1 (PullDown: 평소 LOW, 누르면 HIGH)

int main() {
    int count = 0;
    leds = 0;

    while (1) {
        if (btn1 == 1) {                // 버튼 눌림 감지
            ThisThread::sleep_for(20ms); // 디바운싱: 접점 떨림 20ms 무시
            if (btn1 == 1) {            // 디바운싱 후 다시 확인
                count = (count + 1) % 16; // 0~15 순환 카운트
                leds = count;
                while(btn1 == 1);       // 버튼 뗄 때까지 대기 (한 번만 인정)
            }
        }
    }
}
*/

/* =============================================
   실습문제 3-1 2번: 상향/하향 2진 계수
   버튼1: 증가 / 버튼2: 감소
============================================= */
/*
#include "mbed.h"

BusOut leds(A2, D13, D12, D11);
DigitalIn btn_up(PC_0, PullDown);       // 상향 버튼
DigitalIn btn_down(PC_1, PullDown);     // 하향 버튼

int main() {
    int count = 0;
    leds = 0;

    while (1) {
        // 상향 버튼 처리
        if (btn_up == 1) {
            ThisThread::sleep_for(20ms);
            if (btn_up == 1) {
                count = (count + 1) % 16;   // 15 다음은 0으로 순환
                leds = count;
                while(btn_up == 1);
            }
        }
        // 하향 버튼 처리
        if (btn_down == 1) {
            ThisThread::sleep_for(20ms);
            if (btn_down == 1) {
                count = (count == 0) ? 15 : count - 1;  // 0 이하면 15로 순환
                leds = count;
                while(btn_down == 1);
            }
        }
    }
}
*/

/* =============================================
   실습문제 3-1 3번: 버튼으로 LED 왕복 이동
   버튼1: 오른쪽 이동 / 버튼2: 왼쪽 이동
============================================= */
/*
#include "mbed.h"

BusOut leds(A2, D13, D12, D11);
DigitalIn btn_right(PC_0, PullDown);    // 오른쪽 이동 버튼
DigitalIn btn_left(PC_1, PullDown);     // 왼쪽 이동 버튼

int main() {
    int pos = 1;    // 초기 위치: 0001 (첫 번째 LED)
    leds = pos;

    while (1) {
        if (btn_right == 1) {
            // 끝(1000)에 도달하면 처음(0001)으로 순환
            pos = (pos >= 8) ? 1 : pos << 1;   // 왼쪽 시프트 = 오른쪽 이동
            leds = pos;
            ThisThread::sleep_for(200ms);       // 이동 속도 조절
        }
        else if (btn_left == 1) {
            // 처음(0001)에 도달하면 끝(1000)으로 순환
            pos = (pos <= 1) ? 8 : pos >> 1;   // 오른쪽 시프트 = 왼쪽 이동
            leds = pos;
            ThisThread::sleep_for(200ms);
        }
        ThisThread::sleep_for(10ms);            // 버튼 폴링 간격
    }
}
*/

/* =============================================
   실습문제 4-1 1번: 가변저항으로 LED 밝기 단계 제어
   가변저항 값에 따라 0~15단계로 LED 표시
============================================= */
/*
#include "mbed.h"

AnalogIn mypot(PA_0);                   // 가변저항 (0.0~1.0 값 반환)
BusOut leds(PA_4, PA_5, PA_6, PA_7);   // LED 4개

int main() {
    int last_step = -1;

    while(1) {
        // 노이즈 제거: 20번 읽어서 평균값 사용
        unsigned int sum = 0;
        for(int i = 0; i < 20; i++) {
            sum += mypot.read_u16();    // 16비트 원시값(0~65535) 읽기
        }
        unsigned short avg_val = sum / 20;

        // 0~65535 값을 0~15 단계로 변환
        int current_step = avg_val / 3500;
        if(current_step > 15) current_step = 15;   // 최대값 15로 제한

        // 값이 변경될 때만 LED 업데이트 (불필요한 갱신 방지)
        if (current_step != last_step) {
            leds = current_step;
            last_step = current_step;
        }
        ThisThread::sleep_for(100ms);
    }
}
*/

/* =============================================
   실습문제 4-1 2번: 가변저항 전압값 출력
   계산값과 함수값 비교하여 터미널에 출력
============================================= */
/*
#include "mbed.h"

AnalogIn pot(PA_0);

int main() {
    printf("--- 4-1 (2) Voltage Comparison Start ---\r\n");

    while(1) {
        float raw_ratio = pot.read();           // 0.0~1.0 비율값
        float calc_v = raw_ratio * 3.3f;        // 직접 계산한 전압 (비율 * 3.3V)
        float direct_v = pot.read_voltage();    // 라이브러리 함수로 읽은 전압

        // 함수값이 0이면 계산값으로 대체 (버그 보정)
        if (direct_v < 0.01f && raw_ratio > 0.01f) {
            direct_v = calc_v;
        }

        // float 출력 시 깨짐 방지: 정수부/소수부 분리 출력
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
   실습문제 5-1 1번: 온도센서로 LED ON/OFF
   20도 이상이면 LED 모두 켜기, 미만이면 끄기
============================================= */
/*
#include "mbed.h"

AnalogIn temp_in(PA_0);                 // 온도센서 (LM35: 10mV/°C)
DigitalOut leds[] = {PA_4, PA_5, PA_6, PA_7};

int main() {
    printf("Problem 1: LED On/Off by Temperature\r\n");

    while(1) {
        // LM35 공식: read() * 3.3V * 100(°C/V) = 온도(°C)
        float temp_c = temp_in.read() * 330.0f;
        printf("Current Temp: %.2f C\r\n", temp_c);

        if (temp_c >= 20.0f) {
            for(int i=0; i<4; i++) leds[i] = 1;    // 모두 켜기
        } else {
            for(int i=0; i<4; i++) leds[i] = 0;    // 모두 끄기
        }
        thread_sleep_for(500);
    }
}
*/

/* =============================================
   실습문제 5-1 2번: 온도센서로 LED 깜빡이기
   20도 이상이면 0.5초 간격으로 깜빡임
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
            // 20도 이상: 모두 켰다가 끄기 반복 (깜빡임)
            led1 = 1; led2 = 1; led3 = 1; led4 = 1;
            thread_sleep_for(500);
            led1 = 0; led2 = 0; led3 = 0; led4 = 0;
            thread_sleep_for(500);
        } else {
            led1 = 0; led2 = 0; led3 = 0; led4 = 0;   // 20도 미만: 모두 끄기
        }
    }
}
*/

/* =============================================
   실습문제 5-1 3번: 온도에 따른 LED 개수 조절
   온도 구간별로 켜지는 LED 개수 다르게 설정
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

        // 온도 구간별 LED 개수 제어
        if (temp_c < 36.0f) {
            led1 = 0; led2 = 0; led3 = 0; led4 = 0;   // 0개
        } else if (temp_c < 37.0f) {
            led1 = 1; led2 = 0; led3 = 0; led4 = 0;   // 1개
        } else if (temp_c < 38.0f) {
            led1 = 1; led2 = 1; led3 = 0; led4 = 0;   // 2개
        } else if (temp_c < 39.0f) {
            led1 = 1; led2 = 1; led3 = 1; led4 = 0;   // 3개
        } else {
            led1 = 1; led2 = 1; led3 = 1; led4 = 1;   // 4개 (39도 이상)
        }
        thread_sleep_for(200);
    }
}
*/

/* =============================================
   실습문제 5-2 1번: 조도센서로 LED ON/OFF
   어두우면 모두 켜고, 밝으면 모두 끄기
============================================= */
/*
#include "mbed.h"

AnalogIn cds_in(PA_0);                  // 조도센서 CDS (밝을수록 값 증가)
DigitalOut led1(PA_4);
DigitalOut led2(PA_5);
DigitalOut led3(PA_6);
DigitalOut led4(PA_7);

int main() {
    printf("--- Photoresistor Lab 1: All ON/OFF ---\r\n");

    while(1) {
        float val = cds_in.read();      // 0.0~1.0 (밝을수록 높은 값)
        printf("Current Light: %.3f\r\n", val);

        // 0.150 미만이면 어두운 것으로 판단 → LED 켜기
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
   실습문제 5-2 2번: 조도에 따른 LED 개수 조절
   어두울수록 켜지는 LED 개수 증가
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

        // 조도 구간별 LED 개수 제어 (값이 작을수록 어두움)
        if (val < 0.090f) {
            L1 = 1; L2 = 1; L3 = 1; L4 = 1;   // 매우 어두움: 4개
        } else if (val < 0.140f) {
            L1 = 1; L2 = 1; L3 = 1; L4 = 0;   // 어두움: 3개
        } else if (val < 0.190f) {
            L1 = 1; L2 = 1; L3 = 0; L4 = 0;   // 보통: 2개
        } else if (val < 0.230f) {
            L1 = 1; L2 = 0; L3 = 0; L4 = 0;   // 밝음: 1개
        } else {
            L1 = 0; L2 = 0; L3 = 0; L4 = 0;   // 매우 밝음: 0개
        }
        wait_us(100000);    // 0.1초 대기
    }
}
*/

/* =============================================
   실습문제 5-3 1번: 초음파 센서로 거리 측정
   5cm 이내 접근 시 LED 4개 깜빡임
============================================= */
/*
#include "mbed.h"

DigitalOut trigger(PC_7);   // 초음파 발사 핀 (Trig)
DigitalIn  echo(PB_6);      // 반사파 수신 핀 (Echo)
Timer timer;                // 시간 측정용 타이머
DigitalOut L1(PA_4);
DigitalOut L2(PA_5);
DigitalOut L3(PA_6);
DigitalOut L4(PA_7);

int main() {
    float distance = 0.0;
    printf("--- Practice 5-3: Problem 1 Start ---\r\n");

    while(1) {
        // 1. 초음파 발사: 10us 펄스 생성
        trigger = 1;
        timer.reset();
        wait_us(10);
        trigger = 0;

        // 2. Echo 신호로 왕복 시간 측정
        while(echo == 0) {};    // Echo HIGH 대기
        timer.start();
        while(echo == 1) {};    // Echo LOW 대기
        timer.stop();

        // 3. 거리 계산: 시간(us) * 0.0173 = 거리(cm)
        auto round_trip_time = timer.elapsed_time().count();
        distance = round_trip_time * 0.0173;
        printf("Distance = %.2f cm\r\n", distance);

        // 4. 5cm 이내면 LED 깜빡이기
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
   실습문제 5-3 2번: 거리에 따른 LED 개수 조절
   가까울수록 켜지는 LED 개수 증가
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

        // 거리 구간별 LED 개수 제어
        if (distance > 0.0f && distance <= 5.0f) {
            L1=1; L2=1; L3=1; L4=1;    // 5cm 이내: 4개
        } else if (distance <= 10.0f) {
            L1=1; L2=1; L3=1; L4=0;    // 10cm 이내: 3개
        } else if (distance <= 15.0f) {
            L1=1; L2=1; L3=0; L4=0;    // 15cm 이내: 2개
        } else if (distance <= 20.0f) {
            L1=1; L2=0; L3=0; L4=0;    // 20cm 이내: 1개
        } else {
            L1=0; L2=0; L3=0; L4=0;    // 20cm 이상: 0개
        }
        ThisThread::sleep_for(200ms);
    }
}
*/

/* =============================================
   실습문제 5-4 1번: PIR 센서로 경보 시스템
   움직임 감지 시 초록 LED 끄고 파란 LED 5회 깜빡임
============================================= */
/*
#include "mbed.h"

DigitalIn alarm(D7, PullDown);          // PIR 센서 출력 (움직임 감지 시 HIGH)
BusOut blue_leds(D13, A2);              // 파란 LED 2개 (경보등)
BusOut green_leds(D11, D12);            // 초록 LED 2개 (정상등)

int main() {
    ThisThread::sleep_for(2000ms);      // PIR 워밍업 대기

    while(1) {
        green_leds = 0x3;   // 정상 상태: 초록 LED ON
        blue_leds = 0;      // 정상 상태: 파란 LED OFF

        if (alarm.read() == 1) {
            ThisThread::sleep_for(50ms);        // 디바운싱
            if (alarm.read() == 1) {            // 진짜 감지 확인
                green_leds = 0;                 // 초록 LED 끄기

                // 파란 LED 5회 깜빡임 (경보)
                for(int i = 0; i < 5; i++) {
                    blue_leds = 0x3;
                    ThisThread::sleep_for(300ms);
                    blue_leds = 0;
                    ThisThread::sleep_for(300ms);
                }

                while(alarm.read() == 1) {      // 움직임 멈출 때까지 대기
                    ThisThread::sleep_for(50ms);
                }
                ThisThread::sleep_for(500ms);   // 안정화 대기
            }
        }
    }
}
*/

/* =============================================
   코드 6-2 예제: DS3231 시간설정 및 출력
   RTC에 시간을 설정하고 1초마다 터미널에 출력
============================================= */
/*
#include "mbed.h"

// DS3231 I2C 주소 및 레지스터 주소 정의
#define DS3231_ADDR (0x68)
#define REG_SEC     (0x00)  // 초 레지스터
#define REG_MIN     (0x01)  // 분 레지스터
#define REG_HOUR    (0x02)  // 시 레지스터
#define REG_WEEK    (0x03)  // 요일 레지스터
#define REG_DAY     (0x04)  // 일 레지스터
#define REG_MONTH   (0x05)  // 월 레지스터
#define REG_YEAR    (0x06)  // 연도 레지스터

I2C i2c(I2C_SDA, I2C_SCL);

// 함수 선언
void write_data(uint8_t addr, uint8_t reg, uint8_t data);
uint8_t read_data(uint8_t addr, uint8_t reg);
uint8_t bcd_to_decimal(uint8_t bcd);
uint8_t decimal_to_bcd(uint8_t decimal);

int main() {
    char week[8][4] = {"nul", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    unsigned char times[7];
    uint8_t addr = DS3231_ADDR << 1;    // 7비트 주소를 8비트로 변환 (쓰기용)

    // 초기 시간 설정: 2021년 5월 18일 15:59:30 (화요일)
    write_data(addr, REG_SEC,   decimal_to_bcd(30));    // 30초
    write_data(addr, REG_MIN,   decimal_to_bcd(59));    // 59분
    write_data(addr, REG_HOUR,  decimal_to_bcd(15));    // 15시
    write_data(addr, REG_WEEK,  decimal_to_bcd(3));     // 화요일(3)
    write_data(addr, REG_DAY,   decimal_to_bcd(18));    // 18일
    write_data(addr, REG_MONTH, decimal_to_bcd(5));     // 5월
    write_data(addr, REG_YEAR,  decimal_to_bcd(21));    // 2021년

    while(1) {
        ThisThread::sleep_for(1000ms);  // 1초마다 출력

        // 레지스터에서 시간 데이터 읽기 (BCD → 10진수 변환)
        times[0] = bcd_to_decimal(read_data(addr, REG_SEC));
        times[1] = bcd_to_decimal(read_data(addr, REG_MIN));
        times[2] = bcd_to_decimal(read_data(addr, REG_HOUR));
        times[3] = bcd_to_decimal(read_data(addr, REG_WEEK));

        // 터미널 출력: HH:MM:SS 요일
        printf("%02d:%02d:%02d %s\n", times[2], times[1], times[0], week[times[3]]);
    }
}

// I2C로 DS3231 레지스터에 데이터 쓰기
void write_data(uint8_t addr, uint8_t reg, uint8_t data) {
    char byte[2];
    byte[0] = reg;      // 레지스터 주소
    byte[1] = data;     // 쓸 데이터
    i2c.write(addr, byte, 2, 0);
}

// I2C로 DS3231 레지스터에서 데이터 읽기
uint8_t read_data(uint8_t addr, uint8_t reg) {
    char data[1];
    char byte[1];
    byte[0] = reg;
    i2c.write(addr, byte, 1, 1);    // 레지스터 주소 전송 (repeated start)
    i2c.read(addr, data, 1, 0);     // 데이터 읽기
    return data[0];
}

// BCD 형식 → 10진수 변환 (DS3231은 BCD로 저장)
// 예: 0x25(BCD) = 0010 0101 → (2*10)+5 = 25
uint8_t bcd_to_decimal(uint8_t bcd) {
    return (bcd >> 4) * 10 + (bcd & 0x0F);
}

// 10진수 → BCD 형식 변환
// 예: 25 → (2<<4)|5 = 0x25
uint8_t decimal_to_bcd(uint8_t decimal) {
    return ((decimal / 10) << 4) | (decimal % 10);
}
*/

/* =============================================
   실습문제 6-1 1번: DS3231 시간 전체 출력
   날짜/시간/요일을 AM/PM 형식으로 터미널 출력
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
    // 요일/월 이름 배열
    char week[8][4] = {"nul", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    char month_name[13][4] = {"nul", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                               "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    uint8_t addr = DS3231_ADDR << 1;
    unsigned char times[7];

    // 시간 설정: 2021년 5월 18일 22:30:00 (화요일)
    write_data(addr, REG_SEC,   decimal_to_bcd(0));
    write_data(addr, REG_MIN,   decimal_to_bcd(30));
    write_data(addr, REG_HOUR,  decimal_to_bcd(22));    // 22시 = 10 PM
    write_data(addr, REG_WEEK,  decimal_to_bcd(3));     // 화요일
    write_data(addr, REG_DAY,   decimal_to_bcd(18));
    write_data(addr, REG_MONTH, decimal_to_bcd(5));
    write_data(addr, REG_YEAR,  decimal_to_bcd(21));

    printf("RTC Start!\n");

    while(1) {
        ThisThread::sleep_for(1000ms);

        // 전체 날짜/시간 데이터 읽기
        times[0] = bcd_to_decimal(read_data(addr, REG_SEC));
        times[1] = bcd_to_decimal(read_data(addr, REG_MIN));
        times[2] = bcd_to_decimal(read_data(addr, REG_HOUR));
        times[3] = bcd_to_decimal(read_data(addr, REG_WEEK));
        times[4] = bcd_to_decimal(read_data(addr, REG_DAY));
        times[5] = bcd_to_decimal(read_data(addr, REG_MONTH));
        times[6] = bcd_to_decimal(read_data(addr, REG_YEAR));

        // 24시간 → 12시간 AM/PM 변환
        int h24 = times[2];
        int h12 = h24;
        const char* ampm = "AM";

        if (h24 >= 12) {
            ampm = "PM";
            if (h24 > 12) h12 = h24 - 12;
        } else if (h24 == 0) {
            h12 = 12;   // 자정(0시) = 12 AM
        }

        // 출력 형식: HH:MM PM Wed, May 18, 2021
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
   실습문제 6-2 1번: DS3231 내장 온도센서 출력
   레지스터 0x11(정수부), 0x12(소수부) 읽어서 온도 계산
============================================= */
/*
#include "mbed.h"

#define DS3231_ADDR (0x68 << 1)     // 8비트 주소로 변환
#define REG_TEMP_MSB 0x11           // 온도 정수부 레지스터
#define REG_TEMP_LSB 0x12           // 온도 소수부 레지스터

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
        // 온도 정수부: 부호 있는 8비트 정수 (int8_t)
        int8_t temp_msb = read_data(REG_TEMP_MSB);
        // 온도 소수부: 상위 2비트만 사용 (0x40=0.25, 0x80=0.5, 0xC0=0.75)
        uint8_t temp_lsb = read_data(REG_TEMP_LSB);

        // 소수부 계산: 상위 2비트 >> 6 * 0.25
        // 예: 0x40(0100 0000) >> 6 = 1, 1 * 0.25 = 0.25
        float fraction = (temp_lsb >> 6) * 0.25f;
        float current_temp = (float)temp_msb + fraction;

        printf("현재 온도 : %.2f C\n", current_temp);
        ThisThread::sleep_for(1000ms);
    }
}
*/

/* =============================================
   실습문제 7-1 OLED 제어 테스트
   Hello World 출력 후 시간 표시
============================================= */
/*
#include "mbed.h"
#include "Adafruit_SSD1306.h"

I2C i2c(D14, D15);
// SSD1306 OLED: I2C주소 0x78, 높이 64px, 너비 128px
Adafruit_SSD1306_I2c oled(i2c, NC, 0x78, 64, 128);

void oled_write_string(const char *str);

int main() {
    i2c.frequency(50000);   // I2C 통신 속도 50kHz (안정성 우선)
    oled.begin();           // OLED 초기화

    // 1단계: Hello, World! 출력
    oled.clearDisplay();
    ThisThread::sleep_for(10ms);    // 화면 지운 후 처리 시간 대기

    oled.setTextSize(1);            // 글자 크기 1 (작은 글씨)
    oled.setTextCursor(0, 0);       // 커서 위치 (x=0, y=0)
    oled_write_string("Hello, World!");

    oled.setTextSize(2);            // 글자 크기 2 (큰 글씨)
    oled.setTextCursor(0, 15);
    oled_write_string("SSD1306");
    oled.display();                 // 버퍼 내용을 실제 화면에 출력

    ThisThread::sleep_for(5000ms);  // 5초 유지

    // 2단계: 화면 지우기
    oled.clearDisplay();
    ThisThread::sleep_for(10ms);
    oled.display();
    ThisThread::sleep_for(2000ms);

    // 3단계: 시간 표시
    oled.setTextSize(2);
    oled.setTextCursor(0, 15);
    oled_write_string("10:25 AM");
    oled.display();

    while(1) { }
}

// 문자열을 한 글자씩 OLED에 출력하는 함수
void oled_write_string(const char *str) {
    for(int i = 0; str[i]; i++) {
        oled.writeChar(str[i]);
    }
}
*/

/* =============================================
   실습문제 7-1 실습: I2C 주소 OLED 출력
   sprintf로 16진수 주소값을 문자열로 변환하여 출력
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

    // sprintf: 정수값을 형식에 맞춰 문자열로 변환
    // %X: 16진수 대문자로 출력 → "Addr: 78"
    sprintf(buff, "Addr: %X", i2c_address);

    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextCursor(0, 0);
    oled_write_string(buff);    // "Addr: 78" 출력
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
   실습문제 7-2: DS3231 + SSD1306 디지털 시계
   OLED에 날짜/시간/온도를 디지털 시계 형식으로 표시
============================================= */
/*
#include "mbed.h"
#include "Adafruit_SSD1306.h"

I2C i2c(D14, D15);
Adafruit_SSD1306_I2c oled(i2c, NC, 0x78, 64, 128);

// DS3231 I2C 주소 (8비트: 0x68 << 1 = 0xD0)
#define DS3231_ADDR 0xD0

// BCD → 10진수 변환
int bcd2dec(int bcd) {
    return (bcd >> 4) * 10 + (bcd & 0x0F);
}

// OLED에 문자열 출력 함수
void write_string(const char* str) {
    while(*str) oled.writeChar(*str++);
}

int main() {
    oled.begin();
    i2c.frequency(100000);  // I2C 속도 100kHz

    char timeBuff[30] = {0};    // 시간 문자열 버퍼
    char tempBuff[30] = {0};    // 온도 문자열 버퍼

    while(1) {
        // 1. DS3231에서 시간 데이터 읽기 (레지스터 0x00~0x06)
        char cmd = 0x00;
        char data[7] = {0};
        i2c.write(DS3231_ADDR, &cmd, 1, true);  // 시작 레지스터 주소 전송
        i2c.read(DS3231_ADDR, data, 7);          // 7바이트 연속 읽기

        int min  = bcd2dec(data[1]);             // 분
        int hour = bcd2dec(data[2] & 0x3F);      // 시 (비트6,7 마스킹)

        // 2. DS3231 내장 온도센서 읽기 (레지스터 0x11~0x12)
        char tempCmd = 0x11;
        char tempData[2] = {0, 0};
        i2c.write(DS3231_ADDR, &tempCmd, 1, true);
        i2c.read(DS3231_ADDR, tempData, 2);
        float temp = (int8_t)tempData[0] + ((tempData[1] >> 6) * 0.25f);
        sprintf(tempBuff, "Temp: %dC", (int)temp);

        // 3. 24시간 → 12시간 AM/PM 변환
        const char* ampm = (hour >= 12) ? "PM" : "AM";
        int h12 = hour % 12;
        if(h12 == 0) h12 = 12;

        sprintf(timeBuff, "%02d:%02d %s", h12, min, ampm);

        // 4. OLED 화면 출력
        oled.clearDisplay();

        // 1줄: 날짜 (고정값, 작은 글씨)
        oled.setTextSize(1);
        oled.setTextCursor(10, 0);
        write_string("Mon, 20 May 2021");

        // 2줄: 시간 (큰 글씨 2배)
        oled.setTextSize(2);
        oled.setTextCursor(5, 14);
        write_string(timeBuff);

        // 3줄: 온도 (작은 글씨)
        oled.setTextSize(1);
        oled.setTextCursor(10, 45);
        write_string(tempBuff);

        oled.display();
        ThisThread::sleep_for(1000ms);  // 1초마다 갱신
    }
}
*/

/* =============================================
   실습문제 8-1 1번: PWM으로 LED 밝기 자동 조절
   조도센서 값에 따라 LED 밝기 반비례 제어
============================================= */
/*
#include "mbed.h"

PwmOut myLed(A0);   // PWM 출력 LED (0.0~1.0으로 밝기 조절)
AnalogIn cds(A1);   // 조도센서

int main() {
    myLed.period(0.01f);    // PWM 주기 10ms (100Hz)

    while(1) {
        float val = cds.read();             // 조도값 읽기 (0.0~1.0)
        float brightness = 1.0f - val;      // 밝기는 조도의 반비례

        // 조도가 너무 밝으면(0.2 미만) LED 완전히 끄기
        if (val < 0.2f) {
            brightness = 0.0f;
        }

        myLed.write(brightness);    // PWM 듀티사이클로 밝기 설정
        printf("CDS: %.2f | LED: %.2f\n", val, brightness);
        ThisThread::sleep_for(100ms);
    }
}
*/

/* =============================================
   실습문제 8-2: 초음파 + PWM 부저 경보
   10cm 이내 접근 시 1000Hz 경고음 발생
============================================= */
/*
#include "mbed.h"

Timer t;
DigitalOut trig(D9);
DigitalIn echo(D10);
PwmOut buzzer(D3);  // PWM 부저 (주파수로 음높이 제어)

int main() {
    float duration, distance;

    while(1) {
        // 초음파 발사
        trig = 0;
        wait_us(2);
        trig = 1;
        wait_us(10);
        trig = 0;

        // 거리 측정
        while(!echo);
        t.start();
        while(echo);
        t.stop();

        duration = t.read_us();
        distance = duration * 0.0343f / 2.0f;  // cm 단위
        t.reset();

        printf("Distance: %.2f cm\n", distance);

        if (distance > 0 && distance < 10.0f) {
            buzzer.period_us(1000); // 1000us 주기 = 1kHz
            buzzer.write(0.5f);     // 50% 듀티사이클로 소리 켜기
        } else {
            buzzer.write(0.0f);     // 소리 끄기
        }
        ThisThread::sleep_for(100ms);
    }
}
*/

/* =============================================
   실습문제 8-2 사이렌 소리
   10cm 이내 접근 시 5초간 사이렌 효과음 발생
   주파수를 500~1500Hz로 점점 올렸다 내리는 방식
============================================= */
/*
#include "mbed.h"

Timer t;
Timer sirenTimer;       // 사이렌 지속시간 측정용
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

            // 5초 동안 사이렌 효과 반복
            while (sirenTimer.read() < 5.0f) {
                // 주파수 상승: 500Hz → 1500Hz
                for (int freq = 500; freq < 1500; freq += 10) {
                    buzzer.period(1.0f / (float)freq);
                    buzzer.write(0.5f);
                    wait_us(1000);
                }
                // 주파수 하강: 1500Hz → 500Hz
                for (int freq = 1500; freq > 500; freq -= 10) {
                    buzzer.period(1.0f / (float)freq);
                    buzzer.write(0.5f);
                    wait_us(1000);
                }
            }
            sirenTimer.stop();
            buzzer.write(0.0f);     // 사이렌 종료
            ThisThread::sleep_for(2000ms);  // 2초 대기 후 재감지
        } else {
            buzzer.write(0.0f);
        }
        ThisThread::sleep_for(100ms);
    }
}
*/

/* =============================================
   실습문제 10-2: 인터럽트 연습 2
   버튼 인터럽트로 외부 LED 토글
   내장 LED는 메인루프에서 0.5초 깜빡임
============================================= */
/*
#include "mbed.h"

InterruptIn button(BUTTON1);    // 보드 내장 버튼 (인터럽트 입력)
DigitalOut led1(LED1);          // 보드 내장 LED (메인루프 제어)
DigitalOut led2(PA_4);          // 외부 LED (인터럽트 제어)

// 버튼 인터럽트 함수: 버튼 누를 때마다 호출
void toggle() {
    led2 = !led2;   // 외부 LED 토글
}

int main() {
    button.rise(&toggle);   // 버튼 상승엣지(누름)에 인터럽트 등록
    while (1) {
        led1 = !led1;           // 내장 LED 깜빡임 (인터럽트와 동시 동작)
        ThisThread::sleep_for(500ms);
    }
}
*/

/* =============================================
   실습문제 10-1-2: 인터럽트 카운트다운 폭탄
   버튼으로 카운트다운 시작/정지, 0이 되면 부저 폭발음
============================================= */
/*
#include "mbed.h"

InterruptIn button(BUTTON1);
DigitalOut buzzer(D3);
int my_counter = 10;        // 카운트다운 시작값
bool running = true;        // 카운트다운 진행 상태

// 버튼 인터럽트: 누를 때마다 진행/정지 토글
void toggle_countdown() {
    running = !running;
}

int main() {
    button.rise(&toggle_countdown);
    printf("Counter: %d\n", my_counter);

    while (1) {
        ThisThread::sleep_for(1s);  // 1초마다 실행

        if (running && my_counter > 0) {
            my_counter--;
            printf("Counter: %d\n", my_counter);

            if (my_counter == 0) {
                printf("Boom!\n");
                // 수동 부저로 폭발음: 400ms 동안 1kHz 소리
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
   실습문제 10-3: Ticker + 인터럽트 동시 사용
   Ticker: 0.5초마다 내장 LED 자동 깜빡임
   버튼 인터럽트: 외부 LED 토글
============================================= */
/*
#include "mbed.h"

InterruptIn button(BUTTON1);
DigitalOut led1(LED1);
DigitalOut led_external(PA_4);
Ticker flipper;     // 하드웨어 타이머 기반 주기적 인터럽트

// 버튼 인터럽트: 외부 LED 토글
void toggle_external() {
    led_external = !led_external;
}

// Ticker 인터럽트: 0.5초마다 내장 LED 토글
void flip_internal() {
    led1 = !led1;
}

int main() {
    button.rise(&toggle_external);
    // Ticker: 0.5초마다 flip_internal 함수 자동 호출
    flipper.attach(&flip_internal, 0.5);

    // 메인 루프가 바빠도 Ticker는 독립적으로 동작
    while (1) {
        ThisThread::sleep_for(1s);
    }
}
*/

/* =============================================
   실습문제 10-4-2: 디바운싱 적용 부저 토글
   버튼으로 부저 ON/OFF, Timer로 200ms 디바운싱
============================================= */
/*
#include "mbed.h"

InterruptIn button(BUTTON1);
DigitalOut buzzer(D3);
bool buzzer_on = false;
Timer debounce_timer;   // 디바운싱용 타이머

void toggle_buzzer() {
    // 마지막 누름으로부터 200ms 이상 지났을 때만 동작 (디바운싱)
    if (chrono::duration_cast<chrono::milliseconds>(debounce_timer.elapsed_time()).count() > 200 ||
        chrono::duration_cast<chrono::milliseconds>(debounce_timer.elapsed_time()).count() == 0) {
        buzzer_on = !buzzer_on;
        debounce_timer.reset();     // 타이머 리셋
    }
}

int main() {
    debounce_timer.start();
    button.rise(&toggle_buzzer);

    while (1) {
        if (buzzer_on) {
            // 수동 부저: 1과 0 빠르게 반복으로 소리 생성
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
   실습문제 11-1: RTOS 멀티스레드 LED 제어
   스레드1: LED2 200ms 깜빡임
   스레드2: LED3 500ms 깜빡임 (10초 후 종료)
   인터럽트: 버튼으로 내장 LED 토글
============================================= */
/*
#include "mbed.h"

DigitalOut led1(LED1);      // 내장 LED (인터럽트 제어)
DigitalOut led2(PA_4);      // 외부 LED2 (스레드1 제어)
DigitalOut led3(PA_7);      // 외부 LED3 (스레드2 제어)
InterruptIn button(BUTTON1);

Thread thread_led2;     // LED2 제어 스레드
Thread thread_led3;     // LED3 제어 스레드

// 스레드1: LED2를 200ms 간격으로 깜빡임
void led2_blink() {
    while (1) {
        led2 = !led2;
        ThisThread::sleep_for(200ms);
    }
}

// 스레드2: LED3를 500ms 간격으로 깜빡임
void led3_blink() {
    while (1) {
        led3 = !led3;
        ThisThread::sleep_for(500ms);
    }
}

void toggle() {
    led1 = !led1;   // 버튼으로 내장 LED 토글
}

int main() {
    button.rise(toggle);

    thread_led2.start(led2_blink);  // LED2 스레드 시작
    thread_led3.start(led3_blink);  // LED3 스레드 시작

    ThisThread::sleep_for(10s);     // 10초 대기
    thread_led3.terminate();        // LED3 스레드만 종료 (LED2는 계속 동작)

    while (1) { }
}
*/

/* =============================================
   실습문제 11-2: 멀티스레드 초음파+조도 동시 제어
   스레드1: 초음파로 10cm 이내 감지 시 부저 5초 울림
   스레드2: 조도센서로 어두우면 LED 켜기
============================================= */
/*
#include "mbed.h"

DigitalOut buzzer(PB_0);    // 수동 부저 (A3핀)
DigitalOut led(PA_4);       // LED (A2핀)
AnalogIn cds(A0);           // 조도센서
DigitalOut trig(D9);        // 초음파 Trig
DigitalIn  echo(D10);       // 초음파 Echo

Thread thread_ultrasonic;   // 초음파/부저 스레드
Thread thread_cds;          // 조도/LED 스레드
Timer pulse_timer;          // 초음파 시간 측정

// 스레드1: 초음파 감지 및 부저 제어
void ultrasonic_task() {
    while (1) {
        // 초음파 발사
        trig = 0;
        wait_us(2);
        trig = 1;
        wait_us(10);
        trig = 0;

        // 거리 측정
        while (echo == 0);
        pulse_timer.start();
        while (echo == 1);
        pulse_timer.stop();

        float duration = pulse_timer.elapsed_time().count();
        float distance = duration * 0.0343f / 2.0f;
        pulse_timer.reset();

        if (distance > 0 && distance <= 10.0f) {
            // 수동 부저 5초간 2kHz 경고음
            // 500us 주기(250us ON + 250us OFF) = 2kHz
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

// 스레드2: 조도센서로 LED 자동 제어
void cds_task() {
    while (1) {
        float cds_val = cds.read();
        // 0.3 미만이면 어두운 것 → LED 켜기
        led = (cds_val < 0.3f) ? 1 : 0;
        ThisThread::sleep_for(100ms);
    }
}

int main() {
    // 두 스레드 동시 시작 (병렬 실행)
    thread_ultrasonic.start(ultrasonic_task);
    thread_cds.start(cds_task);

    while (1) {
        ThisThread::sleep_for(1s);
    }
}
*/

/* =============================================
   기말과제: 비상경보시스템
   4가지 기능을 RTOS 멀티스레드로 동시 동작
   1. 초음파 접근 경보: 20cm 이내 접근 시 부저
   2. PIR 움직임 경보: 움직임 감지 시 빨간 LED 깜빡임
   3. 조도 자동 조명: 어두우면 노란 LED 자동 ON
   4. 버튼 조명 제어: 사용자 버튼으로 파란 LED ON/OFF
============================================= */
#include "mbed.h"

// ===== 핀 설정 =====
DigitalIn pir(D4, PullDown);      // PIR 움직임 감지 센서 (D4핀, 기본값 LOW)
AnalogIn cds(A0);                  // 조도센서 (A0핀, 0.0~1.0 값 반환)
DigitalOut red_led(D5);            // 빨간 LED - 움직임 감지 경고등 (D5핀)
DigitalOut yellow_led(D6);         // 노란 LED - 조도 자동 조명등 (D6핀)
DigitalOut blue_led(D8);           // 파란 LED - 사용자 버튼 조명등 (D8핀)
PwmOut buzzer(D7);                 // 부저 - PWM으로 삑삑 경고음 발생 (D7핀)
DigitalOut trig(D11);              // 초음파 센서 Trig 핀 - 초음파 발사 (D11핀)
DigitalIn echo(D12);               // 초음파 센서 Echo 핀 - 반사파 수신 (D12핀)
InterruptIn user_btn(PC_13);       // Nucleo 내장 사용자 버튼 (PC_13핀)

bool blue_state = false;           // 파란 LED 현재 상태 (true=켜짐, false=꺼짐)

// ===== 버튼 인터럽트 함수 =====
// 사용자 버튼을 누를 때마다 호출됨
// blue_state를 반전시켜 파란 LED를 토글
void btn_pressed() {
    blue_state = !blue_state;      // 상태 반전
    blue_led = blue_state;         // LED에 상태 적용
}

// ===== 초음파 거리 측정 함수 =====
// 반환값: 센서로부터 물체까지의 거리 (cm 단위)
float getDistance() {
    // Trig 핀에 10us 펄스 발사 → 초음파 송신
    trig = 0;
    wait_us(2);                    // 안정화를 위해 2us 대기
    trig = 1;
    wait_us(10);                   // 10us 동안 HIGH → 초음파 발사
    trig = 0;

    // Echo 핀으로 반사파 도달 시간 측정
    Timer t;
    while(echo == 0);              // Echo HIGH 대기
    t.start();                     // 타이머 시작
    while(echo == 1);              // Echo LOW 대기
    t.stop();                      // 타이머 정지

    // 거리 계산: 시간(us) * 음속(34300cm/s) / 2(왕복)
    return t.elapsed_time().count() / 1000000.0f * 34300.0f / 2.0f;
}

// ===== 스레드1: 접근 경보 =====
// 초음파로 20cm 이내 접근 감지 시 부저 경고음 발생
void thread_distance() {
    while(1) {
        float dist = getDistance();

        if(dist < 20.0f) {                 // 20cm 이내 접근
            buzzer.period(1.0/2000.0);     // 2000Hz 주파수
            buzzer.write(0.5f);            // 50% 듀티사이클로 소리 ON
            ThisThread::sleep_for(100ms);
            buzzer.write(0.0f);            // 소리 OFF → 삑삑 효과
            ThisThread::sleep_for(100ms);
        } else {
            buzzer.write(0.0f);            // 범위 밖이면 부저 끄기
            ThisThread::sleep_for(200ms);
        }
    }
}

// ===== 스레드2: 움직임 경보 =====
// PIR 센서로 움직임 감지 시 빨간 LED 깜빡임
void thread_pir() {
    ThisThread::sleep_for(2000ms);  // PIR 워밍업 2초 대기

    while(1) {
        // 노이즈 필터: 5번 중 4번 이상 감지 시 동작
        int count = 0;
        for(int i = 0; i < 5; i++) {
            if(pir == 1) count++;
            ThisThread::sleep_for(10ms);
        }

        if(count >= 4) {                   // 진짜 움직임 감지
            red_led = 1;
            ThisThread::sleep_for(500ms);
            red_led = 0;
        } else {
            red_led = 0;
        }
    }
}

// ===== 스레드3: 조명 자동 제어 =====
// 조도센서 값 0.2 미만(어두움) → 노란 LED ON
void thread_cds() {
    while(1) {
        float val = cds.read();
        yellow_led = (val < 0.2f) ? 1 : 0;
        ThisThread::sleep_for(100ms);
    }
}

// 스레드 객체 선언
Thread t1;   // 초음파/부저
Thread t2;   // PIR/빨간LED
Thread t3;   // 조도/노란LED

int main() {
    // 사용자 버튼 인터럽트 등록 (fall=버튼 누름 순간)
    user_btn.fall(&btn_pressed);

    // 3개 스레드 동시 시작 → 4가지 기능 병렬 동작
    t1.start(thread_distance);   // 초음파 접근 경보
    t2.start(thread_pir);        // PIR 움직임 경보
    t3.start(thread_cds);        // 조도 자동 조명
    // 파란 LED는 인터럽트로 제어 → 별도 스레드 불필요

    while(1) {
        ThisThread::sleep_for(1000ms);
    }
}
