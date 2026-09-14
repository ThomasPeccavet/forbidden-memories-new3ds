/* Analysis pseudo-C, not buildable source. */

void FUN_8002fc24(void)

{
  ushort uVar1;
  int iVar2;
  
  uVar1 = *DAT_8009c624;
  DAT_8009c624 = DAT_8009c624 + 1;
  iVar2 = FUN_8002f0f0();
  if (iVar2 == 0) {
    DAT_8009c624 = (ushort *)((int)&DAT_801a8000 + (uint)uVar1);
  }
  DAT_8009c610 = 0;
  return;
}

