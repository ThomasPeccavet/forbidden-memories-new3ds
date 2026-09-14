/* Analysis pseudo-C, not buildable source. */

void FUN_80031948(int param_1,undefined4 param_2,int param_3,int param_4)

{
  *(undefined1 *)(param_1 + 0xf) = 0x40;
  while (param_4 = param_4 + -1, -1 < param_4) {
    if (*(byte *)(param_3 + param_4) < 10) {
      *(byte *)(param_1 + 0xe) = *(byte *)(param_3 + param_4) * '\b' + -0x80;
      FUN_80084978(param_1,param_2,0);
    }
    *(short *)(param_1 + 4) = *(short *)(param_1 + 4) + 8;
  }
  return;
}

