/* Analysis pseudo-C, not buildable source. */

/* WARNING: Removing unreachable block (ram,0x8001d3b8) */
/* WARNING: Removing unreachable block (ram,0x8001d40c) */

void FUN_8001d324(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_80042ec8();
  if (iVar1 == 0) {
    if (*(ushort *)(param_1 + 0x2c) != (ushort)*(byte *)(param_1 + 0x21)) {
      *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) | 4;
    }
    *(undefined2 *)(param_1 + 0x2e) = *(undefined2 *)(param_1 + 0x60);
    FUN_800434a8(param_1);
    *(undefined2 *)(param_1 + 0x60) = 0;
  }
  if ((ushort)*(byte *)(param_1 + 0x21) != *(ushort *)(param_1 + 0x2c)) {
    if (*(short *)(param_1 + 0x2e) == 0) {
      trap(0x1c00);
    }
    *(byte *)(param_1 + 0x21) =
         *(byte *)(param_1 + 0x21) + (char)(0x80 / (int)*(short *)(param_1 + 0x2e));
  }
  FUN_800434bc(param_1,(int)*(short *)(param_1 + 0x28),(int)*(short *)(param_1 + 0x2a),
               (int)*(short *)(param_1 + 0x60));
  if (*(short *)(param_1 + 0x2e) == 0) {
    trap(0x1c00);
  }
  iVar1 = (uint)*(ushort *)(param_1 + 0x60) + 0x800 / (int)*(short *)(param_1 + 0x2e);
  *(short *)(param_1 + 0x60) = (short)iVar1;
  if (0x7ff < iVar1 * 0x10000 >> 0x10) {
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x2c);
    *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x28);
    if (*(char *)(param_1 + 0x2c) == '\0') {
      *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) & 0xfffb;
    }
    *(undefined1 *)(param_1 + 0x6c) = 0;
    *(undefined4 *)(param_1 + 0x24) = 0;
  }
  return;
}

