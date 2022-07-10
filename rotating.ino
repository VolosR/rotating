#include <TFT_eSPI.h> 
TFT_eSPI tft = TFT_eSPI(); 
TFT_eSprite img = TFT_eSprite(&tft);

double rad=0.01745;
float x[95][60];
float y[95][60];

int colors[5]={0x7F1B,0x33F8,0x3617,0x9939,0xB139};
int chosen=0; //chosen color

float px[95][60];
float py[95][60];

int sx=105;
int sy=105;
int r=80;
int dif=30;

const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 0;
int brightnes=255;

void setup() {
  tft.init();
  tft.fillScreen(TFT_BLACK);

  ledcSetup(pwmLedChannelTFT, pwmFreq, pwmResolution);
  ledcAttachPin(5, pwmLedChannelTFT);
  ledcWrite(pwmLedChannelTFT, brightnes);
  
  img.createSprite(210,210);
  for(int j=0;j<95;j++)
  for(int i=0;i<60;i++)
    {
       x[j][i]=(j*cos(rad*i*6))+sx;
       y[j][i]=(j*sin(rad*i*6))+sy;
       px[j][i]=(j*cos(rad*i*6))+sx;
       py[j][i]=(j*sin(rad*i*6))+sy;

    }
}
float rot=0;
int num=1;
float spe=0;
void loop() {


  
  rot=rot+spe;
  if(rot>59)
  rot=0;
  img.fillSprite(TFT_BLACK);
  r=map(analogRead(34),0,4095,10,90);
  num=map(analogRead(32),0,4095,1,55);
  dif=map(analogRead(35),0,4095,10,90);
  spe=map(analogRead(33),0,4095,10,200)*0.01;
  chosen=map(analogRead(26),0,4095,0,4);
  img.drawString("radius1:"+String(r),0,0);
  img.drawString("radius2:"+String(dif),70,0);
  img.drawString("speed:"+String(spe),140,0);
  img.drawString("Number of lines: "+String(num),0,200);
  img.drawString("color: "+String(chosen),130,200);
  for(int i=0;i<num;i++)
  if((i+(int)rot)<60)
  img.drawLine(x[r][i+(int)rot],y[r][i+(int)rot],px[dif][i+(int)rot],py[dif][i+(int)rot],colors[chosen]-(int)rot);
  else
  img.drawLine(x[r][(i+(int)rot)-60],y[r][(i+(int)rot)-60],px[dif][(i+(int)rot)-60],py[dif][(i+(int)rot)-60],colors[chosen]-(int)rot);
  img.pushSprite(20,20);

}
