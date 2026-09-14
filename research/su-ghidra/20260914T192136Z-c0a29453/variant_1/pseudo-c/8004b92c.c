/* Analysis pseudo-C, not buildable source. */

void FUN_8004b92c(uint param_1,byte param_2,byte param_3)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  bVar2 = false;
  iVar3 = DAT_8009c7d8 + (param_1 & 0xff) * 0x18;
  if (param_2 == 0x1e) {
    *(ushort *)(DAT_8009c7d8 + 0x512) = (ushort)param_3;
    FUN_8004a788();
    bVar1 = false;
  }
  else {
    bVar1 = bVar2;
    if (param_2 < 0x1f) {
      if (param_2 == 7) {
        *(byte *)(iVar3 + 3) = param_3;
      }
      else {
        if (param_2 < 8) {
          bVar1 = false;
          if (param_2 == 6) {
            *(byte *)(iVar3 + 0x13) = param_3;
            bVar1 = bVar2;
            if ((*(char *)(iVar3 + 0x12) != '\x14') &&
               (bVar1 = false, *(char *)(iVar3 + 0x12) != '\x1e')) {
              FUN_8004b174(iVar3,param_1 & 0xff);
              bVar1 = false;
            }
          }
          goto LAB_8004baa8;
        }
        if (param_2 == 10) {
          if (param_3 == 0) {
            *(undefined1 *)(iVar3 + 1) = 1;
          }
          else {
            *(byte *)(iVar3 + 1) = param_3;
          }
        }
        else {
          bVar1 = false;
          if (param_2 != 0xb) goto LAB_8004baa8;
          *(byte *)(iVar3 + 5) = param_3;
        }
      }
      bVar1 = true;
    }
    else if (param_2 == 0x62) {
      *(byte *)(iVar3 + 0x11) = param_3;
    }
    else if (param_2 < 99) {
      if (param_2 == 0x30) {
        *(byte *)(iVar3 + 6) = *(byte *)(iVar3 + 6) & 0xf | param_3 << 4;
      }
      else {
        bVar1 = false;
        if (param_2 == 0x5b) {
          *(byte *)(iVar3 + 0x10) = param_3 & 0x7f;
          bVar1 = bVar2;
        }
      }
    }
    else {
      bVar1 = false;
      if (param_2 == 99) {
        *(byte *)(iVar3 + 0x12) = param_3;
        bVar1 = bVar2;
      }
    }
  }
LAB_8004baa8:
  if ((bVar1) && (iVar3 = 0, 0 < *(short *)(DAT_8009c7d8 + 0x510))) {
    iVar5 = 0x180;
    iVar4 = 0;
    do {
      if (((param_1 & 0xff) == (uint)*(byte *)(DAT_8009c7d8 + iVar4 + 0x183)) &&
         (*(char *)(DAT_8009c7d8 + iVar4 + 0x18d) != '\0')) {
        FUN_8004a58c(DAT_8009c7d8 + iVar5,DAT_8009c7d8 + (param_1 & 0xff) * 0x18);
        FUN_8004a70c(iVar3,*(undefined2 *)(DAT_8009c7d8 + iVar4 + 0x194),
                     *(undefined2 *)(DAT_8009c7d8 + iVar4 + 0x196));
      }
      iVar5 = iVar5 + 0x28;
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + 0x28;
    } while (iVar3 < *(short *)(DAT_8009c7d8 + 0x510));
  }
  return;
}

