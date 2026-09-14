/* Analysis pseudo-C, not buildable source. */

int FUN_8004cf9c(int *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char cVar6;
  undefined4 in_zero;
  uint in_at;
  uint *in_v0;
  uint in_v1;
  int iVar7;
  int iVar8;
  uint *puVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  undefined4 *puVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  int unaff_s0;
  int unaff_s1;
  int unaff_s2;
  int unaff_s3;
  int unaff_s6;
  int unaff_s7;
  uint uVar18;
  
  DAT_800ff5c4 = (uint *)param_1[4];
  uVar18 = (uint)*(ushort *)(*param_1 + 2);
  iVar7 = *(int *)(*param_1 + 4);
  param_1[8] = unaff_s0;
  param_1[9] = unaff_s1;
  param_1[10] = unaff_s2;
  param_1[0xb] = unaff_s3;
  param_1[0xc] = unaff_s6;
  param_1[0xd] = unaff_s7;
  cVar6 = (char)DAT_8009c374;
  iVar5 = DAT_8009c370;
  uVar4 = DAT_8009c36c;
  uVar3 = DAT_8009c368;
  uVar2 = DAT_8009c344;
  puVar9 = (uint *)(param_1[5] + iVar7 * 4);
  if (uVar18 != 0) {
    iVar7 = param_1[6];
    iVar8 = param_1[7];
    setCopReg(2,0x3000,DAT_8009c344);
    uVar16 = param_1[2];
    iVar17 = *(int *)(param_1[1] + 4);
    do {
      uVar10 = puVar9[3];
      uVar11 = puVar9[4];
      uVar12 = puVar9[5];
      puVar14 = (undefined4 *)((uVar10 >> 0x10) * 8 + iVar7);
      setCopReg(2,in_zero,*puVar14);
      setCopReg(2,in_at,puVar14[1]);
      puVar14 = (undefined4 *)((uVar11 >> 0x10) * 8 + iVar7);
      setCopReg(2,in_v0,*puVar14);
      setCopReg(2,in_v1,puVar14[1]);
      puVar14 = (undefined4 *)((uVar12 >> 0x10) * 8 + iVar7);
      setCopReg(2,param_1,*puVar14);
      setCopReg(2,iVar7,puVar14[1]);
      copFunction(2,0x280030);
      in_at = 1;
      if (cVar6 == '\x01') {
LAB_8004d0ac:
        copFunction(2,0x158002d);
        puVar14 = (undefined4 *)((uVar10 & 0xffff) * 8 + iVar8);
        if (cVar6 == '\0') {
          uVar11 = *(uint *)((uVar11 & 0xffff) * 4 + iVar5);
          uVar12 = *(uint *)((uVar12 & 0xffff) * 4 + iVar5);
          DAT_800ff5c4[1] = *(uint *)((uVar10 & 0xffff) * 4 + iVar5);
          DAT_800ff5c4[4] = uVar11;
          DAT_800ff5c4[7] = uVar12;
          *(char *)((int)DAT_800ff5c4 + 7) = (char)(uVar2 >> 0x18);
        }
        else {
          setCopReg(2,in_zero,*puVar14);
          setCopReg(2,1,puVar14[1]);
          puVar14 = (undefined4 *)((uVar11 & 0xffff) * 8 + iVar8);
          setCopReg(2,in_v0,*puVar14);
          setCopReg(2,in_v1,puVar14[1]);
          puVar14 = (undefined4 *)((uVar12 & 0xffff) * 8 + iVar8);
          setCopReg(2,param_1,*puVar14);
          setCopReg(2,iVar7,puVar14[1]);
          copFunction(2,0x118043f);
          if (iVar5 != 0) {
            uVar1 = getCopReg(2,0x14);
            *(undefined4 *)((uVar10 & 0xffff) * 4 + iVar5) = uVar1;
            uVar1 = getCopReg(2,0x15);
            *(undefined4 *)((uVar11 & 0xffff) * 4 + iVar5) = uVar1;
            uVar1 = getCopReg(2,0x16);
            *(undefined4 *)((uVar12 & 0xffff) * 4 + iVar5) = uVar1;
          }
          uVar10 = getCopReg(2,0x14);
          DAT_800ff5c4[1] = uVar10;
          uVar10 = getCopReg(2,0x15);
          DAT_800ff5c4[4] = uVar10;
          uVar10 = getCopReg(2,0x16);
          DAT_800ff5c4[7] = uVar10;
          in_at = 1;
          if (cVar6 == '\x01') goto LAB_8004d224;
        }
        uVar11 = *puVar9;
        uVar13 = puVar9[2];
        uVar10 = getCopReg(2,0x3800);
        in_v1 = uVar2 & 0x2000000;
        uVar12 = puVar9[1] | uVar3;
        in_v0 = (uint *)((uVar10 >> (uVar16 & 0x1f)) * 4 + iVar17);
        uVar15 = *in_v0;
        uVar10 = getCopReg(2,0xc);
        DAT_800ff5c4[2] = uVar10;
        uVar10 = getCopReg(2,0xd);
        DAT_800ff5c4[5] = uVar10;
        uVar10 = getCopReg(2,0xe);
        DAT_800ff5c4[8] = uVar10;
        while( true ) {
          DAT_800ff5c4[3] = uVar11;
          DAT_800ff5c4[6] = uVar12;
          DAT_800ff5c4[9] = uVar13;
          in_at = uVar15 & 0xffffff;
          *DAT_800ff5c4 = in_at | 0x9000000;
          uVar15 = (uint)DAT_800ff5c4 & 0xffffff;
          *in_v0 = uVar15;
          if ((in_v1 == 0) || (uVar4 == 0)) break;
          uVar11 = uVar11 & 0xffff | uVar4;
          uVar12 = uVar12 & 0xff9fffff | 0x400000;
          DAT_800ff5c4[0xb] = uVar2;
          DAT_800ff5c4[0xc] = DAT_800ff5c4[2];
          DAT_800ff5c4[0xe] = uVar2;
          DAT_800ff5c4[0xf] = DAT_800ff5c4[5];
          DAT_800ff5c4[0x11] = uVar2;
          DAT_800ff5c4[0x12] = DAT_800ff5c4[8];
          DAT_800ff5c4 = DAT_800ff5c4 + 10;
          in_v1 = 0;
        }
        DAT_800ff5c4 = DAT_800ff5c4 + 10;
      }
      else {
        in_v0 = (uint *)getCopControlWord(2,0xf800);
        if (-1 < (int)in_v0) {
          copFunction(2,0x1400006);
          in_v0 = (uint *)getCopReg(2,0xc000);
          if (0 < (int)in_v0) goto LAB_8004d0ac;
        }
      }
LAB_8004d224:
      uVar18 = uVar18 - 1;
      puVar9 = puVar9 + 6;
    } while (uVar18 != 0);
  }
  return *param_1 + 8;
}

