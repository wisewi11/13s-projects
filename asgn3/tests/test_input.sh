# Create a file with a test input
echo > /tmp/lrc_input

# Run the xxd  with the test input and redirect the output and errors to a separate file
xxd </tmp/lrc_input > /tmp/ref_out 2> /tmp/ref_err
ref_returncode=$?

# Run your binary with the test input and redirect the output and errors to a separate file
./xd </tmp/lrc_input > /tmp/my_out 2> /tmp/my_err
my_returncode=$?



# Compare what was printed to stdout
diff /tmp/ref_out /tmp/my_out
if [ $? -ne 0 ]; then
    echo "standard out doesn't match!"
    exit 1
fi

# Compare what was printed to stderr
diff /tmp/ref_err /tmp/my_err
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

