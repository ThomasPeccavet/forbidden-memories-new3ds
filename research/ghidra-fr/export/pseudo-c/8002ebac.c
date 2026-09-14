/* Analysis pseudo-C, not buildable source. */

void FUN_8002ebac(void)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  
  uVar1 = *DAT_8009c624;
  if ((uVar1 & 0x4000) == 0) {
    uVar2 = DAT_8009c624[1];
    DAT_8009c624 = DAT_8009c624 + 2;
    iVar3 = FUN_8002ce7c(uVar1);
    if (iVar3 != 0) {
      DAT_8009c624 = (ushort *)((int)&DAT_801a8000 + (uint)uVar2);
    }
  }
  else {
    DAT_8009c624 = DAT_8009c624 + 1;
    FUN_8002ceb8(uVar1 & 0xbfff);
  }
  DAT_8009c610 = 0;
  return;
}

