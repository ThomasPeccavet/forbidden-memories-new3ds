/* Analysis pseudo-C, not buildable source. */

void FUN_8004af8c(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  uint *puVar6;
  int iVar7;
  int iVar8;
  byte local_38 [24];
  
  FUN_8007795c(local_38);
  iVar7 = 0;
  uVar5 = 0;
  if (0 < *(short *)(DAT_8009c7d8 + 0x510)) {
    puVar6 = &DAT_80011360;
    pbVar4 = local_38;
    iVar8 = 0x180;
    do {
      iVar3 = DAT_8009c7d8 + iVar8;
      if (*(byte *)(iVar3 + 3) < 0x10) {
        FUN_8004a8cc(iVar3,0);
      }
      if (*pbVar4 == 0) {
        if (*(char *)(iVar3 + 0xd) != '\0') {
          iVar2 = DAT_8009c7d8 + (uint)*(byte *)(iVar3 + 3) * 0x18;
          bVar1 = *(byte *)(iVar2 + 6);
          if ((bVar1 & 0xf) != 0) {
            *(byte *)(iVar2 + 6) = bVar1 - 1;
          }
          *(undefined1 *)(iVar3 + 0xd) = 0;
          *(undefined2 *)(iVar3 + 0x1e) = 0;
          *(undefined1 *)(iVar3 + 3) = 99;
          goto LAB_8004b070;
        }
      }
      else {
LAB_8004b070:
        bVar1 = *(byte *)(iVar3 + 0xd);
        if ((bVar1 != 0) && (*pbVar4 == 3)) {
          if (bVar1 < 2) {
            *(byte *)(iVar3 + 0xd) = bVar1 + 1;
          }
          else {
            uVar5 = uVar5 | *puVar6;
            FUN_8004ac50(iVar7);
          }
        }
      }
      if ((*(char *)(iVar3 + 0xf) == '\0') && (*pbVar4 - 1 < 2)) {
        do {
          FUN_80077468(0,*puVar6);
          iVar3 = FUN_80077628(*puVar6);
          if (iVar3 == 2) break;
        } while (iVar3 != 0);
        uVar5 = uVar5 | *puVar6;
      }
      puVar6 = puVar6 + 1;
      pbVar4 = pbVar4 + 1;
      iVar7 = iVar7 + 1;
      iVar8 = iVar8 + 0x28;
    } while (iVar7 < *(short *)(DAT_8009c7d8 + 0x510));
  }
  if (uVar5 != 0) {
    FUN_80077468(0,uVar5);
  }
  return;
}

