/* Analysis pseudo-C, not buildable source. */

void FUN_80083f38(int *param_1,undefined4 param_2,undefined2 param_3)

{
  undefined1 uVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = DAT_800ff5c4;
  iVar5 = *param_1;
  if (-1 < iVar5) {
    *(uint *)(DAT_800ff5c4 + 4) = iVar5 >> 0x17 & 0x60U | 0xe1000200;
    *(char *)(iVar4 + 8) = (char)param_1[3];
    *(undefined1 *)(iVar4 + 9) = *(undefined1 *)((int)param_1 + 0xd);
    uVar1 = *(undefined1 *)((int)param_1 + 0xe);
    *(byte *)(iVar4 + 0xb) = (byte)(iVar5 >> 0x1d) & 2 | 0x40;
    *(undefined1 *)(iVar4 + 10) = uVar1;
    sVar3 = DAT_800ff446;
    sVar2 = DAT_800ff444;
    *(short *)(iVar4 + 0xc) = (short)param_1[1] + DAT_800ff444;
    *(short *)(iVar4 + 0xe) = *(short *)((int)param_1 + 6) + sVar3;
    *(short *)(iVar4 + 0x10) = (short)param_1[2] + sVar2;
    *(short *)(iVar4 + 0x12) = *(short *)((int)param_1 + 10) + sVar3;
    DAT_800ff5c4 = FUN_80084018(iVar4,param_2,param_3,4);
  }
  return;
}

