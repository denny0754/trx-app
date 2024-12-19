# Add source to this project's executable.
add_executable (
	TRXAPP
	"EntryPoint.cpp"
 	"Application.cpp"
	"Core.cpp"

	# Event System Source Files
	"ev/MiddlewareFw.cpp"

	# User Interface(UI) Source Files
	"ui/FrontendFw.cpp"
	"ui/LayerStack.cpp"
	"ui/MenuOverlay.cpp"
	"ui/SessionSelectorLayer.cpp"
	"ui/AppSettingsLayer.cpp"
	"ui/AboutLayer.cpp"
	
	# Utilities and Logging Tools
	"util/logging/LogManager.cpp"
	"util/config/ConfigEntry.cpp"
	"util/config/ConfigSection.cpp"
	"util/config/Config.cpp"
	"util/config/ConfigIO.cpp"
	
	# Resource Management System Source Files
	"rsrc/RTResourceManagerFw.cpp"
	"rsrc/RTAppConfig.cpp"

	# Network Related Source Files
	"net/SessionFw.cpp"
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
find_package(boost_beast CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(wt CONFIG REQUIRED)

target_link_libraries(
	TRXAPP
	PRIVATE
	fmt::fmt
	spdlog::spdlog
	glfw
	opengl32
	imgui::imgui
	Boost::regex
	Boost::beast
	nlohmann_json::nlohmann_json
	Wt::Wt
	Wt::Dbo
	Wt::HTTP
	Wt::DboSqlite3
)