#!/bin/bash

curl --header "PRIVATE-TOKEN: $DOWNLOAD_TOKEN" "https://git.splentity.com/api/v4/projects/openblox%2Flibopenblox/jobs/artifacts/master/download?job=build" -o libopenblox.zip

unzip libopenblox.zip

sed "1cprefix=$(pwd)/artifacts" artifacts/lib/pkgconfig/libopenblox.pc > libopenblox.pc
