/* Analysis pseudo-C, not buildable source. */

void FUN_800219ac(void)

{
  int *piVar1;
  byte bVar2;
  short sVar3;
  ushort uVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  
  DAT_800f11e2 = DAT_800f11e2 + 2;
  FUN_80013448();
  if ((DAT_8009c564 & 0x8000) != 0) {
    if ((DAT_8009c564 & 0x4000) != 0) {
      if ((DAT_800eb24e & 0x80) != 0) {
        return;
      }
      if ((DAT_8009c564 & 0x2000) == 0) {
        DAT_8009c564 = DAT_8009c564 | 0x2000;
        FUN_80015820();
        DAT_800eb24c = 0xff;
        FUN_800155d4();
        return;
      }
      DAT_8009c582 = DAT_8009c582 | 0x2000;
      if ((&DAT_8009c4f8)[DAT_8009c584] == 0) {
        return;
      }
      if ((DAT_8009c6f2 < '\0') && (-1 < DAT_8009c6f3)) {
        *(uint *)(DAT_8009c4f8 + 0x5e0) =
             *(int *)(DAT_8009c4f8 + 0x5e0) + (uint)*(byte *)((int)DAT_8009c508 + 0x3a);
        if (999999 < *(uint *)(DAT_8009c4f8 + 0x5e0)) {
          *(undefined4 *)(DAT_8009c4f8 + 0x5e0) = 999999;
        }
        FUN_80021950((int)(short)DAT_8009c508[0xf]);
        return;
      }
      uVar5 = (uint)DAT_8009c584;
      iVar8 = (&DAT_8009c4f8)[uVar5];
      uVar4 = *(short *)(iVar8 + 0x518) + 1;
      *(ushort *)(iVar8 + 0x518) = uVar4;
      if (9999 < uVar4) {
        *(undefined2 *)((&DAT_8009c4f8)[uVar5] + 0x518) = 9999;
      }
      uVar5 = (uint)DAT_8009c584;
      iVar8 = (&DAT_8009c4f8)[uVar5 ^ 1];
      uVar4 = *(short *)(iVar8 + 0x51a) + 1;
      *(ushort *)(iVar8 + 0x51a) = uVar4;
      if (uVar4 < 10000) {
        return;
      }
      *(undefined2 *)((&DAT_8009c4f8)[uVar5 ^ 1] + 0x51a) = 9999;
      return;
    }
    if ((DAT_8009c728 & 0xa000) == 0) {
      if ((DAT_8009c72c & 0x40) == 0) {
        return;
      }
      DAT_8009c564 = DAT_8009c564 | 0x4000;
      FUN_80015af4(0,6);
      FUN_80040204(0x30);
      return;
    }
    *(char *)((int)DAT_8009c508 + 0x37) = *(char *)((int)DAT_8009c508 + 0x37) + '\x01';
    if (((DAT_8009c728 & 0x8000) != 0) &&
       (bVar2 = *(char *)((int)DAT_8009c508 + 0x37) - 2, *(byte *)((int)DAT_8009c508 + 0x37) = bVar2
       , (int)((uint)bVar2 << 0x18) < 0)) {
      *(undefined1 *)((int)DAT_8009c508 + 0x37) = 2;
    }
    if ('\x02' < *(char *)((int)DAT_8009c508 + 0x37)) {
      *(undefined1 *)((int)DAT_8009c508 + 0x37) = 0;
    }
    FUN_80040204(6);
    goto LAB_8002210c;
  }
  DAT_8009c564 = DAT_8009c564 | 0x8000;
  FUN_80015ba0();
  FUN_80015af4(0x80,2);
  DAT_8009c508 = &DAT_801799d8;
  DAT_801bf98c = 4;
  DAT_8009c4c2 = 0;
  DAT_8009c4c0 = 0;
  DAT_8009c6d1 = 0;
  DAT_8009c6d8 = '\0';
  DAT_801bf98d = 4;
  (&DAT_801bf98c)[DAT_8009c584] = 0;
  uVar7 = 0x72e1;
  if (DAT_8009c584 != 0) {
    uVar7 = 0x72f1;
    DAT_8009c6d8 = '\x01';
    DAT_8009c6b4 = DAT_8009c6f3 + -0x7cd8;
  }
  FUN_8004022c(uVar7);
  if ((DAT_8009c6f2 < '\0') && (DAT_8009c6f3 < '\0')) {
    DAT_8009c6d1 = 1;
    DAT_8009c6d8 = DAT_8009c6d8 + '\x02';
  }
  *(undefined1 *)((int)DAT_8009c508 + 0x39) = 0;
  FUN_80021654();
  iVar8 = DAT_8009c508[DAT_8009c584 + 0xb];
  if (iVar8 < 0x32) {
    *(undefined1 *)((int)DAT_8009c508 + 0x39) = 1;
    if (iVar8 < 0) {
      iVar8 = 0;
    }
    iVar8 = 99 - iVar8;
  }
  if (99 < iVar8) {
    iVar8 = 99;
  }
  *(char *)(DAT_8009c508 + 0xe) = (char)((iVar8 + -0x32) / 10);
  *(undefined1 *)((int)DAT_8009c508 + 0x37) = 0;
  uVar7 = FUN_80040350();
  iVar8 = FUN_800403d0(uVar7,2);
  FUN_80040800(iVar8,0x20,0x10,3,1,2,0xb,0x20c);
  FUN_80042c48(iVar8);
  *(ushort *)(iVar8 + 8) = *(ushort *)(iVar8 + 8) | 0x28;
  uVar7 = FUN_80040350();
  iVar8 = FUN_800403d0(uVar7,2);
  FUN_80040800(iVar8,0x120,0x10,3,1,0,0xb,0x20c);
  FUN_80042c48(iVar8);
  iVar10 = 9;
  *(ushort *)(iVar8 + 8) = *(ushort *)(iVar8 + 8) | 0x28;
  uVar7 = FUN_80040350();
  iVar8 = FUN_800403d0(uVar7,2);
  FUN_80042bd8(iVar8,0,8,0,4,0,0x10,8,&DAT_801af000);
  FUN_80042c48(iVar8);
  FUN_80042c1c(iVar8,0xffffffff);
  piVar1 = DAT_8009c508;
  piVar9 = DAT_8009c508 + 9;
  *(ushort *)(iVar8 + 8) = *(ushort *)(iVar8 + 8) | 0x20;
  *piVar1 = iVar8;
  do {
    piVar9[1] = 0;
    iVar10 = iVar10 + -1;
    piVar9 = piVar9 + -1;
  } while (-1 < iVar10);
  DAT_8009c6b8 = 0;
  if ((DAT_8009c6f2 < '\0') && (-1 < DAT_8009c6f3)) {
    uVar5 = (uint)DAT_8009c584;
    if (uVar5 == 0) {
      *(char *)((int)DAT_8009c508 + 0x3a) = (char)DAT_8009c508[0xe] + '\x01';
      iVar8 = (uint)(*(char *)((int)DAT_8009c508 + 0x39) != '\0') << 1;
      if (*(byte *)(DAT_8009c508 + 0xe) < 3) {
        iVar8 = 1;
      }
      iVar10 = 0;
      sVar3 = FUN_800218cc(iVar8);
      piVar1 = DAT_8009c508;
      DAT_8009c6b8 = sVar3;
      *(short *)(DAT_8009c508 + 0xf) = sVar3;
      DAT_801bf92c = (int)sVar3;
      iVar8 = 8;
      if (*(char *)((int)piVar1 + 0x3a) != '\0') {
        iVar11 = 0xa0;
        do {
          iVar10 = iVar10 + 1;
          uVar7 = FUN_80040350();
          iVar6 = FUN_800403d0(uVar7,2);
          FUN_80040800(iVar6,iVar11,0xd2,3,4,0,0xb,0x20c);
          FUN_80042c48(iVar6);
          piVar1 = DAT_8009c508;
          iVar11 = iVar11 + 0x14;
          *(ushort *)(iVar6 + 8) = *(ushort *)(iVar6 + 8) | 0x20;
          *(int *)((int)piVar1 + iVar8 + 4) = iVar6;
          iVar8 = iVar8 + 4;
        } while (iVar10 < (int)(uint)*(byte *)((int)piVar1 + 0x3a));
      }
      goto LAB_80021dd8;
    }
  }
  else {
LAB_80021dd8:
    uVar5 = (uint)DAT_8009c584;
  }
  if ((&DAT_8009c6f2)[uVar5] < '\0') {
    uVar7 = FUN_80040350();
    iVar8 = FUN_800403d0(uVar7,2);
    FUN_80042bd8(iVar8,0,0x28,0,5,*(undefined1 *)((int)DAT_8009c508 + 0x39),0x10,8,&DAT_801af000);
    FUN_80042c48(iVar8);
    FUN_80042c1c(iVar8,0xfffffffe);
    piVar1 = DAT_8009c508;
    *(ushort *)(iVar8 + 8) = *(ushort *)(iVar8 + 8) | 0x20;
    piVar1[1] = iVar8;
    uVar7 = FUN_80040350();
    iVar8 = FUN_800403d0(uVar7,2);
    FUN_80042bd8(iVar8,0,0x28,0,6,(char)DAT_8009c508[0xe],0x10,8,&DAT_801af000);
    FUN_80042c48(iVar8);
    FUN_80042c1c(iVar8,0xffffffff);
    piVar1 = DAT_8009c508;
    *(ushort *)(iVar8 + 8) = *(ushort *)(iVar8 + 8) | 0x20;
    piVar1[2] = iVar8;
  }
LAB_8002210c:
  FUN_80021538((int)*(char *)((int)DAT_8009c508 + 0x37));
  return;
}

