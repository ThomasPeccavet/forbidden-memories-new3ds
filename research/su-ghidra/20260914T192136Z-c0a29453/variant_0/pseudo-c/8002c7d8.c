/* Analysis pseudo-C, not buildable source. */

undefined2 * FUN_8002c7d8(undefined2 param_1)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined2 *puVar3;
  
  puVar3 = (undefined2 *)FUN_8002c7a0();
  puVar1 = PTR_FUN_80010000;
  if (puVar3 != (undefined2 *)0x0) {
    *(undefined1 *)(puVar3 + 0xe) = 0x80;
    puVar3[0xc] = param_1;
    puVar3[0xd] = 0;
    *(undefined1 *)((int)puVar3 + 0x1d) = 0;
    *(undefined **)(puVar3 + 10) = puVar1 + 0x3800;
    *(undefined4 *)(puVar3 + 4) = DAT_8009c860;
    uVar2 = DAT_8009c85c;
    puVar3[8] = 8;
    *puVar3 = 0;
    puVar3[1] = 0;
    puVar3[2] = 0;
    puVar3[9] = 0;
    *(undefined4 *)(puVar3 + 6) = uVar2;
  }
  return puVar3;
}

