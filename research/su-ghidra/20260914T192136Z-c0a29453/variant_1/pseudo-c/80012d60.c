/* Analysis pseudo-C, not buildable source. */

void FUN_80012d60(void)

{
  byte *pbVar1;
  uint *puVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  
  if (DAT_8009c44a == '\0') {
    DAT_800ff3e8 = DAT_8009c434;
    DAT_800ff3e6 = DAT_8009c456;
    DAT_800ff3e9 = DAT_8009c4bb;
    DAT_800ff3ea = DAT_8009c4ba;
    DAT_800ff3eb = DAT_8009c4b9;
    FUN_80085488();
    if ((DAT_8009c440 & 0x2000) != 0) {
      FUN_80080494(&DAT_8009c8a8);
    }
  }
  FUN_8007f8e8(1);
  if ((((DAT_8009c6a0 & 0x80) == 0) || (FUN_80035eb0(), (DAT_8009c6a0 & 0x80) == 0)) &&
     (DAT_8009c4b8 != 0)) {
    FUN_80085d98((int)DAT_8009c414 + 0x5124,(int)DAT_8009c414 + 0x5110);
    if ((DAT_8009c4b8 & 0x80) == 0) {
      FUN_80085d98((int)DAT_8009c414 + 0x5138,(int)DAT_8009c414 + 0x5110);
      FUN_80085d98((int)DAT_8009c414 + 0x514c,(int)DAT_8009c414 + 0x5110);
    }
    FUN_80085d08((int)DAT_8009c414 + 0x5110);
  }
  iVar4 = 3;
  DAT_8009c332 = FUN_800852a8();
  DAT_8009c414 = &DAT_800e0eb0 + (uint)DAT_8009c332 * 0x5160;
  iVar5 = 0x514c;
  DAT_8009c455 = DAT_8009c332;
  FUN_80086248((uint)DAT_8009c332 * 140000 + -0x7ff63710);
  puVar3 = &DAT_8009c864;
  do {
    pbVar1 = &DAT_8009c430 + iVar4;
    iVar4 = iVar4 + -1;
    puVar2 = (uint *)(DAT_8009c414 + iVar5);
    *puVar3 = puVar2;
    puVar3 = puVar3 + -1;
    iVar5 = iVar5 + -0x14;
    *puVar2 = (uint)*pbVar1;
    FUN_80085d38(0,0);
  } while (-1 < iVar4);
  return;
}

