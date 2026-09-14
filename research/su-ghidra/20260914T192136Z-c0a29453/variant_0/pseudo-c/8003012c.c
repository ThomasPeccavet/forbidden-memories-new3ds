/* Analysis pseudo-C, not buildable source. */

void FUN_8003012c(int param_1,int param_2)

{
  int iVar1;
  char cVar2;
  int iVar3;
  
  if ((*(ushort *)(param_1 + 4) & 0x8000) == 0) {
    *(ushort *)(param_1 + 4) = *(ushort *)(param_1 + 4) | 0x8000;
    *(undefined2 *)(param_1 + 6) = 0;
  }
  *(ushort *)(param_1 + 6) = *(short *)(param_1 + 6) + 0x20U & 0xfff;
  iVar3 = FUN_80086628();
  iVar3 = iVar3 * 0x18;
  if (iVar3 < 0) {
    iVar3 = iVar3 + 0xfff;
  }
  iVar3 = iVar3 >> 0xc;
  if (iVar3 == 0) {
    iVar3 = 1;
  }
  cVar2 = (char)iVar3 + -0x68;
  if (iVar3 == 0x18) {
    iVar3 = 0x17;
    cVar2 = -0x51;
  }
  *(char *)(param_2 + 0xe) = cVar2;
  *(char *)(param_2 + 0xd) = cVar2;
  *(char *)(param_2 + 0xc) = cVar2;
  iVar1 = DAT_800ec220;
  if (DAT_800ec220 != 0) {
    cVar2 = (char)((iVar3 + 0x18) / 2) + -0x80;
    *(char *)(DAT_800ec220 + 0xe) = cVar2;
    *(char *)(iVar1 + 0xd) = cVar2;
    *(char *)(iVar1 + 0xc) = cVar2;
  }
  iVar1 = DAT_800ec234;
  if (DAT_800ec234 != 0) {
    cVar2 = (char)((iVar3 + 0x18) / 2) + -0x80;
    *(char *)(DAT_800ec234 + 0xe) = cVar2;
    *(char *)(iVar1 + 0xd) = cVar2;
    *(char *)(iVar1 + 0xc) = cVar2;
  }
  return;
}

