/* Analysis pseudo-C, not buildable source. */

void FUN_8002bc38(void)

{
  bool bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  byte bVar7;
  int iVar8;
  undefined4 uVar9;
  
  bVar7 = DAT_800eb570 & 0xf;
  if (bVar7 == 1) {
    FUN_8002a918(&DAT_800eb570);
  }
  else if (bVar7 < 2) {
    if ((DAT_800eb570 & 0xf) == 0) {
      FUN_8002bc24(&DAT_800eb570);
    }
  }
  else if (bVar7 == 2) {
    FUN_8002ae34(&DAT_800eb570);
    iVar4 = FUN_8005bee0(0);
    if (iVar4 == 1) {
      iVar4 = FUN_8005bf70(0);
      if (iVar4 == 1) {
        iVar4 = (int)DAT_80181002;
        if (DAT_800f1200 != iVar4) {
          if (iVar4 < DAT_800f1200) {
            DAT_800f1200 = DAT_800f1200 + -8;
            bVar1 = DAT_800f1200 < iVar4;
          }
          else {
            DAT_800f1200 = DAT_800f1200 + 8;
            bVar1 = iVar4 < DAT_800f1200;
          }
          if (bVar1) {
            DAT_800f1200 = iVar4;
          }
        }
        DAT_800eb590 = DAT_800eb590 + -1;
        if (DAT_800eb590 < 1) {
          DAT_800eb590 = 300;
          uVar9 = 2;
          uVar5 = FUN_8008f708(0);
          if ((uVar5 & 1) != 0) {
            uVar9 = 7;
          }
          FUN_8005ac78(0,uVar9,1);
        }
      }
      else {
        FUN_8005c0b8(0,&DAT_80181010);
        iVar8 = (int)DAT_80181012;
        iVar4 = iVar8 - DAT_80181002;
        if (iVar4 < 0) {
          iVar4 = -iVar4;
        }
        iVar4 = iVar4 / 0x18 + 1;
        if (iVar8 < DAT_800f1200) {
          DAT_800f1200 = DAT_800f1200 - iVar4;
        }
        if (DAT_800f1200 < iVar8) {
          DAT_800f1200 = DAT_800f1200 + iVar4;
        }
      }
    }
    DAT_800f11e2 = DAT_800f11e2 + 0xc;
    FUN_80013448();
    puVar6 = (undefined4 *)FUN_8005c304();
    uVar3 = DAT_800f11fc;
    uVar2 = DAT_800f11f8;
    uVar9 = DAT_800f11f4;
    *puVar6 = DAT_800f11f0;
    puVar6[1] = uVar9;
    puVar6[2] = uVar2;
    puVar6[3] = uVar3;
    uVar3 = DAT_800f120c;
    uVar2 = DAT_800f1208;
    uVar9 = DAT_800f1204;
    puVar6[4] = DAT_800f1200;
    puVar6[5] = uVar9;
    puVar6[6] = uVar2;
    puVar6[7] = uVar3;
    FUN_8005b0bc(0);
  }
  else if (bVar7 == 3) {
    FUN_8002bc30(&DAT_800eb570);
  }
  return;
}

