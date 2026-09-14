/* Analysis pseudo-C, not buildable source. */

uint FUN_80079c8c(int param_1,undefined1 *param_2)

{
  byte bVar1;
  undefined1 uVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  undefined1 *puVar6;
  
  iVar4 = FUN_800746b8(0xffffffff);
  DAT_800f7148 = iVar4 + 0x3c0;
  DAT_800f714c = 0;
  DAT_800f7150 = s_CD_sync_80011c50;
  while( true ) {
    iVar4 = FUN_800746b8(0xffffffff);
    if ((DAT_800f7148 < iVar4) ||
       (iVar4 = DAT_800f714c + 1, bVar3 = 0x3c0000 < DAT_800f714c, DAT_800f714c = iVar4, bVar3)) {
      FUN_80090cf8(s_CD_timeout__80011bc8);
      FUN_8008fa78(s__s___s__Sync__s__Ready__s_80011bd8,DAT_800f7150,
                   (&PTR_s_CdlSync_80094934)[DAT_8009492d],(&PTR_s_NoIntr_800949b4)[DAT_80094bec],
                   (&PTR_s_NoIntr_800949b4)[DAT_80094bed]);
      FUN_8007a668();
      iVar4 = -1;
    }
    else {
      iVar4 = 0;
    }
    if (iVar4 != 0) {
      return 0xffffffff;
    }
    iVar4 = FUN_80074a2c();
    if (iVar4 != 0) {
      bVar1 = *DAT_80094bd4;
      while( true ) {
        uVar5 = FUN_80079728();
        if (uVar5 == 0) break;
        if (((uVar5 & 4) != 0) && (DAT_80094914 != (code *)0x0)) {
          (*DAT_80094914)(DAT_80094bed,&DAT_800f7138);
        }
        if (((uVar5 & 2) != 0) && (DAT_80094910 != (code *)0x0)) {
          (*DAT_80094910)(DAT_80094bec,&DAT_800f7130);
        }
      }
      *DAT_80094bd4 = bVar1 & 3;
    }
    uVar5 = (uint)DAT_80094bec;
    if ((uVar5 == 2) || (uVar5 == 5)) break;
    if (param_1 != 0) {
      return 0;
    }
  }
  DAT_80094bec = 2;
  puVar6 = &DAT_800f7130;
  iVar4 = 7;
  if (param_2 == (undefined1 *)0x0) {
    DAT_80094bec = 2;
    return uVar5;
  }
  do {
    uVar2 = *puVar6;
    puVar6 = puVar6 + 1;
    iVar4 = iVar4 + -1;
    *param_2 = uVar2;
    param_2 = param_2 + 1;
  } while (iVar4 != -1);
  return uVar5;
}

