project(VISP_MATLAB)

cmake_minimum_required(VERSION 2.6)

find_package(VISP REQUIRED visp_core)
include_directories(${VISP_INCLUDE_DIRS})

set(MATLAB_LIBS C:/Program\ Files/MATLAB/R2017b/extern/lib/win64/microsoft/libeng.lib C:/Program\ Files/MATLAB/R2017b/extern/lib/win64/microsoft/libmx.lib)
set(MATLAB_INCLUDES C:/Program\ Files/MATLAB/R2017b/extern/include)
set(MATLAB_LIB_PATHS C:/Program\ Files/MATLAB/R2017b/extern/lib/win64/microsoft)
#set(MATLAB_DEFS -DMATLAB_MEX_FILE -D_GNU_SOURCE -DGLNXA64 -DGCC -DMX_COMPAT_32 -DNDEBUG)
include_directories(${MATLAB_INCLUDES})
link_directories(${MATLAB_LIB_PATHS})
#add_definitions(${MATLAB_DEFS})

add_executable(main main.cpp)
target_link_libraries(main ${VISP_LIBRARIES} ${MATLAB_LIBS})