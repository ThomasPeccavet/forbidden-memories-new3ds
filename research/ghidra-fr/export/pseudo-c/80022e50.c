/* Analysis pseudo-C, not buildable source. */

void FUN_80022e50(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = (param_2 - DAT_800f11e0) * 0x10000;
  if (param_1 == 0) {
    trap(0x1c00);
  }
  if ((param_1 == -1) && (iVar4 == -0x80000000)) {
    trap(0x1800);
  }
  iVar3 = (param_3 - DAT_800f11e4) * 0x10000;
  if (param_1 == 0) {
    trap(0x1c00);
  }
  if ((param_1 == -1) && (iVar3 == -0x80000000)) {
    trap(0x1800);
  }
  iVar2 = (param_4 - DAT_800f11e2) * 0x10000;
  if (param_1 == 0) {
    trap(0x1c00);
  }
  if ((param_1 == -1) && (iVar2 == -0x80000000)) {
    trap(0x1800);
  }
  iVar1 = (param_5 - DAT_800f1204) * 0x10000;
  if (param_1 == 0) {
    trap(0x1c00);
  }
  if ((param_1 == -1) && (iVar1 == -0x80000000)) {
    trap(0x1800);
  }
  DAT_8009c4cc = (short)param_1;
  DAT_8009c4ca = (short)param_2;
  DAT_8009c566 = (short)param_3;
  DAT_8009c562 = (short)param_4;
  DAT_8009c530 = (short)param_5;
  DAT_8009c5c8 = (int)DAT_800f11e0 << 0x10 | 0x8000;
  DAT_8009c540 = (int)DAT_800f11e4 << 0x10 | 0x8000;
  DAT_8009c53c = (int)DAT_800f11e2 << 0x10 | 0x8000;
  DAT_8009c518 = DAT_800f1204 << 0x10 | 0x8000;
  DAT_8009c4dc = iVar4 / param_1;
  DAT_8009c570 = iVar3 / param_1;
  DAT_8009c56c = iVar2 / param_1;
  DAT_8009c534 = iVar1 / param_1;
  return;
}

