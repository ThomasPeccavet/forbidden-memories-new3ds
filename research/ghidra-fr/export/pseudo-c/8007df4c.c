/* Analysis pseudo-C, not buildable source. */

int FUN_8007df4c(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  
  iVar2 = 0;
  puVar4 = &DAT_800f7924;
  iVar3 = 0;
  while( true ) {
    if (*(int *)((int)&DAT_800f791c + iVar3) == 0) {
      return -1;
    }
    if ((*(int *)((int)&DAT_800f791c + iVar3) == param_1) &&
       (iVar1 = FUN_8008f7f8(param_2,puVar4), iVar1 == 0)) break;
    puVar4 = puVar4 + 0x2c;
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + 0x2c;
    if (0x7f < iVar2) {
      return -1;
    }
  }
  return iVar2 + 1;
}

