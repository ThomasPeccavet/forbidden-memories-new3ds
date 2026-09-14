/* Analysis pseudo-C, not buildable source. */

void FUN_8007b28c(char param_1,undefined4 param_2)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int *piVar6;
  
  iVar2 = DAT_800f726c;
  piVar6 = &DAT_800f71a8 + DAT_800f726c * 6;
  if (*piVar6 == 0) goto LAB_8007b3f4;
  DAT_800f7178 = *piVar6;
  DAT_800f717c = param_1;
  FUN_8007d304(&DAT_800f717d);
  if (param_1 == '\x02') {
    iVar5 = DAT_800f726c + 1;
    iVar3 = iVar5;
    if (7 < iVar5) {
      iVar3 = 0;
    }
    if ((&DAT_800f71a8)[iVar3 * 6] == *piVar6) {
      DAT_800f726c = iVar5;
      if (7 < iVar5) {
        DAT_800f726c = 0;
      }
      goto LAB_8007b3f4;
    }
    FUN_8007b4b0(*piVar6,2,param_2);
    pcVar1 = (code *)(&DAT_800f71b8)[iVar2 * 6];
    uVar4 = 2;
  }
  else {
    if (param_1 != '\x05') goto LAB_8007b3f4;
    if ((0 < (int)(&DAT_800f71bc)[iVar2 * 6]) || ((&DAT_800f71bc)[iVar2 * 6] == -1)) {
      DAT_800f726c = DAT_800f7268;
      if ((&DAT_800f71bc)[iVar2 * 6] != -1) {
        (&DAT_800f71bc)[iVar2 * 6] = (&DAT_800f71bc)[iVar2 * 6] + -1;
      }
      goto LAB_8007b3f4;
    }
    FUN_8007b4b0(*piVar6,5,param_2);
    pcVar1 = (code *)(&DAT_800f71b8)[iVar2 * 6];
    uVar4 = 5;
  }
  if (pcVar1 != (code *)0x0) {
    (*pcVar1)(uVar4,param_2);
  }
  FUN_8007ae58();
LAB_8007b3f4:
  if (DAT_800f9718 != (code *)0x0) {
    (*DAT_800f9718)(param_1,param_2);
  }
  iVar2 = FUN_8007c484(0);
  if ((((iVar2 == 1) && (0 < DAT_800f7270)) && (iVar2 = FUN_8007c484(0), iVar2 == 1)) &&
     ((&DAT_800f71a8)[DAT_800f726c * 6] != 0)) {
    FUN_8007c3d8((&DAT_800f71ac)[DAT_800f726c * 0x18],(&DAT_800f71b4)[DAT_800f726c * 6]);
  }
  return;
}

