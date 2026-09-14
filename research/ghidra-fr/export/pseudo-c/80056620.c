/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80056620(void)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  char *pcVar6;
  ushort *puVar7;
  undefined *puVar8;
  char *pcVar9;
  int iVar10;
  uint local_40 [2];
  uint local_38;
  uint local_30;
  uint local_2c;
  uint local_28;
  
  iVar10 = 0;
  pcVar9 = s__cff0_8009c39c;
  if (DAT_8009c32a == -2) {
    return 1;
  }
  if ('\'' < DAT_8009c32a) {
    return 0;
  }
  if (((DAT_8009c72c & 0x20) != 0) || ((DAT_8009c72e & 0x20) != 0)) {
    DAT_8009c32a = 0x28;
    return 0;
  }
  if (DAT_800f6bd7 == '\0') {
    FUN_8005cbf4(1);
    FUN_8007f520(s_LOAD_STAGE__d__d__80011444,DAT_800f6bb0,DAT_800f6bcc);
    if (DAT_800f6bcc == -1) {
      if ((DAT_8009c460 & 0x2000030) == 0 && DAT_8009c484 == 0) {
        FUN_8005967c(2,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0);
      }
    }
    else {
      FUN_800599a0(2);
    }
    if (DAT_800f6bd7 != '\0') {
      DAT_8009c396 = *(short *)(PTR_DAT_8009c318 + 0xa4);
      iVar3 = (int)DAT_8009c396;
      if (DAT_800f6ad0 != 0) {
        *(undefined2 *)(DAT_800f6ad0 + 0x44) = 0;
        *(undefined2 *)(DAT_800f6ad0 + 0x46) = 0;
        *(undefined2 *)(DAT_800f6ad0 + 0x48) = 0;
        *(undefined4 *)(DAT_800f6ad0 + 0x18) = 0;
        *(int *)(DAT_800f6ad0 + 0x1c) = iVar3;
        *(undefined4 *)(DAT_800f6ad0 + 0x20) = 0;
      }
      FUN_8005c334(DAT_800f6ad0,0);
      DAT_8009c32a = '\0';
    }
    goto LAB_80056974;
  }
  if (DAT_800f4f97 == '\0') {
    FUN_8005cbf4(1);
    FUN_8007f520(s_LOAD_MODEL0__d__d__80011458,DAT_800f4f70,DAT_800f4f8c);
    if (DAT_800f4f8c == -1) {
      if ((DAT_8009c460 & 0x2000030) == 0 && DAT_8009c484 == 0) {
        FUN_8005967c(0,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0);
      }
    }
    else {
      FUN_800599a0(0);
    }
    uVar2 = 0;
    if (DAT_800f4f97 == '\0') goto LAB_80056974;
    bVar1 = PTR_DAT_8009c318[0xa1];
  }
  else {
    if (DAT_800f5db7 != '\0') goto LAB_80056974;
    FUN_8005cbf4(1);
    FUN_8007f520(s_LOAD_MODEL1__d__d__8001146c,DAT_800f5d90,DAT_800f5dac);
    if (DAT_800f5dac == -1) {
      if ((DAT_8009c460 & 0x2000030) == 0 && DAT_8009c484 == 0) {
        FUN_8005967c(1,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0);
      }
    }
    else {
      FUN_800599a0(1);
    }
    uVar2 = 1;
    if (DAT_800f5db7 == '\0') goto LAB_80056974;
    bVar1 = PTR_DAT_8009c318[0xa1];
  }
  FUN_8005cbb0(uVar2,(bVar1 >> 1 ^ 1) & 1);
LAB_80056974:
  if (((DAT_8009c710 & 0x100) != 0) && ((DAT_8009c72e & 0x100) != 0)) {
    DAT_8009c398 = DAT_8009c398 ^ 1;
  }
  if (DAT_8009c398 != 0) {
    if (DAT_8009c32a == -2) {
      iVar10 = 0;
      puVar8 = &DAT_800f4178;
      do {
        do {
          do {
            iVar3 = FUN_8008f708();
            uVar4 = (iVar3 >> 8) % 0x2d2;
          } while (0x2d1 < uVar4);
        } while ((((uVar4 - 300 < 0x32) || (uVar4 - 0x28a < 0x32)) || (uVar4 == 0x2d0)) ||
                ((&DAT_8009c808)[iVar10] = (short)uVar4,
                (uVar4 & 0xffff) == (uint)*(ushort *)(puVar8 + 0xdf8)));
        iVar10 = iVar10 + 1;
        puVar8 = puVar8 + 0xe20;
      } while (iVar10 < 2);
      iVar10 = 1;
      iVar3 = FUN_8008f708();
      DAT_8009c80c = (short)((uint)iVar3 >> 8) + (short)((iVar3 >> 8) / 7) * -7;
    }
    if ((DAT_8009c72c & 0x10) != 0) {
      iVar10 = iVar10 + 1;
    }
    if ((DAT_8009c728 & 0x900) != 0) {
      if ((DAT_8009c728 & 0x100) == 0) {
        uVar4 = DAT_8009c80c + 8;
      }
      else {
        uVar4 = DAT_8009c80c + 6;
      }
      DAT_8009c80c = (short)uVar4 + (short)(uVar4 / 7) * -7;
    }
    if ((DAT_8009c728 & 0xa000) != 0) {
      if ((DAT_8009c728 & 0x8000) == 0) {
        iVar3 = DAT_8009c331 + 7;
      }
      else {
        iVar3 = DAT_8009c331 + 5;
      }
      DAT_8009c331 = (char)iVar3 + (char)((ulonglong)((longlong)iVar3 * 0x2aaaaaab) >> 0x20) * -6;
    }
    if ((DAT_8009c710 & 0x80) == 0) {
      if ((DAT_8009c728 & 0x5000) != 0) {
        uVar4 = DAT_8009c331 < 3 ^ 1;
        puVar7 = &DAT_8009c808 + uVar4;
        local_30 = (*puVar7 / 100) % 10;
        local_2c = (*puVar7 / 10) % 10;
        local_28 = (uint)*puVar7 % 10;
        local_40[0] = local_30;
        local_40[1] = local_2c;
        local_38 = (uint)*puVar7 % 10;
        if ((DAT_8009c728 & 0x1000) == 0) {
          puVar5 = local_40 + (uint)DAT_8009c331 % 3;
          iVar3 = *puVar5 + 9;
        }
        else {
          puVar5 = local_40 + (uint)DAT_8009c331 % 3;
          iVar3 = *puVar5 + 0xb;
        }
        *puVar5 = iVar3 % 10;
        (&DAT_8009c808)[uVar4] =
             (short)local_38 + (short)local_40[0] * 100 + (short)local_40[1] * 10;
      }
    }
    else if ((DAT_8009c728 & 0x5000) != 0) {
      if ((DAT_8009c728 & 0x1000) == 0) {
        DAT_8009c396 = DAT_8009c396 + 10;
      }
      else {
        DAT_8009c396 = DAT_8009c396 + -10;
      }
      if (DAT_800f6bd7 != '\0') {
        iVar3 = (int)DAT_8009c396;
        if (DAT_800f6ad0 != 0) {
          *(undefined2 *)(DAT_800f6ad0 + 0x44) = 0;
          *(undefined2 *)(DAT_800f6ad0 + 0x46) = 0;
          *(undefined2 *)(DAT_800f6ad0 + 0x48) = 0;
          *(undefined4 *)(DAT_800f6ad0 + 0x18) = 0;
          *(int *)(DAT_800f6ad0 + 0x1c) = iVar3;
          *(undefined4 *)(DAT_800f6ad0 + 0x20) = 0;
        }
        FUN_8005c334(DAT_800f6ad0,0);
      }
    }
    if ((DAT_8009c72c & 4) != 0) {
      DAT_8009c80e = DAT_8009c80e ^ 1;
    }
    if ((DAT_8009c72c & 1) != 0) {
      DAT_8009c810 = DAT_8009c810 ^ 1;
    }
    if ((DAT_8009c72c & 8) != 0) {
      DAT_8009c80f = DAT_8009c80f ^ 1;
    }
    if ((DAT_8009c72c & 2) != 0) {
      DAT_8009c811 = DAT_8009c811 ^ 1;
    }
    pcVar6 = pcVar9;
    if (DAT_8009c331 == 0) {
      pcVar6 = s__cf00_8009c3a4;
    }
    FUN_8007f520(&DAT_8009c3ac,pcVar6,(DAT_8009c808 / 100) % 10);
    pcVar6 = pcVar9;
    if (DAT_8009c331 == 1) {
      pcVar6 = s__cf00_8009c3a4;
    }
    FUN_8007f520(&DAT_8009c3ac,pcVar6,(DAT_8009c808 / 10) % 10);
    pcVar6 = pcVar9;
    if (DAT_8009c331 == 2) {
      pcVar6 = s__cf00_8009c3a4;
    }
    FUN_8007f520(&DAT_8009c3ac,pcVar6,(uint)DAT_8009c808 % 10);
    FUN_8007f520(s__cff0_8009c39c);
    FUN_8007f520(s__AF__d_GF__d__80011480,DAT_8009c80e,DAT_8009c810);
    FUN_8007f520(&DAT_8009c3b4);
    pcVar6 = pcVar9;
    if (DAT_8009c331 == 3) {
      pcVar6 = s__cf00_8009c3a4;
    }
    FUN_8007f520(&DAT_8009c3ac,pcVar6,(DAT_8009c80a / 100) % 10);
    pcVar6 = pcVar9;
    if (DAT_8009c331 == 4) {
      pcVar6 = s__cf00_8009c3a4;
    }
    FUN_8007f520(&DAT_8009c3ac,pcVar6,(DAT_8009c80a / 10) % 10);
    if (DAT_8009c331 == 5) {
      pcVar9 = s__cf00_8009c3a4;
    }
    FUN_8007f520(&DAT_8009c3ac,pcVar9,(uint)DAT_8009c80a % 10);
    FUN_8007f520(s__cff0_8009c39c);
    FUN_8007f520(s__AF__d_GF__d__80011480,DAT_8009c80f,DAT_8009c811);
    FUN_8007f520(&DAT_8009c3bc);
    FUN_8007f520(s_STAGE__d_Y__d_80011490,DAT_8009c80c,(int)DAT_8009c396);
    if (iVar10 == 0) {
      return 0;
    }
    FUN_80013700();
    FUN_80056540();
    FUN_800563b0(0,DAT_8009c808,0xffffffff,0xffffffff,DAT_8009c80e,DAT_8009c810);
    FUN_800563b0(1,DAT_8009c80a,0xffffffff,0xffffffff,DAT_8009c80f,DAT_8009c811);
    FUN_800563b0(2,DAT_8009c80c);
  }
  return 0;
}

