/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_8001b100(void)

{
  bool bVar1;
  undefined2 uVar2;
  ushort uVar3;
  short sVar4;
  ushort uVar5;
  int iVar6;
  undefined2 *puVar7;
  uint uVar8;
  int iVar9;
  
  iVar9 = DAT_800eb370;
  if ((DAT_8009c564 & 0x8000) != 0) {
LAB_8001b21c:
    switch(DAT_8009c585 & 0xf) {
    case 1:
      FUN_800434bc(iVar9,0x86,0x2a,(int)*(short *)(iVar9 + 0x60));
      sVar4 = *(short *)(iVar9 + 0x60) + 0x80;
      *(short *)(iVar9 + 0x60) = sVar4;
      if (sVar4 < 0x800) {
        return;
      }
      *(undefined2 *)(iVar9 + 0x30) = 0x86;
      *(undefined2 *)(iVar9 + 0x32) = 0x2a;
    case 2:
      if (*(byte *)(iVar9 + 0x68) < 0x14) {
        DAT_8009c585 = 3;
switchD_8001b24c_caseD_3:
        if ((DAT_8009c585 & 0x80) == 0) {
          DAT_8009c585 = DAT_8009c585 | 0x80;
          DAT_8009c6b8 = *(undefined2 *)(&DAT_801a7ae4 + (uint)*(byte *)(iVar9 + 0x6a) * 0x1c);
          iVar9 = FUN_800361d8(0,0x21,0x48,0x6e,0xb0,0x30,0x40);
          do {
            FUN_80039770();
          } while (*(int *)(iVar9 + 0x30) == 0);
          return;
        }
        if ((DAT_8009c585 & 0x10) == 0) {
          iVar9 = FUN_80036f7c(&DAT_800f0850);
          if (iVar9 != 0) {
            return;
          }
          if ((DAT_8009c72c & 0xc0) == 0) {
            return;
          }
          FUN_80040204(7);
          DAT_8009c585 = DAT_8009c585 | 0x10;
          return;
        }
        bVar1 = DAT_8009c6d0 != '\0';
        (&DAT_801a7aee)[(uint)*(byte *)(iVar9 + 0x6a) * 0xe] =
             (&DAT_801a7aee)[(uint)*(byte *)(iVar9 + 0x6a) * 0xe] & 0xfdff;
        if (bVar1) {
          (&DAT_801a7aee)[(uint)*(byte *)(iVar9 + 0x6a) * 0xe] =
               (&DAT_801a7aee)[(uint)*(byte *)(iVar9 + 0x6a) * 0xe] | 0x200;
        }
        FUN_800360d8(&DAT_800f0850);
      }
LAB_8001b3c8:
      DAT_8009c585 = 4;
      break;
    case 3:
      goto switchD_8001b24c_caseD_3;
    case 4:
      if ((DAT_8009c585 & 0x80) == 0) {
        DAT_8009c585 = DAT_8009c585 | 0x80;
        sVar4 = FUN_8001b05c(DAT_8009c59c);
        *(short *)(iVar9 + 0x2e) = sVar4 + -0x1e;
        FUN_800434a8(iVar9);
        *(undefined2 *)(iVar9 + 0x60) = 0x400;
      }
      if ((DAT_8009c585 & 0x40) == 0) {
        FUN_80043560(iVar9,(int)*(short *)(iVar9 + 0x2e),0xffffff44,(int)*(short *)(iVar9 + 0x60));
        uVar5 = *(short *)(iVar9 + 0x60) - 0x2a;
        *(ushort *)(iVar9 + 0x60) = uVar5;
        if ((int)((uint)uVar5 << 0x10) < 1) {
          DAT_8009c585 = DAT_8009c585 | 0x40;
          uVar8 = (uint)*(byte *)(iVar9 + 0x6a);
          iVar6 = uVar8 * 0x1c;
          _DAT_1f800000 = (&DAT_801a7ad8)[uVar8 * 7];
          _DAT_1f800004 = (&DAT_801a7adc)[uVar8 * 7];
          _DAT_1f800008 = *(undefined4 *)(&DAT_801a7ae0 + iVar6);
          _DAT_1f80000c = *(undefined4 *)(&DAT_801a7ae4 + iVar6);
          _DAT_1f800010 = *(undefined4 *)(&DAT_801a7ae8 + iVar6);
          _DAT_1f800014 = *(undefined4 *)(&DAT_801a7aec + uVar8 * 0xe);
          _DAT_1f800018 = *(undefined4 *)(&DAT_801a7af0 + iVar6);
          FUN_80024df0(DAT_8009c59c,*(undefined1 *)(iVar9 + 0x6b));
          uVar8 = (uint)DAT_8009c59c;
          uVar5 = (&DAT_801a7aee)[uVar8 * 0xe] | _DAT_1f800016 & 0x7e00;
          (&DAT_801a7aee)[uVar8 * 0xe] = uVar5 & 0xfbff;
          if ((uVar5 & 0x1000) == 0) {
            (&DAT_801a7aee)[uVar8 * 0xe] = uVar5 & 0xdbff;
          }
          *(undefined2 *)(&DAT_801a7aea + uVar8 * 0x1c) = _DAT_1f800012;
          FUN_80040690(iVar9);
          iVar9 = (&DAT_801a7ad8)[uVar8 * 7];
          DAT_800eb370 = iVar9;
          FUN_80018010(iVar9);
          *(undefined2 *)(iVar9 + 0x32) = 0xff00;
          FUN_800434a8(iVar9);
          *(undefined2 *)(iVar9 + 0x60) = 0xfc00;
        }
      }
      else {
        FUN_80043560(iVar9,(int)*(short *)(iVar9 + 0x30),0xffffffe8,(int)*(short *)(iVar9 + 0x60));
        uVar5 = *(short *)(iVar9 + 0x60) + 0x2a;
        *(ushort *)(iVar9 + 0x60) = uVar5;
        if (-1 < (int)((uint)uVar5 << 0x10)) {
          *(undefined2 *)(iVar9 + 0x32) = 0xffe8;
          DAT_8009c585 = 5;
          FUN_80040204(0xc);
        }
      }
      break;
    case 5:
      if ((DAT_8009c57c == 0) || (iVar9 = FUN_800250d8(0x2b1), iVar9 == 0)) {
        DAT_8009c564 = 5;
      }
      else {
        DAT_8009c585 = 6;
      }
      break;
    case 6:
      if ((DAT_8009c585 & 0x80) == 0) {
        DAT_8009c520 = 0;
        DAT_8009c585 = DAT_8009c585 | 0xc0;
      }
      if ((DAT_8009c585 & 0x40) == 0) {
        DAT_8009c564 = 5;
        iVar9 = (uint)*(byte *)(iVar9 + 0x6a) * 0x1c;
        *(short *)(&DAT_801a7aea + iVar9) = *(short *)(&DAT_801a7aea + iVar9) + DAT_8009c57c * -2;
      }
      else {
        iVar6 = FUN_8001f2c4();
        if (iVar6 == 0) {
          puVar7 = (undefined2 *)FUN_8002c860(0xd);
          *puVar7 = *(undefined2 *)(iVar9 + 0x30);
          puVar7[1] = *(undefined2 *)(iVar9 + 0x32);
          uVar2 = *(undefined2 *)(iVar9 + 0x34);
          puVar7[9] = -DAT_8009c57c;
          puVar7[2] = uVar2;
          FUN_80040204(0x21);
          DAT_8009c585 = DAT_8009c585 & 0xbf;
        }
      }
    }
    return;
  }
  uVar3 = DAT_8009c564 | 0x8000;
  uVar5 = DAT_8009c564 & 0x4000;
  DAT_8009c564 = uVar3;
  if (uVar5 == 0) {
    if (((char)(&DAT_8009c6f2)[DAT_8009c504] < '\0') || (0x13 < *(byte *)(DAT_800eb370 + 0x68))) {
      DAT_8009c585 = 1;
      FUN_800434a8(DAT_800eb370);
      *(undefined2 *)(iVar9 + 0x60) = 0;
      if ((*(short *)(iVar9 + 0x30) == 0x86) || (*(short *)(iVar9 + 0x32) == 0x2a)) {
        DAT_8009c585 = 2;
        return;
      }
      goto LAB_8001b21c;
    }
    (&DAT_801a7aee)[(uint)*(byte *)(DAT_800eb370 + 0x6a) * 0xe] =
         (&DAT_801a7aee)[(uint)*(byte *)(DAT_800eb370 + 0x6a) * 0xe] & 0xfdff;
    if ((DAT_800ec217 & 1) != 0) {
      (&DAT_801a7aee)[(uint)*(byte *)(iVar9 + 0x6a) * 0xe] =
           (&DAT_801a7aee)[(uint)*(byte *)(iVar9 + 0x6a) * 0xe] | 0x200;
    }
  }
  goto LAB_8001b3c8;
}

