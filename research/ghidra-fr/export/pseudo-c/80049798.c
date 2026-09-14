/* Analysis pseudo-C, not buildable source. */

void FUN_80049798(void)

{
  int iVar1;
  short sVar2;
  
  if (*(short *)(DAT_8009c7e0 + 0x157a) != 0) {
    sVar2 = FUN_80049b54(*(int *)(DAT_8009c7e0 + 0x1564) + 0x50,0,
                         *(undefined4 *)(*(int *)(DAT_8009c7e0 + 0x1564) + 0xc));
    iVar1 = DAT_8009c7e0;
    *(short *)(DAT_8009c7e0 + 0x157a) = sVar2;
    if (sVar2 != 0) {
      *(undefined2 *)(iVar1 + 0x1578) = 0xffff;
      *(undefined2 *)(iVar1 + 0x157a) = 0xffff;
      return;
    }
  }
  *(undefined2 *)(DAT_8009c7e0 + 0x1578) = **(undefined2 **)(DAT_8009c7e0 + 0x1564);
  return;
}

