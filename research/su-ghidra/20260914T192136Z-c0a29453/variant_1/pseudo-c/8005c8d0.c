/* Analysis pseudo-C, not buildable source. */

void FUN_8005c8d0(int param_1,uint param_2,short param_3)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined *puVar5;
  
  iVar4 = 0;
  iVar2 = param_1 * 0xe20;
  cVar1 = (&DAT_800f4f93)[iVar2];
  (&DAT_800f4f7e)[param_1 * 0x710] = param_3 << 4;
  puVar5 = &DAT_800f4178 + iVar2;
  if (cVar1 != '\0') {
    do {
      uVar3 = (uint)(byte)(&DAT_800f4d6d)[iVar2];
      if (param_2 != 0) {
        *(char *)(*(int *)(puVar5 + 0x1e0) + 0xc) = (char)param_2;
        uVar3 = param_2;
      }
      FUN_80050d8c(&DAT_800f4178 + iVar2,iVar4,uVar3,param_3 << 4);
      iVar4 = iVar4 + 1;
      puVar5 = puVar5 + 4;
    } while (iVar4 < (int)(uint)(byte)(&DAT_800f4f93)[iVar2]);
  }
  if (param_2 != 0) {
    (&DAT_800f4d6d)[iVar2] = (char)param_2;
  }
  (&DAT_800f4f46)[param_1 * 0x710] = 0;
  return;
}

