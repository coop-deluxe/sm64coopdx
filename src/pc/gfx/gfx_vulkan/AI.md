# A Note on the Creation Process

This Vulkan backend was developed with assistance from an AI coding
assistant (Claude, by Anthropic). This document describes the process
followed.

## Process

- The existing OpenGL (`gfx_opengl.c`) and Direct3D 11
  (`gfx_direct3d11.cpp`) backends were used as the functional reference —
  the Vulkan backend implements the same `GfxRenderingAPI` /
  `GfxWindowBackendAPI` contracts described in [`VULKAN.md`](VULKAN.md), not
  a new architecture.
- Design and sequencing decisions (initialization order, resource
  lifetimes, the render pipeline layout described in
  [`PIPELINE.md`](PIPELINE.md), and the init/teardown sequence described in
  [`INIT.md`](INIT.md)) were worked out iteratively, with the AI assistant
  used for drafting boilerplate code (Vulkan is particularly verbose) and
  for looking up the official API specification.
- The generated code was compiled and tested on real hardware (see the
  "Platforms tested" row in `VULKAN.md`) before being considered done.
  Issues found during testing were fixed through further iteration.
- The working log, intermediate planning documents, and research notes used
  to arrive at this implementation are kept in a separate repository, for
  anyone who wants to see the process in more detail:

  https://github.com/HyperNova-0ring/sm64coopdx_vulkan_specialAI
