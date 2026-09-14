/* Analysis pseudo-C, not buildable source. */

void FUN_8004f080(int param_1)

{
  short *psVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  short *psVar4;
  int iVar5;
  int iVar6;
  
  puVar2 = (undefined2 *)FUN_8005c304();
  puVar3 = (undefined2 *)FUN_8005c310();
  psVar1 = DAT_8009c30c;
  DAT_800f3ea8 = *puVar2;
  DAT_800f3eaa = puVar2[2];
  DAT_800f3eac = puVar2[4];
  DAT_800f3eb0 = puVar2[6];
  DAT_800f3eb2 = puVar2[8];
  DAT_800f3eb4 = puVar2[10];
  DAT_800f3eb8 = *puVar3;
  DAT_800f3eba = puVar3[1];
  DAT_800f3ebc = puVar3[2];
  if (param_1 != 0) {
    iVar6 = 0;
    if (DAT_8009c30c != (short *)0x0) {
      iVar5 = 0x10;
      psVar4 = DAT_8009c30c;
      do {
        if ((psVar4[3] < 4) && (1 < psVar4[3])) {
          FUN_8005c0b8((int)*psVar4,(int)psVar1 + iVar5);
        }
        iVar5 = iVar5 + 8;
        iVar6 = iVar6 + 1;
        psVar4 = psVar4 + 4;
      } while (iVar6 < 2);
    }
  }
  return;
}

