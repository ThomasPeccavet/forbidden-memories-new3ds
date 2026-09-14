/* Analysis pseudo-C, not buildable source. */

void FUN_800593c8(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined *puVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  undefined *puVar9;
  undefined4 uVar10;
  
  FUN_8004fc2c();
  if (param_2 == 0) {
    return;
  }
  FUN_800508b0(param_1);
  FUN_80050a68(param_1);
  iVar2 = param_1 * 0xe20;
  puVar5 = &DAT_800f4178 + iVar2;
  iVar8 = 0;
  if (param_1 < 2) {
    iVar7 = 0;
    puVar9 = puVar5;
    if ((byte)(&DAT_800f4f93)[iVar2] != 0) {
      do {
        if (*(short *)(puVar9 + 0x33c) != -1) {
          iVar3 = iVar7;
          if (iVar7 < 0) {
            iVar3 = iVar7 + 7;
          }
          if (((int)(uint)(byte)puVar5[(iVar3 >> 3) + 0xbec] >> (iVar7 + (iVar3 >> 3) * -8 & 0x1fU)
              & 1U) == 0) {
            iVar8 = iVar8 + 0xc;
          }
          else {
            iVar8 = iVar8 + 0x14;
          }
        }
        iVar7 = iVar7 + 1;
        puVar9 = puVar9 + 2;
      } while (iVar7 < (int)(uint)(byte)(&DAT_800f4f93)[iVar2]);
    }
  }
  *(int *)(&DAT_800f4f68 + iVar2) = *(int *)(&DAT_800f4f58 + iVar2) + iVar8;
  *(uint *)(&DAT_800f4f6c + iVar2) =
       *(int *)(&DAT_800f4f58 + iVar2) + iVar8 + (uint)*(ushort *)(&DAT_800f4f7a + iVar2) * 4;
  if (param_1 == 1) {
    uVar10 = 0x800;
  }
  else {
    uVar10 = 0;
  }
  FUN_8005d5cc(puVar5,0,0,0,uVar10);
  iVar2 = param_1 * 0xe20;
  piVar6 = (int *)(&DAT_800f4358 + iVar2);
  iVar8 = 0;
  if ((&DAT_800f4f93)[iVar2] != '\0') {
    do {
      *(undefined2 *)(*piVar6 + 8) = 0xffff;
      *(undefined2 *)(*piVar6 + 0x16) = *(undefined2 *)(*piVar6 + 0x18);
      *(undefined2 *)(*piVar6 + 10) = 0xffff;
      *(undefined1 *)(*piVar6 + 0xc) = *(undefined1 *)(*piVar6 + 0x1a);
      *(undefined2 *)(*piVar6 + 0x10) = 0;
      iVar8 = iVar8 + 1;
      *(undefined1 *)(*piVar6 + 0xd) = 0x10;
      piVar6 = piVar6 + 1;
    } while (iVar8 < (int)(uint)(byte)(&DAT_800f4f93)[iVar2]);
  }
  iVar2 = param_1 * 0xe20;
  (&DAT_800f4f97)[iVar2] = 1;
  FUN_8005c1e4(param_1);
  uVar4 = (uint)*(byte *)((int)&DAT_800f4f84 + iVar2 + 1);
  bVar1 = (&DAT_800f4f8e)[iVar2];
  iVar2 = uVar4 * 2;
  if (bVar1 == 0x3c) {
    iVar2 = uVar4 * -2;
  }
  else if (bVar1 < 0x3d) {
    if (bVar1 != 0x23) goto LAB_80059634;
    iVar2 = 0;
  }
  else if (bVar1 != 0x3e) goto LAB_80059634;
  FUN_8005d570(param_1,iVar2);
LAB_80059634:
  if (param_1 < 2) {
    FUN_8005b444(param_1,*(undefined1 *)(&DAT_800f4f84 + param_1 * 0x388),
                 *(undefined2 *)(&DAT_800f4f82 + param_1 * 0xe20));
  }
  return;
}

