/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8006a4d8(int param_1)

{
  bool bVar1;
  ushort uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined2 uVar6;
  int iVar7;
  undefined4 local_20;
  int local_1c;
  
  if (DAT_8009c3eb == '\0') {
    if (param_1 != 0) {
      DAT_8009c3f0 = FUN_80078974(&DAT_8009c81c);
    }
    while( true ) {
      iVar4 = FUN_800746b8(0xffffffff);
      iVar7 = 0;
      while (iVar5 = FUN_80078b58(&local_20,&local_1c), iVar5 != 0) {
        iVar5 = FUN_800746b8(0xffffffff);
        if (0x3b < iVar5 - iVar4) {
          if (DAT_8009c3eb != '\0') {
            return 1;
          }
          iVar7 = iVar7 + 1;
          iVar4 = iVar5;
          if ((param_1 != 0) || (9 < iVar7)) {
            iVar7 = 0;
            FUN_8006ab28(&DAT_8009c81c);
          }
        }
      }
      iVar4 = FUN_80078788(local_1c + 0x1c);
      if (DAT_8009c3f8 <= iVar4 + (uint)*(ushort *)(local_1c + 6) * 2) {
        DAT_8009c3eb = '\x01';
      }
      if (DAT_8009c3f4 <= DAT_8009c3f0) {
        DAT_8009c3ec = 1;
      }
      if (DAT_8009c3f4 <= *(uint *)(local_1c + 8)) {
        DAT_8009c3ec = 1;
      }
      if ((DAT_8009c3eb != '\0') || (DAT_8009c3f0 <= *(uint *)(local_1c + 8))) break;
      FUN_80078a68(local_20);
    }
    DAT_8009c3ee = DAT_8009c3ee + 1 & 1;
    FUN_800914a8(local_20,DAT_8009c818 + (uint)DAT_8009c3ee * 0xe000 + 0x1b000);
    uVar2 = *(ushort *)(local_1c + 0x10);
    if (DAT_8009c3e8 != '\0') {
      uVar2 = (ushort)((uint)uVar2 * 3 >> 1);
    }
    uVar6 = 0x10;
    *(ushort *)(DAT_8009c818 + 0x43024) = uVar2;
    iVar4 = DAT_8009c818;
    bVar1 = DAT_8009c3e8 != '\0';
    *(undefined2 *)(DAT_8009c818 + 0x43026) = *(undefined2 *)(local_1c + 0x12);
    if (bVar1) {
      uVar6 = 0x18;
    }
    *(undefined2 *)(iVar4 + 0x4302c) = uVar6;
    *(undefined2 *)(iVar4 + 0x4302e) = *(undefined2 *)(local_1c + 0x12);
    FUN_80078a68(local_20);
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}

