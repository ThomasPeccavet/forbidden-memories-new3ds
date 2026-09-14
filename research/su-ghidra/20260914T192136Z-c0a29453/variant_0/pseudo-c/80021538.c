/* Analysis pseudo-C, not buildable source. */

void FUN_80021538(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  
  FUN_80040734(*DAT_8009c508,param_1);
  iVar3 = 0;
  puVar4 = DAT_8009c508;
  if (param_1 == 0) {
    do {
      iVar2 = puVar4[1];
      if (iVar2 == 0) break;
      iVar3 = iVar3 + 1;
      *(ushort *)(iVar2 + 8) = *(ushort *)(iVar2 + 8) | 0x40;
      puVar4 = puVar4 + 1;
    } while (iVar3 < 10);
  }
  else {
    do {
      iVar2 = puVar4[1];
      if (iVar2 == 0) break;
      iVar3 = iVar3 + 1;
      *(ushort *)(iVar2 + 8) = *(ushort *)(iVar2 + 8) & 0xffbf;
      puVar4 = puVar4 + 1;
    } while (iVar3 < 10);
  }
  uVar1 = FUN_80036184(0,*(undefined1 *)((int)DAT_8009c508 + param_1 + 0x34),0x1a,0x38,0x120,0xf0);
  FUN_800399f0(uVar1);
  return;
}

