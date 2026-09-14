/* Analysis pseudo-C, not buildable source. */

void FUN_80075154(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  uVar3 = *DAT_80093ef8 >> 0x18 & 0x7f;
  if (uVar3 != 0) {
    do {
      puVar4 = &DAT_80093efc;
      for (iVar1 = 0; (uVar3 != 0 && (iVar1 < 7)); iVar1 = iVar1 + 1) {
        if ((uVar3 & 1) != 0) {
          *DAT_80093ef8 = *DAT_80093ef8 & (1 << (iVar1 + 0x18U & 0x1f) | 0xffffffU);
          if ((code *)*puVar4 != (code *)0x0) {
            (*(code *)*puVar4)();
          }
        }
        puVar4 = puVar4 + 1;
        uVar3 = uVar3 >> 1;
      }
      uVar3 = *DAT_80093ef8 >> 0x18 & 0x7f;
    } while (uVar3 != 0);
  }
  if (((*DAT_80093ef8 & 0xff000000) == 0x80000000) || ((*DAT_80093ef8 & 0x8000) != 0)) {
    FUN_8008fa78(s_DMA_bus_error__code__08x_8001193c,*DAT_80093ef8);
    iVar1 = 0;
    do {
      iVar2 = iVar1 + 1;
      FUN_8008fa78(s_MADR__d___08x_80011958,iVar1,*(undefined4 *)(iVar1 * 0x10 + DAT_80093f1c));
      iVar1 = iVar2;
    } while (iVar2 < 7);
  }
  return;
}

