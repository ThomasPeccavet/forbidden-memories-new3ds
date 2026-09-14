/* Analysis pseudo-C, not buildable source. */

void FUN_80054078(uint param_1)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = param_1 * 0xe20;
  uVar1 = *(ushort *)(&DAT_800f493c + iVar3 + ((byte)(&DAT_800f4f76)[iVar3] + 3) * 0x76);
  if (uVar1 != 0) {
    FUN_8005ac78(param_1,(byte)(&DAT_800f4f76)[iVar3] + 3,1);
  }
  uVar4 = ((uint)uVar1 << 1) / 3;
  if (uVar4 < 0x3c) {
    uVar4 = 0x3c;
  }
  uVar2 = (uint)(ushort)(&DAT_800f4e70)[param_1 * 0x710 + (byte)(&DAT_800f4f76)[iVar3] + 6];
  if (uVar2 != 0) {
    uVar4 = uVar2;
  }
  FUN_8005d020(1,0xffffffff,param_1 ^ 1,uVar4);
  FUN_8004f190((uint)((*(byte *)((int)&DAT_800f4e70 +
                                (uint)(byte)(&DAT_800f4f76)[iVar3] + iVar3 + 10) & 0x80) == 0) << 1)
  ;
  if ((*(byte *)((int)&DAT_800f4e70 + (uint)(byte)(&DAT_800f4f76)[iVar3] + iVar3 + 10) & 0x40) != 0)
  {
    FUN_8004f190(1);
  }
  return;
}

