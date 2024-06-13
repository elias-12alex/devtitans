#include <Keypad.h>
const int ledPinVermelho = 32;
const int ledPinVerde = 33;

byte rows[] = { 23, 22, 21, 19 };
byte columns[] = { 18, 5, 4, 2 };
const byte numRows = 4;
const byte numCols = 4;

char keys[numRows][numCols] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

Keypad myKeypad = Keypad(makeKeymap(keys), rows, columns, numRows, numCols);

char key;
float accumulatedMoney = 0.0;
const float productCost = 1.00;

void setup()
{
    pinMode (ledPinVermelho, OUTPUT);
    pinMode (ledPinVerde, OUTPUT);
    digitalWrite(ledPinVermelho, LOW);
    digitalWrite(ledPinVerde, LOW);
    Serial.begin(9600);
}

void loop() {
    key = myKeypad.getKey();
    
    if (key) {
        switch(key) {
            case '1':
                accumulatedMoney += 0.10;
                Serial.print("Money inserted: R$ ");
                Serial.println(accumulatedMoney, 2);
                break;
            case '2':
                accumulatedMoney += 0.20;
                Serial.print("Money inserted: R$ ");
                Serial.println(accumulatedMoney, 2);
                break;
            case '3':
                accumulatedMoney += 0.25;
                Serial.print("Money inserted: R$ ");
                Serial.println(accumulatedMoney, 2);
                break;
            case '4':
                accumulatedMoney += 0.50;
                Serial.print("Money inserted: R$ ");
                Serial.println(accumulatedMoney, 2);
                break;
            case '*':
                if (accumulatedMoney >= productCost) {
                    digitalWrite(ledPinVerde, HIGH);
                    delay(2000);
                    digitalWrite(ledPinVerde, LOW);
                    Serial.println("Product dispensed");
                } else {
                    digitalWrite(ledPinVermelho, HIGH);
                    delay(3000);
                    digitalWrite(ledPinVermelho, LOW);
                    Serial.println("Insufficient money");
                }
                accumulatedMoney = 0.0; // Reset money
                break;
            default:
                // Ignore other keys
                break;
        }
    }
}