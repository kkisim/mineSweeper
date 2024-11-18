// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//모듈파일 헤더 파일입니다.
#include "Ms_Interface.h"
#include "Ms_Level.h"
#include "Ms_Logic.h"
#include <cstdlib> // 랜덤 함수 사용(rand, srand)
#include <ctime>   // 시간 함수 사용(time)
#include <queue>   // BFS를 위한 큐 사용
