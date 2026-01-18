#!/bin/bash

set -e

echo "Installing Powder Trickler dependencies..."

# Detect package manager
if command -v apt &> /dev/null; then
    PKG_MANAGER="apt"
elif command -v dnf &> /dev/null; then
    PKG_MANAGER="dnf"
elif command -v pacman &> /dev/null; then
    PKG_MANAGER="pacman"
else
    echo "Error: Unsupported package manager. Please install dependencies manually."
    exit 1
fi

echo "Detected package manager: $PKG_MANAGER"

case $PKG_MANAGER in
    apt)
        sudo apt update
        sudo apt install -y \
            build-essential \
            cmake \
            git \
            qt6-base-dev \
            qt6-declarative-dev \
            qt6-serialport-dev \
            libqt6serialport6-dev \
            qml6-module-qtquick \
            qml6-module-qtquick-controls \
            qml6-module-qtquick-layouts \
            qml6-module-qtquick-window \
            qml6-module-qtquick-templates \
            qml6-module-qtqml-workerscript \
            libgtest-dev \
            libgmock-dev
        ;;
    dnf)
        sudo dnf install -y \
            gcc-c++ \
            cmake \
            git \
            qt6-qtbase-devel \
            qt6-qtdeclarative-devel \
            qt6-qtserialport-devel \
            gtest-devel \
            gmock-devel
        ;;
    pacman)
        sudo pacman -Syu --noconfirm \
            base-devel \
            cmake \
            git \
            qt6-base \
            qt6-declarative \
            qt6-serialport \
            gtest
        ;;
esac

echo ""
echo "Dependencies installed successfully!"
echo ""
echo "To build the project:"
echo "  mkdir build && cd build"
echo "  cmake .."
echo "  make"
echo ""
echo "To run tests:"
echo "  cd build"
echo "  ctest --output-on-failure"
