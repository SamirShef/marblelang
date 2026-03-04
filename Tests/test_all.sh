if ! command -v marblec &> /dev/null; then
    echo "Error: marblec not found in PATH"
    exit 1
fi

TARGET_DIR="${1:-.}"

if [ ! -d "$TARGET_DIR" ]; then
    echo "Error: Directory '$TARGET_DIR' does not exist"
    exit 1
fi

echo "Processing .mr files in directory: $TARGET_DIR"

total=0
success=0
failed=0

shopt -s nullglob
for file in "$TARGET_DIR"/*.mr; do
    ((total++))
    filename="${file%.mr}"
    
    echo -e "\e[1;37mCompilation ${file%.mr}\e[0m"

    if marblec "$file"; then
        echo -e "\e[1;33mTEST $file\e[0m"

        if [ -f "./$filename" ]; then
            "./$filename"
            status=$?
            
            if [ $status -eq 0 ]; then
                echo -e "\e[1;32mWAS SUCCESSFUL\e[0m"
                ((success++))
            else
                echo "Program exited with code $status"
                ((failed++))
            fi
            
            rm "./$filename"
            echo -e "\e[1;33mRemoved $filename\e[0m"
        else
            echo -e "\e[1;31mError: executable file $filename not found\e[0m"
            ((failed++))
        fi
    else
        echo -e "\e[1;31mCompilation error for $file\e[0m"
        ((failed++))
    fi
    
    echo ""
done

echo -e "=================================="
echo -e "\e[1;37mStatistics:"
echo -e "Total files: $total\e[0m"
echo -e "\e[1;32mSuccessful: $success\e[0m"
echo -e "\e[1;31mFailed: $failed\e[0m"
echo -e "=================================="

if [ $failed -eq 0 ]; then
    echo -e "\e[1;32mAll tests passed successfully!\e[0m"
    exit 0
else
    echo -e "\e[1;31mErrors detected\e[0m"
    exit 1
fi
