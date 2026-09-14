/* Analysis pseudo-C, not buildable source. */

void FUN_8002e60c(int param_1)

{
  undefined *puVar1;
  int iVar2;
  
  iVar2 = 2;
  puVar1 = &DAT_800ec340;
  do {
    iVar2 = iVar2 + -1;
    if (-1 < (char)puVar1[0x30]) {
      *(ushort *)(param_1 + 0x34) = *(ushort *)(param_1 + 0x34) | 4;
      return;
    }
    puVar1 = puVar1 + -0x4c;
  } while (-1 < iVar2);
  return;
}

