/* Analysis pseudo-C, not buildable source. */

int FUN_80017e94(int param_1,undefined2 param_2,undefined2 param_3)

{
  undefined1 uVar1;
  short sVar2;
  undefined4 uVar3;
  int iVar4;
  
  uVar3 = FUN_80040350();
  iVar4 = FUN_800403d0(uVar3,6);
  sVar2 = *(short *)(param_1 + 0xc);
  *(undefined1 *)(iVar4 + 0x67) = 0;
  uVar3 = (&DAT_801d4244)[sVar2 + -1];
  *(undefined1 *)(iVar4 + 0x69) = 0;
  *(byte *)(iVar4 + 0x68) = (byte)((int)uVar3 >> 0x1a) & 0x1f;
  *(char *)(iVar4 + 0x6a) = (char)((ulonglong)(param_1 + 0x7fe58528U >> 2) * 0x24924925 >> 0x20);
  uVar1 = *(undefined1 *)(*(int *)(param_1 + 4) + 2);
  *(undefined2 *)(iVar4 + 0x30) = param_2;
  *(undefined2 *)(iVar4 + 0x32) = param_3;
  *(uint *)(iVar4 + 4) = *(uint *)(iVar4 + 4) | 0x1000000;
  *(undefined1 **)(iVar4 + 0x10) = &LAB_80016694;
  *(undefined1 *)(iVar4 + 0x6b) = uVar1;
  FUN_80042c48(iVar4);
  *(code **)(iVar4 + 0x4c) = FUN_80016c20;
  FUN_80017dcc(iVar4);
  FUN_80017d44(iVar4);
  return iVar4;
}

