/* Analysis pseudo-C, not buildable source. */

uint FUN_80076de8(int param_1,uint param_2,int param_3,int param_4)

{
  ushort uVar1;
  undefined *puVar2;
  ushort *puVar3;
  ushort uVar4;
  uint uVar5;
  
  puVar2 = &DAT_800f6f20;
  if ((DAT_80093fa4 & 1) == 0) {
    puVar2 = DAT_80093fb8;
  }
  uVar5 = (uint)*(ushort *)(puVar2 + param_3 * 2) |
          (*(ushort *)(puVar2 + param_4 * 2) & 0xff) << 0x10;
  uVar4 = (ushort)param_2;
  uVar1 = (ushort)(param_2 >> 0x10);
  if (param_1 == 1) {
    if ((DAT_80093fa4 & 1) == 0) {
      puVar3 = (ushort *)(DAT_80093fb8 + param_4 * 2);
      *(ushort *)(DAT_80093fb8 + param_3 * 2) = *(ushort *)(DAT_80093fb8 + param_3 * 2) | uVar4;
      *puVar3 = *puVar3 | uVar1 & 0xff;
    }
    else {
      *(ushort *)(&DAT_800f6f20 + param_3 * 2) = *(ushort *)(&DAT_800f6f20 + param_3 * 2) | uVar4;
      *(ushort *)(&DAT_800f6f20 + param_4 * 2) =
           *(ushort *)(&DAT_800f6f20 + param_4 * 2) | uVar1 & 0xff;
      DAT_80093f70 = DAT_80093f70 | 1 << (param_3 + -0xc6 >> 1 & 0x1fU);
    }
    uVar5 = uVar5 | param_2 & 0xffffff;
  }
  else if (param_1 < 2) {
    if (param_1 == 0) {
      if ((DAT_80093fa4 & 1) == 0) {
        puVar3 = (ushort *)(DAT_80093fb8 + param_4 * 2);
        *(ushort *)(DAT_80093fb8 + param_3 * 2) = *(ushort *)(DAT_80093fb8 + param_3 * 2) & ~uVar4;
        *puVar3 = *puVar3 & ~(uVar1 & 0xff);
      }
      else {
        *(ushort *)(&DAT_800f6f20 + param_3 * 2) = *(ushort *)(&DAT_800f6f20 + param_3 * 2) & ~uVar4
        ;
        *(ushort *)(&DAT_800f6f20 + param_4 * 2) =
             *(ushort *)(&DAT_800f6f20 + param_4 * 2) & ~(uVar1 & 0xff);
        DAT_80093f70 = DAT_80093f70 | 1 << (param_3 + -0xc6 >> 1 & 0x1fU);
      }
      uVar5 = uVar5 & ~(param_2 & 0xffffff);
    }
  }
  else if (param_1 == 8) {
    if ((DAT_80093fa4 & 1) == 0) {
      puVar3 = (ushort *)(DAT_80093fb8 + param_4 * 2);
      *(ushort *)(DAT_80093fb8 + param_3 * 2) = uVar4;
      *puVar3 = uVar1 & 0xff;
    }
    else {
      *(ushort *)(&DAT_800f6f20 + param_3 * 2) = uVar4;
      *(ushort *)(&DAT_800f6f20 + param_4 * 2) = uVar1 & 0xff;
      DAT_80093f70 = DAT_80093f70 | 1 << (param_3 + -0xc6 >> 1 & 0x1fU);
    }
    uVar5 = param_2 & 0xffffff;
  }
  return uVar5;
}

