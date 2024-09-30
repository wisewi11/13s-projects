# Run your binary with the test input and redirect the output and errors to a separate file
./calc < ./binary_error_input.txt > /tmp/my_out 2> /tmp/my_err
my_returncode=$?

# Compare what was printed to stdout
diff ./binary_error_result.txt /tmp/my_out
if [ $? -ne 0 ]; then
    echo "standard out doesn't match!"
    exit 1
fi

# Compare what was printed to stderr
diff ./binary_error_error.txt /tmp/my_err
if [ $?  -ne 0 ]; then
    echo "standard err doesn't match!"
    exit 1
fi

# Compare the return codes.
if [ 0 -ne $my_returncode ] ; then 
    echo "Return codes don't match!"
    exit 1
fi

# Everything matches as expected!
echo "Working Correctly"
exit 0

