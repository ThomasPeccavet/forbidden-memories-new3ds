/* Analysis pseudo-C, not buildable source. */

void FUN_8002ff64(undefined2 param_1)

{
  short sVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined *puVar4;
  
  puVar2 = &DAT_800ec220;
  DAT_8009c4c2 = 0;
  DAT_8009c4c0 = 0;
  DAT_8009c614 = 0;
  DAT_8009c628 = param_1;
  FUN_80014d38(0,0,0x23c9,0x2d,FUN_8002fdc8,0,0);
  iVar3 = 0;
  FUN_8003a22c();
  DAT_800ec25c = 0xffff;
  do {
    *puVar2 = 0;
    *(undefined2 *)(puVar2 + 1) = 0;
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 5;
  } while (iVar3 < 3);
  FUN_80013700();
  do {
    iVar3 = FUN_8008288c(10);
  } while (iVar3 != 0);
  iVar3 = 0;
  DAT_8009c838 = 0x380;
  DAT_8009c83c = 0x18;
  DAT_8009c840 = 0x380;
  DAT_8009c83e = 0x30;
  DAT_8009c83a = 0;
  DAT_8009c842 = 0xf0;
  DAT_8009c844 = 0x40;
  DAT_8009c846 = 1;
  puVar4 = PTR_FUN_80010000;
  do {
    FUN_80082380(&DAT_8009c838,puVar4);
    FUN_80082380(&DAT_8009c840,puVar4 + 0x900);
    iVar3 = iVar3 + 1;
    DAT_8009c842 = DAT_8009c842 + 1;
    sVar1 = (short)(iVar3 / 5);
    DAT_8009c838 = ((short)iVar3 + sVar1 * -5) * 0x18 + 0x380;
    DAT_8009c83a = sVar1 * 0x30;
    if (0xff < DAT_8009c842) {
      DAT_8009c842 = 0xf0;
      DAT_8009c840 = DAT_8009c840 + 0x40;
    }
    puVar4 = puVar4 + 0x980;
  } while (iVar3 < 0x19);
  DAT_8009c614 = FUN_8002e698();
  return;
}

