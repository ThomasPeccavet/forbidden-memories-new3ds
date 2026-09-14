/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_80033ed0(int *param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  int *piVar5;
  undefined2 *puVar6;
  
  iVar3 = FUN_80033034();
  if (iVar3 == 0) {
    FUN_80040204(8);
    iVar3 = FUN_80033e98();
    if (iVar3 != 0) {
      bVar1 = DAT_8009c680 & 0x80;
      *(ushort *)((int)param_1 + 0x633e) = *(ushort *)((int)param_1 + 0x633e) | 0x4000;
      if (bVar1 == 0) {
        iVar3 = FUN_800361d8(0,9,0x30,0x6c,0xe0,0x30,0x40);
        *(undefined1 *)(iVar3 + 0x59) = 10;
        do {
          FUN_80039770();
        } while (*(int *)(iVar3 + 0x30) == 0);
      }
      else {
        iVar3 = FUN_800361d8(0,8,0x28,0x84,0xf0,0x10,0x1050);
        *(undefined1 *)(iVar3 + 0x59) = 10;
      }
      FUN_80015af4(0xc0,2);
      DAT_8009c4c4 = DAT_8009c2fa + -8;
    }
  }
  piVar5 = param_1 + 0x1766;
  if ((*(ushort *)((int)param_1 + 0x633e) & 0x4000) == 0) {
    iVar3 = 0;
    puVar4 = (undefined1 *)(*param_1 + 0x50);
    do {
      iVar2 = *piVar5;
      piVar5 = (int *)((int)piVar5 + 1);
      iVar3 = iVar3 + 1;
      *puVar4 = (char)iVar2;
      puVar4 = puVar4 + 1;
    } while (iVar3 < 0x2d2);
    puVar6 = (undefined2 *)*param_1;
    iVar3 = 0;
    piVar5 = param_1 + 0xb55;
    do {
      *puVar6 = 0;
      if (*(char *)((int)piVar5 + 9) != '\0') {
        *puVar6 = (short)*piVar5;
      }
      puVar6 = puVar6 + 1;
      iVar3 = iVar3 + 1;
      piVar5 = piVar5 + 4;
    } while (iVar3 < 0x28);
    FUN_8003279c();
    *(undefined2 *)((int)param_1 + 0x633e) = 0;
  }
  else {
    FUN_80039770();
    if ((_DAT_800f0884 & 0x2010) == 0x2000) {
      FUN_800360d8(&DAT_800f0850);
      if (((DAT_8009c680 & 0x80) == 0) && (DAT_8009c6d0 != '\0')) {
        *(ushort *)((int)param_1 + 0x633e) = *(ushort *)((int)param_1 + 0x633e) & 0xbfff;
      }
      else {
        *(short *)((int)param_1 + 0x633e) = (short)param_1[0x18d0];
        FUN_80015af4(0xff,2);
      }
    }
  }
  return;
}

