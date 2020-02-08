#include <MsTimer2.h>
const int UmMittari = A0;
const int UsyottoMittari = A1;
float mitattuUsyottoArvo = 0.0;
float mitattuUmArvo = 0.0;
float Ulaite = 0.0;
float Rm = 12; // 8.8
float virta = 0.0;
float teho = 0.0;
float energia = 0.0;
float kokonaisEnergia = 0.0;
unsigned long aikaLeima;

void setup()
{
    Serial.begin(57600);
    MsTimer2::set(0.7, energiaLaskenta);
    MsTimer2::start();
}

void loop()
{

    aikaLeima = millis();
    mitattuUmArvo = analogRead(UmMittari);
    mitattuUsyottoArvo = analogRead(UsyottoMittari);
    Ulaite = (mitattuUsyottoArvo - mitattuUmArvo);
    virta = (((mitattuUmArvo * 5.0) / 1024.00) / Rm);
    teho = (((Ulaite * 5.0) / 1024.00) * virta);
    energiaLaskenta();
    kokonaisEnergia += energia;

    /*Serial.print("T: ");
    Serial.print(aikaLeima);
    Serial.print(" ");
    Serial.print("Usyöttö: ");
    Serial.print((mitattuUsyottoArvo * 5.0) / 1024.00);
    Serial.print(" ");
    Serial.print("Um: ");
    Serial.print((mitattuUmArvo * 5.0) / 1024.00);
    Serial.print(" ");
    Serial.print("Ulaite: ");
    Serial.print((Ulaite * 5.0) / 1024.00);
    Serial.print(" ");
    Serial.print("E: ");
    Serial.print(energia, 7);
    Serial.print(" ");
    Serial.print("Ekok: ");
    Serial.println(kokonaisEnergia, 7); */
    Serial.print((mitattuUmArvo * 5.0) / 1024.00); // A0
    Serial.print(" ");
    Serial.print(" ");
    Serial.println((1/1.57) * virta); // A1
    // Serial.println((mitattuUsyottoArvo * 5.0) / 1024.00); // A1
}

void energiaLaskenta ()
{
    energia = teho * 0.007;
}
