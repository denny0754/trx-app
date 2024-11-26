# Add source to this project's executable.
add_executable (
	TRXAPP
	"EntryPoint.cpp"
 "core/Application.cpp")

set_target_properties(TRXAPP PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TRXAPP PROPERTY CXX_STANDARD 20)
endif()

find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

target_link_libraries(
	TRXAPP
	PRIVATE
	fmt::fmt
	spdlog::spdlog
	glfw
	imgui::imgui
)