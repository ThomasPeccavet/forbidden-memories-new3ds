/* Analysis pseudo-C, not buildable source. */

void FUN_80046750(void)

{
  short sVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  
  iVar6 = 0;
  if (0 < *(short *)(DAT_8009c7e0 + 0x4c)) {
    iVar7 = 0x30;
    iVar5 = 0;
    while (*(short *)(DAT_8009c7e0 + 0x4c) != 0) {
      switch(*(undefined1 *)(DAT_8009c7e0 + iVar5 + 0x80)) {
      case 0x20:
        puVar2 = (undefined4 *)(DAT_8009c7e0 + iVar5 + 0x80);
        if (*(int *)(DAT_8009c7e0 + iVar5 + 0x90) == 0x20) {
          iVar3 = DAT_8009c7e0 + iVar7;
          puVar4 = (undefined4 *)(iVar3 + 0x80);
          do {
            uVar8 = puVar4[1];
            uVar9 = puVar4[2];
            uVar10 = puVar4[3];
            *puVar2 = *puVar4;
            puVar2[1] = uVar8;
            puVar2[2] = uVar9;
            puVar2[3] = uVar10;
            puVar4 = puVar4 + 4;
            puVar2 = puVar2 + 4;
          } while (puVar4 != (undefined4 *)(iVar3 + 0xb0));
          goto LAB_80046868;
        }
        break;
      default:
        iVar7 = iVar7 + 0x30;
        iVar5 = iVar5 + 0x30;
        iVar6 = iVar6 + 1;
        break;
      case 0x42:
      case 0x43:
      case 0x45:
      case 0x46:
      case 0x48:
        puVar2 = (undefined4 *)(DAT_8009c7e0 + iVar5 + 0x80);
        iVar3 = DAT_8009c7e0 + iVar7;
        puVar4 = (undefined4 *)(iVar3 + 0x80);
        do {
          uVar8 = puVar4[1];
          uVar9 = puVar4[2];
          uVar10 = puVar4[3];
          *puVar2 = *puVar4;
          puVar2[1] = uVar8;
          puVar2[2] = uVar9;
          puVar2[3] = uVar10;
          puVar4 = puVar4 + 4;
          puVar2 = puVar2 + 4;
        } while (puVar4 != (undefined4 *)(iVar3 + 0xb0));
LAB_80046868:
        *(short *)(DAT_8009c7e0 + 0x4c) = *(short *)(DAT_8009c7e0 + 0x4c) + -1;
      }
      if ((*(short *)(DAT_8009c7e0 + 0x4c) <= iVar6) || (iVar6 < 0)) break;
    }
  }
  switch(*(undefined1 *)(DAT_8009c7e0 + 0x7c)) {
  case 0x42:
  case 0x43:
  case 0x45:
  case 0x46:
  case 0x48:
    *(undefined1 *)(DAT_8009c7e0 + 0x7c) = 0;
    *(undefined1 *)(DAT_8009c7e0 + 0x7d) = 0;
  }
  if (((*(ushort *)(DAT_8009c7e0 + 0x40) & 0x80) != 0) && (*(short *)(DAT_8009c7e0 + 0x157e) != -1))
  {
    sVar1 = FUN_8004a3e0();
    if (sVar1 == 1) {
      FUN_8004a0d0((int)*(short *)(DAT_8009c7e0 + 0x157e));
    }
    *(ushort *)(DAT_8009c7e0 + 0x40) = *(ushort *)(DAT_8009c7e0 + 0x40) & 0xff7f;
  }
  return;
}

