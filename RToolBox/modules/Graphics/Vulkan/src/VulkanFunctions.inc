#pragma once

#if __INTELLISENSE__
#  include <vulkan/vulkan.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// Macros
////////////////////////////////////////////////////////////////////////////////

#if !defined(VK_FUNCTION_POINTER)
/**
 * @brief Defines Vulkan function pointer.
 *
 */
#  define VK_FUNCTION_POINTER(functionName) PFN_vk##functionName functionName
#else
#  error 'VK_FUNCTION_POINTER' is not defined!
#endif

////////////////////////////////////////////////////////////////////////////////
// Function pointers
////////////////////////////////////////////////////////////////////////////////

VK_FUNCTION_POINTER(GetInstanceProcAddr);

// Loader

// Vulkan 1.0
VK_FUNCTION_POINTER(CreateInstance);
VK_FUNCTION_POINTER(EnumerateInstanceExtensionProperties);
VK_FUNCTION_POINTER(EnumerateInstanceLayerProperties);

// Vulkan 1.1
VK_FUNCTION_POINTER(EnumerateInstanceVersion);

// Instance

// Vulkan 1.0
VK_FUNCTION_POINTER(CreateDevice);
VK_FUNCTION_POINTER(DestroyInstance);
VK_FUNCTION_POINTER(EnumerateDeviceExtensionProperties);
VK_FUNCTION_POINTER(EnumerateDeviceLayerProperties);
VK_FUNCTION_POINTER(EnumeratePhysicalDevices);
VK_FUNCTION_POINTER(GetDeviceProcAddr);
