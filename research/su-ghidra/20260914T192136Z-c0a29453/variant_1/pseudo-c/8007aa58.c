/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8007aa58(int param_1)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = FUN_800746b8(0xffffffff);
  DAT_800f7148 = iVar2 + 0x3c0;
  DAT_800f714c = 0;
  DAT_800f7150 = s_CD_datasync_80011cd4;
  do {
    iVar2 = FUN_800746b8(0xffffffff);
    if ((DAT_800f7148 < iVar2) ||
       (iVar2 = DAT_800f714c + 1, bVar1 = 0x3c0000 < DAT_800f714c, DAT_800f714c = iVar2, bVar1)) {
      FUN_80090cf8(s_CD_timeout__80011bc8);
      FUN_8008fa78(s__s___s__Sync__s__Ready__s_80011bd8,DAT_800f7150,
                   (&PTR_s_CdlSync_80094934)[DAT_8009492d],(&PTR_s_NoIntr_800949b4)[DAT_80094bec],
                   (&PTR_s_NoIntr_800949b4)[DAT_80094bed]);
      FUN_8007a668();
      iVar2 = -1;
    }
    else {
      iVar2 = 0;
    }
    uVar3 = 0xffffffff;
  } while (((iVar2 == 0) && (uVar3 = 0, (*DAT_80094c08 & 0x1000000) != 0)) &&
          (uVar3 = 1, param_1 == 0));
  return uVar3;
}

