/* Analysis pseudo-C, not buildable source. */

void FUN_80083178(uint *param_1,int param_2,ushort param_3)

{
  ushort uVar1;
  byte *pbVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  int iVar8;
  int *piVar9;
  int *piVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  byte local_a8;
  undefined1 local_a7;
  undefined1 local_a6;
  undefined1 local_a5;
  ushort local_a4;
  undefined2 local_a2;
  char local_a0;
  char local_9f;
  short local_9e;
  short local_9c;
  undefined2 local_9a;
  undefined2 local_98;
  short local_96;
  short local_94;
  undefined2 local_92;
  undefined4 local_90;
  int local_88;
  ushort local_84;
  ushort local_80;
  uint local_78;
  int local_74;
  int local_70;
  ushort local_68;
  ushort local_60;
  int local_58;
  uint local_54;
  int local_50;
  int *local_48;
  int local_44;
  int local_40;
  uint local_3c;
  uint local_38;
  int local_34;
  int local_30;
  
  uVar5 = *param_1;
  piVar9 = DAT_800ff5c4;
  if (-1 < (int)uVar5) {
    pbVar2 = (byte *)param_1[5];
    uVar6 = (uint)*(ushort *)(pbVar2 + 2);
    if ((uVar6 != 0) && (*(ushort *)(pbVar2 + 4) != 0)) {
      local_68 = (ushort)*pbVar2;
      if (*pbVar2 == 0) {
        local_68 = 0x100;
      }
      local_60 = (ushort)pbVar2[1];
      if (pbVar2[1] == 0) {
        local_60 = 0x100;
      }
      local_74 = local_68 * uVar6;
      local_a8 = (byte)(uVar5 >> 0x1d) & 2 | (byte)(uVar5 >> 6) & 1 | 0x2c;
      local_a7 = (undefined1)param_1[4];
      local_a6 = *(undefined1 *)((int)param_1 + 0x11);
      local_70 = (uint)local_60 * (uint)*(ushort *)(pbVar2 + 4);
      uVar1 = (ushort)(uVar5 >> 0x10);
      local_80 = uVar1 >> 1 & 0x180 | uVar1 >> 7 & 0x60;
      local_a5 = *(undefined1 *)((int)param_1 + 0x12);
      local_88 = param_2;
      local_84 = param_3;
      if (((uVar5 & 0x8000000) == 0) && ((param_1[7] != 0x10001000 || (param_1[8] != 0)))) {
        local_90 = 1;
        local_c8 = DAT_800ff4f0;
        local_c4 = DAT_800ff4f4;
        local_c0 = DAT_800ff4f8;
        local_bc = DAT_800ff4fc;
        local_b8 = DAT_800ff500;
        local_b4 = DAT_800ff504;
        local_b0 = DAT_800ff508;
        local_ac = DAT_800ff50c;
        FUN_80085e58(&local_c8,param_1[8]);
        FUN_80085f18(&local_c8,(int)(short)param_1[7],(int)*(short *)((int)param_1 + 0x1e),0x1000);
      }
      else {
        local_90 = 0;
      }
      iVar14 = (int)(short)param_1[3] % local_74;
      if (local_74 == 0) {
        trap(0x1c00);
      }
      if ((local_74 == -1) && ((short)param_1[3] == -0x80000000)) {
        trap(0x1800);
      }
      local_54 = (uint)local_60;
      local_78 = (uint)(short)param_1[2];
      uVar5 = (uint)*(short *)((int)param_1 + 10);
      if (iVar14 < 0) {
        iVar14 = iVar14 + local_74;
      }
      local_30 = (int)*(short *)((int)param_1 + 0xe) % local_70;
      if (local_70 == 0) {
        trap(0x1c00);
      }
      if ((local_70 == -1) && (*(short *)((int)param_1 + 0xe) == -0x80000000)) {
        trap(0x1800);
      }
      if (local_30 < 0) {
        local_30 = local_30 + local_70;
      }
      local_44 = local_30 % (int)local_54;
      if (local_54 == 0) {
        trap(0x1c00);
      }
      if ((local_54 == 0xffffffff) && (local_30 == -0x80000000)) {
        trap(0x1800);
      }
      local_9c = *(short *)((int)param_1 + 6);
      local_58 = (int)local_9c;
      uVar12 = (uint)local_60 - local_44;
      if ((int)uVar5 < (int)((uint)local_60 - local_44 & 0xffff)) {
        uVar12 = uVar5;
      }
      local_50 = local_30 + uVar5;
      local_38 = (uint)local_68;
      local_48 = DAT_800ff5c4 + 1;
      local_98 = (undefined2)uVar12;
      local_34 = iVar14 + local_78;
      local_94 = -*(short *)((int)param_1 + 0x1a);
      local_3c = uVar6;
      piVar9 = DAT_800ff5c4;
      iVar11 = local_30;
      do {
        if (local_38 == 0) {
          trap(0x1c00);
        }
        if ((local_38 == 0xffffffff) && (iVar14 == -0x80000000)) {
          trap(0x1800);
        }
        local_9e = (short)param_1[1];
        iVar13 = (int)local_9e;
        uVar5 = (uint)local_68 - iVar14 % (int)local_38;
        if ((int)local_78 < (int)(uVar5 & 0xffff)) {
          uVar5 = local_78 & 0xffff;
        }
        if (local_70 == 0) {
          trap(0x1c00);
        }
        if ((local_70 == -1) && (iVar11 == -0x80000000)) {
          trap(0x1800);
        }
        if (local_74 == 0) {
          trap(0x1c00);
        }
        if ((local_74 == -1) && (iVar14 == -0x80000000)) {
          trap(0x1800);
        }
        if (local_54 == 0) {
          trap(0x1c00);
        }
        if ((local_54 == 0xffffffff) && (iVar11 % local_70 == -0x80000000)) {
          trap(0x1800);
        }
        if (local_38 == 0) {
          trap(0x1c00);
        }
        if ((local_38 == 0xffffffff) && (iVar14 % local_74 == -0x80000000)) {
          trap(0x1800);
        }
        iVar8 = (iVar14 % local_74) / (int)local_38 +
                ((iVar11 % local_70) / (int)local_54) * local_3c;
        uVar6 = (uint)*(ushort *)(iVar8 * 2 + *(int *)(param_1[5] + 0xc));
        local_40 = iVar14;
        if (uVar6 != 0xffff) {
          iVar3 = *(int *)(param_1[5] + 8);
          *piVar9 = (int)(piVar9 + 10);
          *(undefined1 *)((int)local_48 + -1) = 9;
          pcVar7 = (char *)(iVar3 + uVar6 * 8);
          local_a4 = local_80 | *(ushort *)(pcVar7 + 6) & 0x81f;
          local_a2 = *(undefined2 *)(pcVar7 + 2);
          if ((*(ushort *)(pcVar7 + 4) & 2) == 0) {
            local_a0 = *pcVar7 + (char)(iVar14 % (int)local_38);
          }
          else {
            local_a0 = *pcVar7;
          }
          if ((*(ushort *)(pcVar7 + 4) & 1) == 0) {
            local_9f = pcVar7[1] + (char)local_44;
          }
          else {
            local_9f = (((char)local_60 + pcVar7[1]) - (char)uVar12) - (char)local_44;
          }
          local_9a = (undefined2)uVar5;
          local_96 = -(short)param_1[6];
          local_92 = *(undefined2 *)(pcVar7 + 4);
          piVar9 = piVar9 + 10;
          piVar4 = local_48;
          local_48 = local_48 + 10;
          FUN_800839c8(piVar4,&local_a8,&local_c8);
        }
        if (iVar14 < local_34) {
          piVar4 = piVar9 + 1;
          do {
            iVar8 = iVar8 + 1;
            if (local_3c == 0) {
              trap(0x1c00);
            }
            if ((local_3c == 0xffffffff) && (iVar8 == -0x80000000)) {
              trap(0x1800);
            }
            if (iVar8 % (int)local_3c == 0) {
              iVar8 = iVar8 - local_3c;
            }
            iVar14 = iVar14 + (uVar5 & 0xffff);
            iVar13 = iVar13 + (uVar5 & 0xffff);
            uVar5 = local_34 - iVar14;
            if (local_38 < (uVar5 & 0xffff)) {
              uVar5 = (uint)local_68;
            }
            uVar6 = (uint)*(ushort *)(iVar8 * 2 + *(int *)(param_1[5] + 0xc));
            piVar10 = piVar4;
            if (uVar6 != 0xffff) {
              iVar3 = *(int *)(param_1[5] + 8);
              *piVar9 = (int)(piVar9 + 10);
              *(undefined1 *)((int)piVar4 + -1) = 9;
              pcVar7 = (char *)(iVar3 + uVar6 * 8);
              local_a4 = local_80 | *(ushort *)(pcVar7 + 6) & 0x81f;
              local_a2 = *(undefined2 *)(pcVar7 + 2);
              local_9e = ((short)iVar13 - (short)iVar14) + (short)local_40;
              if ((*(ushort *)(pcVar7 + 4) & 2) == 0) {
                local_a0 = *pcVar7;
              }
              else {
                local_a0 = ((char)local_68 + *pcVar7) - (char)uVar5;
              }
              if ((*(ushort *)(pcVar7 + 4) & 1) == 0) {
                local_9f = pcVar7[1] + (char)local_44;
              }
              else {
                local_9f = (((char)local_60 + pcVar7[1]) - (char)uVar12) - (char)local_44;
              }
              piVar10 = piVar4 + 10;
              local_48 = local_48 + 10;
              local_9a = (undefined2)uVar5;
              local_96 = ((short)iVar14 - (short)local_40) - (short)param_1[6];
              local_92 = *(undefined2 *)(pcVar7 + 4);
              piVar9 = piVar9 + 10;
              FUN_800839c8(piVar4,&local_a8,&local_c8);
            }
            piVar4 = piVar10;
          } while (iVar14 < local_34);
        }
        local_58 = local_58 + (uVar12 & 0xffff);
        iVar11 = iVar11 + (uVar12 & 0xffff);
        uVar12 = local_50 - iVar11;
        if (local_54 < (uVar12 & 0xffff)) {
          uVar12 = (uint)local_60;
        }
        local_98 = (undefined2)uVar12;
        local_9c = ((short)local_58 - (short)iVar11) + (short)local_30;
        local_94 = ((short)iVar11 - (short)local_30) - *(short *)((int)param_1 + 0x1a);
        local_44 = 0;
        iVar14 = local_40;
      } while (iVar11 < local_50);
      iVar14 = (uint)local_84 + *(int *)(local_88 + 8);
      if (iVar14 < 0) {
        iVar14 = 0;
      }
      if (piVar9 != DAT_800ff5c4) {
        piVar4 = (int *)(*(int *)(local_88 + 4) + iVar14 * 4);
        piVar9[-10] = *piVar4;
        *(undefined1 *)((int)piVar9 + -0x25) = 9;
        *piVar4 = (int)DAT_800ff5c4;
        *(undefined1 *)((int)piVar4 + 3) = 0;
      }
    }
  }
  DAT_800ff5c4 = piVar9;
  return;
}

