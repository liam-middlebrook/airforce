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
