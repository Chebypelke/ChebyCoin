#!/bin/bash

BUILD_MODE=""
TYPE=""

print_help()
{
    echo "ChebyCoin build script v1"
    echo ""

    echo "Usage: "
    echo ""
    echo "./build.sh [options]"
    echo ""

    echo "Arguments: "
    echo ""
    echo "    --help        - show this help page"
    echo ""
    echo "    --build-mode  - choose compiler build mode"
    echo "        Release"
    echo "        Debug"
    echo "    --type        - choose program mode (tester or main app)"
    echo "        main-app"
    echo ""
    echo "        Testers: "
    echo "            chebychain-tester"
    echo "            chebyhash32-tester"
    echo "            chebyhash64-tester"
    echo "            chebyhash128-tester"
    echo "            chebysignature-tester"
    echo "            chebywallet-tester"
    echo ""
}

while [[ $# -gt 0 ]]; do 
    case "$1" in
        --help)
            print_help
            
            exit 0
            ;;

        --build-mode)
            if [[ $# -lt 2 ]]; then
                echo "Missing '--build-mode' value"

                exit 1
            fi

            case "$2" in
                Release|Debug)
                    BUILD_MODE="$2"
                    ;;
                
                *)

                    echo "Unknown '--build-mode' value: $2"
                    echo "Try 'Release' or 'Debug'"
                    echo ""

                    exit 1
                    ;;
            esac
            
            shift 2

            ;;
        
        --type)
            if [[ $# -lt 2 ]]; then
                echo "Missing '--type' value"

                exit 1
            fi

            case "$2" in
                main-app|chebychain-tester|chebyhash32-tester|chebyhash64-tester|chebyhash128-tester|chebysignature-tester|chebywallet-tester)
                    TYPE="$2"
                    ;;
                
                *)
                
                    echo "Unknown '--type' value: $2"
                    echo "Try 'main-app' or check testers list in '--help'"
                    echo ""

                    exit 1
                    ;;
            esac
            shift 2
            ;;

        *)
            echo "Unknown argument: $1"
            echo ""
            echo "Run './build.sh --help' for show help page"
            echo ""

            exit 1
            ;;
        
    esac
done

if [[ -z "$BUILD_MODE" ]]; then
    echo "Missing '--build-mode'"
    exit 1
fi

if [[ -z "$TYPE" ]]; then
    echo "Missing '--type'"
    exit 1
fi

echo "$BUILD_MODE, $TYPE, let's compile it!"

echo "CMake log: "
echo ""

cmake -S . -B build -DCMAKE_BUILD_TYPE="$BUILD_MODE"
STATUS=$?

if [[ $STATUS -eq 0 ]]; then
    echo "CMake configure successful!"
else
    echo "CMake configure failed!"
    exit "$STATUS"
fi

cmake --build build --target "$TYPE" -j
STATUS=$?

if [[ $STATUS -eq 0 ]]; then
    echo "Build successful!"
else
    echo "Build failed!"
    exit "$STATUS"
fi

echo "Done!"