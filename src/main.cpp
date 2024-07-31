#include <Arduino.h>
#include <TFT_eSPI.h>

//
bool SentidoHorario = true;
int Angulo = 0;
int Pivot_X = TFT_WIDTH / 2;
int Pivot_Y = TFT_HEIGHT / 2;
int Pos_Y = 190;
String AnguloAviacao = "N";
String PontoCardeal = "N";
String PontoCardealExtenso = "Norte";
bool PausaPonto = false;
constexpr int TempoEspera = 1500;

// cria uma instância do display tft
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite back = TFT_eSprite(&tft);
TFT_eSprite needle = TFT_eSprite(&tft);

void iniciaDisplay()
{
  tft.init(); // TTGO T-DISPLAY 135 larg x 240 alt na visao em pe ( default )
  tft.fillScreen(TFT_BLACK);
  tft.setPivot(Pivot_X, Pivot_Y);
  needle.createSprite(60, Pivot_Y);
  back.createSprite(TFT_WIDTH, TFT_HEIGHT);
}

void creditos()
{
  // Serial.begin(115200);
  // Serial.println("");
  // Serial.println("Raspbery PI Pico Modulo RP2040 com Display TFT 1.28' 240x240");
  // Serial.println("Veja o codigo fonte em:");
  // Serial.println("C:\\Users\\breno\\OneDrive\\Documentos\\PlatformIO\\Projects\\CoeBrothers\\2023\\Altimetro_GPS_RP2040");
  // Serial.println("");
}

void setup()
{
  creditos();
  iniciaDisplay();
}

void loop()
{
  //
  if (SentidoHorario)
    Angulo++;
  else
    Angulo--;
  //
  switch (Angulo)
  {
  case 0:
    PausaPonto = true;
    SentidoHorario = !SentidoHorario;
    PontoCardeal = "N";
    AnguloAviacao = PontoCardeal;
    PontoCardealExtenso = "North";
    break;
  case 360:
    PausaPonto = true;
    SentidoHorario = !SentidoHorario;
    PontoCardeal = "N";
    AnguloAviacao = PontoCardeal;
    PontoCardealExtenso = "North";
    break;
  case 45:
    PausaPonto = true;
    PontoCardeal = "NE";
    PontoCardealExtenso = "Northeast";
    break;
  case 90:
    PausaPonto = true;
    PontoCardeal = "E";
    AnguloAviacao = PontoCardeal;
    PontoCardealExtenso = "East";
    break;
  case 135:
    PausaPonto = true;
    PontoCardeal = "SE";
    PontoCardealExtenso = "Southeast";
    break;
  case 180:
    PausaPonto = true;
    PontoCardeal = "S";
    AnguloAviacao = PontoCardeal;
    PontoCardealExtenso = "South";
    break;
  case 225:
    PausaPonto = true;
    PontoCardeal = "SW";
    PontoCardealExtenso = "Southwest";
    break;
  case 270:
    PausaPonto = true;
    PontoCardeal = "W";
    AnguloAviacao = PontoCardeal;
    PontoCardealExtenso = "West";
    break;
  case 315:
    PausaPonto = true;
    PontoCardeal = "NW";
    PontoCardealExtenso = "Northwest";
    break;
  default:
    PausaPonto = false;
    if (Angulo < 100)
      AnguloAviacao = String(Angulo).substring(0, 1);
    else
      AnguloAviacao = String(Angulo).substring(0, 2);
    break;
  }
  //
  back.fillSprite(TFT_BLACK);
  // back.fillCircle(Pivot_X, Pivot_Y, Pivot_X, TFT_SILVER);
  needle.fillSprite(TFT_BLACK);
  // needle.drawWedgeLine(20, Pivot_Y / 2, 20, Pivot_Y, 20, 1, TFT_DARKGREY, TFT_BLACK);
  needle.drawWedgeLine(30, 0, 30, Pivot_Y * 0.75, 1, 30, TFT_RED, TFT_BLACK);
  // needle.drawChar('', x, y, 2);
  needle.fillCircle(30, 90, 25, TFT_BLACK);
  // needle.drawCentreString(PontoCardeal, 30, Pivot_Y - 40, 4);
  // needle.drawCentreString(String(Angulo), 30, Pivot_Y - 40, 2);
  needle.drawCentreString(AnguloAviacao, 30, Pivot_Y - 40, 4);
  // needle.fillCircle(20, Pivot_Y / 2, 15, TFT_MAROON);
  // needle.fillCircle(20, Pivot_Y / 2, 5, TFT_DARKGREY);
  needle.pushRotated(&back, Angulo, TFT_BLACK);
  back.pushSprite(0, 0);
  tft.drawCentreString(String(Angulo), Pivot_X, Pos_Y, 6);
  //
  if (PausaPonto)
  {
    tft.fillRect(0, 0, TFT_WIDTH, 50, TFT_BLACK);
    tft.drawCentreString(PontoCardealExtenso, Pivot_X, 10, 4);
    delay(TempoEspera);
  }
}