/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8008cc70(int param_1,int *param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = DAT_800ff6d0;
  if ((DAT_800ff6d0 != 0) || (uVar2 = 0xffffffff, DAT_800ff6d8 != 0)) {
    if (param_1 == 0) {
      if (DAT_800ff6d8 == 0) {
        do {
        } while( true );
      }
      if (param_3 != (undefined4 *)0x0) {
        *param_3 = DAT_800ff6c4;
      }
      if (param_2 != (int *)0x0) {
        *param_2 = DAT_800ff6c0;
      }
      DAT_800ff6d8 = 0;
      uVar2 = 1;
    }
    else if (DAT_800ff6d8 == 0) {
      if (param_3 != (undefined4 *)0x0) {
        *param_3 = DAT_800ff6d4;
      }
      uVar2 = 0;
      if (param_2 != (int *)0x0) {
        *param_2 = iVar1;
      }
    }
    else {
      if (param_3 != (undefined4 *)0x0) {
        *param_3 = DAT_800ff6c4;
      }
      if (param_2 != (int *)0x0) {
        *param_2 = DAT_800ff6c0;
      }
      DAT_800ff6d8 = 0;
      uVar2 = 1;
    }
  }
  return uVar2;
}

