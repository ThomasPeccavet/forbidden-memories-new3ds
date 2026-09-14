/* Analysis pseudo-C, not buildable source. */

void FUN_8002a918(undefined1 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar1 = FUN_8002a55c();
  if (iVar1 != 0) goto LAB_8002ab34;
  if ((DAT_8009c72c & 0x40) != 0) {
    uVar2 = FUN_8002a848(param_1);
    uVar3 = FUN_8002a048(param_1,uVar2);
    if ((uVar3 & 0x80) != 0) {
      *(short *)(param_1 + 6) = (short)uVar2;
      *param_1 = 2;
      return;
    }
  }
  if ((DAT_8009c72c & 0x20) != 0) {
    DAT_8009c60a = DAT_8009c60d;
    return;
  }
  if ((DAT_8009c710 & 0xf00c) == 0) goto LAB_8002ab34;
  iVar1 = (int)DAT_8009c5f0;
  iVar5 = (int)DAT_8009c5f1;
  iVar6 = 6;
  if ((DAT_8009c710 & 0x80) != 0) {
    iVar6 = 2;
  }
  if ((DAT_8009c710 & 0xc) == 0) {
    if ((DAT_8009c710 & 0xa000) != 0) {
      if ((DAT_8009c710 & 0x2000) == 0) {
        iVar1 = iVar1 + -1;
        if ((iVar1 < 0) && (iVar1 = 0, iVar5 != 0)) {
          iVar1 = 0x13;
          iVar5 = iVar5 + -1;
          goto LAB_8002aad0;
        }
      }
      else {
        iVar1 = iVar1 + 1;
        if ((0x13 < iVar1) && (iVar1 = 0x13, iVar5 < 0x27)) {
          iVar1 = 0;
          iVar5 = iVar5 + 1;
LAB_8002aad0:
          iVar6 = iVar6 << 2;
        }
      }
    }
    if ((DAT_8009c710 & 0x5000) != 0) {
      if ((DAT_8009c710 & 0x4000) == 0) {
        iVar5 = iVar5 + -1;
        if (iVar5 < 0) {
          iVar5 = 0;
        }
      }
      else {
        iVar5 = iVar5 + 1;
        if (0x27 < iVar5) {
          iVar5 = 0x27;
        }
      }
    }
  }
  else {
    if ((DAT_8009c710 & 8) == 0) {
      iVar5 = iVar5 + -10;
      if (iVar5 < 0) {
        iVar5 = 0;
      }
    }
    else {
      iVar5 = iVar5 + 10;
      if (0x27 < iVar5) {
        iVar5 = 0x27;
      }
    }
    iVar4 = iVar5 - DAT_8009c5f1;
    iVar6 = iVar4 * 2;
    if (iVar4 < 0) {
      iVar6 = (DAT_8009c5f1 - iVar5) * 2;
    }
  }
  FUN_8002a638(iVar1,iVar5,iVar6);
LAB_8002ab34:
  FUN_8002a7f0(param_1);
  return;
}

