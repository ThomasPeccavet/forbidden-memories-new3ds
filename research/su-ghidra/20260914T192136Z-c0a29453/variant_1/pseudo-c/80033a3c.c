/* Analysis pseudo-C, not buildable source. */

void FUN_80033a3c(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1 + (uint)*(byte *)(param_1 + 0x6342) * 0x2d4c + 4;
  FUN_80033034();
  iVar1 = FUN_800335b8(iVar2);
  if (iVar1 == 0) {
    if ((DAT_8009c72c & 0x10) == 0) {
      if (DAT_8009c710 == -0x8000) {
        *(undefined2 *)(param_1 + 0x633e) = 1;
        *(undefined4 *)(param_1 + 0x5aa4) = 0;
        *(undefined2 *)(param_1 + 0x6340) = 2;
      }
      else if ((DAT_8009c72c & 0x20) == 0) {
        if ((DAT_8009c728 & 0xc0) != 0) {
          iVar1 = FUN_80033a00(iVar2);
          if (iVar1 == 0) {
            FUN_80040204(9);
          }
          else {
            FUN_80040204(7);
            *(undefined1 *)
             (iVar2 + ((int)*(short *)(iVar2 + 0x2d3c) + (int)*(char *)(iVar2 + 0x2d48)) * 0x10 +
             0xd) = 0;
            FUN_80033144(param_1 + 0x2d50);
            FUN_800323f0(param_1);
            FUN_800322b8(param_1,iVar1);
            FUN_80032230(param_1);
            FUN_800317cc(iVar1,0x235,0x14,0x162,0xc);
          }
        }
      }
      else {
        *(undefined2 *)(param_1 + 0x633e) = 4;
        *(undefined2 *)(param_1 + 0x6340) = 3;
      }
    }
    else {
      iVar1 = FUN_80033a00(iVar2);
      if (iVar1 != 0) {
        DAT_8009c5dd = 0x14;
        DAT_8009c5d8 = (undefined2)iVar1;
        DAT_8009c5dc = 2;
      }
    }
  }
  return;
}

