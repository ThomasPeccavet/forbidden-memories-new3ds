/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8007a1d4(byte param_1,undefined1 *param_2,undefined1 *param_3,int param_4)

{
  byte bVar1;
  undefined1 uVar2;
  bool bVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  
  if (1 < DAT_80094918) {
    FUN_8008fa78(s__s____80011c64,(&PTR_s_CdlSync_80094934)[param_1]);
  }
  if ((*(int *)(&DAT_80094b54 + (uint)param_1 * 4) == 0) || (param_2 != (undefined1 *)0x0)) {
    FUN_80079c8c(0,0);
    if (param_1 == 2) {
      iVar7 = 0;
      puVar5 = param_2;
      do {
        (&DAT_80094928)[iVar7] = *puVar5;
        iVar7 = iVar7 + 1;
        puVar5 = param_2 + iVar7;
      } while (iVar7 < 4);
    }
    if (param_1 == 0xe) {
      DAT_8009492c = *param_2;
    }
    iVar7 = (uint)param_1 * 4;
    DAT_80094bec = 0;
    if (*(int *)(&DAT_80094a54 + iVar7) != 0) {
      DAT_80094bed = 0;
    }
    *DAT_80094bd4 = 0;
    iVar8 = 0;
    puVar5 = param_2;
    if (0 < *(int *)(&DAT_80094b54 + iVar7)) {
      do {
        *DAT_80094be4 = *puVar5;
        iVar8 = iVar8 + 1;
        puVar5 = param_2 + iVar8;
      } while (iVar8 < *(int *)(&DAT_80094b54 + iVar7));
    }
    DAT_8009492d = param_1;
    *DAT_80094be0 = param_1;
    uVar4 = 0;
    if (param_4 == 0) {
      iVar7 = FUN_800746b8(0xffffffff);
      DAT_800f7148 = iVar7 + 0x3c0;
      DAT_800f714c = 0;
      DAT_800f7150 = s_CD_cw_80011c7c;
      while (DAT_80094bec == 0) {
        iVar7 = FUN_800746b8(0xffffffff);
        if ((DAT_800f7148 < iVar7) ||
           (iVar7 = DAT_800f714c + 1, bVar3 = 0x3c0000 < DAT_800f714c, DAT_800f714c = iVar7, bVar3))
        {
          FUN_80090cf8(s_CD_timeout__80011bc8);
          FUN_8008fa78(s__s___s__Sync__s__Ready__s_80011bd8,DAT_800f7150,
                       (&PTR_s_CdlSync_80094934)[DAT_8009492d],
                       (&PTR_s_NoIntr_800949b4)[DAT_80094bec],(&PTR_s_NoIntr_800949b4)[DAT_80094bed]
                      );
          FUN_8007a668();
          iVar7 = -1;
        }
        else {
          iVar7 = 0;
        }
        if (iVar7 != 0) {
          return 0xffffffff;
        }
        iVar7 = FUN_80074a2c();
        if (iVar7 != 0) {
          bVar1 = *DAT_80094bd4;
          while( true ) {
            uVar6 = FUN_80079728();
            if (uVar6 == 0) break;
            if (((uVar6 & 4) != 0) && (DAT_80094914 != (code *)0x0)) {
              (*DAT_80094914)(DAT_80094bed,&DAT_800f7138);
            }
            if (((uVar6 & 2) != 0) && (DAT_80094910 != (code *)0x0)) {
              (*DAT_80094910)(DAT_80094bec,&DAT_800f7130);
            }
          }
          *DAT_80094bd4 = bVar1 & 3;
        }
      }
      puVar5 = &DAT_800f7130;
      iVar7 = 7;
      if (param_3 != (undefined1 *)0x0) {
        do {
          uVar2 = *puVar5;
          puVar5 = puVar5 + 1;
          iVar7 = iVar7 + -1;
          *param_3 = uVar2;
          param_3 = param_3 + 1;
        } while (iVar7 != -1);
      }
      uVar4 = 0;
      if (DAT_80094bec == 5) {
        uVar4 = 0xffffffff;
      }
    }
  }
  else {
    uVar4 = 0xfffffffe;
    if (0 < DAT_80094918) {
      FUN_8008fa78(s__s__no_param_80011c6c,(&PTR_s_CdlSync_80094934)[param_1]);
      uVar4 = 0xfffffffe;
    }
  }
  return uVar4;
}

