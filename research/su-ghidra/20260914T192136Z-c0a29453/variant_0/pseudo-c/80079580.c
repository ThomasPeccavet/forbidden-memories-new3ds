/* Analysis pseudo-C, not buildable source. */

void FUN_80079580(uint param_1,undefined4 param_2,int param_3,uint param_4,undefined4 param_5,
                 char param_6)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  iVar4 = param_1 * 0x10;
  uVar2 = *(uint *)(&DAT_1f801088 + iVar4);
  do {
    if ((uVar2 & 0x1000000) == 0) {
LAB_800795fc:
      if (param_6 == '\x01') {
        bVar1 = *(byte *)(DAT_800948d4 + 2) | (byte)(1 << (param_1 & 0x1f));
      }
      else {
        bVar1 = *(byte *)(DAT_800948d4 + 2) & ~(byte)(1 << (param_1 & 0x1f));
      }
      *(byte *)(DAT_800948d4 + 2) = bVar1;
      iVar3 = param_1 * 0x10;
      *DAT_800948d0 = *DAT_800948d0 | 1 << (param_1 * 4 + 3 & 0x1f);
      *(undefined4 *)(&DAT_1f801080 + iVar3) = param_2;
      *(uint *)(&DAT_1f801084 + iVar3) = param_3 << 0x10 | param_4;
      bVar1 = *DAT_800948b8;
      while ((bVar1 & 0x40) == 0) {
        bVar1 = *DAT_800948b8;
      }
      *(undefined4 *)(&DAT_1f801088 + iVar3) = param_5;
      return;
    }
    if (iVar3 == 0x10000) {
      FUN_8008fa78(s_DMA_STATUS_ERROR__x_80011a6c,*(undefined4 *)(&DAT_1f801088 + iVar4));
      goto LAB_800795fc;
    }
    uVar2 = *(uint *)(&DAT_1f801088 + iVar4);
    iVar3 = iVar3 + 1;
  } while( true );
}

