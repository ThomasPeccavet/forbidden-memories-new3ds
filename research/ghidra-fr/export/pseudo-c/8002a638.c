/* Analysis pseudo-C, not buildable source. */

void FUN_8002a638(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  if ((param_1 != DAT_8009c5f0) || (param_2 != DAT_8009c5f1)) {
    DAT_8009c5f0 = (char)param_1;
    DAT_8009c5f1 = (char)param_2;
    DAT_800eb586 = (undefined1)param_3;
    if (param_1 < 10) {
      DAT_800eb582 = ((short)param_1 + (short)(param_1 / 10) * -10) * 0xe + 0xe;
    }
    else {
      DAT_800eb582 = ((short)param_1 + (short)(param_1 / 10) * -10) * 0xe + 0xae;
    }
    iVar1 = ((int)DAT_800eb582 - (int)DAT_800eb578) * 0x10000;
    DAT_800eb588 = iVar1 / param_3;
    if (param_3 == 0) {
      trap(0x1c00);
    }
    if ((param_3 == -1) && (iVar1 == -0x80000000)) {
      trap(0x1800);
    }
    iVar2 = param_2 * 0x10 + (param_2 / 10) * 0x12 + 0xe;
    iVar1 = ((iVar2 * 0x10000 >> 0x10) - (int)DAT_800eb57a) * 0x10000;
    DAT_800eb58c = iVar1 / param_3;
    if (param_3 == 0) {
      trap(0x1c00);
    }
    if ((param_3 == -1) && (iVar1 == -0x80000000)) {
      trap(0x1800);
    }
    DAT_800eb584 = (undefined2)iVar2;
    DAT_800eb57e = 0x8000;
    DAT_800eb57c = 0x8000;
    DAT_800eb587 = 1;
  }
  return;
}

