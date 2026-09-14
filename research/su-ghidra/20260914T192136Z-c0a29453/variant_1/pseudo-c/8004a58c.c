/* Analysis pseudo-C, not buildable source. */

void FUN_8004a58c(int param_1,int param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  if (*(char *)(DAT_8009c7d8 + 0x815) == '\0') {
    uVar4 = ((uint)*(byte *)(DAT_8009c7d8 + 0x4bf) + (uint)*(byte *)(param_1 + 10) +
             (uint)*(byte *)(param_1 + 0xb) + (uint)*(byte *)(param_2 + 1)) - 0xc0;
  }
  else {
    uVar4 = 0x40;
  }
  uVar5 = uVar4;
  if ((int)uVar4 < 0) {
    uVar5 = 0;
  }
  if (0x7f < (int)uVar4) {
    uVar5 = 0x7f;
  }
  *(char *)(param_1 + 0xc) = (char)uVar5;
  iVar2 = (int)(((int)((uint)*(byte *)(DAT_8009c7d8 + 0x4bc) *
                       (uint)*(ushort *)(DAT_8009c7d8 + 0x512) * (uint)*(byte *)(param_2 + 5) *
                      (uint)*(byte *)(param_2 + 3)) >> 0xe) * (uint)*(byte *)(param_1 + 8) *
               (uint)*(byte *)(param_1 + 9)) >> 0xe;
  if ((int)uVar5 < 0x40) {
    iVar3 = (int)(uVar5 * iVar2 * 2) >> 7;
  }
  else {
    iVar3 = iVar2;
    if (uVar5 != 0x40) {
      iVar2 = (int)((0x40 - (uVar5 & 0x3f)) * iVar2 * 2) >> 7;
    }
  }
  sVar1 = *(short *)(DAT_8009c7d8 + 0x7e6);
  *(short *)(param_1 + 0x14) =
       (short)((int)((iVar2 * *(short *)(DAT_8009c7d8 + 0x7e4) >> 7) *
                    (*(byte *)(param_1 + 0xe) & 0x7f)) >> 7);
  *(short *)(param_1 + 0x16) =
       (short)((int)((iVar3 * sVar1 >> 7) * (*(byte *)(param_1 + 0xe) & 0x7f)) >> 7);
  return;
}

