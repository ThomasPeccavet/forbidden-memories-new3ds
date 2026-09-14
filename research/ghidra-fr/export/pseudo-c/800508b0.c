/* Analysis pseudo-C, not buildable source. */

void FUN_800508b0(int param_1)

{
  int iVar1;
  uint uVar2;
  uint *puVar3;
  undefined *puVar4;
  int iVar5;
  undefined *puVar6;
  int iVar7;
  int iVar8;
  
  param_1 = param_1 * 0xe20;
  puVar4 = &DAT_800f4178 + param_1;
  if (*(int *)(&DAT_800f4f50 + param_1) != 0) {
    iVar5 = 0;
    if ((&DAT_800f4f93)[param_1] != '\0') {
      iVar8 = 0;
      iVar7 = 0x74;
      puVar6 = puVar4;
      do {
        uVar2 = 1;
        if (*(int *)(puVar6 + 0x1e0) == 0) break;
        *(undefined1 *)(*(int *)(puVar6 + 0x1e0) + 0x1a) = 1;
        puVar3 = (uint *)(*(int *)(&DAT_800f4f50 + param_1) +
                         (uint)*(ushort *)(*(int *)(puVar6 + 0x1e0) + 0x18) * 4);
        *(ushort *)(puVar4 + iVar7 + 0x2c8) = *(ushort *)(*(int *)(puVar6 + 0x1e0) + 0x18);
        while( true ) {
          for (; -1 < (int)*puVar3; puVar3 = puVar3 + 1) {
            iVar1 = iVar8 + uVar2 * 0x76;
            *(ushort *)(puVar4 + iVar1 + 0x750) =
                 *(short *)(puVar4 + iVar1 + 0x750) + (ushort)*(byte *)((int)puVar3 + 2);
          }
          uVar2 = *puVar3 >> 0x10 & 0x7f;
          if (uVar2 == 0) break;
          iVar1 = iVar8 + uVar2 * 0x74;
          if (*(short *)(puVar4 + iVar1 + 0x2c8) == -1) {
            *(ushort *)(puVar4 + iVar1 + 0x2c8) = (ushort)*puVar3;
            puVar3 = (uint *)(*(int *)(&DAT_800f4f50 + param_1) + (uint)(ushort)*puVar3 * 4);
          }
          else {
            puVar3 = puVar3 + 1;
          }
        }
        iVar8 = iVar8 + 2;
        iVar7 = iVar7 + 2;
        iVar5 = iVar5 + 1;
        puVar6 = puVar6 + 4;
      } while (iVar5 < (int)(uint)(byte)(&DAT_800f4f93)[param_1]);
    }
    iVar5 = param_1 + -0x7ff0be12;
    iVar7 = 0x76;
    do {
      *(undefined2 *)(iVar5 + 0x7c4) = 0;
      iVar1 = 0;
      iVar8 = iVar7;
      if ((&DAT_800f4f93)[param_1] != '\0') {
        do {
          if (*(ushort *)(iVar5 + 0x7c4) < *(ushort *)(puVar4 + iVar8 + 0x750)) {
            *(ushort *)(iVar5 + 0x7c4) = *(ushort *)(puVar4 + iVar8 + 0x750);
          }
          iVar1 = iVar1 + 1;
          iVar8 = iVar8 + 2;
        } while (iVar1 < (int)(uint)(byte)(&DAT_800f4f93)[param_1]);
      }
      iVar5 = iVar5 + 0x76;
      iVar7 = iVar7 + 0x76;
    } while (iVar5 < param_1 + -0x7ff0b9ec);
  }
  return;
}

