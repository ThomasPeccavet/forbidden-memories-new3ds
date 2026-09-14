/* Analysis pseudo-C, not buildable source. */

void FUN_80058860(int param_1)

{
  byte bVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char cVar6;
  uint uVar7;
  
  iVar3 = param_1 * 0xe20;
  if ((&DAT_800f4f97)[iVar3] == '\0') {
    return;
  }
  if (*(int *)(&DAT_800f4f50 + iVar3) != 0) {
    bVar1 = (&DAT_800f4d6d)[iVar3];
    uVar7 = (uint)*(ushort *)(&DAT_800f4178 + iVar3 + (uint)bVar1 * 0x76 + 0x7c4) * 0x10;
    iVar4 = FUN_8005bf24();
    iVar4 = (uint)*(byte *)((int)&DAT_800f4f84 + iVar3 + 1) * iVar4;
    if (bVar1 == 6) {
      if ((((&DAT_800f4f8e)[iVar3] == '>') &&
          ((int)(uVar7 - iVar4) <= (int)(uint)(ushort)(&DAT_800f4f7e)[param_1 * 0x710])) ||
         (((&DAT_800f4f8e)[iVar3] == '<' && ((ushort)(&DAT_800f4f7e)[param_1 * 0x710] < 2)))) {
        FUN_8005c808(param_1,0);
      }
    }
    if (param_1 < 2) {
      FUN_800541c0(param_1);
    }
    if ((&DAT_800f4f8e)[iVar3] != '#') {
      if ((&DAT_800f4f8e)[iVar3] == '>') {
        if (uVar7 <= (ushort)(&DAT_800f4f7e)[param_1 * 0x710]) {
          (&DAT_800f4f7e)[param_1 * 0x710] = 0;
        }
        if ((int)((uint)(ushort)(&DAT_800f4f7e)[param_1 * 0x710] + iVar4) < (int)uVar7) {
          (&DAT_800f4f7e)[param_1 * 0x710] =
               (short)((uint)(ushort)(&DAT_800f4f7e)[param_1 * 0x710] + iVar4);
        }
        else {
          (&DAT_800f4f7e)[param_1 * 0x710] = (short)uVar7;
        }
      }
      else {
        iVar5 = (uint)(ushort)(&DAT_800f4f7e)[param_1 * 0x710] - iVar4;
        if ((ushort)(&DAT_800f4f7e)[param_1 * 0x710] == 0) {
          (&DAT_800f4f7e)[param_1 * 0x710] = (short)uVar7;
          iVar5 = (uint)(ushort)(&DAT_800f4f7e)[param_1 * 0x710] - iVar4;
        }
        if (iVar5 < 1) {
          (&DAT_800f4f7e)[param_1 * 0x710] = 0;
        }
        else {
          (&DAT_800f4f7e)[param_1 * 0x710] = (short)iVar5;
        }
      }
    }
    if ((&DAT_800f4f88)[iVar3] == '\0') {
      if ((&DAT_800f4f8e)[iVar3] == '>') {
        if ((ushort)(&DAT_800f4f7e)[param_1 * 0x710] < uVar7) {
          cVar6 = '>';
          goto LAB_80058ac8;
        }
      }
      else if ((&DAT_800f4f7e)[param_1 * 0x710] != 0) goto LAB_80058ac0;
      if ((&DAT_800f4f3f)[iVar3] == '\x06') {
        (&DAT_800f4d6c)[iVar3] = 2;
      }
      if ((&DAT_800f4d6c)[iVar3] != (&DAT_800f4d6e)[iVar3]) {
        FUN_8005c8d0(param_1,(&DAT_800f4d6c)[iVar3],0);
        cVar6 = *(char *)((int)&DAT_800f4f84 + iVar3 + 3);
        (&DAT_800f4d6e)[iVar3] = (&DAT_800f4d6c)[iVar3];
        if (cVar6 != '\0') {
          FUN_8005ac78(param_1,0,0);
        }
        if ((&DAT_800f4f3f)[iVar3] == '\x06') {
          FUN_8004f724(0xffffffff,param_1 + 2,*(undefined2 *)(&DAT_800f4a28 + iVar3));
          (&DAT_800f4f3f)[iVar3] = 0;
          (&DAT_800f4d6c)[iVar3] = 1;
        }
      }
    }
  }
LAB_80058ac0:
  cVar6 = (&DAT_800f4f8e)[iVar3];
LAB_80058ac8:
  if (((cVar6 == '#') || (*(char *)((int)&DAT_800f4f84 + iVar3 + 1) != '\x10')) ||
     (iVar4 = FUN_8005bf24(), iVar4 != 2)) {
    uVar2 = (&DAT_800f4f7e)[param_1 * 0x710];
    iVar4 = 0;
    if ((&DAT_800f4f93)[iVar3] != '\0') {
      do {
        FUN_80050d8c(&DAT_800f4178 + iVar3,iVar4,(&DAT_800f4d6d)[iVar3],uVar2);
        iVar4 = iVar4 + 1;
      } while (iVar4 < (int)(uint)(byte)(&DAT_800f4f93)[iVar3]);
    }
  }
  return;
}

