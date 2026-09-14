/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_8007dff0(int param_1)

{
  int iVar1;
  byte *pbVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  
  if (param_1 != DAT_80094e38) {
    pbVar2 = &DAT_800f8f18;
    iVar1 = FUN_8007e28c(1,*(undefined4 *)(&DAT_800f78f4 + param_1 * 0x2c),&DAT_800f8f18);
    if (iVar1 != 1) {
      if (DAT_80094918 < 1) {
        return 0xffffffff;
      }
      FUN_80090cf8(s_DS_cachefile__dir_not_found_80011f38);
      return 0xffffffff;
    }
    if (1 < DAT_80094918) {
      FUN_80090cf8(s_DS_cachefile__searching____80011f58);
    }
    iVar3 = 0;
    puVar5 = &DAT_800f7318;
    puVar4 = &DAT_800f7320;
    iVar1 = 0;
    while (*pbVar2 != 0) {
      FUN_8007eb98(*(undefined4 *)(pbVar2 + 2),puVar5);
      *(undefined4 *)((int)&DAT_800f731c + iVar1) = *(undefined4 *)(pbVar2 + 10);
      if (iVar3 == 0) {
        _DAT_800f7320 = DAT_80011f74;
      }
      else if (iVar3 == 1) {
        DAT_800f7338 = DAT_80011f78;
        DAT_800f733a = DAT_80011f7a;
      }
      else {
        FUN_8008f508(puVar4,pbVar2 + 0x21,pbVar2[0x20]);
        puVar4[pbVar2[0x20]] = 0;
      }
      if (1 < DAT_80094918) {
        FUN_8008fa78(s___02x__02x__02x___8d__s_80011f7c,(&DAT_800f7318)[iVar1],
                     (&DAT_800f7319)[iVar1],(&DAT_800f731a)[iVar1],
                     *(undefined4 *)((int)&DAT_800f731c + iVar1),puVar4);
      }
      puVar4 = puVar4 + 0x18;
      iVar1 = iVar1 + 0x18;
      iVar3 = iVar3 + 1;
      pbVar2 = pbVar2 + *pbVar2;
      puVar5 = puVar5 + 0x18;
      if ((0x3f < iVar3) || ((byte *)0x800f9717 < pbVar2)) break;
    }
    DAT_80094e38 = param_1;
    if (iVar3 < 0x40) {
      (&DAT_800f7320)[iVar3 * 0x18] = 0;
    }
    if (DAT_80094918 < 2) {
      return 1;
    }
    FUN_8008fa78(s_DS_cachefile___d_files_found_80011f98,iVar3);
  }
  return 1;
}

