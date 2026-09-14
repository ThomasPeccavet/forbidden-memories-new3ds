/* Analysis pseudo-C, not buildable source. */

void FUN_80036238(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = 800;
  puVar1 = &DAT_800ec39f;
  do {
    if ((uint)(byte)puVar1[1] == param_1 + 1U) {
      *puVar1 = 0;
    }
    iVar2 = iVar2 + -1;
    puVar1 = puVar1 + 0x16;
  } while (iVar2 != 0);
  return;
}

