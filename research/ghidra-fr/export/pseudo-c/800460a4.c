/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_800460a4(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  if (*(short *)(DAT_8009c7e0 + 0x4c) < 0x10) {
    *(undefined1 *)(DAT_8009c7e0 + *(short *)(DAT_8009c7e0 + 0x4c) * 0x30 + 0x80) =
         *(undefined1 *)param_1;
    puVar2 = param_1 + 0xc;
    puVar1 = (undefined4 *)(DAT_8009c7e0 + *(short *)(DAT_8009c7e0 + 0x4c) * 0x30 + 0x80);
    do {
      uVar3 = param_1[1];
      uVar4 = param_1[2];
      uVar5 = param_1[3];
      *puVar1 = *param_1;
      puVar1[1] = uVar3;
      puVar1[2] = uVar4;
      puVar1[3] = uVar5;
      param_1 = param_1 + 4;
      puVar1 = puVar1 + 4;
    } while (param_1 != puVar2);
    *(short *)(DAT_8009c7e0 + 0x4c) = *(short *)(DAT_8009c7e0 + 0x4c) + 1;
    return 1;
  }
  return 0;
}

