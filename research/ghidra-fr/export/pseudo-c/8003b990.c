/* Analysis pseudo-C, not buildable source. */

void FUN_8003b990(void)

{
  ushort uVar1;
  byte *pbVar2;
  ushort *puVar3;
  int iVar4;
  
  pbVar2 = &DAT_801bf870;
  uVar1 = (ushort)DAT_801bf870;
  iVar4 = 0;
  if (uVar1 != 0xff) {
    puVar3 = &DAT_800ec290;
    do {
      if (0xef < uVar1) {
        pbVar2 = pbVar2 + 1;
        uVar1 = (uVar1 & 0xf) << 8 | (ushort)*pbVar2;
      }
      pbVar2 = pbVar2 + 1;
      *puVar3 = uVar1;
      iVar4 = iVar4 + 1;
      puVar3 = puVar3 + 1;
    } while ((iVar4 < 10) && (uVar1 = (ushort)*pbVar2, uVar1 != 0xff));
  }
  return;
}

