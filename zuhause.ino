#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define ERRO "{\"s\":500}"

DHT dht(DHTPIN, DHTTYPE);

char in;
char buf[4];

void setup()
{
    Serial.begin(9600);

    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);

    dht.begin();
}

void loop()
{
    if (Serial.available() > 0)
    {
        in = Serial.read();
        if (in == '$')
        {
            Serial.readBytes(buf, 4);
            if (buf[3] == '#')
            {

                // Digital
                if (buf[0] == 'D')
                {
                    char p = buf[1];
                    const int pin = strtol(&p, NULL, 16);

                    if (buf[2] == '0')
                    {
                        digitalWrite(pin, LOW);
                    }
                    else if (buf[2] == '1')
                    {
                        digitalWrite(pin, HIGH);
                    }
                    else
                    {
                        Serial.print(ERRO);
                        goto saida;
                    }

                    Serial.print("{\"s\":200,");
                    Serial.print("\"m\":\"");
                    Serial.print(buf[0]);
                    Serial.print("\",\"p\":\"");
                    Serial.print(buf[1]);
                    Serial.print("\",\"v\":");
                    Serial.print(digitalRead(pin));
                    Serial.print("}");
                }
                // Analógico
                else if (buf[0] == 'A')
                {
                    Serial.print(ERRO);
                }
                // Temperatura
                else if (buf[0] == 'T')
                {
                    Serial.print("{\"s\":200,");
                    Serial.print("\"t\":");
                    Serial.print(dht.readTemperature());
                    Serial.print(",\"h\":");
                    Serial.print(dht.readHumidity());
                    Serial.print("}");
                }
                else
                {
                    Serial.print(ERRO);
                }
            }
            else
            {
                Serial.print(ERRO);
            }

        saida:;
        }
    }
}