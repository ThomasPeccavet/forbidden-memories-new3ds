/* Analysis pseudo-C, not buildable source. */

void FUN_800235a0(int param_1)

{
  char cVar1;
  char cVar2;
  undefined2 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  
  cVar1 = *(char *)(param_1 + 0x10);
  cVar2 = *(char *)(param_1 + 0xf);
  uVar4 = FUN_80040350();
  iVar5 = FUN_800403d0(uVar4,2);
  FUN_8004078c(iVar5,4,3,(uint)*(byte *)(param_1 + 0x17) + (uint)DAT_8009c504 * 4,0x1f,0x100);
  iVar6 = (cVar1 * 5 + (int)cVar2) * 4 + (uint)DAT_8009c504 * 0x50;
  *(undefined2 *)(iVar5 + 0x28) = *(undefined2 *)(&DAT_80091a08 + iVar6);
  uVar3 = *(undefined2 *)(&DAT_80091a0a + iVar6);
  *(ushort *)(iVar5 + 8) = *(ushort *)(iVar5 + 8) | 0x28;
  *(code **)(iVar5 + 0x24) = FUN_80015c34;
  *(undefined2 *)(iVar5 + 0x2a) = uVar3;
  *(int *)(param_1 + 4) = iVar5;
  return;
}

