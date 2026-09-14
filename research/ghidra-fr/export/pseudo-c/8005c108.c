/* Analysis pseudo-C, not buildable source. */

void FUN_8005c108(int param_1,short *param_2)

{
  byte bVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(&DAT_800f4f44 + param_1 * 0x710);
  *(undefined4 *)param_2 = *(undefined4 *)(&DAT_800f4f40 + param_1 * 0x710);
  *(undefined4 *)(param_2 + 2) = uVar2;
  bVar1 = *(byte *)((int)&DAT_800f4e74 + param_1 * 0xe20 + 3);
  if (bVar1 != 0) {
    *param_2 = (ushort)bVar1 << 4;
  }
  if (*(byte *)(&DAT_800f4e78 + param_1 * 0x388) != 0) {
    param_2[1] = (ushort)*(byte *)(&DAT_800f4e78 + param_1 * 0x388) << 4;
  }
  bVar1 = *(byte *)((int)&DAT_800f4e78 + param_1 * 0xe20 + 1);
  if (bVar1 != 0) {
    param_2[2] = (ushort)bVar1 << 4;
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

