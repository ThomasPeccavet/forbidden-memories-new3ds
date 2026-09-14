/* Analysis pseudo-C, not buildable source. */

void FUN_80035f64(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 4;
  puVar1 = &DAT_800f0878;
  do {
    *(undefined2 *)(puVar1 + 3) = 0;
    puVar1[2] = 0;
    puVar1[1] = 0;
    *puVar1 = 0;
    iVar2 = iVar2 + -1;
    puVar1 = puVar1 + 0x19;
  } while (iVar2 != 0);
  FUN_80036274();
  return;
}

