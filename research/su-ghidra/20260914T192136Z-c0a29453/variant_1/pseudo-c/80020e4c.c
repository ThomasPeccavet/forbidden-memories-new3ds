/* Analysis pseudo-C, not buildable source. */

void FUN_80020e4c(int param_1)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = FUN_80042ec8();
  if (iVar2 == 0) {
    *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) | 4;
  }
  bVar1 = *(char *)(param_1 + 0x21) - 2;
  *(byte *)(param_1 + 0x21) = bVar1;
  if (bVar1 < 0xc0) {
    FUN_80040690(param_1);
  }
  return;
}

