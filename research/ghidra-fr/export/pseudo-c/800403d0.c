/* Analysis pseudo-C, not buildable source. */

undefined2 * FUN_800403d0(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined2 *puVar3;
  undefined2 uVar4;
  
  if (param_1 < 0) {
    return (undefined2 *)0x0;
  }
  iVar1 = param_1 * 0x70;
  puVar3 = (undefined2 *)(&DAT_800f1210 + iVar1);
  DAT_8009c7a6 = DAT_8009c7a6 + 1;
  if (((&DAT_800f1218)[param_1 * 0x38] & 0x80) == 0) {
    iVar2 = (int)(short)(&DAT_800f11c0)[param_2];
    uVar4 = (undefined2)param_1;
    if (iVar2 < 0) {
      (&DAT_800f11d0)[param_2] = uVar4;
      *(undefined2 *)(&DAT_800f1212 + iVar1) = 0xffff;
      *puVar3 = 0xffff;
    }
    else {
      *(undefined2 *)(&DAT_800f1210 + iVar2 * 0x70) = uVar4;
      *(undefined2 *)(&DAT_800f1212 + iVar1) = (&DAT_800f11c0)[param_2];
    }
    *puVar3 = 0xffff;
    (&DAT_800f11c0)[param_2] = uVar4;
    *(undefined4 *)(&DAT_800f1214 + iVar1) = 0x8000000;
    (&DAT_800f1218)[param_1 * 0x38] = 0xc0;
    (&DAT_800f1227)[iVar1] = 2;
    *(undefined **)(&DAT_800f1264 + iVar1) = &DAT_801ac000;
    (&DAT_800f127c)[iVar1] = 0;
    *(undefined4 *)(&DAT_800f1234 + iVar1) = 0;
    *(short *)(&DAT_800f122e + iVar1) = (short)param_2;
    (&DAT_800f121a)[iVar1] = (char)param_1;
    (&DAT_800f121b)[iVar1] = 0;
    *(undefined4 *)(&DAT_800f121c + iVar1) = 0x808080;
    *(undefined4 *)(&DAT_800f1230 + iVar1) = 0;
    *(undefined4 *)(&DAT_800f1220 + iVar1) = 0;
    *(undefined2 *)(&DAT_800f122c + iVar1) = 0;
    *(undefined2 *)(&DAT_800f122a + iVar1) = 0;
    *(undefined2 *)(&DAT_800f1228 + iVar1) = 0;
    (&DAT_800f1276)[iVar1] = 0;
    *(undefined4 *)(&DAT_800f1258 + iVar1) = 0;
    *(undefined4 *)(&DAT_800f1254 + iVar1) = 0x10001000;
    *(undefined4 *)(&DAT_800f1250 + iVar1) = 0;
    *(undefined2 *)(&DAT_800f126e + iVar1) = 0;
    (&DAT_800f1275)[iVar1] = 0;
    (&DAT_800f1226)[iVar1] = 0;
    *(undefined2 *)(&DAT_800f1224 + iVar1) =
         *(undefined2 *)(&DAT_8009c2f8 + (uint)(byte)(&DAT_800f1227)[iVar1] * 2);
  }
  return puVar3;
}

