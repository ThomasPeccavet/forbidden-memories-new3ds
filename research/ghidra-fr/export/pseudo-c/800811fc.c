/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_800811fc(ushort *param_1,uint param_2)

{
  ushort uVar1;
  uint uVar2;
  
  if ((short)param_1[2] < 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = DAT_80095a9c - 1;
    if ((int)(short)param_1[2] <= DAT_80095a9c + -1) {
      uVar1 = param_1[2];
    }
  }
  param_1[2] = uVar1;
  if ((short)param_1[3] < 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = DAT_80095a9e - 1;
    if ((int)(short)param_1[3] <= DAT_80095a9e + -1) {
      uVar1 = param_1[3];
    }
  }
  param_1[3] = uVar1;
  if (((*param_1 & 0x3f) == 0) && ((param_1[2] & 0x3f) == 0)) {
    DAT_800fdb38 = 0x5ffffff;
    DAT_800fdb3c = 0xe6000000;
    DAT_800fdb44 = param_2 & 0xffffff | 0x2000000;
    DAT_800fdb40 = *DAT_80095ba0 & 0x7ff | (param_2 >> 0x1f) << 10 | 0xe1000000;
    DAT_800fdb48 = *(undefined4 *)param_1;
    DAT_800fdb4c = *(uint *)(param_1 + 2);
  }
  else {
    DAT_800fdb38 = 0x80fdb60;
    DAT_800fdb50 = param_2 & 0xffffff | 0x60000000;
    DAT_800fdb48 = 0xe6000000;
    DAT_800fdb3c = 0xe3000000;
    DAT_800fdb40 = 0xe4ffffff;
    DAT_800fdb44 = 0xe5000000;
    DAT_800fdb4c = *DAT_80095ba0 & 0x7ff | (param_2 >> 0x1f) << 10 | 0xe1000000;
    DAT_800fdb54 = *(undefined4 *)param_1;
    DAT_800fdb58 = *(undefined4 *)(param_1 + 2);
    DAT_800fdb60 = 0x3ffffff;
    uVar2 = FUN_8008198c(3);
    DAT_800fdb64 = uVar2 | 0xe3000000;
    uVar2 = FUN_8008198c(4);
    DAT_800fdb68 = uVar2 | 0xe4000000;
    uVar2 = FUN_8008198c(5);
    DAT_800fdb6c = uVar2 | 0xe5000000;
  }
  FUN_80081944(&DAT_800fdb38);
  return 0;
}

