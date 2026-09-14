/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_800272b0(void)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
  int iVar10;
  int local_48;
  int local_44 [5];
  int local_30 [6];
  
  piVar9 = local_30;
  iVar4 = FUN_80026cf4(piVar9,0,0x14);
  if (iVar4 != 0) {
    if (iVar4 != 1) {
      FUN_80035dfc(iVar4);
    }
    uVar5 = FUN_8008f708();
    if ((uVar5 & 1) != 0) {
      FUN_80026da0(&local_48,5,0xffffffff);
      iVar4 = local_48;
      iVar10 = local_30[0];
      while (local_48 = iVar4, iVar10 != 0) {
        if (iVar4 != 0) {
          piVar8 = &local_48;
          do {
            iVar6 = FUN_800199f0((int)*(short *)(iVar10 + 0xc),(int)*(short *)(iVar4 + 0xc));
            piVar8 = piVar8 + 1;
            if (iVar6 != 0) {
              cVar1 = *(char *)(iVar10 + 0x18);
              DAT_800ec211 = '\0';
              cVar2 = *(char *)(iVar4 + 0x18) % '\x05';
              goto LAB_800274c4;
            }
            iVar4 = *piVar8;
          } while (iVar4 != 0);
        }
        piVar9 = piVar9 + 1;
        iVar4 = local_48;
        iVar10 = *piVar9;
      }
      iVar4 = FUN_80026c94(5);
      if (iVar4 < 0) {
        return 1;
      }
      FUN_80026cf4(&local_48,0,0x14);
      iVar10 = 0;
      iVar6 = local_48;
      while (local_30[0] != 0) {
        local_48 = iVar6;
        if (iVar6 != 0) {
          piVar9 = &local_48;
          do {
            if ((*(char *)(local_30[0] + 0x18) != *(char *)(iVar6 + 0x18)) &&
               (iVar7 = FUN_800199f0((int)*(short *)(local_30[0] + 0xc),(int)*(short *)(iVar6 + 0xc)
                                    ), iVar7 != 0)) {
              cVar1 = *(char *)(local_30[0] + 0x18);
              DAT_800ec212 = 0;
              cVar2 = (char)iVar4 + (char)(iVar4 / 5) * -5;
              DAT_800ec211 = *(char *)(iVar6 + 0x18) % '\x05' + '\v';
LAB_800274c4:
              DAT_800ec216 = cVar2 + '\x01';
              DAT_800ec210 = cVar1 % '\x05' + '\v';
              bVar3 = FUN_8008f708();
              DAT_800ec217 = bVar3 & 1;
              DAT_800ec218 = 0;
              return 0;
            }
            piVar9 = piVar9 + 1;
            iVar6 = *piVar9;
          } while (iVar6 != 0);
        }
        iVar10 = iVar10 + 1;
        iVar6 = local_48;
        local_30[0] = local_30[iVar10];
      }
    }
  }
  return 1;
}

