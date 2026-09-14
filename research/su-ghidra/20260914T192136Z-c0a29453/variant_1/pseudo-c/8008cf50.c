/* Analysis pseudo-C, not buildable source. */

void FUN_8008cf50(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = FUN_8008d150();
  if (iVar3 == 0) {
    FUN_8008d0e4();
    iVar3 = FUN_8008d150();
    uVar2 = DAT_800ff6d4;
    uVar1 = DAT_800ff6d0;
    if (iVar3 != 0) {
      DAT_800ff6d8 = 1;
      DAT_800ff6c0 = DAT_800ff6d0;
      DAT_800ff6c4 = DAT_800ff6d4;
      DAT_800ff6d0 = 0;
      DAT_800ff6d4 = 0;
      if (DAT_800ff714 != (code *)0x0) {
        (*DAT_800ff714)(uVar1,uVar2);
      }
    }
  }
  DAT_800ff720 = DAT_800ff720 + 1;
  DAT_800ff724 = DAT_800ff724 + 1;
  return;
}

