/* Analysis pseudo-C, not buildable source. */

void FUN_80074b44(void)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  
  if (DAT_80092e20 == 0) {
    FUN_8008fa78(s_unexpected_interrupt__04x__80011900,*DAT_80093eac);
    FUN_80074fb8();
  }
  DAT_80092e22 = 1;
  uVar2 = (uint)(*DAT_80093eb0 & DAT_80092e50 & *DAT_80093eac);
  if (uVar2 != 0) {
    do {
      puVar5 = &DAT_80092e24;
      for (uVar4 = 0; (uVar2 != 0 && ((int)uVar4 < 0xb)); uVar4 = uVar4 + 1) {
        if ((uVar2 & 1) != 0) {
          *DAT_80093eac = ~(ushort)(1 << (uVar4 & 0x1f));
          if ((code *)*puVar5 != (code *)0x0) {
            (*(code *)*puVar5)();
          }
        }
        puVar5 = puVar5 + 1;
        uVar2 = uVar2 >> 1;
      }
      uVar2 = (uint)(*DAT_80093eb0 & DAT_80092e50 & *DAT_80093eac);
    } while (uVar2 != 0);
  }
  if ((*DAT_80093eac & *DAT_80093eb0) == 0) {
    DAT_80093eb8 = 0;
  }
  else {
    iVar3 = DAT_80093eb8 + 1;
    bVar1 = 0x800 < DAT_80093eb8;
    DAT_80093eb8 = iVar3;
    if (bVar1) {
      FUN_8008fa78(s_intr_timeout__04x__04x__8001191c,*DAT_80093eac,*DAT_80093eb0);
      DAT_80093eb8 = 0;
      *DAT_80093eac = 0;
    }
  }
  DAT_80092e22 = 0;
  FUN_80074fb8();
  return;
}

