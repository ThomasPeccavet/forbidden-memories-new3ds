/* Analysis pseudo-C, not buildable source. */

void FUN_80019598(void)

{
  int iVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  short sVar7;
  uint uVar8;
  
  iVar4 = DAT_800eb370;
  if ((DAT_8009c564 & 0x8000) == 0) {
    DAT_8009c564 = DAT_8009c564 | 0xc000;
    bVar2 = *(byte *)(DAT_800eb370 + 0x6a);
    iVar6 = (uint)bVar2 * 0x1c;
    DAT_8009c574 = *(short *)(&DAT_801a7ae4 + iVar6);
    FUN_800292dc(0,(int)*(short *)(&DAT_801a7ae4 + iVar6));
    if (*(char *)(iVar4 + 0x68) == '\x14') {
      *(char *)(DAT_8009c500 + 5) = *(char *)(DAT_8009c500 + 5) + '\x01';
    }
    FUN_800249d0(&DAT_801a7ad8 + (uint)bVar2 * 7);
    DAT_8009c585 = 1;
  }
  iVar1 = DAT_800eb374;
  iVar6 = DAT_800eb370;
  bVar2 = DAT_8009c585 & 0xf;
  if (bVar2 == 2) {
    FUN_80026c2c((int)DAT_8009c574,0);
    DAT_8009c585 = 3;
  }
  else if (bVar2 < 3) {
    if (bVar2 == 1) {
      if ((DAT_8009c585 & 0x80) == 0) {
        if ((DAT_8009c460 & 0x2000030) == 0 && DAT_8009c484 == 0) {
          DAT_8009c585 = DAT_8009c585 | 0x80;
          *(ushort *)(iVar4 + 8) = *(ushort *)(iVar4 + 8) | 4;
          iVar4 = FUN_80029354(0,0xffffffff,0xffffffff);
          *(undefined2 *)(iVar4 + 0x30) = 0x5a;
          *(undefined2 *)(iVar4 + 0x32) = 0xe;
          *(undefined1 *)(iVar4 + 0x21) = 0xc0;
          FUN_80042c1c(iVar4,0xfffffff6);
          *(ushort *)(iVar4 + 8) = *(ushort *)(iVar4 + 8) & 0xffbf | 4;
          DAT_800eb374 = iVar4;
        }
      }
      else if ((DAT_8009c585 & 0x40) == 0) {
        bVar2 = *(char *)(iVar4 + 0x21) + 6;
        *(byte *)(iVar4 + 0x21) = bVar2;
        if (0x3f < bVar2) {
          DAT_8009c585 = DAT_8009c585 | 0x40;
          FUN_80040690(iVar4);
          DAT_800eb370 = 0;
          *(ushort *)(DAT_800eb374 + 8) = *(ushort *)(DAT_800eb374 + 8) | 0x40;
        }
      }
      else if ((DAT_8009c585 & 0x20) == 0) {
        bVar2 = *(char *)(DAT_800eb374 + 0x21) + 6;
        *(byte *)(DAT_800eb374 + 0x21) = bVar2;
        if (-1 < (int)((uint)bVar2 << 0x18)) {
          *(undefined2 *)(iVar1 + 0x60) = 0x1e;
          *(undefined1 *)(iVar1 + 0x21) = 0;
          DAT_8009c585 = DAT_8009c585 | 0x20;
          *(ushort *)(iVar1 + 8) = *(ushort *)(iVar1 + 8) & 0xfffb;
        }
      }
      else {
        uVar3 = *(short *)(DAT_800eb374 + 0x60) - 1;
        *(ushort *)(DAT_800eb374 + 0x60) = uVar3;
        if ((int)((uint)uVar3 << 0x10) < 1) {
          DAT_8009c585 = 2;
        }
      }
    }
  }
  else if (bVar2 == 3) {
    if ((DAT_8009c585 & 0x80) == 0) {
      DAT_8009c585 = DAT_8009c585 | 0x80;
      FUN_800193dc(DAT_800eb374);
      DAT_800eb370 = FUN_800194f4(iVar1);
      *(uint *)(DAT_800eb370 + 4) = *(uint *)(DAT_800eb370 + 4) | 0x50000000;
      *(uint *)(DAT_800eb370 + 4) = *(uint *)(DAT_800eb370 + 4) & 0xf7ffffff;
      DAT_800eb374 = FUN_800194f4(iVar1);
      FUN_80042c1c(DAT_800eb374,0xffffffff);
      *(uint *)(DAT_800eb374 + 4) = *(uint *)(DAT_800eb374 + 4) | 0x60000000;
      *(uint *)(DAT_800eb374 + 4) = *(uint *)(DAT_800eb374 + 4) & 0xf7ffffff;
      FUN_800296c0(0);
    }
    else {
      sVar7 = *(short *)(DAT_800eb370 + 0x44) + 0x80;
      *(short *)(DAT_800eb374 + 0x46) = sVar7;
      *(short *)(iVar1 + 0x44) = sVar7;
      *(short *)(iVar6 + 0x46) = sVar7;
      *(short *)(iVar6 + 0x44) = sVar7;
      uVar8 = *(byte *)(DAT_800eb370 + 0xc) - 4;
      uVar5 = uVar8 * 0x10000;
      if ((int)uVar8 < 0) {
        uVar8 = 0;
        uVar5 = 0;
      }
      uVar8 = uVar8 | uVar5 | uVar8 << 8;
      *(uint *)(DAT_800eb370 + 0xc) = uVar8;
      *(uint *)(DAT_800eb374 + 0xc) = uVar8;
      if (uVar8 == 0) {
        FUN_80040690(DAT_800eb370);
        FUN_80040690(DAT_800eb374);
        DAT_8009c585 = 4;
      }
    }
  }
  else if (bVar2 == 4) {
    if ((DAT_8009c585 & 0x80) == 0) {
      DAT_8009c585 = DAT_8009c585 | 0x80;
      FUN_80026c2c((int)DAT_8009c574,1);
    }
    else {
      DAT_8009c564 = 5;
    }
  }
  return;
}

