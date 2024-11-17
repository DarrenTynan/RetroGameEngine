#!/bin/bash

pushd ..
Vendor/Binaries/Premake/xcode4/premake5 --cc=clang --file=Build.lua gmake2
popd
