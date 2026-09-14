/* Analysis pseudo-C, not buildable source. */

void FUN_80013b44(char param_1)

{
  undefined2 *puVar1;
  byte bVar2;
  bool bVar3;
  undefined *puVar4;
  int iVar5;
  int iVar6;
  ushort uVar7;
  undefined4 *puVar8;
  int iVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  
  puVar4 = PTR_DAT_8009c2a8;
  DAT_8009c4ac = DAT_8009c4ac + '\x01';
  if (param_1 != '\x01') {
    return;
  }
  DAT_8009c478 = DAT_8009c478 + 1;
  bVar2 = PTR_DAT_8009c2a8[0x46];
  if (bVar2 == 2) {
    puVar10 = *(undefined4 **)
               (PTR_DAT_8009c2a8 + (*(ushort *)(PTR_DAT_8009c2a8 + 0x44) & 1) * 4 + 8);
    iVar9 = 0;
    puVar11 = DAT_8009c4a4;
    puVar8 = puVar10;
    if ((DAT_8009c460 & 0x40000000) == 0) {
      FUN_8007e968(puVar10,0x200);
    }
    else {
      do {
        iVar9 = iVar9 + 1;
        *puVar8 = *puVar11;
        puVar11 = puVar11 + 1;
        puVar8 = puVar8 + 1;
      } while (iVar9 < 0x200);
      DAT_8009c4a4 = DAT_8009c4a4 + 0x200;
    }
    iVar9 = *(int *)(PTR_DAT_8009c2a8 + 0x10);
    *(int *)(PTR_DAT_8009c2a8 + 0x10) = iVar9 + -0x800;
    if (iVar9 + -0x800 < 1) {
      FUN_8007e36c();
      FUN_8007edf8(0);
    }
    puVar4 = PTR_DAT_8009c2a8;
    puVar1 = (undefined2 *)(PTR_DAT_8009c2a8 + 0x32);
    *(undefined2 *)PTR_DAT_8009c2a8 = *(undefined2 *)(PTR_DAT_8009c2a8 + 0x30);
    *(undefined2 *)(puVar4 + 2) = *puVar1;
    do {
      iVar9 = FUN_80082380(PTR_DAT_8009c2a8,puVar10);
      puVar4 = PTR_DAT_8009c2a8;
    } while (iVar9 != 0);
    if ((DAT_8009c460 & 0x20000) == 0) {
      uVar7 = *(short *)(PTR_DAT_8009c2a8 + 0x32) + 0x10;
      *(ushort *)(PTR_DAT_8009c2a8 + 0x32) = uVar7;
      if ((uVar7 & 0xff) == 0) {
        *(ushort *)(puVar4 + 0x32) = (uVar7 ^ 0x100) & 0x100;
        *(short *)(puVar4 + 0x30) = *(short *)(puVar4 + 0x30) + 0x40;
      }
    }
    else {
      *(short *)(PTR_DAT_8009c2a8 + 0x30) = *(short *)(PTR_DAT_8009c2a8 + 0x30) + 0x40;
    }
    puVar4 = PTR_DAT_8009c2a8;
    iVar9 = *(int *)(PTR_DAT_8009c2a8 + 0x28) + -0x800;
    *(int *)(PTR_DAT_8009c2a8 + 0x28) = iVar9;
  }
  else {
    if (bVar2 < 3) {
      if (bVar2 != 1) {
        return;
      }
      if ((DAT_8009c460 & 0x200000) == 0) {
        iVar9 = 0;
        puVar11 = DAT_8009c4a4;
        if ((DAT_8009c460 & 0x40000000) == 0) {
          FUN_8007e968(*(undefined4 *)(PTR_DAT_8009c2a8 + 8),0x200);
        }
        else {
          do {
            iVar5 = iVar9 * 4;
            iVar9 = iVar9 + 1;
            *(undefined4 *)(iVar5 + *(int *)(puVar4 + 8)) = *puVar11;
            puVar11 = puVar11 + 1;
          } while (iVar9 < 0x200);
        }
        *(int *)(PTR_DAT_8009c2a8 + 8) = *(int *)(PTR_DAT_8009c2a8 + 8) + 0x800;
      }
      iVar9 = *(int *)(PTR_DAT_8009c2a8 + 0x10);
      DAT_8009c4a4 = DAT_8009c4a4 + 0x200;
      *(int *)(PTR_DAT_8009c2a8 + 0x10) = iVar9 + -0x800;
      if (iVar9 + -0x800 < 1) {
        FUN_8007e36c();
        FUN_8007edf8(0);
      }
      puVar4 = PTR_DAT_8009c2a8;
      iVar9 = *(int *)(PTR_DAT_8009c2a8 + 0x28);
      *(int *)(PTR_DAT_8009c2a8 + 0x28) = iVar9 + -0x800;
      if (iVar9 + -0x800 < 1) {
        *(undefined4 *)(puVar4 + 0x1c) = 0;
        if (*(int *)(puVar4 + 0x20) != 0) {
          iVar9 = *(int *)(puVar4 + 0x40);
          *(int *)(puVar4 + 0x40) = iVar9 + 1;
          (**(code **)(puVar4 + 0x20))(puVar4,iVar9);
        }
        *(undefined4 *)(puVar4 + 0x28) = *(undefined4 *)(puVar4 + 0x1c);
      }
      iVar9 = *(int *)(PTR_DAT_8009c2a8 + 0x10);
      goto joined_r0x80013f90;
    }
    if (bVar2 != 3) {
      return;
    }
    puVar11 = *(undefined4 **)(PTR_DAT_8009c2a8 + 8);
    iVar5 = 0x800;
    if (*(int *)(PTR_DAT_8009c2a8 + 0x28) < 0x800) {
      iVar5 = *(int *)(PTR_DAT_8009c2a8 + 0x28);
    }
    iVar9 = 0;
    puVar8 = DAT_8009c4a4;
    puVar10 = puVar11;
    if ((DAT_8009c460 & 0x40000000) == 0) {
      iVar9 = iVar5;
      if (iVar5 < 0) {
        iVar9 = iVar5 + 3;
      }
      FUN_8007e968(puVar11,iVar9 >> 2);
    }
    else {
      while( true ) {
        iVar6 = iVar5;
        if (iVar5 < 0) {
          iVar6 = iVar5 + 3;
        }
        bVar3 = iVar6 >> 2 <= iVar9;
        iVar9 = iVar9 + 1;
        if (bVar3) break;
        *puVar10 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar10 = puVar10 + 1;
      }
      DAT_8009c4a4 = (undefined4 *)((int)DAT_8009c4a4 + iVar5);
    }
    iVar9 = *(int *)(PTR_DAT_8009c2a8 + 0x10);
    *(int *)(PTR_DAT_8009c2a8 + 0x10) = iVar9 + -0x800;
    if (iVar9 + -0x800 < 1) {
      FUN_8007e36c();
      FUN_8007edf8(0);
    }
    FUN_80077748(*(undefined4 *)(PTR_DAT_8009c2a8 + 0x30));
    FUN_800776e8(puVar11,iVar5);
    puVar4 = PTR_DAT_8009c2a8;
    iVar9 = *(int *)(PTR_DAT_8009c2a8 + 0x28) + -0x800;
    *(int *)(PTR_DAT_8009c2a8 + 0x30) = *(int *)(PTR_DAT_8009c2a8 + 0x30) + iVar5;
    *(int *)(puVar4 + 0x28) = iVar9;
  }
  if (iVar9 < 1) {
    *(undefined4 *)(puVar4 + 0x1c) = 0;
    if (*(int *)(puVar4 + 0x20) != 0) {
      iVar9 = *(int *)(puVar4 + 0x40);
      *(int *)(puVar4 + 0x40) = iVar9 + 1;
      (**(code **)(puVar4 + 0x20))(puVar4,iVar9);
    }
    *(undefined4 *)(puVar4 + 0x28) = *(undefined4 *)(puVar4 + 0x1c);
  }
  iVar9 = *(int *)(PTR_DAT_8009c2a8 + 0x10);
  *(short *)(PTR_DAT_8009c2a8 + 0x44) = *(short *)(PTR_DAT_8009c2a8 + 0x44) + 1;
joined_r0x80013f90:
  if (iVar9 < 1) {
    DAT_8009c460 = DAT_8009c460 & 0xfffffeff;
  }
  return;
}

