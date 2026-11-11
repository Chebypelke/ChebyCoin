#!/bin/bash

VERSION="1.2.0"
BUILD_MODE=""
TYPE=""
DOCS=""
LOG_LEVEL=""

print_help()
{
    echo "Usage: "
    echo ""
    echo "./build.sh [options]"
    echo ""

    echo "Arguments: "
    echo ""
    echo "    --help               - show this help page"
    echo "    --version            - show build script version"
    echo ""
    echo "    --build-mode         - choose compiler build mode"
    echo "        Release"
    echo "        Debug"
    echo "    --type               - choose program mode (tester or main app)"
    echo "        main-app"
    echo ""
    echo "        Testers: "
    echo "            chebychain-tester"
    echo "            chebyhash32-tester"
    echo "            chebyhash64-tester"
    echo "            chebyhash128-tester"
    echo "            chebysignature-tester"
    echo "            chebywallet-tester"
    echo "        Libs: "
    echo "            chebyhash-lib"
    echo "            chebysignature-lib"
    echo "    --docs(optional)     - choose documentation to generate"
    echo "        full"
    echo "        chebyhash"
    echo "    --log-type(optional) - choose log level"
    echo "        full"
    echo "        errors"
    echo "        silent"
    echo ""
}

print_version()
{
    echo "ChebyCoin build script $VERSION"
    echo ""
}

while [[ $# -gt 0 ]]; do 
    case "$1" in
        --help)
            print_help
            
            exit 0
            ;;
        --version)
            print_version
            
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
                main-app|\
                chebychain-tester|chebyhash32-tester|chebyhash64-tester|chebyhash128-tester|chebysignature-tester|chebywallet-tester|\
                chebyhash-lib|chebysignature-lib)
                    TYPE="$2"
                    ;;
                
                *)
                
                    echo "Unknown '--type' value: $2"
                    echo "Try 'main-app' or check binary list in '--help'"
                    echo ""

                    exit 1
                    ;;
            esac
            shift 2
            ;;

        --docs)
            if [[ $# -lt 2 ]]; then
                echo "Missing '--docs' value"
                exit 1
            fi

            case "$2" in
                full|chebyhash)
                    DOCS="$2"
                    ;;
                
                *)
                
                    echo "Unknown '--docs' value: $2"
                    echo "Try 'full' or check docs list in '--help'"
                    echo "Skipping..."
                    echo ""
                    ;;
            esac
            shift 2
            ;;
        --log-level)
            if [[ $# -lt 2 ]]; then
                echo "Missing '--log-level' value"
                exit 1
            fi

            case "$2" in
                full|errors|silent)
                    LOG_LEVEL="$2"
                    ;;
                
                *)
                
                    echo "Unknown '--log-level' value: $2"
                    echo "Try 'full' or check docs list in '--help'"
                    echo "Skipping..."
                    echo ""
                    ;;
            esac
            shift 2
            ;;
        *)
            echo "Unknown argument: $1"
            echo "Run './build.sh --help' for show help page"
            echo ""
            exit 1
            ;;
        
    esac
done

build_loglevel-full()
{
    echo "Log level: full."
    echo "$BUILD_MODE, $TYPE, let's compile it!"

    echo "CMake configuring..."
    cmake -S . -B build -DCMAKE_BUILD_TYPE="$BUILD_MODE"
    STATUS=$?

    if [[ $STATUS -eq 0 ]]; then
        echo "CMake configure successful!"
    else
        echo "CMake configure failed!"
        exit "$STATUS"
    fi

    echo "Building..."
    cmake --build build --target "$TYPE" -j 
    STATUS=$?

    if [[ $STATUS -eq 0 ]]; then
        echo "Build successful!"
    else
        echo "Build failed!"
        exit "$STATUS"
    fi

    if [[ -z "$DOCS" ]]; then
        echo "Missing '--docs', skipping..."
    else 
        echo "Docs: $DOCS"
        doxygen "docs/doxygen/$DOCS-doxyfile" 
        STATUS=$?

        if [[ $STATUS -eq 0 ]]; then
            echo "Doxygen successful!"
        else
            echo "Doxygen failed!"
            exit "$STATUS"
        fi
    fi
}

build_loglevel-errors()
{
    echo "Log level: errors."
    echo "$BUILD_MODE, $TYPE, let's compile it!"

    echo "CMake configuring..."
    cmake -S . -B build -DCMAKE_BUILD_TYPE="$BUILD_MODE" > /dev/null 
    STATUS=$?

    if [[ $STATUS -eq 0 ]]; then
        echo "CMake configure successful!"
    else
        echo "CMake configure failed!"
        exit "$STATUS"
    fi

    echo "Building..."

    cmake --build build --target "$TYPE" -j > /dev/null
    STATUS=$?

    if [[ $STATUS -eq 0 ]]; then
        echo "Build successful!"
    else
        echo "Build failed!"
        exit "$STATUS"
    fi

    if [[ -z "$DOCS" ]]; then
        echo "Missing '--docs', skipping..."
    else 
        echo "Docs: $DOCS"
        doxygen "docs/doxygen/$DOCS-doxyfile" 1> /dev/null
        STATUS=$?

        if [[ $STATUS -eq 0 ]]; then
            echo "Doxygen successful!"
        else
            echo "Doxygen failed!"
            exit "$STATUS"
        fi
    fi
}

build_loglevel-silent()
{
    echo "Log level: sillent."
    echo "$BUILD_MODE, $TYPE, let's compile it!"

    echo "CMake configuring..."
    cmake -S . -B build -DCMAKE_BUILD_TYPE="$BUILD_MODE" > /dev/null 2>&1
    STATUS=$?

    if [[ $STATUS -eq 0 ]]; then
        echo "CMake configure successful!"
    else
        echo "CMake configure failed!"
        echo "Try '--log-level errors' for see error"
        exit "$STATUS"
    fi

    echo "Building..."

    cmake --build build --target "$TYPE" -j > /dev/null 2>&1
    STATUS=$?

    if [[ $STATUS -eq 0 ]]; then
        echo "Build successful!"
    else
        echo "Build failed!"
        echo "Try '--log-level errors' for see error"
        exit "$STATUS"
    fi

    if [[ -z "$DOCS" ]]; then
        echo "Missing '--docs', skipping..."
    else 
        echo "Docs: $DOCS"
        doxygen "docs/doxygen/$DOCS-doxyfile" > /dev/null 2>&1
        STATUS=$?

        if [[ $STATUS -eq 0 ]]; then
            echo "Doxygen successful!"
        else
            echo "Doxygen failed!"
            echo "Try '--log-level errors' for see error"
            exit "$STATUS"
        fi
    fi
}

if [[ -z "$BUILD_MODE" ]]; then
    echo "Missing '--build-mode'"
    exit 1
fi

if [[ -z "$TYPE" ]]; then
    echo "Missing '--type'"
    exit 1
fi


if [[ -z "$LOG_LEVEL" ]]; then
    echo "Missing '--log-level', skipping..."
    build_loglevel-full
else 
    case "$LOG_LEVEL" in
        full)
            build_loglevel-full
            ;;
        errors)
            build_loglevel-errors
            ;;
        silent)
            build_loglevel-silent
            ;;
        *)
            echo "Unknown --log-level: $LOG_LEVEL"
            ;;
    esac
fi

echo "Done!"