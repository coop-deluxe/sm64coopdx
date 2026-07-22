Vendored for the Vulkan backend (`ENABLE_VULKAN`).

- `volk.h`/`volk.c`: dynamic Vulkan function loader, source at https://github.com/zeux/volk
  (tag `vulkan-sdk-1.4.335.0`). Avoids a hard link-time dependency on
  `vulkan-1.dll`/`libvulkan.so` — the backend can probe for Vulkan support and fall back to
  OpenGL if it's missing.
- `include/vulkan/`, `include/vk_video/`: official Khronos C headers (`vulkan_core.h` and
  friends) from https://github.com/KhronosGroup/Vulkan-Headers (same tag). Only the plain C
  headers are vendored, not the C++ (`.hpp`) wrappers, since this backend is written in C.

Both are Apache-2.0 licensed; see `LICENSE.md` and `include/VULKAN-HEADERS-LICENSE.md`.
