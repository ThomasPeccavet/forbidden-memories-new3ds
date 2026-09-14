/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_80036c64(int param_1,int param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  ushort uVar3;
  uint uVar4;
  undefined2 *puVar5;
  ushort uVar6;
  undefined4 uVar7;
  
  puVar5 = *(undefined2 **)(param_1 + 0x20);
  *(char *)(puVar5 + 8) = *(char *)(param_1 + 0x57) + '\x01';
  *(undefined1 *)((int)puVar5 + 0x11) = 1;
  *(undefined1 *)((int)puVar5 + 0x13) = 0;
  puVar5[1] = *(undefined2 *)(param_1 + 0x38);
  uVar2 = *(undefined2 *)(param_1 + 0x3a);
  *puVar5 = (short)param_2;
  puVar5[2] = uVar2;
  uVar3 = *(ushort *)(param_1 + 0x34);
  uVar7 = 0;
  if ((uVar3 & 0x100) == 0) {
    uVar4 = param_2 >> 0x14 & 0xff;
    uVar6 = uVar3 & 3;
    if (uVar4 == 0) {
      if (uVar6 != 3) {
        return 0xffffffff;
      }
      return 0;
    }
    *(char *)(puVar5 + 7) = (char)(param_2 >> 0x14);
    uVar1 = *(undefined1 *)(param_1 + 0x54);
    *(byte *)((int)puVar5 + 0xf) = (byte)uVar6 | 0x80;
    *(undefined1 *)(puVar5 + 10) = uVar1;
    if (uVar6 == 3) {
      puVar5[1] = puVar5[1] + 2;
    }
    if (uVar6 == 2) {
      if (((uVar4 == 0x28) || (uVar4 == 0x42)) || (uVar4 == 0x45)) {
        uVar7 = 0xfffffffc;
        puVar5[1] = puVar5[1] + -2;
      }
      if (((uVar4 == 0x3f) || (uVar4 == 0x43)) || (uVar4 == 0x4d)) {
        uVar7 = 0xfffffffe;
        puVar5[1] = puVar5[1] + -1;
      }
    }
    if ((uVar3 & 3) == 0) {
      if (uVar4 == 7) {
        uVar7 = 0xfffffffa;
        puVar5[1] = puVar5[1] + -3;
      }
      if (((uVar4 == 0x3f) || (uVar4 == 0x42)) ||
         ((uVar4 == 0x45 || ((uVar4 == 0xe || (uVar4 == 0xc)))))) {
        uVar7 = 0xfffffffe;
        puVar5[1] = puVar5[1] + -1;
      }
    }
  }
  else {
    *(char *)(puVar5 + 7) = (char)param_2;
    *(undefined1 *)((int)puVar5 + 0xf) = 0xc0;
  }
  if ((*(ushort *)(param_1 + 0x34) & 0x1c00) != 0) {
    *(undefined1 *)((int)puVar5 + 0x11) = 0;
  }
  *(undefined1 *)((int)puVar5 + 0x25) = 0;
  *(undefined2 **)(param_1 + 0x20) = puVar5 + 0xb;
  return uVar7;
}

