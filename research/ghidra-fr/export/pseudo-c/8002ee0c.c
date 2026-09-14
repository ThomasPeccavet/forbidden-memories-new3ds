/* Analysis pseudo-C, not buildable source. */

void FUN_8002ee0c(void)

{
  undefined1 uVar1;
  byte bVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  
  iVar3 = FUN_8002e650();
  if (iVar3 == 0) {
    uVar1 = *DAT_8009c624;
    bVar2 = DAT_8009c624[1];
    DAT_8009c624 = DAT_8009c624 + 2;
    iVar5 = (int)(bVar2 & 0x80) >> 7;
    iVar3 = iVar5 * 0x4c;
    puVar4 = &DAT_800ec2a8 + iVar3;
    DAT_8009c634 = puVar4;
    if (-1 < (char)(&DAT_800ec2d8)[iVar3]) {
      FUN_8003a364(puVar4);
    }
    FUN_8003a22c();
    FUN_8003a2d4(puVar4);
    (&DAT_800ec2d9)[iVar3] = bVar2 & 0xf;
    (&DAT_800ec2d8)[iVar3] = uVar1;
    (&DAT_800ec2e4)[iVar3] = (char)iVar5;
    (&DAT_800ec2db)[iVar3] = 2;
    if ((bVar2 & 0x80) != 0) {
      *(undefined2 *)(&DAT_800ec2dc + iVar3) = 0xd8;
    }
  }
  FUN_8003b89c(0);
  if (DAT_8009c634[0x33] == '\0') {
    DAT_8009c610 = 0;
  }
  return;
}

