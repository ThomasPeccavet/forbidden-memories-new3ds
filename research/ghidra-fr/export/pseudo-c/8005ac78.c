/* Analysis pseudo-C, not buildable source. */

void FUN_8005ac78(int param_1,uint param_2,int param_3)

{
  int iVar1;
  int iVar2;
  ushort *puVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  
  iVar1 = param_1 * 0xe20;
  iVar7 = *(int *)(&DAT_800f4f58 + iVar1);
  iVar9 = *(int *)(&DAT_800f4f54 + iVar1);
  piVar6 = (int *)(&DAT_800f4358 + iVar1);
  if ((&DAT_800f4f97)[iVar1] != '\0') {
    if (param_2 == 0xffffffff) {
      iVar7 = 0;
      (&DAT_800f4f88)[iVar1] = 0;
      if ((&DAT_800f4f93)[iVar1] != '\0') {
        do {
          *(undefined2 *)(*piVar6 + 8) = 0xffff;
          iVar7 = iVar7 + 1;
          piVar6 = piVar6 + 1;
        } while (iVar7 < (int)(uint)(byte)(&DAT_800f4f93)[iVar1]);
      }
    }
    else if (param_2 == 0) {
      if (*(char *)((int)&DAT_800f4f84 + iVar1 + 3) != '\0') {
        iVar4 = 0;
        if ((&DAT_800f4f93)[iVar1] != '\0') {
          do {
            uVar8 = (uint)*(ushort *)
                           (&DAT_800f4178 +
                           iVar4 * 2 + (uint)*(byte *)((int)&DAT_800f4f84 + iVar1 + 3) * 0x74 +
                           iVar1 + 0x2c8);
            if (uVar8 != 0xffff) {
              iVar2 = iVar4;
              if (iVar4 < 0) {
                iVar2 = iVar4 + 7;
              }
              iVar5 = 3;
              if (((int)(uint)(byte)(&DAT_800f4178)[(iVar2 >> 3) + iVar1 + 0xbec] >>
                   (iVar4 + (iVar2 >> 3) * -8 & 0x1fU) & 1U) != 0) {
                iVar5 = 5;
              }
              FUN_8004d978(iVar9 + (uint)*(ushort *)(*(int *)(&DAT_800f4f50 + iVar1) + uVar8 * 4) *
                                   4,iVar7,iVar5);
              iVar7 = iVar7 + iVar5 * 4;
            }
            iVar4 = iVar4 + 1;
          } while (iVar4 < (int)(uint)(byte)(&DAT_800f4f93)[iVar1]);
        }
        *(undefined1 *)((int)&DAT_800f4f84 + iVar1 + 3) = 0;
      }
    }
    else {
      uVar8 = (uint)*(byte *)((int)&DAT_800f4f84 + iVar1 + 3);
      if (param_2 != (byte)(&DAT_800f4f76)[iVar1] + 3) {
        *(undefined1 *)((int)&DAT_800f4f84 + iVar1 + 2) = 2;
      }
      if (*(short *)(&DAT_800f4178 + param_2 * 0x76 + iVar1 + 0x7c4) != 0) {
        if (uVar8 != 0) {
          if (param_3 == 0) {
            return;
          }
          (&DAT_800f4d6e)[iVar1] = (&DAT_800f4d6c)[iVar1];
          FUN_8005ac78(param_1,0,0);
        }
        if ((param_2 == (byte)(&DAT_800f4f76)[iVar1] + 3) ||
           ((&DAT_800f4f70)[param_1 * 0x710] == 0x309)) {
          *(undefined1 *)((int)&DAT_800f4f84 + iVar1 + 2) = 7;
        }
        *(char *)((int)&DAT_800f4f84 + iVar1 + 3) = (char)param_2;
        if (uVar8 == param_2) {
          FUN_8005c8d0(param_1,0,0);
        }
        else {
          iVar4 = 0;
          (&DAT_800f4f88)[iVar1] = 1;
          if ((&DAT_800f4f93)[iVar1] != '\0') {
            do {
              uVar8 = (uint)*(ushort *)
                             (&DAT_800f4178 +
                             iVar4 * 2 + (uint)*(byte *)((int)&DAT_800f4f84 + iVar1 + 3) * 0x74 +
                             iVar1 + 0x2c8);
              puVar3 = (ushort *)(*(int *)(&DAT_800f4f50 + iVar1) + uVar8 * 4);
              if (uVar8 != 0xffff) {
                iVar2 = iVar4;
                if (iVar4 < 0) {
                  iVar2 = iVar4 + 7;
                }
                iVar5 = 3;
                if (((int)(uint)(byte)(&DAT_800f4178)[(iVar2 >> 3) + iVar1 + 0xbec] >>
                     (iVar4 + (iVar2 >> 3) * -8 & 0x1fU) & 1U) != 0) {
                  iVar5 = 5;
                }
                *(short *)(*piVar6 + 8) =
                     (short)((int)puVar3 - *(int *)(&DAT_800f4f50 + iVar1) >> 2);
                FUN_8004d978(iVar7,iVar9 + (uint)*puVar3 * 4,iVar5);
                iVar7 = iVar7 + iVar5 * 4;
              }
              iVar4 = iVar4 + 1;
              piVar6 = piVar6 + 1;
            } while (iVar4 < (int)(uint)(byte)(&DAT_800f4f93)[iVar1]);
          }
        }
      }
    }
  }
  return;
}

