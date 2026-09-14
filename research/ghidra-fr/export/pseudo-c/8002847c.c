/* Analysis pseudo-C, not buildable source. */

void FUN_8002847c(void)

{
  byte bVar1;
  ushort uVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  byte bVar7;
  undefined *puVar8;
  int iVar9;
  
  iVar4 = FUN_80028370();
  iVar9 = DAT_8009c5e0;
  iVar5 = DAT_8009c5d4;
  if (iVar4 == 0) {
    DAT_8009c424 = 1;
    FUN_8002970c(3);
    DAT_800eb55a = 0x100;
    DAT_800eb55c = 0x280;
    DAT_800eb558 = 0;
    DAT_800eb55e = 0xdf;
    FUN_800292dc(3,(int)DAT_8009c5d8);
    iVar5 = FUN_80029354(3,0xffffffff,0xffffffff);
    *(undefined2 *)(iVar5 + 0x30) = 0xff74;
    *(undefined1 *)(iVar5 + 0x21) = 0x80;
    *(ushort *)(iVar5 + 8) = *(ushort *)(iVar5 + 8) | 4;
    FUN_800434a8(iVar5);
    *(undefined2 *)(iVar5 + 0x60) = 0xfc00;
    FUN_80042c48(iVar5);
    FUN_80042c1c(iVar5,0x14);
    DAT_8009c5e0 = iVar5;
    uVar6 = FUN_80040350();
    iVar5 = FUN_800403d0(uVar6,2);
    FUN_80040800(iVar5,0x98,0x108,0,2,4,0xd,0x107);
    *(undefined2 *)(iVar5 + 0x60) = 0xfc00;
    *(ushort *)(iVar5 + 8) = *(ushort *)(iVar5 + 8) | 8;
    FUN_80042c48(iVar5);
    FUN_80042c1c(iVar5,0x14);
    FUN_800434a8(iVar5);
    iVar9 = 0;
    puVar8 = &DAT_800f0850;
    *(undefined2 *)(iVar5 + 0x60) = 0xfc00;
    DAT_8009c5e8 = 0;
    do {
      DAT_8009c5d4 = iVar5;
      if ((*(ushort *)(puVar8 + 0x34) & 0x8000) == 0) {
        DAT_801bf88c = (int)DAT_8009c5d8;
        DAT_8009c6b8 = DAT_8009c5d8;
        uVar6 = 0x60;
        if (0x13 < ((int)(&DAT_801d4244)[DAT_801bf88c + -1] >> 0x1a & 0x1fU)) {
          uVar6 = 0x61;
        }
        DAT_8009c5e8 = FUN_80036184(iVar9,uVar6,0x98,0x108,0xa0,0x100);
        *(undefined1 *)(DAT_8009c5e8 + 0x59) = 0x15;
        FUN_800399f0();
        break;
      }
      iVar9 = iVar9 + 1;
      puVar8 = puVar8 + 100;
    } while (iVar9 < 3);
    FUN_80015af4(0x40,2);
    DAT_8009c4c4 = DAT_8009c2fa + -0x13;
    FUN_80040204(0x34);
    DAT_8009c5de = DAT_8009c5de | 0x40;
    return;
  }
  if ((DAT_8009c5de & 0x40) == 0) {
    if ((DAT_8009c5de & 0x20) == 0) {
      bVar1 = *(char *)(DAT_8009c5e0 + 0x21) + 0xc;
      *(byte *)(DAT_8009c5e0 + 0x21) = bVar1;
      if (0x3f < bVar1) {
        return;
      }
      *(undefined1 *)(iVar9 + 0x21) = 0;
      *(ushort *)(iVar9 + 8) = *(ushort *)(iVar9 + 8) & 0xfffb;
      DAT_8009c5de = DAT_8009c5de | 0x20;
      return;
    }
    uVar2 = DAT_8009c72c;
    if ((DAT_8009c60a & 0x1f) == 0xe) {
      uVar2 = DAT_8009c72c | DAT_8009c72e;
    }
    if ((uVar2 & 0x20) == 0) {
      return;
    }
    FUN_800434a8(DAT_8009c5d4);
    iVar5 = DAT_8009c5e0;
    *(undefined2 *)(DAT_8009c5d4 + 0x60) = 0x400;
    FUN_800434a8(iVar5);
    *(undefined2 *)(DAT_8009c5e0 + 0x60) = 0x400;
    FUN_80015af4(0xff,2);
    FUN_80040204(0x34);
    DAT_8009c5de = DAT_8009c5de | 0x50;
    return;
  }
  if (*(short *)(DAT_8009c5d4 + 0x60) != 0) {
    if ((DAT_8009c5de & 0x10) == 0) {
      FUN_80043560(DAT_8009c5d4,(int)*(short *)(DAT_8009c5d4 + 0x30),6);
      uVar2 = *(short *)(iVar5 + 0x60) + 0x55;
      *(ushort *)(iVar5 + 0x60) = uVar2;
      if (-1 < (int)((uint)uVar2 << 0x10)) {
        *(undefined2 *)(iVar5 + 0x32) = 6;
        goto LAB_80028730;
      }
    }
    else {
      FUN_80043560(DAT_8009c5d4,(int)*(short *)(DAT_8009c5d4 + 0x30),0x108);
      uVar2 = *(short *)(iVar5 + 0x60) - 0x55;
      *(ushort *)(iVar5 + 0x60) = uVar2;
      if ((int)((uint)uVar2 << 0x10) < 1) {
        *(undefined2 *)(iVar5 + 0x30) = 0x400;
LAB_80028730:
        *(undefined2 *)(iVar5 + 0x60) = 0;
      }
    }
    if (DAT_8009c5e8 != 0) {
      FUN_80039910(DAT_8009c5e8,(int)*(short *)(iVar5 + 0x30),(int)*(short *)(iVar5 + 0x32));
    }
  }
  iVar5 = DAT_8009c5e0;
  if (*(short *)(DAT_8009c5e0 + 0x60) != 0) {
    if ((DAT_8009c5de & 0x10) == 0) {
      FUN_80043560(DAT_8009c5e0,2,(int)*(short *)(DAT_8009c5e0 + 0x32));
      uVar2 = *(short *)(iVar5 + 0x60) + 0x55;
      *(ushort *)(iVar5 + 0x60) = uVar2;
      uVar3 = 2;
      if ((int)((uint)uVar2 << 0x10) < 0) goto LAB_800287e4;
    }
    else {
      FUN_80043560(DAT_8009c5e0,0xffffff74,(int)*(short *)(DAT_8009c5e0 + 0x32));
      uVar2 = *(short *)(iVar5 + 0x60) - 0x55;
      *(ushort *)(iVar5 + 0x60) = uVar2;
      if (0 < (int)((uint)uVar2 << 0x10)) goto LAB_800287e4;
      uVar3 = 0x400;
    }
    *(undefined2 *)(iVar5 + 0x30) = uVar3;
    *(undefined2 *)(iVar5 + 0x60) = 0;
  }
LAB_800287e4:
  if (((((DAT_8009c460 & 0x2000030) == 0 && DAT_8009c484 == 0) &&
       (*(short *)(DAT_8009c5d4 + 0x60) == 0)) && (*(short *)(DAT_8009c5e0 + 0x60) == 0)) &&
     (bVar7 = DAT_8009c5de & 0xbf, bVar1 = DAT_8009c5de & 0x10, DAT_8009c5de = bVar7, bVar1 != 0)) {
    FUN_80040690();
    FUN_800296c0(3);
    if (DAT_8009c5e8 != 0) {
      FUN_800360d8();
    }
    DAT_8009c424 = 0;
    DAT_8009c5dc = DAT_8009c5dc | 0x40;
  }
  return;
}

