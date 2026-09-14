/* Analysis pseudo-C, not buildable source. */

undefined1 * FUN_8005f57c(uint param_1)

{
  uint uVar1;
  
  uVar1 = param_1 & 0xffff0000;
  if (uVar1 == 0x1100000) {
    param_1 = param_1 & 0xffff;
    if (param_1 == 0x15) {
      return &LAB_80065f14;
    }
    if (param_1 < 0x16) {
      if (param_1 == 0xd) {
        return &LAB_80065cd8;
      }
    }
    else {
      if (param_1 == 0x20d) {
        return &LAB_800661a0;
      }
      if (param_1 == 0x215) {
        return &LAB_800663f8;
      }
    }
  }
  else if (uVar1 < 0x1100001) {
    if (uVar1 == 0x1000000) {
      param_1 = param_1 & 0xffff;
      if (param_1 == 0x15) {
        return &LAB_800654e0;
      }
      if (param_1 < 0x16) {
        if (param_1 == 0) {
          return &LAB_80065164;
        }
        if (param_1 == 0xd) {
          return &LAB_80065298;
        }
      }
      else {
        if (param_1 == 0x20d) {
          return &LAB_8006579c;
        }
        if (param_1 == 0x215) {
          return &LAB_80065a00;
        }
      }
    }
  }
  else if (uVar1 == 0x1200000) {
    param_1 = param_1 & 0xffff;
    if (param_1 == 0x15) {
      return &LAB_80066944;
    }
    if (param_1 < 0x16) {
      if (param_1 == 0xd) {
        return &LAB_800666a0;
      }
    }
    else {
      if (param_1 == 0x20d) {
        return &LAB_80066c5c;
      }
      if (param_1 == 0x215) {
        return &LAB_80066f1c;
      }
    }
  }
  else if (uVar1 == 0x1300000) {
    param_1 = param_1 & 0xffff;
    if (param_1 == 0x15) {
      return &LAB_800674e8;
    }
    if (param_1 < 0x16) {
      if (param_1 == 0xd) {
        return &LAB_80067250;
      }
    }
    else {
      if (param_1 == 0x20d) {
        return &LAB_800677d0;
      }
      if (param_1 == 0x215) {
        return &LAB_80067a84;
      }
    }
  }
  FUN_8008fa78(s_unsupported_SHARED_primitive_0x__800117d4);
  return &LAB_80089da8;
}

