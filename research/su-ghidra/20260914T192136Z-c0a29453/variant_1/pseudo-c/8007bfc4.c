/* Analysis pseudo-C, not buildable source. */

undefined1 FUN_8007bfc4(undefined4 param_1)

{
  char cVar1;
  undefined4 *puVar2;
  
  FUN_8007e8b8(0);
  cVar1 = '\x04';
  if (DAT_800f7198 != 1) {
    cVar1 = DAT_800f7188 == 1;
  }
  if (cVar1 == '\x04') {
    puVar2 = &DAT_800f7198;
  }
  else {
    if (cVar1 != '\x01') {
      return 0;
    }
    puVar2 = &DAT_800f7188;
  }
  *puVar2 = 0;
  FUN_8007d304(param_1,(int)puVar2 + 5);
  return *(undefined1 *)(puVar2 + 1);
}

