/* Analysis pseudo-C, not buildable source. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_8003b0fc(int *param_1)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  int local_20;
  int local_1c;
  
  iVar2 = FUN_8003a2ac();
  if (iVar2 == 0) {
    *(byte *)((int)param_1 + 0x32) = *(byte *)((int)param_1 + 0x32) | 0x10;
    uVar1 = *(undefined1 *)(*param_1 + 0x67);
    iVar2 = (int)*(char *)(*param_1 + 0x16);
    FUN_8003a320(param_1);
    FUN_8003a57c(param_1,param_1,*(undefined1 *)((int)param_1 + 0x31));
    FUN_8003a7d0(param_1,0x50000000,iVar2);
    FUN_8003a57c(param_1,param_1 + 3,*(undefined1 *)((int)param_1 + 0x31));
    FUN_8003a7d0(param_1 + 3,0x60000000,iVar2 + -1);
    FUN_8003a57c(param_1,param_1 + 6,uVar1);
    FUN_8003a7d0(param_1 + 6,0x50000000,iVar2);
    FUN_8003a57c(param_1,param_1 + 9,uVar1);
    FUN_8003a7d0(param_1 + 9,0x60000000,iVar2 + -1);
    *(undefined2 *)(param_1 + 0x10) = 0x80;
  }
  iVar2 = (uint)*(ushort *)(param_1 + 0x10) + _DAT_8009c43c * -8;
  *(short *)(param_1 + 0x10) = (short)iVar2;
  uVar3 = iVar2 * 0x10000 >> 0x10;
  if ((int)uVar3 < 1) {
    *(undefined1 *)((int)param_1 + 0x33) = 0;
    FUN_8003a7d0(param_1,0,(int)*(char *)(*param_1 + 0x16));
    FUN_8003acb0(param_1,(int)(short)param_1[0xd],(int)*(short *)((int)param_1 + 0x36));
    FUN_8003a320(param_1 + 3);
    FUN_8003a320(param_1 + 6);
    FUN_8003a320(param_1 + 9);
    *(byte *)((int)param_1 + 0x32) = *(byte *)((int)param_1 + 0x32) & 0xef;
  }
  else {
    uVar3 = uVar3 | uVar3 << 8 | uVar3 << 0x10;
    iVar2 = 2;
    piVar5 = param_1 + 2;
    do {
      if (piVar5[6] != 0) {
        *(uint *)(piVar5[6] + 0xc) = uVar3;
      }
      if (piVar5[9] != 0) {
        *(uint *)(piVar5[9] + 0xc) = uVar3;
      }
      iVar2 = iVar2 + -1;
      piVar5 = piVar5 + -1;
    } while (-1 < iVar2);
    iVar2 = 2;
    piVar5 = param_1 + 2;
    uVar3 = 0x80 - (int)(short)param_1[0x10];
    uVar3 = uVar3 | uVar3 * 0x100 | uVar3 * 0x10000;
    do {
      if (*piVar5 != 0) {
        *(uint *)(*piVar5 + 0xc) = uVar3;
      }
      if (piVar5[3] != 0) {
        *(uint *)(piVar5[3] + 0xc) = uVar3;
      }
      iVar2 = iVar2 + -1;
      piVar5 = piVar5 + -1;
    } while (-1 < iVar2);
    iVar2 = (int)(short)param_1[0x10];
    if (iVar2 < 0) {
      iVar2 = iVar2 + 7;
    }
    iVar4 = -(int)(short)param_1[0x10] + 0x80;
    if (iVar4 < 0) {
      iVar4 = -(int)(short)param_1[0x10] + 0x87;
    }
    local_20 = iVar2 >> 3;
    local_1c = -(iVar4 >> 3);
    if ((char)param_1[0xf] == '\0') {
      local_20 = -(iVar2 >> 3);
      local_1c = iVar4 >> 3;
    }
    iVar4 = (int)*(short *)((int)param_1 + 0x36);
    iVar2 = ((short)param_1[0xd] + local_20) * 0x10000 >> 0x10;
    FUN_8003acb0(param_1,iVar2,iVar4);
    FUN_8003acb0(param_1 + 3,iVar2,iVar4);
    iVar2 = ((short)param_1[0xd] - local_1c) * 0x10000 >> 0x10;
    FUN_8003acb0(param_1 + 6,iVar2,iVar4);
    FUN_8003acb0(param_1 + 9,iVar2,iVar4);
  }
  return;
}

