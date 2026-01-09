#ifndef CONTROL_H
#define CONTROL_H

#include <IRremote.h>

// --- CONFIGURACIÓN IR ---
const int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

// Códigos Hex (Asegúrate que coinciden con tu mando)
const int KEY_REPEAT = 0xFFFFFFFF; 
const unsigned long POWER_ON = 0xFFA25D;
const unsigned long POWER_OFF = 0xFFE21D;

const unsigned long KEY_UP = 0xFF629D;
const unsigned long KEY_LEFT = 0xFF22DD;
const unsigned long KEY_OK = 0xFF02FD;
const unsigned long KEY_RIGHT = 0xFFC23D;
const unsigned long KEY_DOWN = 0xFFA857;

const unsigned long KEY_1 = 0xFF30CF;
const unsigned long KEY_2 = 0xFF18E7;
// const unsigned long KEY_3 = 0xFFE21D;
// const unsigned long KEY_4 = 0xFF10EF;
// const unsigned long KEY_5 = 0xFF38C7;
// const unsigned long KEY_6 = 0xFF5AA5;
// const unsigned long KEY_7 = 0xFF42BD;
// const unsigned long KEY_8 = 0xFF4AB5;
// const unsigned long KEY_9 = 0xFF52AD;

#endif
