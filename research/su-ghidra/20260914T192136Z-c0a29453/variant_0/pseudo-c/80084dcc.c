/* Analysis pseudo-C, not buildable source. */

void FUN_80084dcc(undefined2 param_1,undefined2 param_2,uint param_3,undefined1 param_4,
                 undefined1 param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if ((param_3 >> 4 & 3) == 3) {
    uVar2 = 3;
  }
  FUN_8007f8e8(uVar2);
  DAT_800ff3da = 0;
  DAT_800ff3d8 = 0;
  DAT_800ff3e2 = 0;
  DAT_800ff3e0 = 0;
  DAT_800ff3de = 0;
  DAT_800ff3dc = 0;
  DAT_800ff3e4 = 0;
  DAT_800ff3e7 = 0;
  DAT_800ff3e8 = 0;
  DAT_800ff3e6 = param_4;
  FUN_800802c8(&DAT_800ff3d0);
  DAT_800ff430 = 0;
  DAT_800ff432 = 0;
  DAT_800ff438._0_2_ = 0;
  DAT_800ff438._2_2_ = 0;
  DAT_800ff43c._0_2_ = 0;
  DAT_800ff43c._2_2_ = 0;
  DAT_800ff434._0_2_ = param_1;
  DAT_800ff434._2_2_ = param_2;
  iVar1 = FUN_800753bc();
  if (iVar1 == 1) {
    DAT_800ff438._2_2_ = 0x18;
    DAT_800ff440._2_1_ = 1;
  }
  DAT_800ff440._0_1_ = (byte)param_3 & 1;
  DAT_800ff456 = (ushort)param_3 & 4;
  DAT_800ff440._1_1_ = param_5;
  FUN_80080494();
  return;
}

