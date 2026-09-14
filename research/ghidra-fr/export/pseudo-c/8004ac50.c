/* Analysis pseudo-C, not buildable source. */

void FUN_8004ac50(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_8009c7d8 + param_1 * 0x28 + 0x180;
  if (*(byte *)(iVar2 + 3) < 0x10) {
    do {
      FUN_80077468(0,(&DAT_80011360)[param_1]);
      iVar1 = FUN_80077628((&DAT_80011360)[param_1]);
      if (iVar1 == 2) break;
    } while (iVar1 != 0);
    *(undefined1 *)(iVar2 + 0xf) = 0;
  }
  return;
}

