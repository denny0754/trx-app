# Add source to this project's executable.
add_executable (
	TRXAPP
	"EntryPoint.cpp"
 	"core/Application.cpp"
	"core/Middleware.cpp"

	"core/framework/FrontendFw.cpp"

	"core/ui/Layer.cpp"
	"core/ui/LayerStack.cpp"
	
	"core/runtime/RTResourceManager.cpp"

	"utils/logging/LogManager.cpp"

	"utils/config/ConfigEntry.cpp"
	"utils/config/ConfigSection.cpp"
	"utils/config/Config.cpp"
	"utils/config/ConfigIO.cpp"

	"app/ui/MenuOverlay.cpp"
	"app/ui/SessionSelectorLayer.cpp"
	"app/ui/AppSettingsLayer.cpp"
	"app/ui/AboutLayer.cpp"

	"app/runtime/RTAppConfig.cpp"

	"core/Core.cpp"
)

set_target_properties(TRXAPP PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TRXAPP PROPERTY CXX_STANDARD 20)
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
   	add_compile_definitions(TRX_DEVELOPER_BUILD)
endif()

find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(boost_regex CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(
	TRXAPP
	PRIVATE
	fmt::fmt
	spdlog::spdlog
	glfw
	opengl32
	imgui::imgui
	Boost::regex
	nlohmann_json::nlohmann_json
)