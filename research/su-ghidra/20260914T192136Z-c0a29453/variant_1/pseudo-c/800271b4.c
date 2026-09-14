/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_800271b4(void)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  int local_28 [6];
  
  iVar2 = FUN_80026da0(local_28,0,0x14);
  if (iVar2 == 0) {
    uVar3 = 1;
  }
  else {
    DAT_800ec211 = 0;
    DAT_800ec217 = 0;
    DAT_800ec218 = 0;
    DAT_800ec216 = '\x06';
    DAT_800ec210 = *(char *)(local_28[0] + 0x18) % '\x05' + '\v';
    iVar2 = FUN_80026c94(10);
    if (-1 < iVar2) {
      bVar1 = FUN_8008f708();
      DAT_800ec218 = bVar1 & 1;
      DAT_800ec216 = DAT_800ec216 + (char)iVar2 + (char)(iVar2 / 5) * -5;
    }
    uVar3 = 0;
  }
  return uVar3;
}

