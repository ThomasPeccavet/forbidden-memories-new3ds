/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8008288c(int param_1)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = 0;
  uVar2 = *DAT_80095bf8;
  while( true ) {
    if ((uVar2 & 0x4000000) != 0) {
      return 0;
    }
    bVar1 = param_1 < iVar3;
    iVar3 = iVar3 + 1;
    if (bVar1) break;
    uVar2 = *DAT_80095bf8;
  }
  return 0xffffffff;
}

