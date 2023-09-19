#pragma once

#if __INTELLISENSE__
#  include <vulkan/vulkan.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// Macros
////////////////////////////////////////////////////////////////////////////////

#if !defined(VK_TYPE)
/**
 * @brief Defines Vulkan type.
 *
 */
#  define VK_TYPE(typeName) using typeName = Vk##typeName
#else
#  error 'VK_TYPE' is already defined!
#endif

#if !defined(VK_TYPE_EXT)
/**
 * @brief Defines multivendor extension Vulkan type.
 *
 */
#  define VK_TYPE_EXT(typeName) using typeName = Vk##typeName##EXT
#else
#  error 'VK_TYPE_EXT' is already defined!
#endif

#if !defined(VK_TYPE_KHR)
/**
 * @brief Defines Khronos extension Vulkan type.
 *
 */
#  define VK_TYPE_KHR(typeName) using typeName = Vk##typeName##KHR
#else
#  error 'VK_TYPE_KHR' is already defined!
#endif

////////////////////////////////////////////////////////////////////////////////
// Types
////////////////////////////////////////////////////////////////////////////////

// Vulkan Core

VK_TYPE(AllocationCallbacks);
VK_TYPE(ApplicationInfo);
VK_TYPE(Bool32);
VK_TYPE(ExtensionProperties);
VK_TYPE(Instance);
VK_TYPE(InstanceCreateInfo);
VK_TYPE(LayerProperties);
VK_TYPE(Result);

// VK_EXT_debug_utils

VK_TYPE_EXT(DebugUtilsMessageSeverityFlagBits);
VK_TYPE_EXT(DebugUtilsMessageTypeFlags);
VK_TYPE_EXT(DebugUtilsMessengerCallbackData);

// VK_KHR_win32_surface

#if defined (VK_USE_PLATFORM_WIN32_KHR)
VK_TYPE_KHR(Win32SurfaceCreateInfo);
#endif
