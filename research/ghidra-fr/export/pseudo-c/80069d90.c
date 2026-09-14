/* Analysis pseudo-C, not buildable source. */

int FUN_80069d90(undefined4 *param_1,int param_2,uint param_3,undefined4 param_4,char param_5,
                undefined1 param_6)

{
  ushort uVar1;
  int iVar2;
  short local_20 [3];
  undefined2 local_1a;
  
  DAT_8009c3eb = 0;
  DAT_8009c3ec = 0;
  DAT_8009c3ed = 0xff;
  DAT_8009c3e8 = param_5;
  DAT_8009c818 = PTR_FUN_80010000;
  DAT_8009c3e9 = param_6;
  DAT_8009c3f8 = param_4;
  if (param_5 != '\0') {
    uVar1 = FUN_800852a8();
    local_20[0] = uVar1 * 0x140;
    local_20[1] = 0;
    local_20[2] = (undefined2)DAT_800ff45c;
    local_1a = (undefined2)DAT_800ff460;
    FUN_8007fde8(local_20,DAT_8009c4bb,DAT_8009c4ba,DAT_8009c4b9);
    FUN_8007fc64(0);
    FUN_800746b8(0);
    FUN_80085488();
    local_20[0] = (uVar1 ^ 1) * 0x140;
    local_20[1] = 0;
    local_20[2] = (undefined2)DAT_800ff45c;
    local_1a = (undefined2)DAT_800ff460;
    FUN_8007fde8(local_20,DAT_8009c4bb,DAT_8009c4ba,DAT_8009c4b9);
    local_20[0] = 0;
    iVar2 = DAT_800ff45c * 0x1800;
    local_20[1] = 0x100;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 0xfff;
    }
    local_20[2] = (short)(iVar2 >> 0xc);
    local_1a = (undefined2)DAT_800ff460;
    FUN_8007fde8(local_20,DAT_8009c4bb,DAT_8009c4ba,DAT_8009c4b9);
    FUN_8007fc64(0);
    FUN_800746b8(0);
    DAT_800ff454 = 1;
    FUN_80085488();
    FUN_80084ee8(0x140,0x100,4,1,1);
    FUN_80085628(0,0,0,0x100);
    DAT_800ff438._2_2_ = 0x14;
    DAT_800ff43c._2_2_ = 0x100;
  }
  if (param_1 != (undefined4 *)0x0) {
    DAT_8009c81c = *param_1;
  }
  DAT_8009c3f0 = param_2;
  if (param_2 == 0) {
    DAT_8009c3f0 = 1;
  }
  DAT_8009c3f4 = param_3;
  if (param_3 == 0) {
    DAT_8009c3f4 = 0xffff;
  }
  DAT_8009c3ee = 0;
  DAT_8009c3ef = 0;
  FUN_80090de8(0);
  FUN_80091084(&LAB_8006a704);
  FUN_800917f8(DAT_8009c818);
  FUN_80078758(DAT_8009c818 + 0x11000,0x14);
  FUN_80078808();
  FUN_800789d8(DAT_8009c3e8,DAT_8009c3f0,DAT_8009c3f4,0,&LAB_8006ab8c);
  if (4 < DAT_8009c3f4) {
    DAT_8009c3f4 = DAT_8009c3f4 - 4;
  }
  FUN_8006ab28(&DAT_8009c81c);
  iVar2 = FUN_8006a4d8(0);
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  return iVar2;
}

