/* Analysis pseudo-C, not buildable source. */

void FUN_8004ca58(int param_1)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = *(ushort *)(DAT_8009c7d8 + 0x7fc);
  if (uVar1 == 0x120) {
LAB_8004cb94:
    *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) / 3;
    return;
  }
  if (uVar1 < 0x121) {
    if (uVar1 == 0x60) {
      iVar2 = *(int *)(param_1 + 0x1c) * 5;
      *(int *)(param_1 + 0x1c) = iVar2;
      *(uint *)(param_1 + 0x1c) = iVar2 + (uint)*(ushort *)(param_1 + 0x18);
      uVar1 = *(ushort *)(param_1 + 0x1c) & 3;
      uVar3 = *(uint *)(param_1 + 0x1c) >> 2;
    }
    else if (uVar1 < 0x61) {
      if (uVar1 != 0x30) {
        return;
      }
      iVar2 = *(int *)(param_1 + 0x1c) * 10;
      *(int *)(param_1 + 0x1c) = iVar2;
      *(uint *)(param_1 + 0x1c) = iVar2 + (uint)*(ushort *)(param_1 + 0x18);
      uVar1 = *(ushort *)(param_1 + 0x1c) & 3;
      uVar3 = *(uint *)(param_1 + 0x1c) >> 2;
    }
    else {
      if ((uVar1 != 0xc0) && (uVar1 != 0xf0)) {
        return;
      }
      *(uint *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + (uint)*(ushort *)(param_1 + 0x18);
      uVar1 = *(ushort *)(param_1 + 0x1c) & 1;
      uVar3 = *(uint *)(param_1 + 0x1c) >> 1;
    }
  }
  else {
    if (uVar1 != 0x1e0) {
      if (0x1e0 < uVar1) {
        if ((uVar1 != 0x300) && (uVar1 != 0x3c0)) {
          return;
        }
        *(uint *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + (uint)*(ushort *)(param_1 + 0x18);
        uVar1 = *(ushort *)(param_1 + 0x1c) & 7;
        uVar3 = *(uint *)(param_1 + 0x1c) >> 3;
        goto LAB_8004cc00;
      }
      if (uVar1 == 0x168) goto LAB_8004cb94;
      if (uVar1 != 0x180) {
        return;
      }
    }
    *(uint *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + (uint)*(ushort *)(param_1 + 0x18);
    uVar1 = *(ushort *)(param_1 + 0x1c) & 3;
    uVar3 = *(uint *)(param_1 + 0x1c) >> 2;
  }
LAB_8004cc00:
  *(ushort *)(param_1 + 0x18) = uVar1;
  *(uint *)(param_1 + 0x1c) = uVar3;
  return;
}

