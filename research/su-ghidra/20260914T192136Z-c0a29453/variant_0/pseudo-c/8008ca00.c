/* Analysis pseudo-C, not buildable source. */

int FUN_8008ca00(uint param_1,undefined4 param_2,int param_3,int *param_4,int param_5,int param_6)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined1 auStack_80 [32];
  undefined4 local_60 [10];
  int local_38;
  int *local_34;
  undefined4 *local_30;
  
  local_34 = param_4;
  if (DAT_800ff6d0 == 0) {
    FUN_8008cffc(param_1,auStack_80);
    FUN_8008f748(auStack_80,param_2);
    iVar10 = 0;
    iVar2 = 0;
    local_38 = 0;
    DAT_800ff6dc = DAT_800ff6dc | 1 << (param_1 & 0x1f);
    iVar12 = 0;
    if (0 < param_5 + param_6) {
      local_30 = local_60 + 8;
      iVar11 = 0;
      do {
        if (iVar2 == 0) {
          while( true ) {
            FUN_8008d4e8();
            iVar3 = FUN_80074008(auStack_80,local_60);
            if (iVar3 != 0) break;
            uVar4 = FUN_8008d6c8();
            local_38 = FUN_8008cefc(uVar4);
            iVar3 = 0;
            if (local_38 == 0) goto LAB_8008cb98;
            iVar10 = iVar10 + 1;
            if (3 < iVar10) {
              DAT_800ff728 = FUN_8008cc5c(0);
              if (DAT_800ff6d0 < 1) {
                DAT_800ff6d0 = 2;
                DAT_800ff6d4 = 0;
                DAT_800ff6d8 = 0;
                DAT_800ff6e0 = param_1;
                FUN_8008d068(FUN_8008bc80);
              }
              else {
                FUN_8008fa78(s_Access_Denied____event_multiple_o_8001236c);
              }
              FUN_8008cc70(0,0,&local_38);
              FUN_8008cc5c(DAT_800ff728);
              return local_38;
            }
          }
        }
        else {
          iVar3 = FUN_80073e68(local_60);
LAB_8008cb98:
          if (iVar3 == 0) break;
        }
        if ((param_5 <= iVar2) && (param_3 != 0)) {
          puVar8 = local_60;
          puVar1 = (undefined4 *)(iVar11 + param_3);
          do {
            puVar9 = puVar1;
            puVar7 = puVar8;
            uVar4 = puVar7[1];
            uVar5 = puVar7[2];
            uVar6 = puVar7[3];
            *puVar9 = *puVar7;
            puVar9[1] = uVar4;
            puVar9[2] = uVar5;
            puVar9[3] = uVar6;
            puVar8 = puVar7 + 4;
            puVar1 = puVar9 + 4;
          } while (puVar8 != local_30);
          uVar4 = puVar7[5];
          puVar9[4] = *puVar8;
          puVar9[5] = uVar4;
          iVar11 = iVar11 + 0x28;
          iVar12 = iVar12 + 1;
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < param_5 + param_6);
    }
    iVar2 = 0;
    if (local_34 != (int *)0x0) {
      *local_34 = iVar12;
    }
  }
  else {
    FUN_8008fa78(s_Access_Denied____system_busy_80012510);
    iVar2 = -1;
  }
  return iVar2;
}

