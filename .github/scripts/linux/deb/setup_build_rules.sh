#!/bin/bash

echo "Append version and build number to build rules"

ls /home/runner/work/ksnip/Qt/5.15.2/gcc_64/lib -al

# sed -i "s;dh_auto_configure --;dh_auto_configure -- -DVERSION_SUFIX=${VERSION_SUFFIX} -DBUILD_NUMBER=${BUILD_NUMBER} -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_PREFIX_PATH=${Qt5_DIR} -DCMAKE_BUILD_TYPE=${BUILD_TYPE};" ksnip-${VERSION_NUMBER}/debian/rules # ; is the delimiter