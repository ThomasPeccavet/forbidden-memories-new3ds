/* Analysis pseudo-C, not buildable source. */

int FUN_8006a354(void)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  short local_68;
  short local_66;
  
  if (DAT_8009c3eb == '\0') {
    if (DAT_8009c3ec != '\0') {
      uVar2 = DAT_8009c3ed - 0x40;
      if (DAT_8009c3ed == 0) goto LAB_8006a388;
      if ((int)uVar2 < 0) {
        uVar2 = 0;
      }
      DAT_8009c3ed = (byte)uVar2;
      FUN_80045414(uVar2 & 0xff);
    }
    DAT_8009c3ea = 0;
    FUN_80080460(&local_68);
    iVar3 = DAT_8009c818;
    cVar1 = DAT_8009c3e8;
    if (DAT_8009c3e8 == '\0') {
      iVar4 = 0x140;
    }
    else {
      iVar4 = 0x1e0;
    }
    local_68 = local_68 + (short)((iVar4 - *(short *)(DAT_8009c818 + 0x43024)) / 2);
    uVar2 = (uint)DAT_8009c3ee;
    *(short *)(DAT_8009c818 + 0x43028) = local_68;
    *(short *)(iVar3 + 0x43020) = local_68;
    iVar3 = DAT_8009c818;
    iVar4 = DAT_8009c818 + uVar2 * 0xe000 + 0x1b000;
    local_66 = local_66 + (short)((0x100 - *(short *)(DAT_8009c818 + 0x43026)) / 2);
    *(short *)(DAT_8009c818 + 0x4302a) = local_66;
    *(short *)(iVar3 + 0x43022) = local_66;
    FUN_80090f40(iVar4,cVar1);
    FUN_80090fbc(DAT_8009c818 + (uint)DAT_8009c3ef * 0x3000 + 0x37000,
                 ((int)*(short *)(DAT_8009c818 + 0x4302c) * (int)*(short *)(DAT_8009c818 + 0x4302e))
                 / 2);
    iVar3 = FUN_8006a4d8(1);
    if (iVar3 == 0) {
      FUN_8006aad0();
      iVar3 = 0;
    }
  }
  else {
LAB_8006a388:
    iVar3 = 1;
  }
  return iVar3;
}

