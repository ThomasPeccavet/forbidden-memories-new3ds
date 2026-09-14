/* Analysis pseudo-C, not buildable source. */

undefined4 * FUN_80024a9c(uint param_1,uint param_2)

{
  byte bVar1;
  ushort uVar2;
  short sVar3;
  undefined2 uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  
  uVar8 = param_1;
  if ((param_1 & 0x80) != 0) {
    uVar8 = (param_1 & 0x7f) + 0xf;
  }
  iVar7 = uVar8 * 0x1c;
  (&DAT_801a7aee)[uVar8 * 0xe] = 0x8000;
  uVar5 = param_2 & 0x80;
  if ((0xe < (int)param_1) && (uVar5 = param_2 & 0x80, (int)param_2 < 0x28)) {
    param_2 = param_2 + 0x28;
    uVar5 = param_2 & 0x80;
  }
  if (uVar5 != 0) {
    param_2 = (param_2 & 0x7f) + 0x28;
  }
  (&DAT_801a7adc)[uVar8 * 7] = &DAT_801a7e20 + param_2 * 3;
  (&DAT_801a7af0)[iVar7] = (char)uVar8;
  uVar2 = (&DAT_801a7e20)[param_2 * 3];
  *(ushort *)(&DAT_801a7ae4 + iVar7) = uVar2;
  *(ushort *)(&DAT_801a7ae6 + iVar7) =
       ((ushort)*(undefined4 *)(&DAT_801d4240 + ((int)((uint)uVar2 << 0x10) >> 0xe)) & 0x1ff) * 10;
  iVar6 = (&DAT_801d4244)[*(short *)(&DAT_801a7ae4 + iVar7) + -1];
  *(undefined2 *)(&DAT_801a7aea + iVar7) = 0;
  *(ushort *)(&DAT_801a7ae8 + iVar7) = ((ushort)(iVar6 >> 9) & 0x1ff) * 10;
  uVar4 = FUN_80024a38((int)(&DAT_801d4244)[*(short *)(&DAT_801a7ae4 + iVar7) + -1] >> 0x1a & 0x1f);
  iVar7 = uVar8 * 0x10;
  (&DAT_801a7aec)[uVar8 * 0xe] = uVar4;
  bVar1 = *(byte *)((&DAT_801a7adc)[uVar8 * 7] + 3);
  *(undefined2 *)(&DAT_80177ea8 + iVar7) = 0x14;
  *(undefined2 *)(&DAT_80177eaa + iVar7) = 0x20;
  iVar6 = (uint)bVar1 * 0x580;
  sVar3 = (short)((int)uVar8 / 5);
  *(short *)(&DAT_80177ea4 + iVar7) = ((short)uVar8 + sVar3 * -5) * 0x14 + 0x380;
  *(short *)(&DAT_80177ea6 + iVar7) = sVar3 * 0x20;
  FUN_8007ff10(&DAT_80177ea4 + iVar7,&DAT_8018c2d8 + iVar6);
  iVar7 = (uVar8 * 2 + 1) * 8;
  *(undefined2 *)(&DAT_80177ea4 + iVar7) = 0x380;
  *(short *)(&DAT_80177ea6 + iVar7) = (short)uVar8 + 0xe0;
  *(undefined2 *)(&DAT_80177ea8 + iVar7) = 0x40;
  *(undefined2 *)(&DAT_80177eaa + iVar7) = 1;
  FUN_8007ff10(&DAT_80177ea4 + iVar7,iVar6 + -0x7fe73828);
  return &DAT_801a7ad8 + uVar8 * 7;
}

