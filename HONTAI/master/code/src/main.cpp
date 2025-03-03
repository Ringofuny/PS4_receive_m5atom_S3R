#include <Arduino.h>
#include <PS4Controller.h>

enum { L_X, L_Y, R_X, R_Y, L_2, R_2, BA1, BA2, SUM };           //データ位置の定義
#define BAUDRATE 38400  //serial baudrate
#define DATA_N 9        //送信するデータ数 number of data
#define SEND_DELAY 18    //送信ディレイ時間 ms

void setup() {
  Serial.begin(115200);
  Serial1.begin(38400, SERIAL_8N1, 22, 21);  // (RX=22, TX=21)
  PS4.begin("90:15:06:fa:84:22");
  Serial.println("Ready.");
}

void loop() {
  unsigned char data[DATA_N] = {};  //データ格納配列
  // Below has all accessible outputs from the controller
  if (PS4.isConnected()) {
    data[L_X] = PS4.LStickX();   //LスティックX軸
    data[L_Y] = PS4.LStickY();   //LスティックY軸
    data[R_X] = PS4.RStickX();  //RスティックX軸
    data[R_Y] = PS4.RStickY();//RスティックY軸
    data[L_2] = PS4.L2();     //L2ボタン
    data[R_2] = PS4.R2();     //R2ボタン

    if (PS4.Square()) data[BA1] |= 0x01;
    if (PS4.Cross()) data[BA1] |= 0x02;
    if (PS4.Circle()) data[BA1] |= 0x04;
    if (PS4.Triangle()) data[BA1] |= 0x08;

    if (PS4.Up()) data[BA1] |= 0x10;
    if (PS4.Right()) data[BA1] |= 0x20;
    if (PS4.Down()) data[BA1] |= 0x40;
    if (PS4.Left()) data[BA1] |= 0x80;

    if (PS4.L1()) data[BA2] |= 0x01;
    if (PS4.L3()) data[BA2] |= 0x02;
    if (PS4.R1()) data[BA2] |= 0x04;
    if (PS4.R3()) data[BA2] |= 0x08;

    if (PS4.Share()) data[BA2] |= 0x10;
    if (PS4.Options()) data[BA2] |= 0x20;
    if (PS4.PSButton()) data[BA2] |= 0x40;

    for (int i = 0; i < DATA_N - 1; ++i) data[SUM] += (int)data[i];  //CheckSUM加算

    Serial1.write(0xAF);                                      //先頭データ送信
    for (int i = 0; i < DATA_N; ++i) Serial1.write(data[i]);  //データ送信
    Serial1.write(0xED);                                      //終端データ送信
    Serial1.write('\r');                                      //CR
    Serial1.write('\n');                                      //LF
    delay(SEND_DELAY);
  }
}
