/* Analysis pseudo-C, not buildable source. */

void FUN_8005d2fc(int param_1)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short local_10;
  short sStack_e;
  short local_c;
  undefined2 uStack_a;
  
  FUN_8008f548(&local_10,0,8);
  sVar1 = (short)DAT_800f6c28 - (&DAT_800f4f48)[param_1 * 0x710];
  sVar2 = (short)DAT_800f6c2c - (&DAT_800f4f4a)[param_1 * 0x710];
  _local_10 = CONCAT22(sVar2,sVar1);
  sVar3 = (short)DAT_800f6c30 - (&DAT_800f4f4c)[param_1 * 0x710];
  _local_c = CONCAT22(uStack_a,sVar3);
  FUN_80086dd8((int)sVar1 * (int)sVar1 + (int)sVar2 * (int)sVar2 + (int)sVar3 * (int)sVar3);
  return;
}

