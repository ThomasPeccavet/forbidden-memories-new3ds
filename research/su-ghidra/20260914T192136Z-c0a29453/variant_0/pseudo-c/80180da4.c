/* Analysis pseudo-C, not buildable source. */

void FUN_80180da4(int param_1)

{
  int iVar1;
  undefined2 uVar2;
  int *piVar3;
  uint uVar4;
  
  uVar4 = 0;
  piVar3 = &DAT_80184794;
  do {
    uVar2 = 0xff60;
    if ((uVar4 & 1) != 0) {
      uVar2 = 0x1e0;
    }
    iVar1 = *piVar3;
    if (iVar1 != 0) {
      if (param_1 == 0) {
        *(undefined2 *)(iVar1 + 0x36) = uVar2;
        *(undefined2 *)(*piVar3 + 0x38) = 0xa0;
      }
      else {
        *(undefined2 *)(iVar1 + 0x36) = 0xa0;
        *(undefined2 *)(*piVar3 + 0x38) = uVar2;
      }
      *(undefined2 *)(*piVar3 + 0x30) = *(undefined2 *)(*piVar3 + 0x36);
      *(undefined2 *)(*piVar3 + 0x60) = 0x10;
    }
    uVar4 = uVar4 + 1;
    piVar3 = piVar3 + 1;
  } while ((int)uVar4 < 0xb);
  DAT_801847c2 = (char)param_1;
  DAT_801847c5 = 1;
  return;
}

