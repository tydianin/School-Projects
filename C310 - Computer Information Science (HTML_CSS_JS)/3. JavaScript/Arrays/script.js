function divideArray(numbers) {
	evenNums = [];
	oddNums = [];
	i = 0;

	// Loop through the array
	for (i = 0; i < numbers.length; i++) {
		if (numbers[i] % 2 === 0)
			evenNums.push(numbers[i]);
		else
			oddNums.push(numbers[i]);
	}

	// Return the two arrays
	evenNums.sort(function (a, b) { return a - b });
	oddNums.sort(function (a, b) { return a - b });

	// Print even numbers to the console
	console.log("Even numbers:");
	if (evenNums.length == 0)
		console.log("None");
	else
		console.log(evenNums.join('\n'));

	// Print odd numbers to the console
	console.log("Odd numbers:");
	if (oddNums.length == 0)
		console.log("None");
	else
		console.log(oddNums.join('\n'));
}