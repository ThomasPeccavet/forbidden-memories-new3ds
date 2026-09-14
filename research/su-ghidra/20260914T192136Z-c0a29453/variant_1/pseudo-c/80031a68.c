/* Analysis pseudo-C, not buildable source. */

void FUN_80031a68(int param_1,undefined4 param_2,byte *param_3,uint param_4)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  
  iVar3 = 0;
  pbVar2 = param_3 + 1;
  *(undefined2 *)(param_1 + 0x12) = 0xfb;
  do {
    *(undefined4 *)(param_1 + 0x14) = 0x202020;
    if ((*pbVar2 & 0xf) == param_4) {
      *(undefined4 *)(param_1 + 0x14) = 0x808080;
    }
    iVar3 = iVar3 + 1;
    *(byte *)(param_1 + 0xe) = (*param_3 & 0xf) * '\b' + -0x80;
    *(byte *)(param_1 + 0xf) = *param_3 & 0xf0;
    bVar1 = *pbVar2;
    pbVar2 = pbVar2 + 2;
    *(ushort *)(param_1 + 0x10) = (bVar1 & 0xf0) + 0x280;
    FUN_80084978(param_1,param_2,0);
    *(short *)(param_1 + 4) = *(short *)(param_1 + 4) + 0x12;
    param_3 = param_3 + 2;
  } while (iVar3 < 7);
  return;
}

