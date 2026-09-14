/* Analysis pseudo-C, not buildable source. */

undefined2 FUN_800340e8(void)

{
  int iVar1;
  char cVar2;
  int iVar3;
  
  FUN_8008f708();
  cVar2 = (char)(DAT_8009c444 & 0x3f);
  if (0x1f < (DAT_8009c444 & 0x3f)) {
    cVar2 = '?' - cVar2;
  }
  iVar3 = *(int *)(DAT_8009c684 + 0x2d38);
  iVar1 = *(int *)(DAT_8009c684 + 0x5a84);
  cVar2 = cVar2 * '\x02' + '@';
  *(char *)(iVar1 + 0xe) = cVar2;
  *(char *)(iVar1 + 0xd) = cVar2;
  *(char *)(iVar1 + 0xc) = cVar2;
  *(char *)(iVar3 + 0xe) = cVar2;
  *(char *)(iVar3 + 0xd) = cVar2;
  *(char *)(iVar3 + 0xc) = cVar2;
  iVar1 = FUN_800289a4();
  if (iVar1 == 0) {
    (*(code *)(&PTR_FUN_80092234)[*(ushort *)(DAT_8009c684 + 0x633e) & 0x3f])();
  }
  return *(undefined2 *)(DAT_8009c684 + 0x633e);
}

