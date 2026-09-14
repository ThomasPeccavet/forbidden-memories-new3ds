/* Analysis pseudo-C, not buildable source. */

/* WARNING: Removing unreachable block (ram,0x80024014) */
/* WARNING: Removing unreachable block (ram,0x80024024) */
/* WARNING: Removing unreachable block (ram,0x8002402c) */

void FUN_80023dc4(int param_1,uint param_2)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  
  iVar6 = *(int *)(param_1 + 4);
  if ((*(byte *)(param_1 + 0x19) & 0x80) == 0) {
    if (-1 < (int)param_2) {
      if ((param_2 & 1) == 0) {
        uVar4 = (int)*(char *)(param_1 + 0xf) + 1;
        if ((param_2 & 2) != 0) {
          uVar4 = (int)*(char *)(param_1 + 0xf) - 1;
        }
        if (4 < uVar4) {
          return;
        }
        cVar1 = *(char *)(param_1 + 0x10);
        *(char *)(param_1 + 0xf) = (char)uVar4;
        FUN_80042d08(iVar6);
        *(undefined1 *)(iVar6 + 0x6c) = 0;
        uVar5 = (uint)DAT_8009c504;
        *(undefined2 *)(iVar6 + 0x60) = 8;
        *(undefined2 *)(iVar6 + 0x2c) =
             *(undefined2 *)(&DAT_80091a08 + (cVar1 * 5 + (int)(char)uVar4) * 4 + uVar5 * 0x50);
        *(undefined2 *)(iVar6 + 0x2e) = *(undefined2 *)(iVar6 + 0x2a);
        DAT_8009c57e = 0x40;
        *(short *)(iVar6 + 0x36) =
             (short)((((int)*(short *)(iVar6 + 0x2c) - (int)*(short *)(iVar6 + 0x28)) * 0x100) / 8);
        bVar2 = *(byte *)(param_1 + 0x19) | 0x80;
      }
      else {
        uVar4 = (uint)*(char *)(param_1 + 0x10);
        uVar5 = uVar4 + 1;
        if ((param_2 & 2) != 0) {
          uVar5 = uVar4 - 1;
        }
        if ((int)*(char *)(param_1 + 0x12) <= (int)uVar5) {
          return;
        }
        if ((int)uVar5 < (int)*(char *)(param_1 + 0x11)) {
          return;
        }
        iVar7 = 0x10;
        if ((uVar4 ^ uVar5) != 3) {
          iVar7 = 8;
        }
        FUN_80022e50(iVar7,0x14e,0x3fe,*(undefined2 *)(&DAT_8009c2b0 + (uint)DAT_8009c504 * 2),
                     (int)*(short *)(&DAT_800919b4 +
                                    uVar5 * 2 + (uint)*(byte *)(param_1 + 0x18) * 8 +
                                    (uint)DAT_8009c504 * 0x10));
        cVar1 = *(char *)(param_1 + 0xf);
        *(char *)(param_1 + 0x10) = (char)uVar5;
        FUN_80042d08(iVar6);
        *(undefined1 *)(iVar6 + 0x6c) = 0;
        uVar4 = (uint)DAT_8009c504;
        *(short *)(iVar6 + 0x60) = (short)iVar7;
        *(undefined2 *)(iVar6 + 0x2c) = *(undefined2 *)(iVar6 + 0x28);
        iVar3 = ((int)*(short *)(&DAT_80091a0a + (uVar5 * 5 + (int)cVar1) * 4 + uVar4 * 0x50) -
                (int)*(short *)(iVar6 + 0x2a)) * 0x100;
        if (iVar7 == 0) {
          trap(0x1c00);
        }
        if ((iVar7 == -1) && (iVar3 == -0x80000000)) {
          trap(0x1800);
        }
        DAT_8009c57e = 0x50;
        *(short *)(iVar6 + 0x2e) =
             *(short *)(&DAT_80091a0a + (uVar5 * 5 + (int)cVar1) * 4 + uVar4 * 0x50);
        *(short *)(iVar6 + 0x3a) = (short)(iVar3 / iVar7);
        bVar2 = *(byte *)(param_1 + 0x19) | 0xc0;
      }
      *(byte *)(param_1 + 0x19) = bVar2;
    }
  }
  else if (DAT_8009c57e == 0) {
    FUN_80023548();
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0x3f;
    FUN_80040204(6);
  }
  return;
}

