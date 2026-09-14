/* Analysis pseudo-C, not buildable source. */

void FUN_8003f69c(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined *puVar3;
  
  iVar2 = 0;
  puVar3 = &DAT_800f0850;
  DAT_8009c73a = 0;
  do {
    if ((*(ushort *)(puVar3 + 0x34) & 0x8000) == 0) {
      DAT_8009c73a = (undefined1)iVar2;
      break;
    }
    iVar2 = iVar2 + 1;
    puVar3 = puVar3 + 100;
  } while (iVar2 < 4);
  uVar1 = FUN_80040350();
  iVar2 = FUN_800403d0(uVar1,2);
  FUN_80040800(iVar2,8,0xffffffc0,3,2,1,0xb,0x20c);
  *(ushort *)(iVar2 + 8) = *(ushort *)(iVar2 + 8) | 0x28;
  FUN_80042c48(iVar2);
  FUN_80042c1c(iVar2,0xf);
  DAT_8009c764 = iVar2;
  return;
}

