# RToolBox

A game programming exercise with **Vulkan**...

## Prerequisites

### Software

- ***C++23 compiler*** (or newer)
- ***CMake 3.27*** (or newer)
- ***vcpkg***

### Third Party Libraries

- ***vcpkg***
  - Set environment variable `VCPKG_ROOT`
- ***Vulkan SDK**
  - Install from **LunarG** web site:
  
    https://vulkan.lunarg.com/sdk/home

  - Set environment variable `VULKAN_ROOT`

## Notes

### Markdown (`*.md`)

Documentation uses the **Markdown** format
Recommended editor: ***Visual Studio Code***'s extension ***Markdown Preview Enhanced***

### UML (`*.puml`)

UML diagrams use **Mermaid** syntax
Recomended editor: ***Visual Studio Code***'s extension: ***Markdown Preview Mermaid Support***

### Code Formatting

Use ***ClangFormat*** to apply the format definitions from: `.clang-format`.
Use `// clang-format off` and `// clang-format` on if necessary to prevent ***ClangFormat*** from changing the desired code formatting.
