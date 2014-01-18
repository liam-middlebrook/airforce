Box2D 2.3.0 compiled by:

mkdir -p ./build_debug
cd ./build_debug
cmake -DCMAKE_BUILD_TYPE=Debug -DLIB_SUFFIX=D -DCMAKE_INSTALL_PREFIX=$PWD/../../../install -DBOX2D_INSTALL=ON -DBOX2D_BUILD_SHARED=OFF ..
make -j 2 install/strip
cd ..

mkdir -p ./build_release
cd ./build_release
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$PWD/../../../install -DBOX2D_INSTALL=ON -DBOX2D_BUILD_SHARED=OFF ..
make -j 2 install/strip

find $PWD/../../../install/include -name *.h -exec dos2unix {} \;

log4cplus 1.1.0 compiled by:

mkdir -p ./build
cd ./build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$PWD/../../install \
-DBUILD_SHARED_LIBS=0 ..
make -j 2 install/strip

boost 1.55.0 compiled by:

./bjam --with-date_time --with-filesystem --with-program_options --with-system --with-thread --with-chrono --layout=versioned link=static
./bjam --with-date_time --with-filesystem --with-program_options --with-system --with-thread --with-chrono --layout=versioned link=static variant=debug

libpng 1.6.8 compiled by:

mkdir -p build
cd build
../configure --disable-shared --prefix=${PWD}/../../install
make install

lua 5.1.5 compiled by:

make CC=g++ CFLAGS="-D_REENTRANT -fPIC -DPIC -g -Wall -DLUA_USE_LINUX -DLUA_USE_APICHECK -Dlua_assert=assert" linux
make install INSTALL_TOP=$PWD/../install
mv ../install/lib/liblua.a ../install/lib/libluad.a

make clean

make CC=g++ CFLAGS="-D_REENTRANT -fPIC -DPIC -O2 -Wall -DLUA_USE_LINUX -DNDEBUG" linux
make install INSTALL_TOP=$PWD/../install

luabind 0.9.1 compiled by:

patch -p1 < luabind_boost.patch

export BOOST_ROOT=$PWD/../boost_1_55_0
export LUA_PATH=$PWD/../install
bjam --prefix=$PWD/../install -d+2 link=static variant=debug cxxflags="-DBOOST_ALL_NO_LIB -DLUABIND_CPLUSPLUS_LUA -D_REENTRANT -fPIC -DPIC -DLUA_USE_APICHECK -Dlua_assert=assert" install
bjam --prefix=$PWD/../install -d+2 link=static variant=release cxxflags="-DBOOST_ALL_NO_LIB -DLUABIND_CPLUSPLUS_LUA -D_REENTRANT -fPIC -DPIC" install
