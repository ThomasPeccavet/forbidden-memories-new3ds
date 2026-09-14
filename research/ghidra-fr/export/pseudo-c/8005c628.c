/* Analysis pseudo-C, not buildable source. */

undefined4 * FUN_8005c628(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = param_1 * 0xe20;
  puVar2 = &DAT_800f4f38 + param_1 * 0x388;
  if (((uint)(byte)(&DAT_800f4f3f)[iVar1] % 6 != 0) &&
     (*(char *)((int)&DAT_800f4f38 + iVar1 + 3) == '\0')) {
    puVar2 = (undefined4 *)(&DAT_800f4f3c + iVar1);
  }
  return puVar2;
}

