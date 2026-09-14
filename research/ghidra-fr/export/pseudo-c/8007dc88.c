/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8007dc88(void)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  byte *pbVar5;
  undefined *puVar6;
  int iVar7;
  
  pbVar5 = &DAT_800f8f18;
  iVar3 = FUN_8007e28c(1,0x10,&DAT_800f8f18);
  if (iVar3 == 1) {
    iVar3 = FUN_8008f988(&DAT_800f8f19,s_CD001_80011e84,5);
    uVar2 = DAT_800f8fa4;
    if (iVar3 == 0) {
      iVar3 = FUN_8007e28c(1,DAT_800f8fa4,&DAT_800f8f18);
      if (iVar3 == 1) {
        if (1 < DAT_80094918) {
          FUN_80090cf8(s_DS_newmedia__sarching_dir___80011ee0);
        }
        iVar3 = 0;
        do {
          iVar7 = iVar3;
          if (*pbVar5 == 0) break;
          (&DAT_800f7920)[iVar3 * 0xb] = *(undefined4 *)(pbVar5 + 2);
          puVar6 = &DAT_800f7924 + iVar3 * 0x2c;
          bVar1 = pbVar5[6];
          iVar7 = iVar3 + 1;
          (&DAT_800f7918)[iVar3 * 0xb] = iVar7;
          (&DAT_800f791c)[iVar3 * 0xb] = (uint)bVar1;
          FUN_8008f508(puVar6,pbVar5 + 8,*pbVar5);
          puVar6[*pbVar5] = 0;
          pbVar5 = pbVar5 + (uint)*pbVar5 + (*pbVar5 & 1) + 8;
          if (1 < DAT_80094918) {
            FUN_8008fa78(s__08x__04x__04x__s_80011f00,(&DAT_800f7920)[iVar3 * 0xb],
                         (&DAT_800f7918)[iVar3 * 0xb],(&DAT_800f791c)[iVar3 * 0xb],puVar6);
          }
          if (0x7f < iVar7) goto LAB_8007def4;
          iVar3 = iVar7;
        } while (pbVar5 < &DAT_800f9718);
        if (iVar7 < 0x80) {
          (&DAT_800f791c)[iVar7 * 0xb] = 0;
        }
LAB_8007def4:
        DAT_80094e38 = 0;
        uVar4 = 1;
        if (1 < DAT_80094918) {
          FUN_8008fa78(s_DS_newmedia___d_dir_entries_foun_80011f14,iVar7);
          uVar4 = 1;
        }
      }
      else {
        uVar4 = 0;
        if (0 < DAT_80094918) {
          FUN_8008fa78(s_DS_newmedia__Read_error__PT__08x_80011ebc,uVar2);
          uVar4 = 0;
        }
      }
    }
    else {
      uVar4 = 0;
      if (0 < DAT_80094918) {
        FUN_80090cf8(s_DS_newmedia__Disc_format_error_i_80011e8c);
        uVar4 = 0;
      }
    }
  }
  else {
    uVar4 = 0;
    if (0 < DAT_80094918) {
      FUN_80090cf8(s_DS_newmedia__Read_error_in_ds_re_80011e58);
      uVar4 = 0;
    }
  }
  return uVar4;
}

