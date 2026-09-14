/* Analysis pseudo-C, not buildable source. */

undefined4 FUN_8001f2c4(void)

{
  undefined4 uVar1;
  undefined2 *puVar2;
  ushort uVar3;
  int iVar4;
  
  if (DAT_8009c57e == 0) {
    uVar3 = DAT_8009c520 & 0xf;
    if (uVar3 == 1) {
      DAT_8009c5c2 = DAT_8009c5c2 - 1;
      uVar1 = 1;
      if ((int)((uint)DAT_8009c5c2 << 0x10) < 1) {
        iVar4 = (&DAT_801a7ad8)[(uint)DAT_8009c5b4 * 7];
        puVar2 = (undefined2 *)FUN_8002c860(8);
        *puVar2 = *(undefined2 *)(iVar4 + 0x30);
        puVar2[1] = *(undefined2 *)(iVar4 + 0x32);
        puVar2[2] = *(undefined2 *)(iVar4 + 0x34);
        FUN_80024a10(&DAT_801a7ad8 + (uint)*(byte *)(iVar4 + 0x6a) * 7);
        FUN_80040204(0x17);
        DAT_8009c520 = 2;
        uVar1 = 1;
      }
    }
    else if (uVar3 < 2) {
      uVar1 = 1;
      if ((DAT_8009c520 & 0xf) == 0) {
        FUN_80022e50(0x10,0x208,0x200,(int)DAT_800f11e2,(uint)DAT_8009c504 * -0x164 + 0xb2);
        DAT_8009c57e = 0x10;
        DAT_8009c520 = 1;
        DAT_8009c5c2 = 0x14;
        uVar1 = 1;
      }
    }
    else if (uVar3 == 2) {
      FUN_80022e50(0x10,600,0x100,(int)DAT_800f11e2,0);
      DAT_8009c57e = 0x10;
      DAT_8009c520 = 3;
      DAT_8009c5c2 = 0x14;
      uVar1 = 1;
    }
    else {
      uVar1 = 1;
      if (uVar3 == 3) {
        DAT_8009c5c2 = DAT_8009c5c2 - 1;
        uVar1 = 1;
        if ((int)((uint)DAT_8009c5c2 << 0x10) < 1) {
          iVar4 = (DAT_8009c504 ^ 1) * 0x20;
          uVar1 = 0;
          (&DAT_800eb27e)[iVar4] = (&DAT_800eb27e)[iVar4] + '\x01';
        }
      }
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

