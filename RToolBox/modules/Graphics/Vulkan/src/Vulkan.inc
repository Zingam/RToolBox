#include <vulkan/vulkan.h>

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

#if 0
extern PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
#endif
VK_FUNCTION_POINTER(vkGetInstanceProcAddr);

// Loader

// Vulkan 1.0
#if 0
extern PFN_vkCreateInstance vkCreateInstance;
extern PFN_vkEnumerateInstanceExtensionProperties
  vkEnumerateInstanceExtensionProperties;
extern PFN_vkEnumerateInstanceLayerProperties
  vkEnumerateInstanceLayerProperties;
#endif
VK_FUNCTION_POINTER(vkCreateInstance);
VK_FUNCTION_POINTER(vkEnumerateInstanceExtensionProperties);
VK_FUNCTION_POINTER(vkEnumerateInstanceLayerProperties);

// Vulkan 1.1
#if 0
extern PFN_vkEnumerateInstanceVersion vkEnumerateInstanceVersion;
#endif
VK_FUNCTION_POINTER(vkEnumerateInstanceVersion);

// Instance

// Vulkan 1.0
VK_FUNCTION_POINTER(vkCreateDevice);
VK_FUNCTION_POINTER(vkDestroyInstance);
VK_FUNCTION_POINTER(vkEnumerateDeviceExtensionProperties);
VK_FUNCTION_POINTER(vkEnumerateDeviceLayerProperties);
VK_FUNCTION_POINTER(vkEnumeratePhysicalDevices);
VK_FUNCTION_POINTER(vkGetDeviceProcAddr);
