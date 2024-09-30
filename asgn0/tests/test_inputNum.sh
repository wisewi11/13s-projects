# Creates the example output
echo "NOT ENOUGH INPUT" > bad_input.txt

# Runs the program
./calc 1 > joe.txt 

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
    echo "Bad error message, should output \"NOT ENOUGH INPUT\""
    rm bad_input.txt
    rm joe.txt
    exit 1
fi

# Prints a message on success
echo "Test found that program successfully handles not enough inputs"

# Cleans up files created
rm bad_input.txt
rm joe.txt

exit 0
