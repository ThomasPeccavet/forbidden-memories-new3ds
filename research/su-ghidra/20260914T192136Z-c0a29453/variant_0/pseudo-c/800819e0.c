/* Analysis pseudo-C, not buildable source. */

uint FUN_800819e0(code *param_1,undefined4 *param_2,int param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  
  FUN_80082168();
  while( true ) {
    if ((DAT_80095bc0 + 1 & 0x3f) != DAT_80095bc4) {
      DAT_80095bc8 = FUN_80074a54(0);
      DAT_80095aa0 = 1;
      if ((DAT_80095a99 == '\0') ||
         (((DAT_80095bc0 == DAT_80095bc4 && ((*DAT_80095bac & 0x1000000) == 0)) &&
          (DAT_80095aa4 == 0)))) {
        do {
        } while ((*DAT_80095ba0 & 0x4000000) == 0);
        (*param_1)(param_2,param_4);
        FUN_80074a54(DAT_80095bc8);
        uVar1 = 0;
      }
      else {
        FUN_80074938(2,FUN_80081c90);
        iVar5 = 0;
        if (param_3 == 0) {
          *(undefined4 **)(&DAT_800fdb8c + DAT_80095bc0 * 0x60) = param_2;
        }
        else {
          while( true ) {
            iVar2 = param_3;
            if (param_3 < 0) {
              iVar2 = param_3 + 3;
            }
            iVar3 = iVar5 * 4;
            if (iVar2 >> 2 <= iVar5) break;
            uVar4 = *param_2;
            param_2 = param_2 + 1;
            iVar5 = iVar5 + 1;
            *(undefined4 *)(&DAT_800fdb94 + iVar3 + DAT_80095bc0 * 0x60) = uVar4;
          }
          *(undefined **)(&DAT_800fdb8c + DAT_80095bc0 * 0x60) = &DAT_800fdb94 + DAT_80095bc0 * 0x60
          ;
        }
        *(undefined4 *)(&DAT_800fdb90 + DAT_80095bc0 * 0x60) = param_4;
        *(code **)(&DAT_800fdb88 + DAT_80095bc0 * 0x60) = param_1;
        DAT_80095bc0 = DAT_80095bc0 + 1 & 0x3f;
        FUN_80074a54(DAT_80095bc8);
        FUN_80081c90();
        uVar1 = DAT_80095bc0 - DAT_80095bc4 & 0x3f;
      }
      return uVar1;
    }
    iVar5 = FUN_8008219c();
    if (iVar5 != 0) break;
    FUN_80081c90();
  }
  return 0xffffffff;
}

