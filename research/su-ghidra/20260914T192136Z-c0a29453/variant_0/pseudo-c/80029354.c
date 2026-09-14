/* Analysis pseudo-C, not buildable source. */

void FUN_80029354(int param_1,ushort param_2,ushort param_3)

{
  byte bVar1;
  ushort uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined1 uVar8;
  uint uVar9;
  
  iVar6 = param_1 * 0x40;
  uVar3 = FUN_80040350();
  iVar4 = FUN_800403d0(uVar3,6);
  FUN_80040844(iVar4,0,0,0x66,0x60,0,0,
               ((int)((uint)(ushort)(&DAT_800eb498)[param_1 * 0x20] << 0x10) >> 0x16) +
               ((int)((uint)(ushort)(&DAT_800eb49a)[param_1 * 0x20] << 0x10) >> 0x18) * 0x10,
               (int)(short)(&DAT_800eb49c)[param_1 * 0x20],
               (int)(short)(&DAT_800eb49e)[param_1 * 0x20]);
  *(undefined4 *)(iVar4 + 0x30) = 0x1f0048;
  *(undefined4 *)(iVar4 + 0x3c) = 0x100038;
  uVar2 = (ushort)DAT_8009c44b;
  *(uint *)(iVar4 + 4) = *(uint *)(iVar4 + 4) | 0x1000000;
  *(ushort *)(iVar4 + 0x5e) = (uVar2 * 0x10 + 0x9e) * 0x100;
  iVar7 = (int)*(short *)(&DAT_800eb4a0 + iVar6);
  iVar5 = (&DAT_801d4244)[iVar7 + -1];
  *(char *)(iVar4 + 0x67) = (char)param_1;
  uVar9 = iVar5 >> 0x1a & 0x1f;
  *(char *)(iVar4 + 0x68) = (char)uVar9;
  if (uVar9 == 0x15) {
    iVar5 = 0x102;
    uVar8 = 1;
    *(char *)(iVar4 + 0x5e) = *(char *)(iVar4 + 0x5e) + '@';
    goto LAB_800295a4;
  }
  if (uVar9 < 0x16) {
    if (uVar9 == 0x14) {
LAB_800294c0:
      iVar5 = 0x101;
      uVar8 = 1;
      goto LAB_800295a4;
    }
    *(undefined2 *)(iVar4 + 0x30) = 0x18;
  }
  else {
    if (uVar9 == 0x16) {
      iVar5 = 0x103;
      uVar8 = 1;
      goto LAB_800295a4;
    }
    if (uVar9 == 0x17) {
      *(char *)(iVar4 + 0x5e) = *(char *)(iVar4 + 0x5e) + -0x80;
      goto LAB_800294c0;
    }
    *(undefined2 *)(iVar4 + 0x30) = 0x18;
  }
  *(undefined2 *)(iVar4 + 0x32) = 0xbe;
  *(undefined1 *)(iVar4 + 0x5e) = 0xc0;
  *(undefined2 *)(iVar4 + 0x3c) = 0x1c;
  bVar1 = DAT_8009c44b;
  *(undefined2 *)(iVar4 + 0x3e) = 9;
  *(byte *)(iVar4 + 0x5f) = bVar1 * '\x10' + -0x60;
  (&DAT_800eb4a2)[param_1 * 0x20] = param_2;
  if ((int)((uint)param_2 << 0x10) < 0) {
    (&DAT_800eb4a2)[param_1 * 0x20] = ((ushort)(&DAT_801d4244)[iVar7 + -1] & 0x1ff) * 10;
  }
  (&DAT_800eb4a4)[param_1 * 0x20] = param_3;
  if ((int)((uint)param_3 << 0x10) < 0) {
    (&DAT_800eb4a4)[param_1 * 0x20] = ((ushort)((int)(&DAT_801d4244)[iVar7 + -1] >> 9) & 0x1ff) * 10
    ;
  }
  iVar5 = 0x100;
  uVar8 = 0;
  *(undefined2 *)(&DAT_800eb4a8 + iVar6) = 0;
  *(undefined2 *)(&DAT_800eb4a6 + iVar6) = 0;
LAB_800295a4:
  (&DAT_800eb4ab)[iVar6] = (byte)(&DAT_801d5332)[iVar7] >> 4;
  bVar1 = (&DAT_801d5332)[iVar7];
  (&DAT_800eb4ac)[iVar6] = 0;
  (&DAT_800eb4aa)[iVar6] = bVar1 & 0xf;
  *(code **)(iVar4 + 0x4c) = FUN_80028c0c;
  FUN_80042c48(iVar4);
  (&DAT_800eb474)[param_1 * 0x10] = iVar4;
  uVar3 = FUN_80040350();
  iVar4 = FUN_800403d0(uVar3,2);
  FUN_80040800(iVar4,2,0,1,0,uVar8,0x1c,iVar5 + 8);
  *(undefined2 *)(iVar4 + 0x18) = 0x46;
  *(undefined2 *)(iVar4 + 0x48) = 0x46;
  *(undefined2 *)(iVar4 + 0x1a) = 0x6a;
  *(undefined2 *)(iVar4 + 0x4a) = 0x6a;
  *(undefined1 *)(iVar4 + 0x6a) = uVar8;
  *(uint *)(iVar4 + 4) = *(uint *)(iVar4 + 4) | 0x1000000;
  *(ushort *)(iVar4 + 8) = *(ushort *)(iVar4 + 8) | 8;
  FUN_80042c48(iVar4);
  FUN_80042c1c(iVar4,0xffffffff);
  *(undefined1 *)((&DAT_800eb474)[param_1 * 0x10] + 0x65) = 3;
  *(undefined1 *)(iVar4 + 0x65) = 3;
  *(code **)(iVar4 + 0x10) = FUN_80029280;
  (&DAT_800eb470)[param_1 * 0x10] = iVar4;
  *(int *)((&DAT_800eb474)[param_1 * 0x10] + 0x54) = iVar4;
  return;
}

