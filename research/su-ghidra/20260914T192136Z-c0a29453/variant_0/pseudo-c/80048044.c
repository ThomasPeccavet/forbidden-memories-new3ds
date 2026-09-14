/* Analysis pseudo-C, not buildable source. */

void FUN_80048044(short *param_1,int param_2)

{
  int iVar1;
  
  FUN_80077468(0,0xf00000);
  iVar1 = 0;
  FUN_80047acc();
  *(ushort *)(DAT_8009c7e0 + 0x40) = *(ushort *)(DAT_8009c7e0 + 0x40) | 2;
  if (0 < param_2) {
    do {
      if (*param_1 != -1) {
        FUN_80047c18(*param_1);
      }
      iVar1 = iVar1 + 1;
      param_1 = param_1 + 1;
    } while (iVar1 < param_2);
  }
  return;
}

