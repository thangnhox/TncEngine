#pragma once

#include <vector>

#include "../graphics/window.hpp"

namespace vulkanEngine { namespace devices {

    #define LOG_VALIDATION_LAYER 1

    struct SwapChainSupportDetail
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct QueueFamilyIndices
    {
        uint32_t graphicsFamily;
        uint32_t presentFamily;
        bool graphicsFamilyHasValue = false;
        bool presentFamilyHasValue = false;
        bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
    };

    class DevicesManager
    {

        private:
        VkInstance m_Instance;
        VkDebugUtilsMessengerEXT m_DebugMessenger;
        VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
        graphics::Window& m_Window;
        VkCommandPool m_CommandPool;

        VkDevice m_Device;
        VkSurfaceKHR m_Surface;
        VkQueue m_GraphicsQueue;
        VkQueue m_PresentQueue;

        const std::vector<const char*> m_ValidationLayers = {"VK_LAYER_KHRONOS_validation"};
        const std::vector<const char*> m_DevicesExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

        public:
        #ifdef NDEBUG
        static const bool s_EnableValidationLayers = false;
        #else
        static const bool s_EnableValidationLayers = true;
        #endif

        VkPhysicalDeviceProperties m_Properties;

        DevicesManager(graphics::Window& window);
        ~DevicesManager();

        // Prevent copy and moving
        DevicesManager(const DevicesManager&) = delete;
        void operator=(const DevicesManager&) = delete;
        DevicesManager(DevicesManager&&) = delete;
        DevicesManager &operator=(DevicesManager&&) = delete;

        VkCommandPool getCommandPool() { return m_CommandPool; }
        VkDevice getDevice() { return m_Device; }
        VkSurfaceKHR getSurface() { return m_Surface; }
        VkQueue getGraphicsQueue() { return m_GraphicsQueue; }
        VkQueue getPresentQueue() { return m_PresentQueue; }

        SwapChainSupportDetail getSwapChainSupport() { return querySwapChainSupport(m_PhysicalDevice, m_Surface); }
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        QueueFamilyIndices findPhysicalQueueFamilies() { return findQueueFamily(m_PhysicalDevice, m_Surface); }
        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

        // buffering
        void createBuffer(
            VkDeviceSize size,
            VkBufferUsageFlags usage,
            VkMemoryPropertyFlags properties,
            VkBuffer& buffer,
            VkDeviceMemory& bufferMemory
        );
        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);
        void copyBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize size);
        void copyBufferToImage(
            VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount
        );
        void createImageWithInfo(const VkImageCreateInfo& imageInfo, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

        // For checking
        static bool isDeviceSuitable(VkPhysicalDevice device, const std::vector<const char*>& deviceExtensions, VkSurfaceKHR surface);
        static std::vector<const char*> getRequiredExtensions();
        static int64_t checkValidationLayerSupport(const std::vector<const char*>& validationLayers);
        static QueueFamilyIndices findQueueFamily(VkPhysicalDevice device, VkSurfaceKHR surface);
        static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
        static void hasGflWRequiredInstanceExtensions();
        static bool checkDeviceExtensionSupport(VkPhysicalDevice device, const std::vector<const char*>& deviceExtensions);
        static SwapChainSupportDetail querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

        private:
        void createInstance();
        void setupDebugMessenger();
        void createSurface();
        void pickPhysicalDevice();
        void createLogicalDevice();
        void createCommandPool();

    };

}}