#include <REGX52.H>
#include "DELAY.H"
#include "Key.h"
#include "NIXIE.H"
#include "Buzzer.h"

unsigned char KeyNum;

void main()
{
  nixie(1, 0);
  while (1)
  {
    KeyNum = Key();
    if (KeyNum)
    {
      Buzzer_Time(100);
      nixie(1, KeyNum);
    }
  }
}
