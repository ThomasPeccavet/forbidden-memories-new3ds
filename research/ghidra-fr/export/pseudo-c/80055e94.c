/* Analysis pseudo-C, not buildable source. */

void FUN_80055e94(int param_1,short *param_2,short *param_3,int param_4)

{
  bool bVar1;
  int iVar2;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  FUN_8008f548(&local_28,0,8);
  local_30 = CONCAT22((undefined2)DAT_800f6c2c,(short)DAT_800f6c28);
  local_24 = CONCAT22(local_24._2_2_,(undefined2)DAT_800f6c30);
  local_2c = local_24;
  local_28 = local_30;
  FUN_8008f548(&local_20,0,8);
  local_28 = CONCAT22((undefined2)DAT_800f6c38,(short)DAT_800f6c34);
  local_1c = CONCAT22(local_1c._2_2_,(undefined2)DAT_800f6c3c);
  local_24 = local_1c;
  local_20 = local_28;
  iVar2 = FUN_8004f184();
  if ((iVar2 == 1) && (iVar2 = FUN_8004f19c(), iVar2 == 1)) {
    return;
  }
  if ((param_2 != (short *)0x0) || (param_1 < 1)) {
    iVar2 = (int)param_2 + -1;
    if ((int)param_2 < 1) {
      DAT_800f4072 = 0xffff;
      DAT_800f406a = 0xffff;
    }
    else {
      param_2 = &DAT_800f4f48 + iVar2 * 0x710;
      DAT_800f4072 = (ushort)iVar2;
      if (param_4 < 0) {
        DAT_800f406a = 0xffff;
      }
      else {
        DAT_800f406a = DAT_800f4072 ^ 1;
      }
    }
  }
  if ((param_3 != (short *)0x0) || (param_1 < 1)) {
    iVar2 = (int)param_3 + -1;
    if ((int)param_3 < 1) {
      DAT_800f4082 = 0xffff;
      DAT_800f407a = 0xffff;
    }
    else {
      param_3 = &DAT_800f4f48 + iVar2 * 0x710;
      DAT_800f4082 = (ushort)iVar2;
      if (param_4 < 0) {
        DAT_800f407a = 0xffff;
      }
      else {
        DAT_800f407a = DAT_800f4082 ^ 1;
      }
    }
    if (param_1 < 0) goto LAB_80056074;
  }
  DAT_800f4058 = (undefined1)param_1;
LAB_80056074:
  DAT_800f405a = 300;
  DAT_800f405e = 8;
  DAT_800f405c = 8;
  bVar1 = param_2 == (short *)0x0;
  if (bVar1) {
    param_2 = (short *)&local_30;
  }
  DAT_800f4059 = !bVar1;
  if (param_3 == (short *)0x0) {
    param_3 = (short *)&local_28;
  }
  else {
    DAT_800f4059 = DAT_800f4059 | 2;
  }
  DAT_800f4064 = (short)local_30;
  DAT_800f4066 = local_30._2_2_;
  DAT_800f4068 = (undefined2)local_2c;
  DAT_800f406c = *param_2;
  DAT_800f406e = param_2[1];
  DAT_800f4070 = param_2[2];
  DAT_800f4074 = (short)local_28;
  DAT_800f4076 = local_28._2_2_;
  DAT_800f4078 = (undefined2)local_24;
  DAT_800f407c = *param_3;
  DAT_800f407e = param_3[1];
  if (param_4 < 0) {
    param_4 = -param_4;
  }
  param_4 = param_4 << 1;
  DAT_800f4080 = param_3[2];
  if (param_4 < 0xffff) {
    DAT_800f4062 = (undefined2)param_4;
  }
  else {
    DAT_800f4062 = 0xffff;
  }
  DAT_800f4060 = 0;
  if (DAT_800f4059 != 0) {
    DAT_8009c328 = 0;
  }
  if (param_4 == 0) {
    if ((DAT_800f4059 & 1) != 0) {
      DAT_800f6c28 = (int)DAT_800f406c;
      DAT_800f6c2c = (int)DAT_800f406e;
      DAT_800f6c30 = (int)DAT_800f4070;
    }
    if ((DAT_800f4059 & 2) != 0) {
      DAT_800f6c34 = (int)DAT_800f407c;
      DAT_800f6c38 = (int)DAT_800f407e;
      DAT_800f6c3c = (int)DAT_800f4080;
    }
    if (DAT_800f4059 != 0) {
      FUN_8005b0bc(0);
    }
    DAT_800f4059 = 0;
  }
  return;
}

