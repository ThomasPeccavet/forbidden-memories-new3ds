/* Analysis pseudo-C, not buildable source. */

void FUN_8003868c(int param_1)

{
  byte bVar1;
  undefined2 uVar2;
  byte *pbVar3;
  uint uVar4;
  undefined4 *puVar5;
  
  puVar5 = (undefined4 *)(param_1 + *(char *)(param_1 + 0x58) * 4);
  pbVar3 = (byte *)*puVar5;
  bVar1 = *pbVar3;
  *puVar5 = pbVar3 + 1;
  if ((bVar1 & 0x3f) == 0) {
    if ((bVar1 & 1) != 0) {
      FUN_8004022c(DAT_8009c780);
    }
    if ((bVar1 & 2) != 0) {
      uVar4 = FUN_80036dfc(param_1);
      DAT_8009c780 = uVar4 & 0xffff;
    }
    if ((bVar1 & 4) != 0) {
      DAT_8009c780 = DAT_8009c788;
    }
  }
  else {
    uVar2 = FUN_80036dfc(param_1);
    FUN_8004022c(uVar2);
  }
  if ((bVar1 & 0x80) != 0) {
    *(undefined1 *)(param_1 + 0x51) = 0xc;
    DAT_8009c6cc = 1;
  }
  return;
}

