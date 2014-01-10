DIR_NAME=`basename ${PWD}`
mkdir -p ../${DIR_NAME}-i386-release
cd ../${DIR_NAME}-i386-release
cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE="Release" ../${DIR_NAME}
