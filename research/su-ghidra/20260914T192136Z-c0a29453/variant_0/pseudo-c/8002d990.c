/* Analysis pseudo-C, not buildable source. */

void seed_8002d990(void)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  
  if ((DAT_8009c60a & 0x40) == 0) {
    DAT_8009c60a = DAT_8009c60a | 0x40;
    FUN_80032754();
    FUN_8004022c(0x72d0);
    FUN_801820c0();
    DAT_8009c60b = '\x01';
    iVar2 = FUN_800361d8(0,0xb,0x18,0x28,0x110,0xa0,0x40);
    *(undefined1 *)(iVar2 + 0x59) = 0x10;
    FUN_800399f0();
    uVar3 = FUN_80040350();
    iVar2 = FUN_800403d0(uVar3,2);
    FUN_80040800(iVar2,0,0,0,4,0xb,0xc,0x208);
    *(ushort *)(iVar2 + 8) = *(ushort *)(iVar2 + 8) | 0x20;
    *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x40000000;
    FUN_80042c48(iVar2);
    FUN_80042c1c(iVar2,0xf);
    DAT_800eb370 = iVar2;
    FUN_8001591c();
  }
  iVar2 = DAT_800eb370;
  if (DAT_8009c60b == '\x01') {
    if (((DAT_8009c72c | DAT_8009c72e) & 0xe0) != 0) {
      FUN_80040204(0x1e);
      FUN_800434a8(iVar2);
      *(undefined2 *)(iVar2 + 0x60) = 0x400;
      DAT_8009c60b = '\x02';
    }
  }
  else if (DAT_8009c60b == '\x02') {
    sVar1 = *(short *)(DAT_800eb370 + 0x60) + -0x20;
    *(short *)(DAT_800eb370 + 0x60) = sVar1;
    FUN_80043560(iVar2,0,0x100,(int)sVar1);
    FUN_80039910(&DAT_800f0850,*(short *)(iVar2 + 0x30) + 0x18,*(short *)(iVar2 + 0x32) + 0x28);
    if (*(short *)(iVar2 + 0x60) < 1) {
      DAT_8009c60b = '\0';
      FUN_800360d8(&DAT_800f0850);
      FUN_80040690(DAT_800eb370);
      DAT_800eb370 = 0;
    }
  }
  else {
    iVar2 = FUN_800289a4();
    if ((iVar2 == 0) && (iVar2 = FUN_80182408(), iVar2 != 0)) {
      FUN_80040258();
      FUN_80015a1c();
      FUN_80184210();
      DAT_8009c60a = DAT_8009c60d;
    }
  }
  return;
}

