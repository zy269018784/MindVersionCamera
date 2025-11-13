cmake -S . -B ../../../BEngine_build/MindVersionCamera_build -DCMAKE_BUILD_TYPE=Release  -DUSE_QT6=true  -DCMAKE_PREFIX_PATH="C:/Qt/6.7.3/msvc2022_64/lib/cmake"
cmake --open  ../../../BEngine_build/MindVersionCamera_build
C:/Qt/6.7.3/msvc2022_64/bin/windeployqt.exe --qmldir ../../../BEngine_build/MindVersionCamera_build   ../../../BEngine_build/MindVersionCamera_build/MindVersionCamera.exe



