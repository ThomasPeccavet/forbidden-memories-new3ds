/* Analysis pseudo-C, not buildable source. */

void FUN_80026384(void)

{
  bool bVar1;
  undefined2 uVar2;
  int iVar3;
  short sVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  ushort uVar9;
  uint uVar10;
  
  iVar5 = FUN_80024ee0();
  iVar3 = DAT_800eb374;
  iVar7 = DAT_800eb370;
  iVar8 = DAT_8009c5bc;
  uVar2 = DAT_8009c59e;
  if (iVar5 == 0) {
    DAT_8009c59e = FUN_8002c9bc(&DAT_800eb378,(int)DAT_8009c5c4);
    if (DAT_8009c59e == 0) {
      DAT_8009c550 = 0;
      return;
    }
    FUN_80019c58();
    DAT_8009c598 = FUN_8002c7d8(0x16);
    DAT_8009c520 = 0;
    *(short *)(DAT_8009c598 + 0x1a) = DAT_8009c5c4;
    FUN_800402ac(0x8022);
    return;
  }
  switch(DAT_8009c520 & 0xf) {
  case 0:
    if (*(char *)(DAT_8009c598 + 0x1d) != '\0') {
      DAT_8009c59c = *(byte *)(DAT_800eb37c + 0x6a);
      FUN_800249d0(&DAT_801a7ad8 + (uint)*(byte *)(DAT_800eb378 + 0x6a) * 7);
      FUN_800249d0(&DAT_801a7ad8 + (uint)*(byte *)(DAT_800eb37c + 0x6a) * 7);
      FUN_800249d0(&DAT_801a7ad8 + (uint)*(byte *)(DAT_800eb380 + 0x6a) * 7);
      DAT_8009c520 = 1;
    }
    break;
  case 1:
    if ((DAT_8009c520 & 0x80) == 0) {
      DAT_8009c520 = DAT_8009c520 | 0x80;
      iVar8 = FUN_80029354(1,0xffffffff,0xffffffff);
      *(undefined2 *)(iVar8 + 0x30) = 0x5a;
      *(undefined2 *)(iVar8 + 0x32) = 0xffd6;
      *(undefined2 *)(iVar8 + 0x60) = 0x18;
      *(undefined2 *)(iVar8 + 0x46) = 0;
      *(undefined2 *)(iVar8 + 0x44) = 0;
      *(uint *)(iVar8 + 4) = *(uint *)(iVar8 + 4) & 0xf7ffffff;
      *(ushort *)(iVar8 + 8) = *(ushort *)(iVar8 + 8) | 4;
      FUN_80042d08(iVar8);
      *(undefined2 *)(iVar8 + 0x38) = 0x255;
      DAT_8009c5bc = iVar8;
      FUN_80040204(0x26);
    }
    FUN_80042d58(iVar8);
    sVar4 = *(short *)(iVar8 + 0x44) + 0xaa;
    uVar9 = *(short *)(iVar8 + 0x60) - 1;
    *(ushort *)(iVar8 + 0x60) = uVar9;
    *(short *)(iVar8 + 0x44) = sVar4;
    *(short *)(iVar8 + 0x46) = sVar4;
    if ((int)((uint)uVar9 << 0x10) < 1) {
      *(undefined2 *)(iVar8 + 0x46) = 0x1000;
      *(undefined2 *)(iVar8 + 0x44) = 0x1000;
      *(undefined2 *)(iVar8 + 0x32) = 0xe;
      DAT_8009c520 = 2;
      *(uint *)(iVar8 + 4) = *(uint *)(iVar8 + 4) | 0x8000000;
      *(ushort *)(iVar8 + 8) = *(ushort *)(iVar8 + 8) & 0xfffb;
    }
    break;
  case 2:
    if ((DAT_8009c520 & 0x80) == 0) {
      DAT_8009c520 = DAT_8009c520 | 0x80;
      DAT_8009c4e4 = 0x20;
    }
    if ((DAT_8009c520 & 0x40) == 0) {
      DAT_8009c4e4 = DAT_8009c4e4 - 1;
      if ((int)((uint)DAT_8009c4e4 << 0x10) < 1) {
        DAT_8009c520 = DAT_8009c520 | 0x40;
        FUN_800193dc(DAT_8009c5bc);
        DAT_800eb370 = FUN_800194f4(iVar8);
        *(uint *)(DAT_800eb370 + 4) = *(uint *)(DAT_800eb370 + 4) | 0x50000000;
        *(uint *)(DAT_800eb370 + 4) = *(uint *)(DAT_800eb370 + 4) & 0xf7ffffff;
        DAT_800eb374 = FUN_800194f4(iVar8);
        FUN_80042c1c(DAT_800eb374,0xffffffff);
        *(uint *)(DAT_800eb374 + 4) = *(uint *)(DAT_800eb374 + 4) | 0x60000000;
        *(uint *)(DAT_800eb374 + 4) = *(uint *)(DAT_800eb374 + 4) & 0xf7ffffff;
        FUN_800296c0(1);
      }
    }
    else {
      sVar4 = *(short *)(DAT_800eb370 + 0x44) + 0x80;
      *(short *)(DAT_800eb374 + 0x46) = sVar4;
      *(short *)(iVar3 + 0x44) = sVar4;
      *(short *)(iVar7 + 0x46) = sVar4;
      *(short *)(iVar7 + 0x44) = sVar4;
      uVar6 = *(byte *)(DAT_800eb370 + 0xc) - 4;
      uVar10 = uVar6 * 0x10000;
      if ((int)uVar6 < 0) {
        uVar6 = 0;
        uVar10 = 0;
      }
      uVar6 = uVar6 | uVar10 | uVar6 << 8;
      *(uint *)(DAT_800eb370 + 0xc) = uVar6;
      *(uint *)(DAT_800eb374 + 0xc) = uVar6;
      if (uVar6 == 0) {
        FUN_80040690(DAT_800eb370);
        FUN_80040690(DAT_800eb374);
        DAT_8009c520 = 3;
      }
    }
    break;
  case 3:
    uVar10 = (uint)DAT_8009c59c;
    if ((DAT_8009c520 & 0x80) == 0) {
      *(short *)(&DAT_801a7adc)[uVar10 * 7] = DAT_8009c59e;
      iVar8 = (&DAT_801a7adc)[uVar10 * 7];
      DAT_8009c520 = DAT_8009c520 | 0x80;
      *(undefined2 *)(&DAT_801a7ae4 + uVar10 * 0x1c) = uVar2;
      DAT_800eb4b8 = DAT_800eb4d8 + 0x38;
      DAT_800eb4bc = 8;
      DAT_800eb4be = 0x58;
      DAT_800eb4ba = DAT_800eb4da;
      FUN_8007ff70(&DAT_800eb4b8,&DAT_8018c2d8 + (uint)*(byte *)(iVar8 + 3) * 0x580);
      return;
    }
    FUN_80024df0(uVar10,(int)*(char *)((&DAT_801a7adc)[uVar10 * 7] + 2));
    DAT_800eb370 = (&DAT_801a7ad8)[uVar10 * 7];
    *(undefined2 *)(DAT_800eb370 + 0x32) = 0xff00;
    if ((char)(&DAT_8009c6f2)[DAT_8009c504] < '\0') {
      DAT_800eb374 = FUN_80017e94(&DAT_801a7ad8 + uVar10 * 7,0x86,0x100);
      DAT_8009c520 = 4;
      goto switchD_80026420_caseD_4;
    }
    (&DAT_801a7aee)[uVar10 * 0xe] = (&DAT_801a7aee)[uVar10 * 0xe] & 0xfdff;
    uVar6 = FUN_8008f708();
    if ((uVar6 & 1) != 0) {
      (&DAT_801a7aee)[uVar10 * 0xe] = (&DAT_801a7aee)[uVar10 * 0xe] | 0x200;
    }
    goto LAB_80026a50;
  case 4:
switchD_80026420_caseD_4:
    iVar8 = DAT_800eb374;
    if ((DAT_8009c520 & 0x80) == 0) {
      DAT_8009c520 = DAT_8009c520 | 0x80;
      *(undefined2 *)(DAT_800eb374 + 0x28) = 0x86;
      *(undefined2 *)(iVar8 + 0x2a) = 0x2a;
      *(undefined2 *)(iVar8 + 0x2c) = 0x10;
      *(undefined1 *)(iVar8 + 0x6c) = 1;
      *(code **)(iVar8 + 0x24) = FUN_8001ebd0;
      return;
    }
    if ((DAT_8009c520 & 0x40) == 0) {
      iVar7 = FUN_80042e70(1);
      if (iVar7 == 0) {
        DAT_8009c6b8 = *(undefined2 *)(&DAT_801a7ae4 + (uint)*(byte *)(iVar8 + 0x6a) * 0x1c);
        iVar8 = FUN_800361d8(0,0x21,0x48,0x6e,0xb0,0x30,0x40);
        do {
          FUN_80039770();
        } while (*(int *)(iVar8 + 0x30) == 0);
        DAT_8009c520 = DAT_8009c520 | 0x40;
        return;
      }
      return;
    }
    if ((DAT_8009c520 & 0x20) == 0) {
      iVar7 = FUN_80036f7c(&DAT_800f0850);
      if (iVar7 != 0) {
        return;
      }
      if ((DAT_8009c72c & 0xc0) != 0) {
        FUN_80040204(7);
        *(undefined2 *)(iVar8 + 0x28) = 0x86;
        *(undefined2 *)(iVar8 + 0x2a) = 0xff80;
        *(undefined2 *)(iVar8 + 0x2c) = 0x10;
        *(undefined1 *)(iVar8 + 0x6c) = 1;
        *(code **)(iVar8 + 0x24) = FUN_8001ebd0;
        uVar10 = (uint)*(byte *)(iVar8 + 0x6a);
        uVar9 = (&DAT_801a7aee)[uVar10 * 0xe];
        bVar1 = DAT_8009c6d0 != '\0';
        (&DAT_801a7aee)[uVar10 * 0xe] = uVar9 & 0xfdff;
        if (bVar1) {
          (&DAT_801a7aee)[uVar10 * 0xe] = uVar9 & 0xfdff | 0x200;
        }
        FUN_800360d8(&DAT_800f0850);
        DAT_8009c520 = DAT_8009c520 | 0x20;
        return;
      }
      return;
    }
    iVar7 = FUN_80042e70(1);
    if (iVar7 != 0) {
      return;
    }
    FUN_80040690(iVar8);
LAB_80026a50:
    DAT_8009c520 = 5;
    break;
  case 5:
    if ((DAT_8009c520 & 0x80) == 0) {
      DAT_8009c520 = DAT_8009c520 | 0x80;
      FUN_800434a8(DAT_800eb370);
      *(undefined2 *)(iVar7 + 0x60) = 0xfc00;
    }
    FUN_80043560(iVar7,(int)*(short *)(iVar7 + 0x30),0xffffffe8,(int)*(short *)(iVar7 + 0x60));
    uVar9 = *(short *)(iVar7 + 0x60) + 0x2a;
    *(ushort *)(iVar7 + 0x60) = uVar9;
    if (-1 < (int)((uint)uVar9 << 0x10)) {
      *(undefined2 *)(iVar7 + 0x32) = 0xffe8;
      DAT_8009c550 = 0;
      return;
    }
    return;
  }
  return;
}

