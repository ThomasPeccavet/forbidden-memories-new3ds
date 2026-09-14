/* Analysis pseudo-C, not buildable source. */

void FUN_8007ae58(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = (&DAT_800f71a8)[DAT_800f7268 * 6];
  do {
    DAT_800f726c = DAT_800f7268;
    if (DAT_800f7270 < 1) {
      return;
    }
    iVar3 = 3;
    iVar1 = DAT_800f7268 * 0x18;
    iVar2 = iVar1 + -0x7ff08e55;
    (&DAT_800f71a8)[DAT_800f7268 * 6] = 0;
    (&DAT_800f71ac)[iVar1] = 0;
    do {
      *(undefined1 *)(iVar2 + 5) = 0;
      iVar3 = iVar3 + -1;
      iVar2 = iVar2 + -1;
    } while (-1 < iVar3);
    (&DAT_800f71b4)[DAT_800f726c * 6] = 0;
    (&DAT_800f71b8)[DAT_800f726c * 6] = 0;
    (&DAT_800f71bc)[DAT_800f726c * 6] = 0;
    DAT_800f7268 = DAT_800f7268 + 1;
    if (7 < DAT_800f7268) {
      DAT_800f7268 = 0;
    }
    DAT_800f7270 = DAT_800f7270 + -1;
  } while ((&DAT_800f71a8)[DAT_800f7268 * 6] == iVar4);
  DAT_800f726c = DAT_800f7268;
  return;
}

