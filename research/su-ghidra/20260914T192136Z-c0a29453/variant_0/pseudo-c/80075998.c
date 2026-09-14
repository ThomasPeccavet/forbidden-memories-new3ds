/* Analysis pseudo-C, not buildable source. */

void FUN_80075998(void)

{
  int iVar1;
  uint uVar2;
  
  if (DAT_80094008 == 0) {
    FUN_80076030();
  }
  iVar1 = DAT_80093fb8;
  *(ushort *)(DAT_80093fb8 + 0x1aa) = *(ushort *)(DAT_80093fb8 + 0x1aa) & 0xffcf;
  if ((*(ushort *)(iVar1 + 0x1aa) & 0x30) != 0) {
    uVar2 = 1;
    do {
      if (0xf00 < uVar2) break;
      uVar2 = uVar2 + 1;
    } while ((*(ushort *)(iVar1 + 0x1aa) & 0x30) != 0);
  }
  if (DAT_80093ff0 == (code *)0x0) {
    FUN_80076098(0xf0000009,0x20);
  }
  else {
    (*DAT_80093ff0)();
  }
  return;
}

