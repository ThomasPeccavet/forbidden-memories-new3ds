/* Analysis pseudo-C, not buildable source. */

void FUN_8004a3a0(undefined2 param_1,undefined2 param_2)

{
  short sVar1;
  int iVar2;
  
  iVar2 = DAT_8009c7d8;
  sVar1 = *(short *)(DAT_8009c7d8 + 0x7e2);
  *(undefined2 *)(DAT_8009c7d8 + 0x514) = param_1;
  *(undefined2 *)(iVar2 + 0x516) = param_2;
  if (sVar1 != 2) {
    FUN_8004a788();
  }
  return;
}

