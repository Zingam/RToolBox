#include <vulkan/vulkan.h>

////////////////////////////////////////////////////////////////////////////////
// Loader macros
////////////////////////////////////////////////////////////////////////////////

#if !defined(VK_EMPTY_SPACE)
#  define VK_EMPTY_SPACE
#endif
#if !defined(VK_ADD_EMPTY_SPACE)
#  define VK_ADD_EMPTY_SPACE VK_EMPTY_SPACE
#endif

#if !defined(VK_FUNCTION_POINTER)
/**
 * @brief Generates a vulkan function pointer.
 *
 */
#  define VK_FUNCTION_POINTER(functionName)                                    \
    PFN_##functionName functionName
#else
#  error VK_FUNCTION_POINTER is not defined!
#endif

////////////////////////////////////////////////////////////////////////////////
// Function pointers
////////////////////////////////////////////////////////////////////////////////

VK_FUNCTION_POINTER(vkGetInstanceProcAddr);

// Loader

// Vulkan 1.0
VK_FUNCTION_POINTER(vkCreateInstance);
VK_FUNCTION_POINTER(vkEnumerateInstanceExtensionProperties);
VK_FUNCTION_POINTER(vkEnumerateInstanceLayerProperties);

// Vulkan 1.1
VK_FUNCTION_POINTER(vkEnumerateInstanceVersion);

// Instance

// Vulkan 1.0
VK_FUNCTION_POINTER(vkCreateDevice);
VK_FUNCTION_POINTER(vkDestroyInstance);
VK_FUNCTION_POINTER(vkEnumerateDeviceExtensionProperties);
VK_FUNCTION_POINTER(vkEnumerateDeviceLayerProperties);
VK_FUNCTION_POINTER(vkEnumeratePhysicalDevices);
VK_FUNCTION_POINTER(vkGetDeviceProcAddr);
