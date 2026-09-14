/* Analysis pseudo-C, not buildable source. */

int FUN_8007ef48(undefined2 param_1,undefined2 param_2,int param_3,undefined2 param_4,int param_5,
                int param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined2 local_30;
  undefined2 local_2e;
  undefined2 local_2c;
  undefined2 local_2a;
  
  if (DAT_80095038 < 8) {
    if (DAT_80095038 == 0) {
      DAT_80095a40 = 0;
    }
    iVar3 = DAT_80095a40;
    iVar1 = DAT_80095038 * 0x30;
    *(uint *)(&DAT_80094ee4 + iVar1) = (uint)(param_3 == 0);
    if (0x400 < iVar3 + param_6) {
      param_6 = 0x400 - iVar3;
    }
    local_2c = 0x100;
    local_2a = 0x100;
    local_30 = 0;
    local_2e = 0;
    FUN_80082f48(iVar1 + -0x7ff6b138,0,0,DAT_800fdb30,&local_30);
    if (param_5 != 0) {
      FUN_80082f28(&DAT_80094eb8 + DAT_80095038 * 0x30);
      (&DAT_80094ebc)[DAT_80095038 * 0x30] = 0;
      (&DAT_80094ebd)[DAT_80095038 * 0x30] = 0;
      (&DAT_80094ebe)[DAT_80095038 * 0x30] = 0;
      FUN_80082da8(&DAT_80094eb8 + DAT_80095038 * 0x30,param_5 == 2);
    }
    iVar3 = DAT_80095a40;
    iVar1 = DAT_80095038 * 0x30;
    iVar2 = DAT_80095a40 + DAT_80095038;
    *(undefined2 *)(&DAT_80094ec0 + iVar1) = param_1;
    *(undefined2 *)(&DAT_80094ec2 + iVar1) = param_2;
    *(short *)(&DAT_80094ec4 + iVar1) = (short)param_3;
    *(undefined2 *)(&DAT_80094ec6 + iVar1) = param_4;
    *(undefined **)(&DAT_80094edc + iVar1) = &DAT_800f9728 + iVar2;
    *(int *)(&DAT_80094ed4 + iVar1) = param_6;
    *(undefined **)(&DAT_80094ed8 + iVar1) = &DAT_800f9b30 + iVar3 * 0x10;
    *(undefined4 *)(&DAT_80094ee0 + iVar1) = 0;
    **(undefined1 **)(&DAT_80094edc + iVar1) = 0;
    iVar3 = *(int *)(&DAT_80094ed8 + DAT_80095038 * 0x30);
    iVar1 = 0;
    if (0 < param_6) {
      do {
        FUN_80082f08(iVar3);
        iVar1 = iVar1 + 1;
        *(undefined2 *)(iVar3 + 0xe) = DAT_800fdb32;
        iVar3 = iVar3 + 0x10;
      } while (iVar1 < param_6);
    }
    DAT_80095a40 = DAT_80095a40 + param_6;
    iVar3 = DAT_80095038;
    DAT_80095038 = DAT_80095038 + 1;
  }
  else {
    iVar3 = -1;
  }
  return iVar3;
}

