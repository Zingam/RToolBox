#pragma once

#if __INTELLISENSE__
#  include <vulkan/vulkan.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// Macros
////////////////////////////////////////////////////////////////////////////////

#if !defined(VK_FUNCTION_POINTER_KHR)
/**
 * @brief Defines Khronos extension Vulkan function pointer.
 *
 */
#  define VK_FUNCTION_POINTER_KHR(functionName)                                \
    PFN_vk##functionName##KHR functionName
#else
#  error 'VK_FUNCTION_POINTER_KHR' is not defined!
#endif

#if !defined(VK_FUNCTION_POINTER_EXT)
/**
 * @brief Defines multivendor extension Vulkan function pointer.
 *
 */
#  define VK_FUNCTION_POINTER_EXT(functionName)                                \
    PFN_vk##functionName##EXT functionName
#else
#  error 'VK_FUNCTION_POINTER_EXT' is not defined!
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
// Extensions
////////////////////////////////////////////////////////////////////////////////

// Extension: VK_EXT_debug_utils

// Types
VK_TYPE_EXT(DebugUtilsMessageSeverityFlagBits);
VK_TYPE_EXT(DebugUtilsMessageTypeFlags);
VK_TYPE_EXT(DebugUtilsMessenger);
VK_TYPE_EXT(DebugUtilsMessengerCallbackData);
VK_TYPE_EXT(DebugUtilsMessengerCreateInfo);
// Commands
VK_FUNCTION_POINTER_EXT(CreateDebugUtilsMessenger);
VK_FUNCTION_POINTER_EXT(DestroyDebugUtilsMessenger);

////////////////////////////////////////////////////////////////////////////////

// Extension: VK_KHR_surface

// Types
VK_TYPE_KHR(Surface);
// Commands
VK_FUNCTION_POINTER_KHR(DestroySurface);

////////////////////////////////////////////////////////////////////////////////

// Extenstion: VK_KHR_win32_surface

#if defined(VK_USE_PLATFORM_WIN32_KHR)
// Types
VK_TYPE_KHR(Win32SurfaceCreateInfo);
VK_TYPE_KHR(Win32SurfaceCreateFlags);
// Commands
VK_FUNCTION_POINTER_KHR(CreateWin32Surface);
VK_FUNCTION_POINTER_KHR(GetPhysicalDeviceWin32PresentationSupport);
#endif
