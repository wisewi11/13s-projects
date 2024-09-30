# Creates the example output
echo "BAD INPUT" > bad_input.txt

# Runs the program
./calc a 1 > joe.txt 

# Ensures exit code is not Zero
if [ $? -eq 0 ]; then
    echo "invalid exit code" $?
    rm bad_input.txt
    rm joe.txt
    exit 1
fi

# Ensures differences *are* not found
diff bad_input.txt joe.txt
if [ $? -eq 0 ]; then
    echo "Bad error message, should output \"BAD INPUT\" for non integers"
    rm bad_input.txt
    rm joe.txt
    exit 1
fi

# Prints a message on success
echo "Test found that program successful handles non integer inputs"

# Cleans up files created
rm bad_input.txt
rm joe.txt
exit 0
