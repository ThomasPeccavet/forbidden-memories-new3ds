/* Analysis pseudo-C, not buildable source. */

char FUN_8002a55c(void)

{
  int iVar1;
  int iVar2;
  
  if (DAT_800eb587 != '\0') {
    iVar1 = CONCAT22(DAT_800eb578,DAT_800eb57c) + DAT_800eb588;
    DAT_800eb57c = (undefined2)iVar1;
    iVar2 = CONCAT22(DAT_800eb57a,DAT_800eb57e) + DAT_800eb58c;
    DAT_800eb57e = (undefined2)iVar2;
    DAT_800eb586 = DAT_800eb586 + -1;
    if (DAT_800eb586 == '\0') {
      DAT_800eb587 = '\0';
      DAT_800eb578 = DAT_800eb582;
      DAT_800eb57a = DAT_800eb584;
      FUN_80040204(0x35);
      FUN_8002a484(&DAT_800eb570);
      iVar2 = CONCAT22(DAT_800eb57a,DAT_800eb57e);
      iVar1 = CONCAT22(DAT_800eb578,DAT_800eb57c);
    }
    DAT_800eb57a = (undefined2)((uint)iVar2 >> 0x10);
    DAT_800eb57e = (undefined2)iVar2;
    DAT_800eb578 = (undefined2)((uint)iVar1 >> 0x10);
    DAT_800eb57c = (undefined2)iVar1;
    *(undefined2 *)(DAT_800eb5b4 + 0x30) = DAT_800eb578;
    *(undefined2 *)(DAT_800eb5b4 + 0x32) = DAT_800eb57a;
  }
  return DAT_800eb587;
}

