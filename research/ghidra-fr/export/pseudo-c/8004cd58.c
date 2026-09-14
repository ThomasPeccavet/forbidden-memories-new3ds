/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8004cd58(void)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  ushort uVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  
  iVar2 = DAT_8009c7d8;
  piVar6 = (int *)(DAT_8009c7d8 + 0x518);
  if ((*(short *)(DAT_8009c7d8 + 0x7e2) == 1) && (uVar7 = 0, *(short *)(DAT_8009c7d8 + 0x7fa) != 0))
  {
    do {
      if ((char)piVar6[9] == '\0') {
        uVar4 = (short)piVar6[5] + *(short *)((int)piVar6 + 0x16);
        *(ushort *)(piVar6 + 5) = uVar4;
        if (0xff < uVar4) {
          *(ushort *)(piVar6 + 5) = uVar4 & 0xff;
          if (uVar7 == *(ushort *)(iVar2 + 0x7f8)) {
            *(int *)(iVar2 + 0x7f0) = *(int *)(iVar2 + 0x7f0) + 1;
          }
          iVar5 = piVar6[7];
          if ((iVar5 == 0) || (*(int *)(DAT_8009c7d8 + 0x80c) != 0)) {
            do {
              do {
                FUN_8004c8b0(piVar6);
                if ((char)piVar6[9] != '\0') goto LAB_8004ce7c;
                iVar5 = FUN_8004bfc4(piVar6);
                piVar6[7] = iVar5;
              } while (iVar5 == 0);
              if (*(int *)(DAT_8009c7d8 + 0x804) != 0) {
                FUN_8004ca58(piVar6);
              }
            } while (piVar6[7] == 0);
LAB_8004ce7c:
            iVar5 = piVar6[7];
            if (iVar5 != 0) goto LAB_8004ce8c;
          }
          else {
LAB_8004ce8c:
            piVar6[7] = iVar5 + -1;
          }
          iVar5 = DAT_8009c7d8;
          puVar1 = (uint *)(DAT_8009c7d8 + 0x80c);
          uVar3 = *(int *)(DAT_8009c7d8 + 0x7dc) + *piVar6;
          *(uint *)(DAT_8009c7d8 + 0x810) = uVar3;
          if ((*puVar1 != 0) && (*puVar1 <= uVar3)) {
            *(undefined4 *)(iVar5 + 0x80c) = 0;
          }
        }
      }
      uVar7 = uVar7 + 1;
      piVar6 = piVar6 + 0xb;
    } while ((int)uVar7 < (int)(uint)*(ushort *)(iVar2 + 0x7fa));
  }
  return 0;
}

