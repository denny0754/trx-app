/* Project Headers */
#include <trx/core/Middleware.hpp>

#include <trx/core/ui/Layer.hpp>
#include <trx/core/ui/LayerStack.hpp>

#include <trx/core/thread/ThreadPool.hpp>

#include <trx/core/runtime/RTResourceManager.hpp>
#include <trx/core/runtime/RTResource.hpp>

#include <trx/core/framework/Framework.hpp>
#include <trx/core/framework/FrontendFw.hpp>

#include <trx/core/event/Event.hpp>
#include <trx/core/event/EventData.hpp>
#include <trx/core/event/EventKey.hpp>

#include <trx/utils/logging/LogManager.hpp>
#include <trx/utils/logging/LogSettings.hpp>
#include <trx/utils/logging/Utility.hpp>

/* External Headers */
#include <GLFW/glfw3.h>

#include <imgui.h>

#include <spdlog/spdlog.h>
#include <spdlog/common.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

/* Standard Headers */
#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include <cstdint>