/* Analysis pseudo-C, not buildable source. */

bool FUN_8005d9cc(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = (uint)DAT_8009c332;
  iVar3 = DAT_800ff5c4 + 0x7ff63710;
  if ((int)param_2 < 0) {
    iVar1 = FUN_8005c628(param_1);
    param_2 = (uint)*(byte *)(iVar1 + 3);
  }
  if (param_2 == 5) {
    iVar1 = (uint)*(ushort *)(&DAT_800f4f78 + param_1 * 0xe20) * -2;
  }
  else {
    iVar1 = -(uint)*(ushort *)(&DAT_800f4f78 + param_1 * 0xe20);
  }
  return (int)((140000 - (iVar3 + uVar2 * -140000)) + iVar1) < 0x401;
}

