/* Analysis pseudo-C, not buildable source. */

void FUN_80033bf0(int param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_1 + (uint)*(byte *)(param_1 + 0x6342) * 0x2d4c + 4;
  FUN_80033034();
  iVar2 = FUN_800335b8(iVar3);
  if (iVar2 == 0) {
    if ((DAT_8009c72c & 0x10) == 0) {
      if (DAT_8009c710 == 0x2000) {
        *(undefined4 *)(param_1 + 0x5aa4) = 0x140;
        *(undefined2 *)(param_1 + 0x633e) = 1;
        *(undefined2 *)(param_1 + 0x6340) = 3;
      }
      else if ((DAT_8009c72c & 0x20) == 0) {
        if ((DAT_8009c728 & 0xc0) != 0) {
          iVar2 = FUN_80033a00(iVar3);
          bVar1 = true;
          if (iVar2 - 0x11U < 5) {
            bVar1 = *(char *)(param_1 + iVar2 + 0x5ac4) == '\0';
          }
          if ((((iVar2 == 0) || (!bVar1)) || (0x27 < *(int *)(param_1 + 0x5aa0))) ||
             ((*(char *)(param_1 + iVar2 + 0x5d97) == '\0' ||
              (2 < *(byte *)(param_1 + iVar2 + 0x5ac4))))) {
            FUN_80040204(9);
          }
          else {
            FUN_80040204(7);
            FUN_80032490(param_1,iVar2);
            FUN_80032350(param_1,iVar2);
            FUN_80032230(param_1);
            FUN_800317cc(iVar2,3,0x14,0x11c,0xd);
          }
        }
      }
      else {
        *(undefined2 *)(param_1 + 0x633e) = 4;
        *(undefined2 *)(param_1 + 0x6340) = 2;
      }
    }
    else {
      iVar2 = FUN_80033a00(iVar3);
      if (iVar2 != 0) {
        DAT_8009c5dd = 0x14;
        DAT_8009c5d8 = (undefined2)iVar2;
        DAT_8009c5dc = 2;
      }
    }
  }
  return;
}

