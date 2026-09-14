/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_800208e8(void)

{
  undefined4 uVar1;
  int iVar2;
  byte bVar3;
  
  iVar2 = DAT_8009c5b8;
  if ((DAT_8009c560 & 0x80) == 0) {
    DAT_8009c560 = DAT_8009c560 | 0x80;
    uVar1 = FUN_80040350();
    iVar2 = FUN_800403d0(uVar1,2);
    FUN_80040800(iVar2,*(short *)(DAT_8009c5b8 + 0x30) + -8,*(short *)(DAT_8009c5b8 + 0x32) + 0x1e,3
                 ,1,2,0xb,0x20c);
    FUN_80042c48(iVar2);
    FUN_80042c1c(iVar2,10);
    *(ushort *)(iVar2 + 8) = *(ushort *)(iVar2 + 8) | 0x28;
    DAT_8009c548 = iVar2;
    uVar1 = FUN_80040350();
    iVar2 = FUN_800403d0(uVar1,2);
    FUN_80040800(iVar2,*(short *)(DAT_8009c5b8 + 0x30) + 0x3c,*(short *)(DAT_8009c5b8 + 0x32) + 0x1e
                 ,3,1,0,0xb,0x20c);
    FUN_80042c48(iVar2);
    FUN_80042c1c(iVar2,10);
    *(ushort *)(iVar2 + 8) = *(ushort *)(iVar2 + 8) | 0x28;
    uVar1 = 0;
    DAT_8009c54c = iVar2;
  }
  else if ((DAT_8009c560 & 0x40) == 0) {
    if ((DAT_8009c728 & 0xa000) == 0) {
      uVar1 = 0;
      if ((DAT_8009c72c & 0xe0) != 0) {
        FUN_80040690(DAT_8009c548);
        FUN_80040690(DAT_8009c54c);
        uVar1 = 0xffffffff;
        if (((DAT_8009c72c & 0x20) == 0) && (uVar1 = 1, *(char *)(iVar2 + 0x21) != '\0')) {
          uVar1 = 2;
        }
      }
    }
    else {
      *(undefined2 *)(DAT_8009c5b8 + 0x60) = 0x10;
      if ((DAT_8009c728 & 0x2000) != 0) {
        *(undefined2 *)(iVar2 + 0x60) = 0xfff0;
      }
      DAT_8009c560 = DAT_8009c560 | 0x40;
      uVar1 = 0;
    }
  }
  else {
    bVar3 = *(char *)(DAT_8009c5b8 + 0x21) + *(char *)(DAT_8009c5b8 + 0x60);
    *(ushort *)(DAT_8009c5b8 + 8) = *(ushort *)(DAT_8009c5b8 + 8) | 4;
    *(byte *)(iVar2 + 0x21) = bVar3;
    if ((bVar3 & 0x7f) == 0) {
      if (bVar3 == 0) {
        *(ushort *)(iVar2 + 8) = *(ushort *)(iVar2 + 8) & 0xfffb;
      }
      DAT_8009c560 = DAT_8009c560 & 0xbf;
      uVar1 = 0;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}

