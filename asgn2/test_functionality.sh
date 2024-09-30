# Run your binary with the test input and redirect the output and errors to a separate file
./hangman "don't go in empty-handed" <./tester.txt> /tmp/my_out

# Compare what was printed to stdout
diff ./lose.txt /tmp/my_out
if [ $? -ne 0 ]; then
    echo "standard out doesn't match!"
    exit 1
fi
# Everything matches as expected!
echo "Working Correctly"
exit 0
