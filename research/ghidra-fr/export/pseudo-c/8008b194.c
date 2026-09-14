/* Analysis pseudo-C, not buildable source. */

int FUN_8008b194(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *param_1;
  iVar2 = param_1[1];
  if (iVar1 < 0) {
    iVar1 = -iVar1;
  }
  if (iVar2 < 0) {
    iVar2 = -iVar2;
  }
  if (iVar1 < iVar2) {
    iVar1 = iVar2;
  }
  iVar2 = param_1[2];
  if (iVar2 < 0) {
    iVar2 = -iVar2;
  }
  if (iVar1 < iVar2) {
    iVar1 = iVar2;
  }
  iVar2 = param_1[3];
  if (iVar2 < 0) {
    iVar2 = -iVar2;
  }
  if (iVar1 < iVar2) {
    iVar1 = iVar2;
  }
  iVar2 = param_1[4];
  if (iVar2 < 0) {
    iVar2 = -iVar2;
  }
  if (iVar1 < iVar2) {
    iVar1 = iVar2;
  }
  iVar2 = param_1[5];
  if (iVar2 < 0) {
    iVar2 = -iVar2;
  }
  if (iVar1 < iVar2) {
    iVar1 = iVar2;
  }
  return iVar1;
}

