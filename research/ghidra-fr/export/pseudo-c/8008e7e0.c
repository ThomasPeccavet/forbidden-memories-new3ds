/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_8008e7e0(void)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  if (DAT_8009b1ec == 1) {
    DAT_8009b1e8 = 4;
    FUN_8008ec6c((int)_DAT_8009b1f0 >> 4);
    FUN_8008ee44(~((_DAT_8009b1f0 & 0xf) + 0x81));
    DAT_800ffb48 = (DAT_8009b1f0 & 0xf) + 0x81;
    DAT_8009b1fc = DAT_8009b1fc + 1;
    iVar2 = 0;
  }
  else {
    DAT_800ffbec = DAT_800ffbec + -1;
    uVar1 = (*DAT_800ffa90)();
    (&DAT_800ffb48)[DAT_8009b1fc] = uVar1;
    DAT_8009b1fc = DAT_8009b1fc + 1;
    uVar3 = FUN_8008ee44();
    if ((int)uVar3 < 0) {
      iVar2 = uVar3 - 1000;
    }
    else {
      (&DAT_800ffab0)[DAT_8009b200] = (char)uVar3;
      DAT_8009b200 = DAT_8009b200 + 1;
      iVar4 = (*DAT_800ffaa4)(uVar3 & 0xff);
      iVar2 = iVar4 + -2000;
      if (iVar4 == 0) {
        if (DAT_800ffbec == 0) {
          iVar2 = 1;
        }
        else {
          iVar2 = 0;
          if (DAT_800ffbec == 1) {
            if (((DAT_800ffbe0 != 0xe) && (DAT_800ffbe0 != 0xf)) ||
               (DAT_8009b200 != DAT_800ffbe4 + 4)) {
              do {
              } while ((*(ushort *)(DAT_8009b204 + 4) & 2) == 0);
            }
            DAT_8009b1ec = DAT_8009b1ec + 1;
            DAT_800ffbec = 0;
            uVar1 = *DAT_8009b204;
            (&DAT_800ffab0)[DAT_8009b200] = uVar1;
            DAT_8009b200 = DAT_8009b200 + 1;
            iVar4 = (*DAT_800ffaa4)(uVar1);
            iVar2 = 1;
            if (iVar4 != 0) {
              iVar2 = iVar4 + -3000;
            }
          }
        }
      }
    }
  }
  return iVar2;
}

