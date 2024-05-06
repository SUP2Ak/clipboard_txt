# CMakeList.txt : projet CMake pour clipboard_txt, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("clipboard_txt")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (clipboard_txt "clipboard_txt.cpp" "clipboard_txt.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET clipboard_txt PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
