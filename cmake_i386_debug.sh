DIR_NAME=`basename ${PWD}`
mkdir -p ../${DIR_NAME}-i386-debug
cd ../${DIR_NAME}-i386-debug
cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE="Debug" ../${DIR_NAME}
