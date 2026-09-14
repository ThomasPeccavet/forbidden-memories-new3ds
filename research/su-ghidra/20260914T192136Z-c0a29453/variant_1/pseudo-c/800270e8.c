/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_800270e8(void)

{
  int iVar1;
  undefined4 uVar2;
  int local_20 [6];
  
  iVar1 = FUN_80026da0(local_20,0,0x15);
  uVar2 = 1;
  if (iVar1 != 0) {
    iVar1 = FUN_80026c94(10);
    if (iVar1 < 0) {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
      DAT_800ec218 = 1;
      DAT_800ec211 = 0;
      DAT_800ec217 = 0;
      DAT_800ec216 = (char)iVar1 + (char)(iVar1 / 5) * -5 + '\x06';
      DAT_800ec210 = *(char *)(local_20[0] + 0x18) % '\x05' + '\v';
    }
  }
  return uVar2;
}

