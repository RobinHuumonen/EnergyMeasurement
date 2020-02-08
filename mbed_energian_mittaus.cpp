#include "mbed.h"
Serial pc(USBTX,USBRX);

Timer timer;
Ticker kello;
#define dt 1 // sekuntia

AnalogIn UsyottoMittari (A0); // Vastaanotetaan vaimennettuna
AnalogIn UmMittari (A1);
float janniteJakoVaimennus = 4.73;
float mitattuUsyottoArvo = 0.0;
float mitattuUmArvo = 0.0;
float Utuuletin = 0.0;
float Rm = 10;
float virta = 0.0;
float teho = 0.0;
float energia = 0.0;
float kokonaisEnergia = 0.0;
unsigned long aika = 0;

void EnergiaLaskenta (void)
{
    aika = timer.read_ms() * 0.001; // Aikaleima sekunteina
    mitattuUmArvo = UmMittari;
    mitattuUsyottoArvo = (UsyottoMittari * janniteJakoVaimennus); // Skaalaus alkuperäiseen DC-jännitesyöttöön
    if (mitattuUmArvo <= 0)
    {
        mitattuUmArvo = 0;
    }
    if (mitattuUsyottoArvo <= 0)
    {
        mitattuUsyottoArvo = 0;
    }
    kokonaisEnergia += energia; // Energia laskettu keskeytyksillä 1 s aikavälein
    Utuuletin = (mitattuUsyottoArvo - mitattuUmArvo);
    virta = ((mitattuUmArvo * 3.3) / Rm);
    teho = ((Utuuletin * 3.3) * virta);
    energia = teho * dt; // Teho * 1
}

int main()
{
    timer.start();
    timer.reset();
    kello.attach(&EnergiaLaskenta, dt);

    while (1)
    {
        /***************************
        TULOSTUS SARAKKEITTAIN:
        1. Aikaleima / s
        2. DC-jännitesyöttö
        3. Mittavastuksen jännite
        4. Tuulettimelle jäävä jännite
        5. Energian muutos aikavälin välillä == teho * dt
        6. Energian kertymä
        ***************************/
        pc.printf("%lu ", aika);
        pc.printf("%f ", (mitattuUsyottoArvo * 3.3));
        pc.printf("%f ", (mitattuUmArvo * 3.3));
        pc.printf("%f ", (Utuuletin * 3.3));
        pc.printf("%f ", energia);
        pc.printf("%f ", kokonaisEnergia);
        pc.printf("\r\n");
    }

}
