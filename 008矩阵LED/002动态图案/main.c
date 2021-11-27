#include <REGX52.H>
#include "DELAY.H"
#include "MatrixLED.H"

// 绘制图案，需要使用`取字模软件`
// 参数设置->其他选择->取模方式选择`纵向取模`，字节倒序`不勾选`
// 基本操作->新建图像->宽32高8
// 模拟动画->放大格点
// 点击白色方格，显示为黑色即绘制
// 绘制完成后，取模方式->C51格式
// 复制下方数组即可
void main()
{
  unsigned char anim[] = {
      // 空白
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      // H
      0x7F,
      0x08,
      0x08,
      0x08,
      0x7F,
      0x00,
      // E
      0x7F,
      0x49,
      0x49,
      0x49,
      0x00,
      // L
      0x7F,
      0x01,
      0x01,
      0x01,
      0x00,
      // L
      0x7F,
      0x01,
      0x01,
      0x01,
      0x00,
      // O
      0x3E,
      0x41,
      0x41,
      0x41,
      0x3E,
      0x00,
      // !
      0x7D,
      // 空白
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
  };
  unsigned char i, offset = 0, count = 0;
  MatrixLED_Init();
  while (1)
  {
    for (i = 0; i < 8; i++)
    {
      // 显示第一组数据
      MatrixLED_ShowColumn(i, anim[i + offset]);
    }
    // 控制移动速度
    count++;
    if (count > 20)
    {
      count = 0;
      // 向左移动1格
      offset++;
      // 8+6+5+5+5+6+1+8-8
      // 移动到尾部重头开始
      if (offset > 36)
      {
        offset = 0;
      }
    }
  }
}
