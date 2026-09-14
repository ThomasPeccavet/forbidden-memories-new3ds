/* Analysis pseudo-C, not buildable source. */

void FUN_80072d88(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  puVar4 = &DAT_800f6f70;
  iVar7 = 0;
  if (DAT_800f700c != 0) {
    iVar8 = 0x84;
    do {
      if (puVar4[0xaa] == '\0') {
        iVar6 = (int)*(short *)(&DAT_801ab000 + iVar8);
        if (((iVar6 != 0) && (iVar1 = FUN_80070f4c(DAT_800f700e,iVar7 + 0xb), iVar1 == 0)) &&
           ((iVar1 = FUN_800199f0(param_1,iVar6), iVar1 != 0 ||
            (iVar1 = FUN_80019998(param_1,iVar6), iVar1 != 0)))) {
          (&DAT_800f7014)[DAT_800f7012] = (char)(iVar7 + 0xb);
          iVar6 = FUN_8002cdc8(iVar1,0);
          if (((int)(uint)DAT_800f7010 < iVar6) ||
             ((uVar2 = FUN_8002cdc8(iVar1,0), uVar2 == DAT_800f7010 && (DAT_800f7012 < DAT_800f7013)
              ))) {
            DAT_800f7010 = FUN_8002cdc8(iVar1,0);
            DAT_800f7013 = DAT_800f7012;
            puVar3 = &DAT_800f6f70;
            iVar6 = 0;
            do {
              iVar5 = iVar6;
              puVar3[0x38] = puVar3[0xa4];
              puVar3 = &DAT_800f6f71 + iVar5;
              iVar6 = iVar5 + 1;
            } while (iVar5 + 1 <= (int)(uint)DAT_800f7013);
            (&DAT_800f6fa9)[iVar5] = 0;
          }
          iVar6 = FUN_8002cdc8(iVar1,1);
          if (((int)(uint)DAT_800f7010 < iVar6) ||
             ((uVar2 = FUN_8002cdc8(iVar1,1), uVar2 == DAT_800f7010 && (DAT_800f7012 < DAT_800f7013)
              ))) {
            DAT_800f7010 = FUN_8002cdc8(iVar1,1);
            DAT_800f7013 = DAT_800f7012;
            puVar3 = &DAT_800f6f70;
            iVar6 = 0;
            do {
              iVar5 = iVar6;
              puVar3[0x38] = puVar3[0xa4];
              puVar3 = &DAT_800f6f71 + iVar5;
              iVar6 = iVar5 + 1;
            } while (iVar5 + 1 <= (int)(uint)DAT_800f7013);
            (&DAT_800f6fa9)[iVar5] = 0;
          }
          if ((int)(uint)DAT_800f7012 < (int)(DAT_800f700d - 1)) {
            puVar4[0xaa] = 1;
            DAT_800f7012 = DAT_800f7012 + 1;
            FUN_80072d88(iVar1);
            puVar4[0xaa] = 0;
            DAT_800f7012 = DAT_800f7012 - 1;
          }
        }
      }
      puVar4 = puVar4 + 1;
      iVar7 = iVar7 + 1;
      iVar8 = iVar8 + 0xc;
    } while (iVar7 < (int)(uint)DAT_800f700c);
  }
  return;
}

