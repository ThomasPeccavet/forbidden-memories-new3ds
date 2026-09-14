/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8008b8fc(int *param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *param_1;
  if (iVar1 == 10) {
LAB_8008b998:
    FUN_8008d4e8();
    FUN_8008b2b8(DAT_800ff6e0);
    *param_1 = *param_1 + 1;
  }
  else {
    if (iVar1 < 0xb) {
      if (iVar1 == 0) {
        DAT_800ff6a4 = 0;
        DAT_800ff6a0 = 0;
        *param_1 = 10;
        DAT_8009b188 = (&DAT_800ff720)[(int)DAT_800ff6e0 >> 4];
        (&DAT_800ff720)[(int)DAT_800ff6e0 >> 4] = 0;
        goto LAB_8008b998;
      }
    }
    else {
      if (iVar1 == 0xb) {
        iVar1 = FUN_8008d7a0();
        if (iVar1 == 0) {
          return 0;
        }
        DAT_800ff6a4 = FUN_8008d5f0();
        piVar2 = &DAT_800ff718 + ((int)DAT_800ff6e0 >> 4);
        DAT_8009b18c = *piVar2;
        if (DAT_800ff6a4 != 1) {
          if (DAT_800ff6a4 < 2) {
            if (DAT_800ff6a4 == 0) {
              if ((DAT_800ff6dc & 1 << (DAT_800ff6e0 & 0x1f)) == 0) {
                DAT_800ff6a4 = 4;
              }
              iVar1 = DAT_800ff6a4;
              *piVar2 = 0;
LAB_8008bb18:
              DAT_800ff6d4 = FUN_8008cefc(iVar1);
              return 1;
            }
          }
          else {
            if (DAT_800ff6a4 == 2) {
              iVar1 = 2;
              if (2 < DAT_800ff6a0 + 1) {
                DAT_800ff6a0 = DAT_800ff6a0 + 1;
                *piVar2 = 1;
                goto LAB_8008bb18;
              }
              goto LAB_8008bb58;
            }
            if (DAT_800ff6a4 == 4) {
              if ((DAT_8009b18c == 0) && (DAT_8009b188 < 0x80)) {
                FUN_8008d4e8();
                FUN_8008b328(DAT_800ff6e0);
                *param_1 = 0x15;
                return 0;
              }
              (&DAT_800ff718)[(int)DAT_800ff6e0 >> 4] = 1;
              DAT_800ff6d4 = FUN_8008cefc(4);
              return 1;
            }
          }
          DAT_800ff6d4 = FUN_8008cefc(DAT_800ff6a4);
          (&DAT_800ff718)[(int)DAT_800ff6e0 >> 4] = 0;
          return 1;
        }
        if (0x10 < DAT_800ff6a0 + 1) {
          DAT_800ff6a0 = DAT_800ff6a0 + 1;
          DAT_800ff6d4 = FUN_8008cefc(1);
          (&DAT_800ff718)[(int)DAT_800ff6e0 >> 4] = 0;
          return 1;
        }
LAB_8008bb58:
        DAT_800ff6a0 = DAT_800ff6a0 + 1;
        *param_1 = 10;
        return 0;
      }
      if (iVar1 == 0x15) {
        iVar1 = FUN_8008d7dc();
        if (iVar1 != 0) {
          FUN_8008d6c8();
          *param_1 = 0;
          return 0;
        }
        return 0;
      }
    }
    FUN_8008fa78(s_error_80012394);
  }
  return 0;
}

