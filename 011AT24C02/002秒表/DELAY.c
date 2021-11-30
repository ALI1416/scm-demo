/**
* @brief  延时n*1ms
* @param  n 延时1ms的倍数，范围：0~65535
*/
void delayMs(unsigned int n)
{
  unsigned int i = 0, j = 0;
  for (i = 0; i < n; i++)
    for (j = 0; j < 111; j++)
      ;
}
