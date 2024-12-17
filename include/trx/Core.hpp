/* Project Headers */
#include <trx/ev/MiddlewareFw.hpp>

#include <trx/ui/Layer.hpp>
#include <trx/ui/LayerStack.hpp>

#include <trx/sys/ThreadPool.hpp>

#include <trx/rsrc/RTResourceManagerFw.hpp>
#include <trx/rsrc/RTResource.hpp>

#include <trx/intf/Framework.hpp>
#include <trx/ui/FrontendFw.hpp>

#include <trx/ev/Event.hpp>
#include <trx/ev/EventData.hpp>
#include <trx/ev/EventKey.hpp>

#include <trx/util/logging/LogManager.hpp>
#include <trx/util/logging/LogSettings.hpp>
#include <trx/util/logging/Utility.hpp>

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