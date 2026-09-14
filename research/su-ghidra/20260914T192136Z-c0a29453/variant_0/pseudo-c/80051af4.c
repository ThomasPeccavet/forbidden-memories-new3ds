/* Analysis pseudo-C, not buildable source. */

/* WARNING: Removing unreachable block (ram,0x80051bd4) */
/* WARNING: Removing unreachable block (ram,0x80051be4) */
/* WARNING: Removing unreachable block (ram,0x80051bec) */

void FUN_80051af4(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (DAT_800f6bd7 != '\0') {
    if (PTR_DAT_8009c318[0xa0] == '\x01') {
      iVar1 = FUN_800746b8(0xffffffff);
      if (iVar1 < 0) {
        iVar1 = iVar1 + 7;
      }
      uVar3 = 0x1c0;
      DAT_8009c7ea = 0x1c0;
      DAT_8009c7ec = 0x10;
      DAT_8009c7ee = 0x40;
      DAT_8009c7e8 = ((short)(iVar1 >> 3) + (short)((iVar1 >> 3) / 3) * -3) * 0x10 + 0x2d0;
      uVar2 = 0x2c0;
    }
    else {
      if (PTR_DAT_8009c318[0xa0] != '\x04') {
        return;
      }
      iVar1 = FUN_800746b8(0xffffffff);
      uVar2 = 0x220;
      uVar3 = 0x168;
      DAT_8009c7e8 = 0x260;
      DAT_8009c7ec = 0x20;
      DAT_8009c7ee = 0x18;
      DAT_8009c7ea = (ushort)(byte)(&DAT_800929cc)[(iVar1 / 10) % 8] * 0x18 + 0x180;
    }
    FUN_8007ffd0(&DAT_8009c7e8,uVar2,uVar3);
  }
  return;
}

