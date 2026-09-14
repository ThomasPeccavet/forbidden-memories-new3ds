/* Analysis pseudo-C, not buildable source. */

void FUN_800841c8(int *param_1,undefined4 param_2,undefined2 param_3)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = DAT_800ff5c4;
  iVar3 = *param_1;
  if (-1 < iVar3) {
    *(uint *)(DAT_800ff5c4 + 4) = iVar3 >> 0x11 & 0x180U | iVar3 >> 0x17 & 0x60U | 0xe1000200;
    *(char *)(iVar2 + 8) = (char)param_1[3];
    *(undefined1 *)(iVar2 + 9) = *(undefined1 *)((int)param_1 + 0xd);
    uVar1 = *(undefined1 *)((int)param_1 + 0xe);
    *(byte *)(iVar2 + 0xb) = (byte)(iVar3 >> 0x1d) & 2 | 0x60;
    *(undefined1 *)(iVar2 + 10) = uVar1;
    *(short *)(iVar2 + 0xc) = (short)param_1[1] + DAT_800ff444;
    *(short *)(iVar2 + 0xe) = *(short *)((int)param_1 + 6) + DAT_800ff446;
    *(short *)(iVar2 + 0x10) = (short)param_1[2];
    *(undefined2 *)(iVar2 + 0x12) = *(undefined2 *)((int)param_1 + 10);
    DAT_800ff5c4 = FUN_80084018(iVar2,param_2,param_3,4);
  }
  return;
}

