/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8006a07c(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined1 *puVar3;
  undefined2 local_3d8;
  short local_3d6;
  undefined2 local_3d4;
  undefined2 local_3d2;
  undefined1 local_3d0 [960];
  
  FUN_8007fc64(0);
  FUN_80045414(0);
  DAT_8009c3eb = 1;
  FUN_80091084(0);
  FUN_80078868();
  do {
    iVar1 = FUN_8007ed88(9,0,0);
  } while (iVar1 == 0);
  if ((DAT_8009c3e9 != '\0') || (param_1 != 0)) {
    FUN_8006aa64(0,0x100);
  }
  if (DAT_8009c3e8 != '\0') {
    iVar1 = 0;
    uVar2 = FUN_800852a8();
    puVar3 = local_3d0;
    do {
      iVar1 = iVar1 + 3;
      *puVar3 = DAT_8009c4bb;
      puVar3[1] = DAT_8009c4ba;
      puVar3[2] = DAT_8009c4b9;
      puVar3 = puVar3 + 3;
    } while (iVar1 < 0x3c0);
    local_3d8 = 0;
    iVar1 = 0;
    local_3d6 = (short)(uVar2 << 8);
    local_3d4 = 0x1e0;
    local_3d2 = 1;
    if (0 < DAT_800ff460) {
      do {
        FUN_8007ff10(&local_3d8,local_3d0);
        FUN_8007fc64(0);
        iVar1 = iVar1 + 1;
        local_3d6 = local_3d6 + 1;
      } while (iVar1 < DAT_800ff460);
    }
    iVar1 = 0;
    local_3d8 = 0x140;
    local_3d6 = 0;
    local_3d2 = 1;
    local_3d4 = (undefined2)DAT_800ff45c;
    if (0 < DAT_800ff460) {
      do {
        FUN_8007ff10(&local_3d8,local_3d0);
        FUN_8007fc64(0);
        iVar1 = iVar1 + 1;
        local_3d6 = local_3d6 + 1;
      } while (iVar1 < DAT_800ff460);
    }
    FUN_8007fc64(0);
    FUN_800746b8(0);
    iVar1 = 0;
    FUN_80085488();
    local_3d6 = (short)((uVar2 ^ 1) << 8);
    local_3d4 = 0x1e0;
    local_3d8 = 0;
    local_3d2 = 1;
    if (0 < DAT_800ff460) {
      do {
        FUN_8007ff10(&local_3d8,local_3d0);
        FUN_8007fc64(0);
        iVar1 = iVar1 + 1;
        local_3d6 = local_3d6 + 1;
      } while (iVar1 < DAT_800ff460);
    }
    FUN_8007fc64(0);
    FUN_800746b8(0);
    DAT_800ff454 = 1;
    FUN_80085488();
    FUN_80084ee8(0x140,0x100,4,1,0);
    FUN_80085628(0,0,0x140,0);
    DAT_800ff438._2_2_ = 0x14;
    DAT_800ff43c._2_2_ = 0x100;
    local_3d8 = 0;
    local_3d6 = 0;
    local_3d4 = (undefined2)(DAT_800ff45c << 1);
    local_3d2 = (undefined2)DAT_800ff460;
    FUN_8007fde8(&local_3d8,DAT_8009c4bb,DAT_8009c4ba,DAT_8009c4b9);
    DAT_8009c3e8 = '\0';
  }
  return 0;
}

