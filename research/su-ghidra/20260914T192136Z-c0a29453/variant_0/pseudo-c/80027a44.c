/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80027a44(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  int local_60 [6];
  int local_48;
  int local_44 [5];
  int local_30 [6];
  
  DAT_800ec219 = 0;
  if ((DAT_8009c582 & 0x1000) == 0) {
    uVar1 = FUN_8008f708();
    if ((uVar1 & 3) == 0) {
      piVar5 = local_30;
      FUN_80026da0(piVar5,10,0x17);
      FUN_80026da0(&local_48,5,0xffffffff);
      iVar7 = local_48;
      while (local_30[0] != 0) {
        local_48 = iVar7;
        if (iVar7 != 0) {
          piVar6 = &local_48;
          do {
            iVar2 = FUN_80019998((int)*(short *)(local_30[0] + 0xc),(int)*(short *)(iVar7 + 0xc));
            piVar6 = piVar6 + 1;
            if (iVar2 != 0) {
              DAT_800ec219 = *(char *)(local_30[0] + 0x18) % '\x05' + '\x06';
              DAT_800ec21a = *(char *)(iVar7 + 0x18) % '\x05' + '\x01';
              DAT_800ec21b = 0;
              return 0;
            }
            iVar7 = *piVar6;
          } while (iVar7 != 0);
        }
        piVar5 = piVar5 + 1;
        iVar7 = local_48;
        local_30[0] = *piVar5;
      }
      iVar7 = FUN_80026da0(local_30,10,0x14);
      if (iVar7 != 0) {
        iVar2 = 0;
        if (iVar7 != 1) {
          iVar2 = FUN_80035dfc(iVar7);
        }
        DAT_800ec219 = *(char *)(local_30[iVar2] + 0x18) % '\x05' + '\x06';
        DAT_800ec21a = 0;
        DAT_800ec21b = 0;
        return 0;
      }
    }
    iVar7 = 10;
    do {
      uVar1 = (uint)(byte)(&DAT_800919e0)[iVar7 + (uint)DAT_8009c504 * 0x14];
      iVar7 = iVar7 + 1;
      if ((*(uint *)(&DAT_801a7aec + uVar1 * 0xe) & 0xc0000000) == 0x80000000) {
        iVar7 = FUN_80027928(&DAT_801a7ad8 + uVar1 * 7);
        if (-1 < iVar7) goto LAB_80027ca0;
        uVar3 = FUN_8008f708();
        if ((uVar3 & 3) == 0) {
          iVar7 = FUN_80027814(&DAT_801a7ad8 + uVar1 * 7);
          if (-1 < iVar7) goto LAB_80027ca0;
        }
        else {
          uVar3 = FUN_8008f708();
          iVar7 = 0;
          if ((uVar3 & 1) != 0) {
            iVar2 = 0;
            piVar5 = local_60;
            puVar4 = &DAT_801a7b64 + (DAT_8009c504 ^ 1) * 0x69;
            do {
              if ((puVar4[5] & 0x90000000) == 0x90000000) {
                *piVar5 = (int)puVar4;
                piVar5 = piVar5 + 1;
                iVar7 = iVar7 + 1;
              }
              iVar2 = iVar2 + 1;
              puVar4 = puVar4 + 7;
            } while (iVar2 < 5);
            if (iVar7 != 0) {
              iVar2 = (iVar7 + -1) * 4;
              if (iVar7 + -1 != 0) {
                iVar2 = FUN_80035dfc();
                iVar2 = iVar2 << 2;
              }
              iVar7 = (int)*(char *)(*(int *)((int)local_60 + iVar2) + 0x18);
LAB_80027ca0:
              if (*(char *)(DAT_8009c500 + 0x19) == '\0') {
                DAT_800ec219 = (char)(&DAT_801a7af0)[uVar1 * 0x1c] % '\x05' + '\x01';
                DAT_800ec21a = (char)iVar7 + (char)(iVar7 / 5) * -5 + '8';
                DAT_800ec21b = 0;
                return 0;
              }
            }
          }
        }
        DAT_800ec219 = (char)((uint)(((int)(char)(&DAT_801a7af0)[uVar1 * 0x1c] % 0xf) * 0x1000000)
                             >> 0x18) + -4;
        DAT_800ec21a = 0;
        DAT_800ec21b = 1;
        return 0;
      }
    } while (iVar7 < 0xf);
  }
  return 0;
}

