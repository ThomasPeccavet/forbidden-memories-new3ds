/* Analysis pseudo-C, not buildable source. */

void FUN_8005afa4(int param_1,short *param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = *(undefined4 *)(&DAT_800f4f44 + param_1 * 0x710);
  *(undefined4 *)param_2 = *(undefined4 *)(&DAT_800f4f40 + param_1 * 0x710);
  *(undefined4 *)(param_2 + 2) = uVar3;
  uVar1 = (uint)*(byte *)((int)&DAT_800f4e74 + param_1 * 0xe20 + 3);
  if ((uVar1 != 0) && (iVar2 = uVar1 << 4, *param_2 < iVar2)) {
    *param_2 = (short)iVar2;
  }
  if ((*(byte *)(&DAT_800f4e78 + param_1 * 0x388) != 0) &&
     (iVar2 = (uint)*(byte *)(&DAT_800f4e78 + param_1 * 0x388) << 4, param_2[1] < iVar2)) {
    param_2[1] = (short)iVar2;
  }
  uVar1 = (uint)*(byte *)((int)&DAT_800f4e78 + param_1 * 0xe20 + 1);
  if ((uVar1 != 0) && (iVar2 = uVar1 << 4, param_2[2] < iVar2)) {
    param_2[2] = (short)iVar2;
  }
  param_2[3] = 0;
  if (0 < *param_2) {
    param_2[3] = *param_2;
  }
  if (param_2[3] < param_2[1]) {
    param_2[3] = param_2[1];
  }
  if (param_2[3] < param_2[2]) {
    param_2[3] = param_2[2];
  }
  return;
}

