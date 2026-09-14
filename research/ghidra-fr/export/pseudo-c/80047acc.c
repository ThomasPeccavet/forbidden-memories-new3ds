/* Analysis pseudo-C, not buildable source. */

void FUN_80047acc(void)

{
  ushort *puVar1;
  ushort uVar2;
  ushort *puVar3;
  uint uVar4;
  
  puVar1 = DAT_8009c7e0;
  uVar4 = (uint)DAT_8009c7e0[2];
  uVar2 = *DAT_8009c7e0;
  DAT_8009c7e0[0x221] = 0xffff;
  if (uVar4 < uVar2) {
    do {
      *(undefined2 *)(uVar4 * 2 + *(int *)(puVar1 + 0x21e)) = 0xffff;
      uVar4 = uVar4 + 1;
    } while ((int)uVar4 < (int)(uint)*puVar1);
  }
  puVar3 = DAT_8009c7e0;
  puVar1 = DAT_8009c7e0 + 0x224;
  DAT_8009c7e0[0x220] = DAT_8009c7e0[2];
  *(int *)(puVar3 + 0x21c) = *(int *)(*(int *)puVar1 + 4) + 0x1010;
  return;
}

