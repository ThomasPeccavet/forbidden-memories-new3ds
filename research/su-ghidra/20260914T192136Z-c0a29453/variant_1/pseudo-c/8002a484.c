/* Analysis pseudo-C, not buildable source. */

void FUN_8002a484(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar4 = 0;
  DAT_8009c6b8 = FUN_8002a848();
  iVar1 = (int)DAT_8009c6b8;
  DAT_801bf88c = iVar1;
  if (iVar1 != 0) {
    uVar2 = FUN_8002a048(param_1,iVar1);
    uVar4 = 5;
    if ((uVar2 & 0x80) == 0) {
      DAT_8009c6b8 = 0;
    }
  }
  iVar3 = FUN_80036184(1,uVar4,0x10,0xd5,0x120,0x30);
  DAT_8009c6e1 = *(undefined1 *)(iVar3 + 0x54);
  if ((*(byte *)(param_1 + iVar1 * 4 + 0x56) & 1) != 0) {
    DAT_8009c6e1 = 4;
  }
  FUN_80039a3c(&DAT_800f08b4);
  return;
}

