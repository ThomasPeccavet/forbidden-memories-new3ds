/* Analysis pseudo-C, not buildable source. */

void FUN_800405c4(undefined2 *param_1,int param_2)

{
  undefined2 uVar1;
  int iVar2;
  
  uVar1 = param_1[4];
  FUN_80040530();
  iVar2 = (int)(short)(&DAT_800f11c0)[param_2];
  if (iVar2 < 0) {
    (&DAT_800f11d0)[param_2] = (ushort)*(byte *)(param_1 + 5);
    param_1[1] = 0xffff;
    *param_1 = 0xffff;
  }
  else {
    *(ushort *)(&DAT_800f1210 + iVar2 * 0x70) = (ushort)*(byte *)(param_1 + 5);
    param_1[1] = (&DAT_800f11c0)[param_2];
  }
  *param_1 = 0xffff;
  (&DAT_800f11c0)[param_2] = (ushort)*(byte *)(param_1 + 5);
  param_1[4] = uVar1;
  return;
}

