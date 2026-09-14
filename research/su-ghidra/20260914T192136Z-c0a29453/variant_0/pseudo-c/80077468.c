/* Analysis pseudo-C, not buildable source. */

void FUN_80077468(int param_1,uint param_2)

{
  int iVar1;
  ushort uVar2;
  ushort uVar3;
  
  iVar1 = DAT_80093fb8;
  param_2 = param_2 & 0xffffff;
  uVar2 = (ushort)param_2;
  uVar3 = (ushort)(param_2 >> 0x10);
  if (param_1 == 0) {
    if ((DAT_80093fa4 & 1) == 0) {
      *(ushort *)(DAT_80093fb8 + 0x18c) = uVar2;
      *(ushort *)(iVar1 + 0x18e) = uVar3;
      DAT_80093f44 = DAT_80093f44 & ~param_2;
    }
    else {
      DAT_80093f70 = DAT_80093f70 | 1;
      DAT_80093f6c = DAT_80093f6c & ~param_2;
      if ((DAT_800f70a8 & param_2) != 0) {
        DAT_800f70a8 = DAT_800f70a8 & (ushort)~param_2;
      }
      DAT_800f70ac = uVar2;
      DAT_800f70ae = uVar3;
      if (((uint)DAT_800f70aa & param_2 >> 0x10) != 0) {
        DAT_800f70aa = DAT_800f70aa & ~uVar3;
      }
    }
  }
  else if (param_1 == 1) {
    if ((DAT_80093fa4 & 1) == 0) {
      DAT_80093f44 = DAT_80093f44 | param_2;
      *(ushort *)(DAT_80093fb8 + 0x188) = uVar2;
      *(ushort *)(iVar1 + 0x18a) = uVar3;
    }
    else {
      DAT_80093f70 = DAT_80093f70 | 1;
      DAT_80093f6c = DAT_80093f6c | param_2;
      if ((DAT_800f70ac & param_2) != 0) {
        DAT_800f70ac = DAT_800f70ac & ~uVar2;
      }
      DAT_800f70a8 = uVar2;
      DAT_800f70aa = uVar3;
      if (((uint)DAT_800f70ae & param_2 >> 0x10) != 0) {
        DAT_800f70ae = DAT_800f70ae & ~uVar3;
      }
    }
  }
  return;
}

