/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80070c7c(void)

{
  int iVar1;
  code *pcVar2;
  
  do {
    DAT_800f6f7c = DAT_800f6f78;
    iVar1 = FUN_80070bb8();
    (**(code **)(&DAT_80092b00 + iVar1 * 4))();
    pcVar2 = *(code **)(&DAT_80092b00 + iVar1 * 4);
    if (pcVar2 == (code *)&LAB_800715c4) {
      return 1;
    }
    if (pcVar2 == (code *)&LAB_800715cc) {
      return 3;
    }
    if (pcVar2 == FUN_800714e8) {
      return 2;
    }
    iVar1 = FUN_800746b8(1);
  } while (iVar1 < 0xf0);
  return 0;
}

