/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8004c178(void)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  undefined2 uVar4;
  uint uVar5;
  ushort uVar6;
  int iVar7;
  
  iVar2 = DAT_8009c7d8;
  iVar7 = DAT_8009c7d8 + 0x518;
  *(undefined1 *)(DAT_8009c7d8 + 0x801) = 0;
  iVar3 = DAT_8009c7d8;
  *(undefined4 *)(DAT_8009c7d8 + 0x7f0) = 0;
  *(undefined4 *)(iVar3 + 0x7f4) = 0;
  *(undefined4 *)(iVar2 + 0x518) = 8;
  uVar4 = FUN_8004c138(iVar7);
  iVar3 = DAT_8009c7d8;
  *(undefined2 *)(DAT_8009c7d8 + 0x7fc) = uVar4;
  *(undefined2 *)(iVar3 + 0x7fa) = 1;
  *(undefined2 *)(iVar3 + 0x7f8) = 0;
  *(undefined4 *)(iVar3 + 0x7ec) = 0x10000;
  uVar5 = FUN_8004c0bc(iVar7);
  iVar3 = DAT_8009c7d8;
  uVar5 = uVar5 >> 8;
  *(uint *)(DAT_8009c7d8 + 0x808) = uVar5;
  if (uVar5 == 0) {
    trap(0x1c00);
  }
  uVar5 = ((60000000 / uVar5) * 100) / 0x73;
  if (0xff < uVar5) {
    uVar5 = 0xff;
  }
  uVar6 = (ushort)uVar5;
  uVar1 = *(ushort *)(iVar3 + 0x7fc);
  if (uVar1 == 0x1e) {
    uVar6 = (ushort)(uVar5 >> 2);
  }
  else {
    if (uVar1 < 0x1f) {
      if (uVar1 != 0x18) goto LAB_8004c294;
    }
    else if (uVar1 != 0x3c) goto LAB_8004c294;
    uVar6 = (ushort)(uVar5 >> 1);
  }
LAB_8004c294:
  *(ushort *)(iVar2 + 0x52e) = uVar6 & 0xff;
  *(ushort *)(iVar2 + 0x52c) = uVar6 & 0xff;
  FUN_8004bf74();
  if (*(ushort *)(DAT_8009c7d8 + 0x7fc) < 0x60) {
    *(undefined4 *)(DAT_8009c7d8 + 0x804) = 0;
  }
  else {
    *(uint *)(DAT_8009c7d8 + 0x804) = (uint)*(ushort *)(DAT_8009c7d8 + 0x7fc);
  }
  *(uint *)(DAT_8009c7d8 + 0x804) = (uint)*(ushort *)(DAT_8009c7d8 + 0x7fc);
  return 1;
}

