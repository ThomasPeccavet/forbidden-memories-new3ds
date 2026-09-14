/* Analysis pseudo-C, not buildable source. */

void FUN_8002ef08(void)

{
  ushort uVar1;
  int iVar2;
  ushort *puVar3;
  
  iVar2 = FUN_8002e650();
  if (iVar2 == 0) {
    uVar1 = *DAT_8009c624;
    puVar3 = (ushort *)((int)DAT_8009c624 + 1);
    if ((uVar1 & 0x3f) == 0) {
      DAT_8009c624 = (ushort *)((int)DAT_8009c624 + 3);
      if ((uVar1 & 0x40) == 0) {
        FUN_8004022c(*puVar3);
      }
      else {
        FUN_80040204(*puVar3);
      }
    }
    else {
      DAT_8009c624 = puVar3;
      if ((uVar1 & 1) != 0) {
        FUN_8004022c(DAT_8009c780);
      }
      if ((uVar1 & 2) != 0) {
        DAT_8009c780 = (uint)*DAT_8009c624;
        DAT_8009c624 = DAT_8009c624 + 1;
      }
      if ((uVar1 & 4) != 0) {
        DAT_8009c780 = DAT_8009c788;
      }
    }
    if ((uVar1 & 0x80) != 0) {
      return;
    }
  }
  else if ((DAT_8009c460 & 0x2000030) != 0 || DAT_8009c484 != 0) {
    return;
  }
  DAT_8009c610 = 0;
  return;
}

