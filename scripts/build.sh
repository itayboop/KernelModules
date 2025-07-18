function build_kernel() {
    echo "Building kernel module..."
    make -C kernel
    if [ $? -ne 0 ]; then
        echo "Kernel module build failed."
        return 1
    fi
    echo "Kernel module built successfully."
}

function clean_kernel() {
    echo "Cleaning kernel module..."
    make -C kernel clean
    if [ $? -ne 0 ]; then
        echo "Kernel module clean failed."
        return 1
    fi
    echo "Kernel module cleaned successfully."
}

