/* Analysis pseudo-C, not buildable source. */

void FUN_80028aa0(int param_1,int param_2)

{
  undefined2 uVar1;
  undefined2 uVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  
  iVar4 = DAT_8009c4b0;
  if (param_2 == 0) {
    *(undefined4 *)(param_1 + 0x1c) = 0x4000;
    iVar4 = DAT_8009c4b0;
    DAT_8009c460 = DAT_8009c460 & 0xffdcffff;
    *(int *)(param_1 + 0xc) = DAT_8009c4b0;
    *(int *)(param_1 + 8) = iVar4;
    *(undefined1 *)(param_1 + 0x46) = 1;
  }
  else {
    iVar6 = *(int *)(param_1 + 0x38);
    iVar7 = iVar6 * 0x40;
    (&DAT_800eb47c)[iVar6 * 0x20] = 0x33;
    (&DAT_800eb47e)[iVar6 * 0x20] = 0x60;
    (&DAT_800eb478)[iVar6 * 0x20] = (&DAT_800eb498)[iVar6 * 0x20];
    (&DAT_800eb47a)[iVar6 * 0x20] = (&DAT_800eb49a)[iVar6 * 0x20];
    FUN_8007ff10(&DAT_800eb478 + iVar6 * 0x20,iVar4);
    iVar4 = DAT_8009c4b0;
    uVar1 = (&DAT_800eb49c)[iVar6 * 0x20];
    *(undefined2 *)(&DAT_800eb484 + iVar7) = 0x100;
    *(undefined2 *)(&DAT_800eb486 + iVar7) = 1;
    uVar2 = (&DAT_800eb49e)[iVar6 * 0x20];
    *(undefined2 *)(&DAT_800eb480 + iVar7) = uVar1;
    *(undefined2 *)(iVar7 + -0x7ff14b7e) = uVar2;
    FUN_8007ff10(&DAT_800eb480 + iVar7,iVar4 + 0x2640);
    uVar5 = (uint)DAT_8009c44b;
    uVar1 = (&DAT_800eb498)[iVar6 * 0x20];
    *(undefined2 *)(&DAT_800eb48c + iVar7) = 0x18;
    *(undefined2 *)(&DAT_800eb48e + iVar7) = 0xe;
    iVar4 = DAT_8009c4b0;
    sVar3 = (&DAT_800eb49a)[iVar6 * 0x20];
    *(undefined2 *)(&DAT_800eb488 + iVar7) = uVar1;
    *(short *)(&DAT_800eb48a + iVar7) = sVar3 + 0x60;
    FUN_8007ff10(&DAT_800eb488 + iVar7,iVar4 + uVar5 * 0x2a0 + 0x2840);
    iVar4 = DAT_8009c4b0;
    *(undefined2 *)(&DAT_800eb494 + iVar7) = 8;
    *(undefined2 *)(&DAT_800eb496 + iVar7) = 0x58;
    uVar1 = (&DAT_800eb49a)[iVar6 * 0x20];
    *(short *)(&DAT_800eb490 + iVar7) = (&DAT_800eb498)[iVar6 * 0x20] + 0x38;
    *(undefined2 *)(iVar7 + -0x7ff14b6e) = uVar1;
    FUN_8007ff10(&DAT_800eb490 + iVar7,iVar4 + 0x3560);
  }
  return;
}

