/* Analysis pseudo-C, not buildable source. */

void FUN_80050a68(int param_1)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  uint *puVar6;
  uint uVar7;
  uint uVar8;
  undefined *puVar9;
  uint *puVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  undefined *puVar14;
  
  param_1 = param_1 * 0xe20;
  puVar9 = &DAT_800f4178 + param_1;
  if ((*(int *)(&DAT_800f4f50 + param_1) == 0) || (iVar13 = 0, (&DAT_800f4f93)[param_1] == '\0')) {
    return;
  }
  iVar12 = 0;
  puVar14 = puVar9;
LAB_80050ad4:
  iVar11 = 1;
  uVar1 = *(ushort *)(puVar14 + 0x33c);
  iVar4 = *(int *)(&DAT_800f4f50 + param_1);
  iVar3 = iVar12;
LAB_80050aec:
  puVar5 = (uint *)(*(int *)(&DAT_800f4f50 + param_1) +
                   (uint)*(ushort *)(puVar9 + iVar3 + 0x33c) * 4);
  if (*(ushort *)(puVar9 + iVar3 + 0x33c) != 0xffff) {
    puVar10 = puVar5 + -1;
    do {
      uVar8 = *puVar5;
      if ((int)uVar8 < 0) {
        uVar7 = uVar8 >> 0x10 & 0x7f;
        uVar2 = *(ushort *)(puVar9 + iVar12 + uVar7 * 0x74 + 0x2c8);
        puVar6 = (uint *)(*(int *)(&DAT_800f4f50 + param_1) + (uint)uVar2 * 4);
        if (uVar7 == 0) goto LAB_80050bfc;
        *puVar5 = uVar8 & 0xc07fffff | (uVar8 >> 0x10 & 0x7f) << 0x17;
        if ((uVar2 != 0xffff) && (1 < uVar7)) {
          for (; puVar6 != (uint *)0x0; puVar6 = puVar6 + 1) {
            uVar8 = *puVar6;
            if ((int)uVar8 < 0) {
              if ((uVar8 >> 0x10 & 0x7f) == uVar7) {
                *puVar6 = uVar8 & 0xff80ffff | 0x10000;
              }
              if ((*puVar6 & 0x7f0000) == 0x10000) {
                *(short *)puVar6 =
                     (short)((int)((iVar4 + (uint)uVar1 * 4) - *(int *)(&DAT_800f4f50 + param_1)) >>
                            2);
                *(short *)puVar5 = (short)((int)puVar6 - *(int *)(&DAT_800f4f50 + param_1) >> 2);
                break;
              }
            }
          }
        }
      }
      puVar5 = puVar5 + 1;
    } while( true );
  }
  goto LAB_80050c2c;
LAB_80050bfc:
  *(short *)puVar10 = (short)((int)puVar5 - *(int *)(&DAT_800f4f50 + param_1) >> 2) + -1;
  *(short *)puVar5 = (short)((int)puVar10 - *(int *)(&DAT_800f4f50 + param_1) >> 2) + 1;
LAB_80050c2c:
  iVar11 = iVar11 + 1;
  iVar3 = iVar3 + 0x74;
  if (9 < iVar11) goto code_r0x80050c3c;
  goto LAB_80050aec;
code_r0x80050c3c:
  iVar12 = iVar12 + 2;
  iVar13 = iVar13 + 1;
  puVar14 = puVar14 + 2;
  if ((int)(uint)(byte)(&DAT_800f4f93)[param_1] <= iVar13) {
    return;
  }
  goto LAB_80050ad4;
}

